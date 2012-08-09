#include <iostream>
#include <fstream>
#include "../headers/Parser.h"
#include <time.h>
#include <math.h>
#include <cstdlib>
using namespace std;

Parser::Parser(string mod, string dat, string name)
{
  // set the type of modification to query for
  modType = mod;
  // set the date to query for
  if(dat.length() >= 1)
    {
      // query for the specified date
      date = dat.substr(1);
      uiDate = convertDate(date);
    }
  else // don't query for a date (not specified)
    {
      date = dat;
    }
  // set the file name to query for
  if(name.length() >= 1)
    {
      // query for the specified file name
      filename = name.substr(1);
    }
  else // don't query for a file name (not specified)
    {
      filename = name;
    }
  // reset the number of matching results for the query
  numTargets = 0;
}

Parser::~Parser()
{
}

void Parser::parse(string directoryToParse)
{
  // the file stream associated with the FileStalker log
  ifstream log;
  // the relative location of the log file (TODO: make an absolute location)
  string logName = directoryToParse;
  // attempt to open the log
  log.open(logName.c_str());
  if(log.fail())
    {
      // the log could not be opened
      log.clear();
      log.ignore();
      cout << "Could not open log file." << endl;
    }
  else // log opened and ready for reading
    {
      // loop through all the entries in the log
      while(!log.eof())
        {
	  // stores the next entry to be added to the query results, 
	  // if applicable
	  string entry;
	  // the change logged on this line of the log
	  string logModType;
	  log >> logModType;
	  // the time of the change logged on this line of the log
	  string logDate;
	  log >> logDate;
	  time_t logTime = (time_t)atol(const_cast<char*>(logDate.c_str()));
	  // the time of the change logged on this line of the log,
	  // in ctime struct form
	  struct tm *loggerDate = new tm;
	  loggerDate = gmtime(&logTime);
	  // stores a pretty-print version of the date
	  logDate = string(asctime(loggerDate));
	  logDate = logDate.substr(0, logDate.length()-1);
	  // the name of the file logged on this line of the log
	  string logName;
	  log >> logName;
	  //There is a user-specified mod type 
	  if(modType.compare("") != 0)
            {
	      //There is a user-specified date
	      if(date.compare("") != 0)
                {
		  //There is a user-specified filename
		  if(filename.compare("") != 0)
                    {
		      //All three fields are specified, check for all three
		      if(uiDate.tm_mday == loggerDate->tm_mday && 
			 uiDate.tm_mon == loggerDate->tm_mon && 
			 uiDate.tm_year == loggerDate->tm_year && 
			 filename.compare(logName) == 0)
                        {
			  entry += logModType + " " + logDate + " " + logName;
			  targets.add(entry);
			  numTargets++;
                        }	
                    }
		  else //There is not a user-specified filename
                    {
		      //Only mod type and date are specified; 
		      //check for these two
		      if(modType.compare(logModType) == 0 && 
			 uiDate.tm_mday == (loggerDate->tm_mday) && 
			 uiDate.tm_mon == (loggerDate->tm_mon) && 
			 uiDate.tm_year == (loggerDate->tm_year))
                        {
			  entry += logModType + " " + logDate + " " + logName;
			  targets.add(entry);
			  numTargets++;
                        }	
                    }
                }
	      else //There is not a user-specified date
                {
		  //Only mod type and filename are specified;
		  //check for these two
		  if(filename.compare("") != 0)
                    {
		      if(modType.compare(logModType) == 0 && 
			 filename.compare(logName) == 0)
                        {
			  entry += logModType + " " + logDate + " " + logName;
			  targets.add(entry);
			  numTargets++;
                        }	
                    }
		  else //There is not a user-specified filename
                    {
		      //Only mod type is specified; check for this only
		      if(modType.compare(logModType) == 0)
                        {
			  entry += logModType + " " + logDate + " " + logName;
			  targets.add(entry);
			  numTargets++;
                        }	
                    }
                }
            }
	  else //There is not a user-specified mod type
            {
	      //Nothing is specified, add without checking
	      entry+= logModType + " " + logDate + " " + logName;
	      targets.add(entry);
	      numTargets++;
            }
        }
    }
}

struct tm Parser::convertDate(string date)
{
  char*tokes[3];
  tokes[0] = strtok(const_cast<char*>(date.c_str()), "/");
  tokes[1] = strtok(NULL, "/");
  tokes[2] = strtok(NULL, "/");
  struct tm t;
  t.tm_sec = 0, t.tm_min = 0, t.tm_hour = 0;
  t.tm_mday = atoi(tokes[0]);
  t.tm_mon = atoi(tokes[1])-1;
  t.tm_year = atoi(tokes[2])-1900;
  return t;
}

void Parser::print()
{
  for(int i = 0; i < numTargets; i++)
    {
      cout << targets.get(i) << endl;
    }
}
