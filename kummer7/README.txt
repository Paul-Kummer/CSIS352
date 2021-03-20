// File: README.txt
// Name: Paul Kummer
// Class: CSIS 352
//Program: prog7
//Modified: 02/23/21


	-[Description]-
prog7 is an implementation of the Josephus Problem. The user controls the setup of the ring of people.
They will specify how many people, the starting person, the skip number, and optionally give the people
names. After the program is setup, the user can then begin the execution process. One lucky survior will
have their position and name outputted.


	-[Inputs]- (input method : input type : description)
1.) keyboard : int : values interpreted as commands to perform ring of people.
2.) test.txt : text file : a text file can be input as a command line argument. This file should hold
							operation commands and values for operations that require additonal input


	-[Outputs]- (output method : output type : description)
1.) display : string : text displayed on monitor showing actions on the ModArray


	-[Design]-
The program is desinged with two types of lists. The first is a modular array, and holds values of ints 
that represent index locations of people in the other list. The other list is a vector, and holds person
objects. Each Person object has their starting location, name, and their life status.

After the user has supplied the number of people, starting person, and number to skip, They can start
the executions. During the executions, the program will start at the index of one minus the user supplied
starting position. This will convert spoken language into an index location. Then, from that index, an
iterator will advance the skip number. The value at that location is removed from the modArray, and the associated
person in the vector will have their life status set to false. Then the process will keep repeating from whatever
index it lands on, even after circling back to the beginning of the modular array hold index values. The process
is complete when the modular array only has one value left. That value at index zero is the index of the last 
surving person in the Person vector.

The entire duration of the program will have user prompts for all options the user can perform. When bad data 
is entered, the user will be told it's bad data and be forced to enter new data. During the executions, the
user will be shown who is being executed. After the executions, the program will go back to the initial command 
prompts at the beginning, and have to reinitialize the execution ring.


	-[Unimplemented Design]-
Instead of having two seperate lists of information, one ModArray could be used to store Person objects.
Initially the ModArray didn't support the Person object, but near the end of development, the ability was
added. However, instead of possibly implementing new errors in the program, the original design of two lists were
used.

To change to a singular ModArray, the vector can be removed and the data type for ModArray can be changed
to Person. Either people can be removed from the modArray the same way the index locatations were removed,
or the people can be set to dead and the execution process can be modified to not count the dead when skipping
people.


	-[Files] (file : function : description)-
main.cpp : main : executes the main line of logic, allowing the user to input operations

modArray.h : ModArray definition/declaration : Creates an modArray namespace that contains the class ModArray and ArrIterator

prototypes.h : declaration : declares the selectOperation function and the Person class

operations.cpp : definition : defines the function selectOperation, which selects an operation to be performed on a ModArray

people.cpp : definition : defines the Person class to be used in a vector

makefile : compilation & linking : creates and executable of prog5

README.txt : information : gives detailed information about prog5

test.txt : test user input : creates user input from a text file

test2.txt : test user input : creates user inputs from a text file, small than test.txt


	-[Testing]-
The test files try all the functions of the user options of the program with valid data and invalid data.
Some of the invalid data consists of strings where there should be integers, excessively large numbers,
negative numbers, and symbols. The program has been shown to handle many forms of input.


	-[Bugs]-
1) no known bugs