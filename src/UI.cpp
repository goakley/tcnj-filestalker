#include <iostream>
#include <fstream>
#include "../headers/UI.h"
#include "../headers/Parser.h"

using namespace std;

//sets the default current directory and filter
UI::UI(bool installed)
{
  isInstalled = installed;
  currentDirectory = "home";
  currentFilter = "";
  mod = "";
  dat = "";
  name = "";
}

//displays the File Stalker logo, instructions, and handles all user interaction
void UI::displayAll()
{
  displayLogo();
  displayInstructions();
  displaySelection();
}	 

//outputs the File Stalker logo
void UI::displayLogo()
{
  cout << "                           ___|__   " << endl;
  cout << "////////// //   /////     |   |  \\  " << endl;
  cout << "/     //   //   //        |       | " << endl;
  cout << "///   //   //   ////    __|__ o __|__ " << endl;
  cout << "/     //   //   //        |       | " << endl;
  cout << "/   ////// //////////     |___|___| " << endl;
  cout << "                              | " << endl;
  cout << "==========================================" << endl;
  cout << "   ____  _____  __              ___  __  " << endl;
  cout << "  /____    |   /__\\  |    |__/ |__  |__| " << endl;
  cout << "  ____/    |  /    \\ |___ |  \\ |___ |  \\ " << endl << endl << endl;
}

//displays the current directory and filter, common commands of the system, and takes user
//input to change filters 
void UI::displaySelection()
{
  //NOT IMPLEMENTED: 
  // cout << "Current directory: \"" << currentDirectory << "\"" << endl;
  cout << "Current filter: \"" << currentFilter << "\"" << endl << endl;
  displayCommands();
  getCommand();
}

//outputs a list of instructions
void UI::displayInstructions()
{
  cout << "Instructions: " << endl;
  cout << "File Stalker is currently monitoring and logging changes "
       << "to your system." << endl
       << "To output the contents of this log, enter \"output\". "
       << "To add search filters for " << endl
       << "this log, enter in one of the commands below or "
       << "choose \"help\" for a more " << endl
       << "detailed list." << endl << endl;
}

//outputs some of the immediately helpful File Stalker commands
void UI::displayCommands()
{
  cout << "Common commands:    [] = entry required    <> = entry not required"
       << endl;
  // cout << "[] = entry required" << endl;
  // cout << "<> = entry not required" << endl;
  //NOT IMPLEMENTED: cout << "cd [name of directory]" << endl;
  cout << "help" << endl;  
  cout << "filter" << endl;
  /*
    cout << "filter -m <file or directory>" << endl;
    cout << "filter -c <directory>" << endl;
    cout << "filter -r <directory>" << endl << endl;
  */
  cout << "filter <-m [file or directory]> <-c [directory]> <-r [directory>"
       << "quit" << endl
       << endl;
}

