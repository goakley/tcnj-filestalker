/*
 *  EventRemoved.cpp
 *  
 *
 *  Created by Steven Schwarcz on 4/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "../headers/EventRemoved.h"

EventRemoved::EventRemoved(string name, time_t time):Event(name)
{
}	

void EventRemoved::output()
{
  cout << filename << " was removed at " << eventTime << ".";
}

ostream& operator<<(ostream& lhs, EventRemoved& rhs)
{
  lsh << "Removed " 
      << rhs.eventTime << " " 
      << rhs.filename << endl;
  return lhs;
}	
