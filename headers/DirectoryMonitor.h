#ifndef DIRECTORYMONITOR_H
#define DIRECTORYMONITOR_H

#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include "../headers/File.h"
#include "../headers/HashMap.h"
#include "../headers/List.h"
#include "../headers/activities.h"
#include "../headers/EventRemoved.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DirectoryMonitor
{
private:
  /* The path to the directory to be monitored by this object */
  char* rootDirectory;
  /* Logging to /var/log or not */
  bool varLog;
  /* The log stream, if varLog == true */
  ofstream logStream;
  /* Stores the data about files in the rootDirectory */
  HashMap<File> *map;
  /* A temporary map used for transition purposes while processing */
  HashMap<File> *limboMap;
  /* firstPass
   * Initializes a first pass check over the rootDirectory.
   * This will be called when this object is created.
   */
  void firstPass();
  /* processDirectory
   * Processes the specified directory, treating it as a 
   * first pass processing if specified to be so (true).
   * Processing a first pass involves finding all the files 
   * in the rootDirectory and storing them in the map.
   * Processing otherwise means checking for differences between 
   * files on the system and file data recorded by this program.
   */
  void processDirectory(char*, bool = false);
  /* removeRecursive
   * Helper function, recursively removes the files in 
   * the specified directory from the main map HashMap.
   */
  void removeRecursive(char*);
  /* isDirectory
   * Checks if the specified path is a directory.
   * See method for more information on return type.
   */
  bool isDirectory(char*);
  /* hasChanged
   * Checks to see if the file at the specified directory has changd or not, 
   * and stores the resultant file as the specified file object.
   * See method for more information on return type.
   * 
   */
  enum activity_t hasChanged(const char* path, File &);
  /* getContents
   * Obtains the contents of the specified directory and stores them 
   * in the specified List of strings.
   * See method for more information on return type.
   */
  bool getContents(char*, List<string> &);
public:
  /* Constructor
   * Initializes a DirectoryMonitor at the specified location.
   */
  DirectoryMonitor(char*, bool = false);
  /* Destructor
   */
  ~DirectoryMonitor();
  /* checkChanges
   * Checks for changes in the directory monitored by this object.
   */
  void checkChanges();
};

#endif
