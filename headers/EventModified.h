/*
 *  EventModified.h
 *  
 *
 *  Created by Steven Schwarcz on 4/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EVENTMODIFIED_H
#define EVENTMODIFIED_H

#include Event.h

class EventModified : public Event
{
 public:
  EventModified(string, time_t);
  void output();
  friend ostream& operator<<(ostream&, EventModified&);
};

#endif
