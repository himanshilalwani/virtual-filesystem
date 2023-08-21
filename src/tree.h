#ifndef TREE_H
#define TREE_H

#include "position.h"
#include "queue.h"
#include "stack.h"
#include "node.h"
class Tree
{
	private:
		Position* root; // pointer to the root
		Queue bin;
		Position* curr; // pointer to the current position
		PositionList positions; // a list of all positions in the tree
		Position* prev; // pointer to the previoud position

	public:
		Tree();
		void help() const; // displays available command
		string c_date(); // returns system date
		bool uniqueName(string name); // checks if the name is unique
		bool validFileName(string name); // checks if the file name is valid
		bool validFolderName(string name); // checks if the folder name is valid
		void mkdir(string foldername); // makes a folder in the current directory
		void touch(string filename, int size); // makes a file in the current directory
		void cd(); // changes current working directory to root
		void cd_folder(string foldername); // changes current working directory the folder
		void cd_par(); // changes current working directory to the parent of the current position
		void pwd(); // prints the path of the current position
		void realpath(string filename); // prints the path of the file
		void ls(); // lists the immediate childrn of the current position
		void ls_sort(); // sorts the children and then lists them
		Position* checkPath(string name, Position* a); // checks if the string is in the children of position
		void cd_path(string path); // changes current directory to the given path
		void cd_prev_dir(); // changes current directory to the previous directory
		void find(string name); // finds the path of the given file/folder if it exists
		void mv(string filename, string foldername); // moves the file to the folder
		void rm(string name); // removes the file/folder and puts it in a bin
		void mv_arb(string filepath, string folderpath); // moves the file at the filepath to the folder at the folderpath
		void rm_arb(string path); // removes the file/folder at the given path
		int size(string path); // returns the size of the position at the given path
		int size_helper(Position* p); // recursive function that helps to calculate the size of all the subfiles of the folder
		void emptyTrash(); // empties the trash
		void showBin(); // shows the next element that will be removed from the bin if the bin is full
		void recover(); // recovers that element
		string getPath(Position* p); // gets the full path of the given position
		string preOrder(Position* p); // printing the contents of the inode while dumping data
		void dumpData(); // dumps the data
		void loadData(); // loads the data
		void mkdir_p(Position* p); // creates a directory while loading data
		void touch_p(Position* p); // creates a file while loading data
};


#endif