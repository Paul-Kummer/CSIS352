// File: README.txt
// Name: Paul Kummer
// Class: CSIS 352
// Program: prog2
// Modified: 1/22/21


	-[Description]-
prog2 creates doubly ended queues. The first Deque, the user can interactivly
manipulate the Deque by specifying what command they want to perform. Upon exit, the
assignment operater and copy constructor are tested along with dumps of all deques.


	-[Inputs]- (input method : input type : description)
1.) keyboard : integers : integers entered by user to select commands and insert values.

2.) command prompt : make test : enters predetermined test commands.

	-[Outputs]- (output method : output type : description)
1.) display : string : text displayed on monitor showing the results of user commands


	-[Design]-
This program takes user input as commands to perform methods of the Deque class. These
commands will assign pointers to the front and back of a doubly linked node list. The
commands will also allow viewing of the the front and back nodes in both a destructive
and non destructive manner. When using destructive viewing, the nodes pointer will be 
set to null and the pointer will be deleted. Deques will be allowed to be of any data 
type and can be copied or assigned from another Deque of the same data type. In this 
program all nodes and Deques are of the data type integer.



	-[Files] (file : function : description)-
main.cpp : main : executes the main line of logic

deque.h : declarations and definitions : declares and defines the node struct and Deque class

makefile : compilation & linking : creates an executable of prog2

README.txt : information : gives detailed information about prog2

test.txt : test prog2 Deque class : tests commands on prog2, showing functionality of Deque



	-[Testing]-
The Deque class has had all its methods tested with valid values. It has not been extensivly
tested with invalid values or other data types other than integers.


	-[Bugs]-
1.) When the Deque is empty, popFront, popRear, front, rear, and dump will all ouput a random
    value for whatever node corresponds to the method.

