/*
 *  EventRemoved.h
 *  
 *
 *  Created by Steven Schwarcz on 4/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef EVENTREMOVED_H
#define EVENTREMOVED_H

#include "../headers/Event.h"

class EventRemoved : public Event
{
public:
  EventRemoved(string, time_t);
  void output();
  friend ostream& operator<<(ostream&, EventRemoved&);
};

#endif
