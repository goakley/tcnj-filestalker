/*
 *  hashDriverTest.cpp
 *  
 *
 *  Created by Steven Schwarcz on 4/11/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "../headers/HashMap.h"
#include <string>
#include <iostream>
using namespace std;

using namespace std;

int main()
{
  HashMap<int> hello (10);
  hello.add(821, 372);
  hello.add(8217, 2);
  hello.add(821, 892);
  hello.add(3811, 721);
  cout << hello.getCount() << endl;
  hello.remove(2912);
  cout << hello.remove(821) << endl;
	cout << hello.remove(8217) << endl;
	cout << hello.remove(821) << endl;
	cout << hello.remove(821) << endl;
  cout << hello.getCount() << endl;
	
  return 0;
}
