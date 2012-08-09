#include <iostream>
#include "../headers/File.h"
#include <sys/stat.h>

using namespace std;

int main()
{
  struct stat asdf;
  File f(&asdf, "HERP"), g, h;
  cout << f.getName() << endl;
}
