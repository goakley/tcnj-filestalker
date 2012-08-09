#include "../headers/File.h"

File::File()
{
  id = (ino_t)(0);
  isDir = false;
  lastModified = (time_t)(0);
  char* tempName = {'\0'};
  name = tempName;
  tempName = NULL;
}

File::File(struct stat *statdat, const char* strName)
{
  id = statdat->st_ino;
  isDir = S_ISDIR(statdat->st_mode);
  lastModified = (statdat->st_mtime);
  char* tempName = new char[strlen(strName)+1];
  strcpy(tempName, strName);
  name = tempName;
  tempName = NULL;
}

File::~File()
{
  delete [] name;
}

ino_t File::getID() { return id; }
bool File::isDirectory() { return isDir; }
time_t File::getModified() { return lastModified; }
const char* File::getName() { return name; }

bool File::operator==(const File &f)
{
  return (id == f.id);
}

File& File::operator=(const File &f)
{
  id = f.id;
  isDir = f.isDir;
  lastModified = f.lastModified;
  return *this;
}
