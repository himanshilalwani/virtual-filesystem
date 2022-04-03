all: output

output: main.o tree.o stack.o node.o mylinkedlist.o position.o positionlist.o queue.o snode.o
		g++ main.o tree.o stack.o node.o mylinkedlist.o position.o positionlist.o queue.o snode.o -o output

main.o: main.cpp tree.h stack.h mylinkedlist.h snode.h queue.h position.h positionlist.h node.h
	g++ -c main.cpp

tree.o: tree.cpp position.h queue.h stack.h node.h
	g++ -c tree.cpp

stack.o: stack.cpp mylinkedlist.h position.h
	g++ -c stack.cpp

node.o: node.cpp position.h
	g++ -c node.cpp

mylinkedlist.o: mylinkedlist.cpp snode.h
	g++ -c mylinkedlist.cpp

position.o: position.cpp positionlist.h
	g++ -c position.cpp

positionlist.o: positionlist.cpp
	g++ -c positionlist.cpp

queue.o: queue.cpp
	g++ -c queue.cpp

snode.o: snode.h
	g++ -c snode.cpp