//takes a command from a user, checks if it is valid, and then 
//passes control to the function that matches that command
void UI::getCommand()
{
  string input;
  string combinedFilter;
  getline(cin, input);
  if(input.compare("help") == 0)
    {
      displayHelp();
    }
  else // if input is not 'help'
    {
      if(input.compare("output") == 0)
	{
	  //calls parser
	  output();
	}
      else // if input is not 'output'
	if(input.compare("quit") == 0)
	{
	
	}
	else
	{
		// ---
		// NOT IMPLEMENTED:
		// if (input.substr(0,3).compare("cd ") == 0)
		//     changeDirectory(input.substr(3));
		// else, do stuff
		// ---
		// check if input is 'clear'
		if(input.compare("clear") == 0)
		{
		currentFilter = "";
		mod = "";
		dat = "";
		name = "";
		displaySelection();
		}
		else // input is not 'clear'
		{
		// check if input is 'filter'
		if(input.substr(0,6).compare("filter") == 0)
		{
			// check if input is a detailed filter
			if(input.length() == 6)
			{
			getFilter();
			}
			else // input is a specific filter
			{
			// check if filter -m
			if(input.substr(6,3).compare(" -m") == 0)
				{
				// filter for 'modified'
				mod = "M";
				name = input.substr(9);
				filter(name);
				}
			else // filter is not -m
				{
				// check if filter -dm
				if (input.substr(6,4).compare(" -dm") == 0)
				{
				//filter for 'modified' and the user wants to 
				//specify a date
				mod = "M";
				//reset date and name filters
				dat = " ";
				name = " ";
				//collect the characters leading up to a space and store them as
				//the date
				for(int i = 11; i < input.length(); i++)
					{
					char next = input.at(i);
					//stop when a white space is found
					if(next == ' ')
					{
					//store whatever comes after the white
					//space as the filename
					name = name + input.substr(i+1);
					i = input.length();
					}
					else // no white space found
					{
					//keep adding characters to the date
					dat = dat + next;
					}
					}
				//checks if anything came after the date
				if(name.length() == 1)
					{ // nothing after the date
					//if there is a date, store it	
					if(input.length() > 10)
					{
					combinedFilter = dat;
					name = "";
					}	
					else // there is no date
					{
					//set date and name to blanks
					dat = "";
					name = "";
					}
					}
				else // something after the date
					{
					//there is also a filename specified, store it
					combinedFilter = dat + name;
					}
				filter(combinedFilter);
				}
				else // filter is not -dm
				{
				if (input.substr(6,3).compare(" -c") == 0)
					{ // filter is -c
					// filter for 'created'
					mod = "C";
					name = input.substr(9);
					filter(name);
					}
				else // filter is not -c
					{
					if (input.substr(6,4).compare(" -dc") == 0)
					{ // filter is -dc
					//filter for 'created' and the user wants
					// to specify a date
					mod = "C";
					//reset date and name filters
					dat = " ";
					name = " ";
					//collect the characters leading up to
					//a space and store them as the date
					for(int i = 11; i < input.length(); i++)
						{
						char next = input.at(i);
						//stop when a white space is found
						if(next == ' ')
						{
						//store whatever comes after the white space as the
						//filename
						name = name + input.substr(i+1);
						i = input.length();
						}
						else
						{
						//continue adding characters to the date
						dat = dat + next;
						}
						}
					//checks if anything came after the date
					if(name.length() == 1)
						{
						//if there is a date, store it	
						if(input.length() > 10)
						{
						combinedFilter = dat;
						name = "";
						}
						else
						{
						//set date and name to blanks
						dat = "";
						name = "";
						}
						}
					else
						{
						//there is a filename specified, store it
						combinedFilter = dat + name;
						}
					filter(combinedFilter);
					}
					else // filter is not -dc
					{
					if (input.substr(6,3).compare(" -r")==0)
						{ // filter is -r
						// filter for 'removed'
						mod = "R";
						name = input.substr(9);
						filter(name);
						}
					else // filter is not -r
						{
						if (input.substr(6,4)
						.compare(" -dr") == 0)
						{ // filter is -dr
						//filter for 'removed' and the user wants to 
						//specify a date
						mod = "R";
						//reset date and name filters
						dat = " ";
						name = " ";
						//collect the characters leading up to a space and store them as
						//the date
						for(int i = 11; i < input.length(); i++)
							{
							char next = input.at(i);
							//stop when a white space is found
							if(next == ' ')
							{
							//store whatever comes after the white space as the
							//filename
							name = name + input.substr(i+1);
							i = input.length();
							}
							else
							{
							//continue adding characters to the date
							dat = dat + next;
							}
							}
						if(name.length() == 1)
							{
							//if there is a date, store it	
							if(input.length() > 10)
							{
							combinedFilter = dat;
							}
							else
							{
							//set date and name to blanks
							dat = "";
							name = "";
							}	
							}
						else
							{
							//there is a filename specified, store it
							combinedFilter = dat + name;
							}
						filter(combinedFilter);
						}
						else // not a valid filter specification
						{
						cout << endl << "Invalid input." << endl << endl;
						displaySelection();
						}
						}
					}
					}
				}
				}
			}
			}
			else
			{
				cout << endl << "Invalid input." << endl << endl;
				displaySelection();
			}
		}
		
	}
    }
} 


