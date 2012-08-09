#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include "sys/types.h"
#include "activities.h"

class Logger
{
 private:
    activity_t modifiedType;
    string filename;
    time_t changeDate;
 public:
  Logger(string, time_t, activity_t, string);
  void write();
};

#endif
