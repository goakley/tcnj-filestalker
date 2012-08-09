/*
 *  Event.cpp
 *  
 *
 *  Created by Steven Schwarcz on 4/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "../headers/Event.h"

//TODO: Initialize the correct value for time_t time
Event::Event(string name, time_t time)
{
  eventTime = time;
  filename = name;
}

Event::setFile(string file)
{
  filename = file;
}	

string Event::getFile()
{
  return filename;
}

void output()
{
  cout << "An event occurred in " << filename << " at " << eventTime << ".";
}	

ostream& operator<<(ostream& lhs, Event& rhs)
{
  lsh << "Event " 
      << rhs.eventTime << " " 
      << rhs.fileName << endl;
  return lhs;
}	


