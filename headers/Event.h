/*
 *  Event.h
 *  
 *
 *  Created by Steven Schwarcz on 4/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EVENT_H
#define EVENT_H

#include <sys/types.h>
#include <string>

class Event
{
 private:
  time_t eventTime;
  string filename;
 public:
  Event(string, time_t);
  void setFile(string);
  string getFile();
  virtual void output();
  friend ostream& operator<<(ostream&, Event&);	
};	

#endif
