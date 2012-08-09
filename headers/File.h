#ifndef FILE_H
#define FILE_H

#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class File
{
private:
  // the serial id of the file
  ino_t id;
  // is this a directory
  bool isDir;
  // the last modified time
  time_t lastModified;
  // the name of the file (x-x)
  const char* name;
public:
  /* Default Constructor
   */
  File();
  /* Constructor
   * Creates a new File, pulling the data for this File object from 
   * the stat struct at the specified pointer.
   */
  File(struct stat *, const char* = "");
  /* Destructor
   */
  ~File();
  /* getID
   * Returns the ID of this file.
   */
  ino_t getID();
  /* isDirectory
   * Returns true if this file is a directory, 
   * otherwise returns false.
   */
  bool isDirectory();
  /* getModified
   * Returns the last modified time of this file.
   */
  time_t getModified();
  /* OVERLOAD : ==
   * Returns true if this File and the specified File have 
   * the same ID, otherwise returns false.
   */
  /**/
  const char* getName();
  bool operator==(const File &);
  /* OVERLOAD : =
   * Copies the data in the specified file to this file.
   * Returns this file.
   */
  File& operator=(const File &);
  void holyhell();
};

#endif
