# Virtual Filesystem
The Virtual Filesystem (VFS) is a project that aims to replicate a filesystem in a virtual environment. It allows users to interact with folders and files through a command-line like interface. The filesystem is organized as a tree structure, with inodes containing metadata about nodes. This README provides an overview of the project's features and instructions on running the program.

## Overview
The VFS project has the following features:
- Create, delete, and move folders and files.
- Organize the filesystem as a tree structure.
- Utilize inodes to store metadata about nodes.
- Handle file deletion through a limited-size queue (Bin/Trash).

The program is designed using object-oriented programming (OOP) principles and custom data structures, with no use of STL-based containers.

## Instructions to Run
- Open a terminal and navigate to the src folder within project directory using the cd command.
- Build the project using the provided makefile. Run the following command in the terminal: `make`.
- Once the project is successfully built, run the generated executable using the terminal: `./output`.
- The Virtual Filesystem application will launch. Follow the on-screen instructions to interact with the program.

## Commands
The program's command-line interface offers the following commands:
- `help`: Prints a menu of available commands.
- `pwd`: Prints the current inode's path.
- `realpath filename`: Prints the absolute/full path of a given filename of a file within the current directory.
- `ls`: Lists children of the current inode (folders/files).
- `mkdir foldername`: Creates a new folder under the current folder.
- `touch filename size`: Creates a file under the current inode location with the specified filename, size, and
current datetime.
- `cd foldername`: Changes current inode to the specified folder.
- `cd ..`: Changes current inode to its parent folder.
- `cd -`: Changes current inode to the previous working directory.
- `cd`: changes current inode to root.
- `find foldername` or `find filename`: Returns the path of the given file or folder.
- `mv filename foldername`: Moves a file located under the current inode location, to the specified folder path.
- `rm foldername` or `rm filename`: Removes a file or folder and adds it to the Bin.
- `size foldername` or `size filename`: Returns the size of a folder or file.
- `emptybin`: Empties the Bin.
- `showbin`: Shows the oldest Bin inode.
- `exit`: Exits the program and saves the filesystem.
