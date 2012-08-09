#include "../headers/DirectoryMonitor.h"

using namespace std;

DirectoryMonitor::DirectoryMonitor(char* directory = "/home", bool varlog)
{
  rootDirectory = directory;
  varLog = varlog;
  if (varlog)
    logStream.open("/var/log/filestalker.log", ios_base::app);
  map = new HashMap<File>(512);
  limboMap = NULL;
  firstPass();
}
DirectoryMonitor::~DirectoryMonitor()
{
  delete map; map = NULL;
  delete limboMap; limboMap = NULL;
  //delete [] rootDirectory; rootDirectory = NULL;
}

void DirectoryMonitor::firstPass()
{
  struct stat rootStat;
  stat(rootDirectory, &rootStat);
  // add the root directory the the map
  map->add((unsigned long int)(rootStat.st_ino), 
	   File(&rootStat, rootDirectory));
  // process the root directory
  processDirectory(rootDirectory, true);
}

void DirectoryMonitor::checkChanges()
{
  struct stat rootStat;
  stat(rootDirectory, &rootStat);
  // check if the root directory changed, and thus
  // check if the subdirectories need to be checked
  //if (rootStat.st_mtime == (map->get(rootStat.st_ino)).getModified())
  //  return;
  // prepare the intermediary hash map
  limboMap = new HashMap<File>(512);
  // transfer the root directory to the intermediary map
  limboMap->add((unsigned long int)rootStat.st_ino, 
		map->remove((unsigned long int)rootStat.st_ino));
  // process the directory for changes
  processDirectory(rootDirectory);
  // check for leftover (deleted) files
  List<File> leftovers = map->iterator();
  File f;
  time_t t;
  // mark all leftover files as removed
  while (leftovers.getSize() > 0)
    {
      f = leftovers.remove();
      t = f.getModified();
      (varLog?logStream:cout) << "R " << t << " " << f.getID() << endl;
    }
  // transfer the new map to the old map
  delete map;
  map = limboMap;
  limboMap = NULL;
}

void DirectoryMonitor::processDirectory(char* path, bool firstPass)
{
  List<string> files;
  // attempt to get the contents of the specified directory
  if (getContents(path, files))
    { // successfully obtained the contents of the directory
      // find the longest file name
      unsigned int nameLength = 0, strLen;
      for (int n = 0; n < files.getSize(); n++)
	{
	  strLen = files.get(n).length();
	  if (nameLength < strLen)
	    nameLength = strLen;
	}
      // create a version of the path string that holds the trailing '/'
      char trailingPath[strlen(path)+2];
      strcpy(trailingPath, path);
      strcat(trailingPath, "/");
      // create a filePath string to hold the new file paths in the loop
      char filePath[strlen(path)+nameLength+2];
      struct stat fileStat;
      // loop through all the files
      for (int n = 0; n < files.getSize(); n++)
	{
	  // get the absolute path of the file
	  strcpy(filePath, trailingPath);
	  strcat(filePath, files.get(n).c_str());
	  stat(filePath, &fileStat);
	  // check if this is the inital pass of the program or not
	  if (firstPass)
	    {
	      // add this file to the map
	      map->add((unsigned long int)(fileStat.st_ino), 
		       File(&fileStat, files.get(n).c_str()));
	      if (isDirectory(filePath))
		{ // this file is a directory
		  // recurse through this file (directory)
		  processDirectory(filePath, true);
		}
	    }
	  else // this is a standard pass (not first pass) of the program
	    {
	      File f;
	      activity_t changed = hasChanged(filePath, f);
	      time_t t = f.getModified();
	      if (!isDirectory(filePath))
		{ // this is not a directory
		  // log the appropriate change
		  switch(changed)
		    {
		    case CREATED:
		      (varLog?logStream:cout) << "C " << t << " " 
					      << f.getID() << endl;
		      break;
		    case MODIFIED:
		      (varLog?logStream:cout) << "M " << t << " " 
					      << f.getID() << endl;
		      break;
		    case ERROR:
		      // lol i dunno sorry
		      break;
		    }
		}
	      else // this file is a directory
		{
		  // log the appropriate change, and
		  // recurse through this directory (if applicable)
		  switch(changed)
		    {
		    case CREATED:
		      (varLog?logStream:cout) << "C " << t << " " 
					      << f.getID() << endl;
		      processDirectory(filePath);
		      break;
		    case MODIFIED:
		      (varLog?logStream:cout) << "M " << t << " " 
					      << f.getID() << endl;
		      processDirectory(filePath);
		      break;
		    case NONE:
		      removeRecursive(filePath);
		      break;
		    case ERROR:
		      // lol i dunno!
		      break;
		    }
		}
	      // add the processed file to the intermediary map
	      limboMap->add(f.getID(), f);
	      (varLog?logStream:cout).flush();
	    }
	}
    }
}


