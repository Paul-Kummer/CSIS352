// File: README.txt
// Name: Paul Kummer
// Class: CSIS 352
// Program: prog3
// Modified: 01/29/21


	-[Description]-
prog3 creates a min heap of nodes of an abstract type and has user input to perform methods on that
heap. The user can insert, view top, pop top, view size, check empty, and dump the min heap. Additionally
the user can run a premade test by using (make test) in the command prompt.


	-[Inputs]- (input method : input type : description)
1.) keyboard : int : values interpreted as commands to perform.


	-[Outputs]- (output method : output type : description)
1.) display : string : text displayed on monitor showing actions on the heap


	-[Design]-
This program will continously loop, prompting the user to enter commands to perform. As commands are entered
they will be carried out on the heap created and have the action displayed to the user. When the program needs
to reach specific nodes, it will recrusively call the left or right side of the nodes until the desired pareameters
are found.


	-[Files] (file : function : description)-
main.cpp : main : executes the main line of logic

minHeap.h : MinHeap definition/declaration and Node definition/declaration : Creates a heap namespace that contains the MinHeap Class and node struct

makefile : compilation & linking : creates and executable of prog3

README.txt : information : gives detailed information about prog3

test.txt : test user input : creates user input from a text file


	-[Testing]-
the program has had all the methods called on it with and without nodes. Values have also been
inserted in varying orders of ascending, descending, or random. This makes sure that parents
will always have a less than value than its children.


	-[Bugs]-
1.) user could enter a command line argument that isn't the test.txt and get unexpected results
2.) more checks for the root being null could be performed to make the code more effiecient and 
	avoid some patching that was done. The issue was arrising during pop() calls

