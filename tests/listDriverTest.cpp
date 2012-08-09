//
//  main.cpp
//  List
//
//  Created by Daniel Dechiara on 4/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "../headers/List.h"

using namespace std;

int main (int argc, const char * argv[])
{
  List<int> list;
  list.add(3);
  list.add(883);
  list.add(41);
  list.get(2);
  list.get();
  cout << "Search\n";
  cout << list.search(883) << endl;;
  cout << "Search\n";
  cout << list.search(5) << endl;
  list.remove(1);
  list.remove();
  list.remove();
  list.remove();
  return 0;
}