//outputs all of the valid commands that the user may enter
void UI::displayHelp()
{
  cout << endl;
  cout << "[] = entry required" << endl
       << "<> = entry not required" << endl
       << "output" << endl 
       << " - **outputs the log based on current filters**" << endl
       << "help" << endl 
       << " - **displays the full list of commands**" << endl
    //NOT IMPLEMENTED: 
    // cout << "cd [name of directory]" << endl 
    //      << "**changes the currently monitored directory**" << endl
       << "clear" << endl
       << " - **sets the filter to blank (all changes will be displayed)**" << endl
       << "filter" << endl 
       << " - **allows the log to be parsed for a specific filter**" << endl
       << "filter -m <file or directory>" << endl 
       << " - **filters the log to only display modifications**" << endl
       << "filter -c <directory>" << endl 
       << " - **filters the log to only display creations**" << endl
       << "filter -r <directory>" << endl 
       << " - **filters the log to only display removals**" << endl
       << "filter -dm [date] <file or directory>" << endl 
       << " - **filters the log to only display modifications "
       << "during the date specified**" << endl
       << "filter -dc [date] <file or directory>" << endl 
       << " - **filters the log to only display creations on "
       << "the date specified**" << endl
       << "filter -dr [date] <file or directory>" << endl 
       << " - **filters the log to only display removals on "
       << "the date specified**" << endl
       << "quit" << endl
       << " - **quits the program**" << endl
       << endl;
  displaySelection();
}

//outputs the correct portions of the log, determined by the current directory and filters
void UI::output()
{
  cout << "MATCHES:" << endl;
  cout << "=============================================================================" << endl;
  Parser parser(mod, dat, name);
  if (isInstalled)
    parser.parse("/var/log/filestalker.log");
  else
    parser.parse("./log.file");
  parser.print();
  cout << "=============================================================================" << endl;
  displaySelection();
}

//changes the current directory to the specified string
void UI::changeDirectory(string dir)
{
  cout << endl;
  currentDirectory = dir;
  displaySelection();
}

//asks the user to specify the type of filter and, if desired, a date and specific file or directory
//to track
void UI::getFilter()
{
  int filterType;
  char choice;
  string combinedFilter = "";
  bool valid = false;
  cout << endl;
  cout << "Which type of filter would you like to choose? Enter '1', '2', or '3':" << endl;
  cout << "1 - Modification" << endl << "2 - Creation" << endl << "3 - Removal" << endl;
  while(!valid)
    {
      cin >> filterType;
      if(cin.fail() || filterType < 1 || filterType > 3)
	{
	  cin.clear();
	  cin.ignore (1000, '\n');
	  cout << "Invalid input. Please re-enter." << endl;
	}
      else
	{
	  valid = true;
	}
    }	
  switch(filterType)
    {
    case 1:
      mod = "M";
      break;
    case 2:
      mod = "C";
      break;
    case 3:
      mod = "R";
      break;
    }
  valid = false;
  cout << "Would you like to specify a date? Enter 'y' or 'n':" << endl;
  while(!valid)
    {
      cin >> choice;
      if(cin.fail() || !(choice == 'y' || choice == 'n'))
	{
	  cin.clear();
	  cin.ignore (1000, '\n');
	  cout << "Invalid input. Please re-enter." << endl;
	}
      else
	{
	  valid = true;
	}
    }
  if(choice == 'y')
    {
      cout << "Enter your date in the form dd/mm/yyyy:" << endl;
      cin >> dat;
      if(!mod.length() == 0)
	{
	  dat = " " + dat;
	}	
    }  
  else
    {
      dat = "";
    }	
  cout << "Would you like to specify a file or directory to monitor? Enter 'y' or 'n':" << endl;
  cin >> choice;
  if(choice == 'y')
    {
      cout << "Enter a filename:" << endl;
      cin >> name;
      if(!dat.compare(" ") == 0)
	{
	  name = " " + name;
	}
    }
  else
    {
      name = "";
    }	
  combinedFilter = dat + name;
  filter(combinedFilter);
}


//**NEED TO FIX THIS** this function requires cin.ignore to avoid having input skipped by getline
//in getCommand()

//sets the current filter, represented by a string 
void UI::filter(string filter)
{
  currentFilter = mod + filter;
  cin.ignore(80, '\n');
  displaySelection();
}
	
