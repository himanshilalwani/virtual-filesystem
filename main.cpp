#include "tree.h"
#include "stack.h"
#include "mylinkedlist.h"
#include "snode.h"
#include "queue.h"
#include "position.h"
#include "positionlist.h"
#include "node.h"
#include<sstream>
#include<iostream>
#include<string>
using namespace std;

int main()
{	
	Tree myTree; // object
	myTree.loadData(); // load data from the file
	myTree.help(); // user terminal

	string user_input;
	string command;
	string parameter;
	string parameter2;
		
	do
	{
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter,' ');
		getline(sstr,parameter2);

		if (command == "help")
		{
			myTree.help();
		}
		else if (command == "pwd")
		{
			myTree.pwd();
		}
		else if (command == "realpath")
		{
			myTree.realpath(parameter);
		}
		else if (command == "ls")
		{
			myTree.ls();
		}
		else if (command == "lssort")
		{
			myTree.ls_sort();
		}
		else if (command == "mkdir")
		{
			myTree.mkdir(parameter);
		}
		else if (command == "touch")
		{
			bool flag = true;
			for (int i = 0; i < parameter2.size(); i++)
			{
				if (isdigit(parameter2[i]) == false)
				{
					flag = false;
				}
			}
			if (flag == true)
			{
				myTree.touch(parameter,stoi(parameter2));
			}
			else
			{
				cout<<"Invalid size"<<endl;
			}	
		}
		else if (command == "cd")
		{
			myTree.cd();
		}
		else if (command == "cd_folder")
		{
			myTree.cd_folder(parameter);
		}
		else if (command == "cd..")
		{
			myTree.cd_par();
		}
		else if (command == "cd-")
		{
			myTree.cd_prev_dir();
		}
		else if (command == "cd_path")
		{
			myTree.cd_path(parameter);
		}
		else if (command == "find")
		{
			myTree.find(parameter);
		}
		else if (command == "mv")
		{
			myTree.mv(parameter, parameter2);
		}
		else if (command == "rm")
		{
			myTree.rm(parameter);
		}
		else if (command == "mv_arb")
		{
			myTree.mv_arb(parameter, parameter2);
		}
		else if (command == "rm_arb")
		{
			myTree.rm_arb(parameter);
		}
		else if (command == "size")
		{
			int a = myTree.size(parameter);
			cout<<a<<endl;
		}
		else if (command == "emptybin")
		{
			myTree.emptyTrash();
		}
		else if (command == "showbin")
		{
			myTree.showBin();
		}
		else if (command == "recover")
		{
			myTree.recover();
		}
	}
	while (command != "exit");
	if (command == "exit")
	{
		myTree.dumpData();
	}
	return 0;
}