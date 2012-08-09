using namespace std;
#include "List.h"
//Given the logfile created by the FileStalker class, this will parse the log for the given token
//and store all of the necessary information.
class Parser
{
 private:
  // the type of modificatino to check the log for
  string modType;
  // the date to check the log for, in string form
  string date;
  // the date to check the log for, in ctime struct form
  struct tm uiDate;
  // the name of the file to check the log for
  string filename;
  // a list of the items found while querying the log
  List<string> targets;
  // the number of targets found during the query
  int numTargets;

  struct tm convertDate(string);

 public:
  Parser(string, string, string);
  ~Parser();
  void parse(string = "/var/log/filestalker.log");
  void print();
};
