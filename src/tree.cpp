#include "tree.h"
#include <iostream>
#include <string>
#include <ctime>
#include "stack.h"
#include <fstream>
#include <sstream>

//=================================================
string Tree::c_date() // returns system date
{
	time_t now = time(0);
	tm *gst = localtime(&now);
	string date = to_string(gst->tm_mday)+"-"+to_string(1+gst->tm_mon)+"-"+to_string(1900+gst->tm_year);
	return date;
}
//=================================================
Tree::Tree() // constructor
{
	string date = c_date();
	this->root = new Position("/",date,0,true);
	curr = root;
	root->Parent = NULL;
	positions.addBack(root);
	prev = root;
}
//=================================================
void Tree::help() const
{
	cout<<"List of Available Commands: "<<endl;
	cout<<"pwd:                                     Prints the path of current inode"<<endl;
	cout<<"realpath <filename>:                     Prints the absolute/full path of a given filename of a file within the current directory"<<endl;
	cout<<"ls:                                      Prints the children of the current inode (folder)"<<endl;
	cout<<"lssort:                                  Prints the children of the current inode by descending file size"<<endl;
	cout<<"mkdir <foldername>:                      Creates a folder under the current folder"<<endl;
	cout<<"touch <filename> <size>:                 Creates a file under the current inode location with the specified filename, size, and current datetime"<<endl;
	cout<<"cd_folder <foldername>:                  Change current inode to the specified folder"<<endl;
	cout<<"cd..:                                    Changes current inode to its parent folder"<<endl;
	cout<<"cd-:                                     Changes current inode to the previous working directory"<<endl;
	cout<<"cd:                                      Changes current inode to root"<<endl;
	cout<<"cd_path </my/path/name>:                 Changes the current inode to the specified path if it exists"<<endl;
	cout<<"find <foldername>:                       Returns the path of the folder if it exists"<<endl;
	cout<<"find <filename>:                         Returns the path of the file if it exists"<<endl;
	cout<<"mv <filename> <foldername>:              Moves a file located under the current inode location, to the specified folder path"<<endl;
	cout<<"rm <foldername>:                         Removes the specified folder"<<endl;
	cout<<"rm <filename>:                           Removes the specified file"<<endl;
	cout<<"mv_arb <filename> <foldername>:          Moves the specified file to the specified folder"<<endl;
	cout<<"rm_arb <foldername>:                     Removes the specified folder"<<endl;
	cout<<"rm_arb <filename>:                       Removes the specified file"<<endl;
	cout<<"size <foldername>:                       Returns the total size of the folder, including all its subfiles"<<endl;
	cout<<"size <filename>:                         Returns the size of the file"<<endl;
	cout<<"emptybin:                                Empties the bin"<<endl;
	cout<<"showbin:                                 Shows the oldest inode of the bin, including its path"<<endl;
	cout<<"recover:                                 Reinstates the oldest inode back if the path exists"<<endl;
	cout<<"Exit:                                    Exits the program"<<endl;
}
//=================================================
bool Tree::uniqueName(string name) // checks if the input name is not taken by any of the children of the current inode
{
	Position* c = curr;

	PositionList::iterator i = c->Children.begin();

	while (i!=c->Children.end())
	{
		if (i.v->p->name != name)
		{
			++i;
			continue;
		}
		return false;
	}
	return true;
}
//=================================================
bool Tree::validFileName(string name) 
{
	for (int i = 0; i < name.length(); i++)
	{
		if (isalnum(name[i]) == true || name[i] == '.')
		{
			continue;
		}
		return false;
	}
	int count = std::count(name.begin(), name.end(), '.');
	
	if (count == 1) // checks if '.' is present in the file name
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
//=================================================
bool Tree::validFolderName(string name)
{
	for (int i = 0; i < name.length(); i++)
	{
		if (isalnum(name[i]) == true) // checks if the folder name only consists of alphanumeric characters
		{
			continue;
		}
		return false;
	}
	return true;
	
}
//=================================================
void Tree::mkdir(string foldername)
{
	
	if (uniqueName(foldername) == true && validFolderName(foldername) == true)
	{
		if (curr->folder == true)
		{
			// create a position
			// set its parent to current
			// add it as a child of current
			// add it to the list of positions

			string date = c_date();
			Position* new_folder = new Position(foldername, date, 10, true);
			new_folder->Parent = curr;
			curr->addChild(new_folder);
			positions.addBack(new_folder);
		}
		else
		{
			cout<<"Invalid Position"<<endl;
		}
	}
	else
	{
		cout<<"Invalid Name"<<endl;
	}
}
//=================================================
void Tree::touch(string filename, int size)
{
	if (uniqueName(filename) == true && validFileName(filename) == true)
	{
		if (curr->folder == true)
		{
			// create a position
			// set its parent to current
			// add it as a child of current
			// add it to the list of position

			string date = c_date();
			Position* new_file = new Position(filename, date, size, false);
			new_file->Parent = curr;
			curr->addChild(new_file);
			positions.addBack(new_file);
		}
		else
		{
			cout<<"Invalid Position"<<endl;
		}
	}
	else
	{
		cout<<"Invalid Name"<<endl;
	}
}
//=================================================
void Tree::pwd()
{
	CStack myStack;

	// push the names of the positions in the stack
	while(curr->Parent!=NULL)
	{
		myStack.push(curr->name);
		curr = curr->Parent;
	}

	// if the stack is empty, we are at the root, print /
	if (myStack.empty())
	{
		cout<<root->name;
	}

	// if the stack is not empty, keep printing and removing the element at the top until it is empty
	while (myStack.empty() == false)
	{
		cout<<"/";
		string u = myStack.top();
		cout<<u;
		myStack.pop();
	}
	cout<<endl;
}
//=================================================
void Tree::cd()
{
	// change previous directory to current and current to root
	prev = curr;
	curr = root;
}
//=================================================
void Tree::cd_folder(string foldername)
{
	// check if the folder exists
	// if yes, change previous to current and current to the folder's position
	bool flag = false;
	bool flag2 = false;
	for (PositionList::iterator i = positions.begin(); i != positions.end(); ++i)
	{
		if (i.v->p->name == foldername)
		{
			if (i.v->p->folder == true)
		 	{
		 		prev = curr;
				curr = i.v->p;
				flag = true;
		 	}
			else
			{
				cout<<"Invalid Input. Enter a folder name."<<endl;
				flag2 = true;
			}
			break;	
		}
	}

	if (flag == false && flag2 == false)
	{
		cout<<"Folder not found"<<endl;
	}	
}
//=================================================
void Tree::cd_par()
{
	// if not at root, change previous to current and current to its parent
	if (curr != root)
	{
		prev = curr;
		curr = curr->Parent;
	}
}
//=================================================
void Tree::realpath(string filename)
{
	// check if the file exists
	// store current in a temporary variable
	// change current to the file's position
	// use pwd to print the path of current
	// set current back to its original position
	bool flag = false;
	for (PositionList::iterator i = curr->Children.begin(); i != curr->Children.end(); ++i)
	{
		if (i.v->p->name == filename && i.v->p->folder == false)
		{
			Position* temp = curr;
			curr = i.v->p;
			pwd();
			flag = true;
			curr = temp;
		}
	}

	if (flag == false)
	{
		cout<<"File not found"<<endl;
	}

}
//=================================================
void Tree::ls()
{
	if (curr->folder == true)
	{
		PositionList::iterator i = curr->Children.begin();

		while(i != curr->Children.end())
		{
			if (i.v->p->folder == true)
			{
				cout<<"Dir ";
			}
			else
			{
				cout<<"File ";
			}

			cout<<i.v->p->name<<" ";
			cout<<i.v->p->size<<" bytes ";
			cout<<i.v->p->date<<endl;

			++i;
		}
	}
	else
	{
		cout<<"Invalid Position! The function does not work inside a file";
	}
}
//=================================================
void Tree::ls_sort()
{
	if (curr->folder == true && curr->Children.empty()==false)
	{
		Node* current;
		Node* end = curr->Children.tail;
		bool swapped;
		// use bubble sort to set the positions in the decreasing order of their size
		do
		{
			current = curr->Children.head->next;
			swapped = false;
			while(current->next!=end)
			{
				if (current->p->size < current->next->p->size)
				{

					Position* tmp = current->p;
					current->p = current->next->p;
					current->next->p = tmp;
					swapped = true;
				}

				current = current->next;
			}
		}
		while (swapped);
	}
	ls(); // use ls to print the positions
	
}
//=================================================
Position* Tree::checkPath(string name, Position* a) // check if name is in the children of a
{
	if (a->folder == true)
	{
		for (PositionList::iterator i = a->Children.begin(); i != a->Children.end(); ++i)
		{
			if (i.v->p->name == name)
			{
				return i.v->p;
			}
		}
	}
	return nullptr;
}
//=================================================
void Tree::cd_path(string path)
{
	prev = curr;
	curr = root;

	if (path[0] == '/' && path.length()>1)
	{
		string s = path.substr(1,path.length()-1) + "/";
	
		string sep = "/";
		
		size_t pos = 0;
		string fname;
	
		while ((pos = s.find(sep)) != string::npos)
		{
			fname = s.substr(0,pos);
			
			Position* flag = checkPath(fname, curr); // validating whether fname exists in curr
			if (flag != NULL) 
			{
				s.erase(0,pos+1);
				if (flag->folder == true)
				{
					curr = flag;
					
				}
				// if fname exists in curr but it is a file
				// and the path is not empty
				// the path is invalid as a file cannot have children
				else if (s.length() > 0)
				{
					cout<<"Invalid path"<<endl;
					curr = prev;
					break;
				}
			}
			else
			{
				cout<<"Invalid Path"<<endl;
				curr = prev;
				break;
			}
		}
	}
	else if (path == "/")
	{
		cd();
	}
	else
	{
		curr = prev;
		cout<<"Invalid path"<<endl;
	}
	// curr = tmp;
	// cout<<curr->name<<endl;
}
//=================================================
void Tree::cd_prev_dir()
{
	Position* temp = curr;
	curr = prev;
	prev = temp; 
}
//=================================================
void Tree::find(string name)
{
	Position* temp = curr;
	bool flag = false;
	// iterate over the list of all positions
	// print the path if the name matches
	for (PositionList::iterator i = positions.begin(); i != positions.end(); ++i)
	{
		if (i.v->p->name == name)
		{
			curr = i.v->p;
			pwd();
			flag = true;
		}
	}
	curr = temp;
	if (flag == false)
	{
		cout<<"File/Folder Not Found"<<endl;
	}
}
//=================================================
void Tree::mv(string filename, string foldername)
{
	
	// check if filename and foldername are both the children of the current inode
	// if yes, remove filename from current's chilren and it to folder's children
	// set filename's parent as foldername
	bool flag1 = false;
	bool flag2 = false;

	Position* file_name;
	Position* folder_name;

	PositionList::iterator i = curr->Children.begin();

	while (i!=curr->Children.end())
	{
		
		if (i.v->p->name == filename)
		{
			file_name = i.v->p;
			flag1 = true;
		}
		else if (i.v->p->name == foldername)
		{
			folder_name = i.v->p;
			flag2 = true;
		}
		if (flag1 == true && flag2 == true)
		{
			break;
		}
		++i;
	}
	
	if (flag1 == true && flag2 == true)
	{
		curr->Children.remove(file_name);
		file_name->Parent = folder_name;
		folder_name->Children.addBack(file_name);	
	}
	else
	{
		cout<<"File/Folder not found in the same inode"<<endl;
	}
}
//=================================================
void Tree::rm(string name)
{
	// check if the input name is in current's children
	// if yes, remove it from current's children list
	// check if the bin has space and add it there
	// remove it from the list of all positions
	Position* fname;
	bool file;
	bool flag = false;

	PositionList::iterator i = curr->Children.begin();

	while (i!=curr->Children.end())
	{
		if (i.v->p->name == name)
		{
			fname = i.v->p;
			flag = true;
			break;
		}
		++i;
	}

	if (flag == true)
	{
		curr->removeChild(fname);
		if (bin.size() == bin.N)
		{
			bin.dequeue();
		}
		bin.enqueue(fname);
		positions.remove(fname);
	}
	else
	{
		cout<<"File/Folder not found"<<endl;
	}
}
//=================================================
void Tree::mv_arb(string filepath, string folderpath)
{
	// check if both the paths are valid
	// make changes as in mv

	Position* file = nullptr;
	Position* folder = nullptr;
	
	Position* tmp = curr;
	curr = root;
	
	bool flag3 = false;
	
	if (filepath[0] == '/' && filepath.length()>1) // checking whether the filepath is valid
	{
		string s = filepath.substr(1,filepath.length()-1) + "/";
		string sep = "/";
		
		size_t pos = 0;
		string fname;
	
		while ((pos = s.find(sep)) != string::npos)
		{
			fname = s.substr(0,pos);
			Position* flag = checkPath(fname, curr);
			if (flag != NULL)
			{
				s.erase(0,pos+1);
		
				if (flag->folder == false && s.length() > 0)
				{
					cout<<"Invalid File Path"<<endl;
					curr = tmp;
					flag3 = true;
					break;
				}
				else
				{
					curr = flag; 
				}
			}
			else
			{
				cout<<"Invalid File Path"<<endl;
				curr = tmp;
				flag3 = true;
				break;
			}	
		}
		if (curr != tmp && curr->folder == false)
		{
			file = curr;
		}
		else
		{
			cout<<"Not a file"<<endl;
			flag3 = true;
		}
	}
	else
	{
		cout<<"Invalid File Path"<<endl;
		flag3 = true;
	}

	if (flag3 == false) // if the filepath is valid, check the folder path
	{
		curr = root;

		if (folderpath[0] == '/' && folderpath.length()>1)
		{
			string s = folderpath.substr(1,folderpath.length()-1) + "/";
			string sep = "/";
		
			size_t pos = 0;
			string fname;
	
			while ((pos = s.find(sep)) != string::npos)
			{
				fname = s.substr(0,pos);
				Position* flag = checkPath(fname, curr);
				if (flag != NULL)
				{
					s.erase(0,pos+1);
					if (flag->folder == true)
					{
						curr = flag;		
					}
					else if (s.length() > 0)
					{
						cout<<"Invalid Folder Path"<<endl;
						curr = tmp;
						break;
					}
				}
				else
				{	
					cout<<"Invalid Folder Path"<<endl;
					curr = tmp;
					break;
				}	
			}

			if (curr != tmp && curr->folder == true)
			{
				folder = curr;
			}
			else
			{
				cout<<"Not a valid folder"<<endl;
			}
		}

		else if (folderpath[0] == '/' && folderpath.length() == 1 )
		{
			folder = root;
		}
	}
	
	curr = tmp;

	if (file!=nullptr && folder!=nullptr) // if the paths are valid, make changes
	{
		Position* file_parent = file->Parent;
		file_parent->Children.remove(file);	
		folder->Children.addBack(file);
		file->Parent = folder; 
	}
}
//=================================================
void Tree::rm_arb(string path)
{
	// check if the path is valid
	// reach the parent
	// remove the position from parent's children
	// put it in bin
	// remove from the list of positions

	Position* tmp = root;
	Position* flag = nullptr;
	if (path[0] == '/' && path.length()>1)
	{
		string s = path.substr(1,path.length()-1) + "/";
	
		string sep = "/";
		
		size_t pos = 0;
		string fname;
	
		while ((pos = s.find(sep)) != string::npos)
		{
			fname = s.substr(0,pos);
			flag = checkPath(fname, tmp);
			if (flag != NULL)
			{
				s.erase(0,pos+1);
				if (flag->folder == true)
				{
					tmp = flag;	
				}
				else if (s.length() > 0)
				{
					cout<<"Invalid path"<<endl;
					flag = nullptr;
					break;
				}
			}
			else
			{
				cout<<"Invalid path"<<endl;
				break;
			}
		}
	}
	else if (path[0] == '/' && path.length() == 1) // check if the path is root, print error
	{
		cout<<"Root folder cannot be deleted"<<endl;
	}
	if (flag != nullptr)
	{
		Position* flag_parent = flag->Parent;
		flag_parent->Children.remove(flag);

		// for (PositionList::iterator i = flag_parent->Children.begin(); i != flag_parent->Children.end(); ++i)
		// {
		// 	cout<<i.v->p->name<<endl;
		// }
		if (bin.size() == bin.N)
		{
			bin.dequeue();
		}
		bin.enqueue(flag);
		positions.remove(flag);
	}
}
//=================================================
int Tree::size_helper(Position* p) // goes to the subfiles of p and adds their sizes
{
	int s = 10;
	for (PositionList::iterator i = p->Children.begin(); i!=p->Children.end(); ++i)
	{
		if (i.v->p->folder == true)
		{
			s+=size_helper(i.v->p);
		}
		else
		{
			s+=i.v->p->size;
		}	
	}
	return s;
}

//=================================================
int Tree::size(string path)
{
	Position* tmp = root;
	Position* flag = nullptr;
	if (path[0] == '/' && path.length()>1)
	{
		string s = path.substr(1,path.length()-1) + "/";
	
		string sep = "/";
		
		size_t pos = 0;
		string fname;
	
		while ((pos = s.find(sep)) != string::npos)
		{
			fname = s.substr(0,pos);
			flag = checkPath(fname, tmp);
			if (flag != NULL)
			{
				s.erase(0,pos+1);
				if (flag->folder == true)
				{
					tmp = flag;	
				}
				else if (s.length() > 0)
				{
					cout<<"Invalid path"<<endl;
					flag = nullptr;
					return -1;
				}
				
			}
			else
			{
				cout<<"Invalid path"<<endl;
				return -1;;
			}
		}
	}
	else if (path[0] == '/' && path.length() == 1)
	{
		flag = root;
	}

	if (flag!=nullptr)
	{
		if (flag->folder == true) // call size-helper for all the children of p if they are folders
		{
			int s = 10;
			for (PositionList::iterator i = flag->Children.begin(); i != flag->Children.end(); ++i)
			{
				
				if (i.v->p->folder == true)
				{
					s+=size_helper(i.v->p);
				}
				else
				{
					s+=i.v->p->size; 
				}
				
			}
			return s;
		}
		else if (flag->folder == false) // return the size of position in case it is a file
		{
			return flag->size;
		}
	}
}
//=================================================
void Tree::emptyTrash()
{
	bin.emptybin(); // empty the trash
}
//=================================================
void Tree::showBin()
{
	if (bin.empty() == false)
	{
		cout<<"Next Element to Remove: ";
		Position* p = bin.front(); // capture the position
		Position* q = bin.front();
		CStack myStack;

		// print the path of the position
		while(p->Parent!=NULL)
		{
			myStack.push(p->name);
			p = p->Parent;
		}
		// cout<<myStack.size()<<endl;
		
		while (myStack.empty() == false)
		{
			cout<<"/";
			string u = myStack.top();
			cout<<u;
			myStack.pop();
		}
		
		// print the size and date
		string s = " ("+to_string(q->size)+" bytes "+q->date+")";
		cout<<s<<endl;
	}
	else
	{
		cout<<"The bin is empty"<<endl;
	}	
}
//=================================================
void Tree::recover()
{
	if (bin.empty() == false)
	{
		// get the path of the captured position
		// check if it exists
		// add the file there
		// error message otherwise
		Position* p = bin.front();
		Position* q = bin.front();
		string p_name = p->name;
		CStack myStack;

		while(p->Parent!=NULL)
		{
			// cout<<"Hello"<<endl;
			myStack.push(p->name);
			p = p->Parent;
		}

		string path;

		if (myStack.empty())
		{
			path = root->name;
		}

		while (myStack.empty() == false)
		{
			path += "/";
			path += myStack.top();
			myStack.pop();
		}
		// cout<<path<<endl;
		Position* tmp = root;
		Position* flag = nullptr;

		string s = path.substr(1,path.length()-1) + "/";
		string sep = "/";
	
		size_t pos = 0;
		string fname;
		int count = 0;
		bool f = false;

		while ((pos = s.find(sep)) != string::npos)
		{
			fname = s.substr(0,pos);
			// cout<<fname<<endl;
			count+=1;
			if (fname == p_name)
			{
				f = true;
				break;
			}
			else
			{
				flag = checkPath(fname, tmp);
				if (flag != NULL)
				{
					if (flag->folder == true)
					{
						// s.erase(0,pos+1);
						tmp = flag;
					}
					else
					{
						cout<<"Invalid Path"<<endl;
						flag = nullptr;
						break;
					}
				}
				else
				{
					cout<<"Path does not exist"<<endl;
					flag = nullptr;
					break;
				}

			}
			s.erase(0,pos+1);
		}

		if (count == 1 && f == true) // if the captured position was located in root
		{
			root->addChild(q);
			positions.addBack(q);
			bin.dequeue();
		}
		if (flag!=nullptr)
		{
			string str = path;
			string s = p_name;
			size_t found = str.find(s);

			string folderpath = path.substr(0, found);
			// cout<<path<<endl;
			// cout<<folderpath<<endl;

			// Position* a = curr;
			// curr = flag;
			// curr
			flag->addChild(q);
			positions.addBack(q);
			bin.dequeue();
		}
	}
	else
	{
		cout<<"The bin is empty"<<endl;
	}
}
//=================================================
string Tree::getPath(Position* p) // too late, returns the path of the given position
{
	CStack myStack;
	while(p->Parent!=NULL)
	{
			// cout<<"Hello"<<endl;
		myStack.push(p->name);
		p = p->Parent;
	}

	string path;

	if (myStack.empty())
	{
		path = root->name;
	}

	while (myStack.empty() == false)
	{
		path += "/";
		path += myStack.top();
		myStack.pop();
	}
	return path;
}
//=================================================
string Tree::preOrder(Position* p) // returns a string containing the content of all the positions using pre-order traversal
{
	string data = getPath(p)+","+to_string(p->size)+","+p->date+"\n";

	PositionList::iterator i = p->Children.begin();
	
	while(i!=p->Children.end())
	{
		data += preOrder(i.v->p);
		++i;
	}
	return data;
}
//=================================================
void Tree::dumpData() // dumps data into the file
{
	string path = "vfs.dat";
	ofstream fout(path);
	if (fout.is_open())
	{
		fout<<preOrder(root);	
		fout.close();
	}
}
//=================================================
void Tree::loadData()
{
	ifstream fin("vfs.dat");
	if (fin.is_open())
	{
		string text;
		bool folder;
		while (fin>>text)
		{
			stringstream s(text);
			string path, size, date;
			getline(s,path,',');
			getline(s,size,',');
			getline(s,date,'\n');

			if (path == "/")
			{
				root->date = date;
				continue;
			}
			
			string temp = path + '/';
			string delimiter = "/";

			size_t pos = 0;
			string token; // name of the file/folder
			while ((pos = temp.find(delimiter)) != string::npos)
			{
   				token = temp.substr(0, pos);
    			temp.erase(0, pos + delimiter.length());
			}

			if (token.find('.')!=-1) // check if the position is a file/folder
			{
				folder = false;
			}
			else
			{
				folder = true;
			}
			int idx = path.find(token);
			string par = path.substr(0, idx-1); // path of the parent of the position
			if (par.length()==0) // if the path is root, create a directory/file in the root
			{
				Position* temp = curr;
				curr = root;
				if (folder == true)
				{
					
					Position* new_fol = new Position(token, date, stoi(size), true);
					mkdir_p(new_fol);
				}
				else
				{
					Position* new_file = new Position(token, date, stoi(size), false);
					touch_p(new_file);
				}
				curr = temp;
				continue;
			}
			
			cd_path(par); // if the path is not root, go to that path and create a folder/file there
			// cout<<par<<endl;
			if (folder == true)
			{
				Position* new_fol = new Position(token, date, stoi(size), true);
				mkdir_p(new_fol);
			}
			else
			{
				Position* new_file = new Position(token, date, stoi(size), false);
				touch_p(new_file);
			}
		}
		curr = root; // change current path to root
		prev = root; // change prev to root
		fin.close();
	}
}
//=================================================
void Tree::mkdir_p(Position* p) // create a directory from position
{
	string foldername = p->name;
	if (uniqueName(foldername) == true && validFolderName(foldername) == true)
	{
		if (curr->folder == true)
		{
			p->Parent = curr;
			curr->addChild(p);
			positions.addBack(p);
		}
	}
}
//=================================================
void Tree::touch_p(Position* p) // create a file from position
{
	string filename = p->name;
	if (uniqueName(filename) == true && validFileName(filename) == true)
	{
		if (curr->folder == true)
		{
			p->Parent = curr;
			curr->addChild(p);
			positions.addBack(p);
		}
	}
}
//=================================================
