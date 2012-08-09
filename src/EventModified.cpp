/*
 *  EventModified.cpp
 *  
 *
 *  Created by Steven Schwarcz on 4/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "../headers/EventModified.h"

EventModified::EventModified(string name, time_t time):Event(name)
{
}	

void EventModified::output()
{
  cout << filename << " was modified at " << eventTime << ".";
}

ostream& operator<<(ostream& lhs, EventModified& rhs)
{
  lsh << "Modified " 
      << rhs.eventTime << " " 
      << rhs.filename << endl;
  return lhs;
}	
