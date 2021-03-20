// File: README.txt
// Name: Paul Kummer
// Class: CSIS 352
// Program: prog5
// Modified: 02/11/21


	-[Description]-
prog5 creates a modular array of elements of an abstract type and has user input to perform methods on that
array. The user can insert, view first, view last, pop last, view size, check empty, find value at index, 
insert a value at an index, and dump the array. Additionally the user can run a premade test by using (make test)
in the command prompt or specififying a text document at the command prompt with a command per line in the text 
document. Upon exit, the program will run some default tests on the array and newly instantiated arrays. In
general, the ModArray class is an extention of the std::vector class from the STL. It does inherit from
std::vector, and should be used with caution. The main goal of ModArray is to provide error checking that
the vector class doesn't provide.


	-[Inputs]- (input method : input type : description)
1.) keyboard : int : values interpreted as commands to perform or values to store on/in ModArray.
2.) file.txt : text file : a text file can be input as a command line argument. This file should hold
							operation commands and values for operations that require additonal input


	-[Outputs]- (output method : output type : description)
1.) display : string : text displayed on monitor showing actions on the ModArray


	-[Design]-
This program will continously loop, prompting the user to enter commands to perform. As commands are entered
they will be carried out on the ModArray created and have the action displayed to the user. When the program needs
to reach specific elements, it will use std::vector's subscript operator to get to the location of the index.
Elements can be of any valid data type, however the program only uses int values. There are multiple 
try catch blocks to handle errors that could be thrown, and some methods throw specified exceptions to allow
exception handling.

For storing elements, the vector class from the STL is used. ModArray inherits from std::vector and overloads
some of its methods in order to provide error-checking.


	-[Files] (file : function : description)-
main.cpp : main : executes the main line of logic, allowing the user to input operations

modArray.h : ModArray definition/declaration : Creates an modArray namespace that contains the class ModArray, which is a modular array

prototypes.h : declaration : declares the selectOperation function

operations.cpp : definition : defines the function selectOperation, which selects an operation to be performed on a ModArray

makefile : compilation & linking : creates and executable of prog5

README.txt : information : gives detailed information about prog5

test.txt : test user input : creates user input from a text file


	-[Testing]-
The program has been tested with an empty ModArray and a full ModArray. the following have been tested
	-default constructor
	-parameter constructor
	-copy constructor
	-assignment operator
	-front()
	-back()
	-pop_back()
	-size()
	-empty()
	-const operator[]
	-operator[]
	-dump()
	-capacity()
	-max_size()
	-resize()


	-[Bugs]-
1.) When the user enters a non-integer at a prompt, the prompt will loop many times with invalid data