/*
 *  EventCreated.h
 *  
 *
 *  Created by Steven Schwarcz on 4/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EVENTCREATED_H
#define EVENTCREATED_H

#include Event.h

class EventCreated : public Event
{
 public:
  EventCreated(string, time_t);
  void output();
  friend ostream& operator<<(ostream&, EventCreated&);
};

#endif
