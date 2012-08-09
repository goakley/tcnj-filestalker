#include "../headers/DirectoryMonitor.h"

int main(int argc, char* argv[])
{
  if (argc > 2)
    return 0;
  char* monitorThis;
  if (argc == 2)
    monitorThis = argv[1];
  else
    monitorThis = "./";
  DirectoryMonitor MONITOR_DESU(monitorThis);
  for (;;)
    {
      sleep(1);
      MONITOR_DESU.checkChanges();
    }
}
