// File: README.txt
// Name: Paul Kummer
// Class: CSIS 352
//Program: prog7
//Modified: 02/23/21


	-[Description]-
prog6 creates a modular array of elements of an abstract type and has user input to perform methods on that
array. The user can insert, view first, view last, pop last, view size, check empty, find value at index, 
insert a value at an index, dump the array, iterate forward, and iterate backwards. Additionally the user 
can run a premade test by using (make test) in the command prompt or specififying a text document at the 
command prompt with a command per line in the text document. Upon exit, the program will run some default 
tests on the array and newly instantiated arrays. The main goal of ModArray is to provide error checking and
have indexing that will loop to the start or end of the array.


	-[Inputs]- (input method : input type : description)
1.) keyboard : int : values interpreted as commands to perform or values to store on/in ModArray.
2.) file.txt : text file : a text file can be input as a command line argument. This file should hold
							operation commands and values for operations that require additonal input


	-[Outputs]- (output method : output type : description)
1.) display : string : text displayed on monitor showing actions on the ModArray


	-[Design]-
This program will continously loop, prompting the user to enter commands to perform. As commands are entered
they will be carried out on the ModArray created and have the action displayed to the user. When the program needs
to reach specific elements in ModArray, it will used ModArray::ArrIterator, an iterator. The iterator keeps track
of what index is being accessed in the ModArray's list container and accesses the element at the index by using the
subscript operator of the ModArray object within the methods of the iterator. Elements can be of any valid data type, 
however the program only uses int values. There are multiple try catch blocks to handle errors that could be thrown, 
and some methods throw specified exceptions to allow exception handling.

All elements in modArray objects are stored interanally in an std::list<T> object.


	-[Files] (file : function : description)-
main.cpp : main : executes the main line of logic, allowing the user to input operations

modArray.h : ModArray definition/declaration : Creates an modArray namespace that contains the class ModArray and ArrIterator

prototypes.h : declaration : declares the selectOperation function

operations.cpp : definition : defines the function selectOperation, which selects an operation to be performed on a ModArray

makefile : compilation & linking : creates and executable of prog5

README.txt : information : gives detailed information about prog5

test.txt : test user input : creates user input from a text file


	-[Testing]-
The following are tested with make test either directly or indirectly.
	[ModArray]
	-default constructor
	-parameter constructor
	-copy constructor
	-subscript operator
	-pop_back
	-front
	-back
	-size
	-insert
	-empty
	-dump
	-begin
	-end

	[ModArray::ArrIterator]
	-parameter constructors
	-reference operator
	-pointer operator
	-postincrement operator
	-predecrement operator
	-addtion operator
	-subtraction operator
	-greater than operator
	-less than operator
	-not equal operator



	-[Bugs]-
1) no known bugs