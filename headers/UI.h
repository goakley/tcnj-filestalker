#include <iostream>
using namespace std;
class UI
{
	private:
		bool isInstalled;
		string currentDirectory;
		string currentFilter;
		string mod;
		string dat;
		string name;
	public:
		UI(bool);
		void displayAll();
		void displayLogo();
		void displaySelection();
		void displayInstructions();
		void displayCommands();
		void getCommand();
		void displayHelp();
		void output();
		void changeDirectory(string);
		void getFilter();
		void filter(string);
};
