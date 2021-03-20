// File: README.txt
// Name: Paul Kummer
// Class: CSIS 352
// Program: prog4
// Modified: 02/04/21


	-[Description]-
prog4 creates an array of nodes of an abstract type and has user input to perform methods on that
array. The user can insert, view end, pop first, view size, check empty, find value at index, and dump the array. 
Additionally the user can run a premade test by using (make test) in the command prompt or specififying a text
document at the command prompt with a command per line in the text document.


	-[Inputs]- (input method : input type : description)
1.) keyboard : int : values interpreted as commands to perform or values to store in an array.
2.) file.txt : text file : a text file can be input as a command line argument. This file should hold
							operation commands and values for operations that require additonal input


	-[Outputs]- (output method : output type : description)
1.) display : string : text displayed on monitor showing actions on the array


	-[Design]-
This program will continously loop, prompting the user to enter commands to perform. As commands are entered
they will be carried out on the array created and have the action displayed to the user. When the program needs
to reach specific nodes, it will linearally call the left or right side of a node until the desired node location
is reached. Nodes can be of any valid data type, however the program only uses int values. There are multiple 
try catch blocks to handle errors that could be thrown, and some methods throw specified exceptions to allow
exception handling.


	-[Files] (file : function : description)-
main.cpp : main : executes the main line of logic, and contains and operationSelect defitiion and declaration

array.h : array definition/declaration and Node definition/declaration : Creates an array namespace that contains the array Class and node struct

makefile : compilation & linking : creates and executable of prog4

README.txt : information : gives detailed information about prog4

test.txt : test user input : creates user input from a text file


	-[Testing]-
the program has had all the methods called on it with and without nodes. All methods of array
have also been tested when only one value is in the array, meaning that the first node is 
also the last node and that node has left and right pointers set to null.


	-[Bugs]-
1.) user could enter a command line argument that isn't the test.txt and get unexpected results