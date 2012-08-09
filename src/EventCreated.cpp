/*
 *  EventCreated.cpp
 *  
 *
 *  Created by Steven Schwarcz on 4/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "../headers/EventCreated.h"

EventCreated::EventCreated(string name, time_t time) : Event(name)
{
}	

void EventModified::output()
{
  cout << filename << " was created at " << eventTime << ".";
}	

ostream& operator<<(ostream& lhs, EventCreated& rhs)
{
  lsh << "Created " 
      << rhs.eventTime << " " 
      << rhs.filename << endl;
  return lhs;
}