void DirectoryMonitor::removeRecursive(char* path)
{
  List<string> files;
  unsigned int length = 0;
  if (getContents(path, files))
    {
      // find the longest file name
      unsigned int nameLength = 0, strLen;
      for (int n = 0; n < files.getSize(); n++)
	{
	  strLen = files.get(n).length();
	  if (nameLength < strLen)
	    nameLength = strLen;
	}
      // create a version of the path string that holds the training '/'
      char trailingPath[strlen(path)+2];
      strcpy(trailingPath, path);
      strcat(trailingPath, "/");
      // create a filePath string to hold the new file paths in the loop
      char filePath[strlen(path)+nameLength+2];
      struct stat fileStat;
      for (int n = 0; n < files.getSize(); n++)
	{
	  strcpy(filePath, trailingPath);
	  strcat(filePath, files.get(n).c_str());
	  stat(filePath, &fileStat);
	  if (isDirectory(filePath))
	    processDirectory(filePath);
	  map->remove((unsigned long int)(fileStat.st_ino));
	}
    }
}


/**
 * Outcomes:
 *    true  - This is a directory.
 *    false - This is not a directory.
 */
bool DirectoryMonitor::isDirectory(char* path)
{
  DIR *dstream = opendir(path);
  if (dstream == NULL)
    {
      return !(errno == ENOENT || errno == ENOTDIR);
    }
  closedir(dstream);
  return true;
}

/**
 * Outcomes:
 *     true  - The 'directory' was successfully opened and read
 *             files[] contains the name of each file,
 *             length counts the number of files, 
 *             errno is cleared
 *     false - The 'directory' could not successfully be opened or read, 
 *             files and length are zeroed/null, 
 *             errno is set to the specified error code
 */
bool DirectoryMonitor::getContents(char* path, List<string> &files)
{
  errno = 0;
  struct dirent *filedat;
  DIR *dstream = opendir(path);
  if (!dstream)
    {
      // error opening the directory!
      return false;
    }
  errno = 0;
  while ((filedat = readdir(dstream)) != NULL)
    {
      if ((filedat->d_name)[0] != '.' && 
	  (filedat->d_name)[strlen(filedat->d_name)-1] != '~')
	{
	  // MUST copy d_name
	  char* file_name = new char[strlen(filedat->d_name)+1];
	  strcpy(file_name, (filedat->d_name));
	  files.add(string(file_name));
	  delete [] file_name;
	}
    }
  if (errno != 0)
    return false;
  closedir(dstream);
  return true;
}


/**
 * If the file pointer argument points to anything, it will be deleted.
 * This function removes the checked file from the directory map 
 *     if it is present.
 * Resets errno.
 * Outcomes:
 *     NONE     - File has not been changed
 *     CREATED  - File has been created
 *     MODIFIED - File has been changed
 *     ERROR    - There was a problem reading the file's statistics, 
 *                    errno will contain the error code
 */
enum activity_t DirectoryMonitor::hasChanged(const char* path, File &file)
{
  errno = 0;
  struct stat statbuf;
  if (!stat(path, &statbuf) && errno)
    {
      return ERROR;
    }
  ino_t id = statbuf.st_ino;
  time_t time = statbuf.st_mtime;
  file = map->remove(id);
  if ((unsigned long int)(file.getID()) == 0)
    {
      file = File(&statbuf, path);
      return CREATED;
    }
  if (file.getModified()<time)
    {
      file = File(&statbuf, path);
      return MODIFIED;
    }
  return NONE;
}
