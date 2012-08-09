#include "../headers/Logger.h"

using namespace std;


Logger::Logger(activity_t type, time_t modified, string &name)
{
  modifiedType = type;
  changeDate = modified;
  filename = name;
}


void Logger::write()
{
	ofstream myfile;
	myfile.open(log.txt);
//To Do: Make this work? Not exactly sure what's passed into Logger object from where and how to print it all to file.
	myfile << "Modification Type \t Date \t Filename" << endl;
	for (int i = 0 ; i < getSize() ; i++)
	{
		myfile << type << "\t" << modified << "\t" << name << endl;
	}
	myfile.close();
}
