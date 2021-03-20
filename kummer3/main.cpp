// File: main.cpp
// Name: Paul Kummer
// Class: CSIS 352
// Program: prog3
// Modified: 01/29/21

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "minHeap.h"


/*
Description:
This program will create a min heap and let the user execute its methods to ensure that it operates correctly,
or the user can run a premade test by executing the program with (make test) at the command prompt
*/


using namespace std;

int main(int argc, char **argv)
{
		cout <<         "************************************************************" << endl
		     << endl << "           Programmed By: Paul Kummer"                        << endl 
			 << endl
		     <<         "This program will let you interactivly modify a min Heap."    << endl 
			 <<         "Then it will perform some test operations on exit"            << endl 
			 << endl
		     <<         "************************************************************" << endl 
			 << endl;

	bool promptUser = true; //sentinel for determining if operations should still be done the heap
	int minHeapOperation; //the operation that will be performed, determined by switch statement
	int valueToPlace; //temporary value holder for integers to be inserted into the heap
	heap::MinHeap<int> newMinHeap = heap::MinHeap<int>(); //the heap that will be manipulated
	cout << "\t*Variable newMinHeap Initialized" << endl;

	//run test file if user entered make test
	if(argc == 2)
	{
		string fileName = argv[1];
		ifstream testDoc;
		testDoc.open(fileName);
		int selection;

		while(!testDoc.eof())
		{
			testDoc >> selection;

			switch(selection)
			{
				case 1: //top value from the minHeap
				{
					cout << "\tValue at the Top: " << newMinHeap.top() << endl << endl;
					break;
				}
					
				case 2: //pop top value from the minHeap
				{
					cout << "\tValue removed from the Top: " << newMinHeap.pop() << endl << endl;
					break;
				}

				case 3: //check the heap size
				{
					cout << "\tNumber of Nodes: " << newMinHeap.size() << endl << endl;
					break;
				}

				case 4: //check if heap is empty
				{
					std::string emptyHeap = newMinHeap.isEmpty()? "True":"False";
					cout << "\tIs the Heap Empty: " << emptyHeap << endl << endl;
					break;			
				}

				case 5: //insert a value into the heap
				{
					cout << "\tInteger Inserted: " << endl << endl;
					cin.clear();
					testDoc >> selection;
					newMinHeap.insert(selection);
					break;
				}

				case 6: //view information about the current minHeap and its nodes
				{
					newMinHeap.dump();
					break;
				}

				case 0: //exit the program and run some additional tests
				{
					cout << endl << "\t--- Goodbye ---" << endl;
					
					break;
				}

				default: //user entered a bad command
				{
					cout << "\t*Unrecognized Command* Please Try Again" << endl;
					break;
				}
			}
		}

		testDoc.close();
	}

	//use user inputs
	else
	{
		//loop that will allow user to continue executing commands on the minHeap
		while (promptUser)
		{
			//give the user a list of options
			cout << "Manipulate the minHeap:" << endl << "(1)Top; (2)Pop; (3)Size; (4)Is_Empty; (5)Insert; (6)Dump; (0)Exit" << endl << "Enter Selection: ";
			
			//clear the input stream so that the make test can run properly
			cin.clear();
			//make sure that the user enters proper integer
			if(!(cin >> minHeapOperation))
			{
				//causes the default case to execute on switch statement
				minHeapOperation = -1;
			}

			//determines what operation the user wanted to perform
			switch(minHeapOperation)
			{
				case 1: //top value from the minHeap
				{
					cout << "\tValue at the Top: " << newMinHeap.top() << endl << endl;
					break;
				}
					
				case 2: //pop top value from the minHeap
				{
					cout << "\tValue removed from the Top: " << newMinHeap.pop() << endl << endl;
					break;
				}

				case 3: //check the heap size
				{
					cout << "\tNumber of Nodes: " << newMinHeap.size() << endl << endl;
					break;
				}

				case 4: //check if heap is empty
				{
					std::string emptyHeap = newMinHeap.isEmpty()? "True":"False";
					cout << "\tIs the Heap Empty: " << emptyHeap << endl << endl;
					break;			
				}

				case 5: //insert a value into the heap
				{
					cout << "\tEnter and interger to insert into the Heap" << endl << "\tEnter an Integer: ";
					cin.clear();
					cin >> valueToPlace;
					newMinHeap.insert(valueToPlace);
					break;
				}

				case 6: //view information about the current minHeap and its nodes
				{
					newMinHeap.dump();
					break;
				}

				case 0: //exit the program and run some additional tests
				{
					promptUser = false;
					
					//display the minHeap that the user just manipulated
					cout << endl << "\t*original MinHeap created" << endl;
					newMinHeap.dump();

					//assign the minHeap the user just created to a new minHeap and display it
					cout << endl << "\t*test assignment operator=" << endl;
					heap::MinHeap<int> assignMinHeap = heap::MinHeap<int>();
					cout << "\t*Variable assignMinHeap Initialized" << endl;
					assignMinHeap = newMinHeap;
					cout << "\t*Variable assignMinHeap assigned values from newMinHeap" << endl;
					assignMinHeap.dump();

					//copy the minHeap that was just created into a new minHeap and display it
					cout << endl << "\t*test copy constructor" << endl;
					heap::MinHeap<int> copyMinHeap = heap::MinHeap<int>(assignMinHeap);
					cout << "\t*Variable copyminHeap Initialized with copy constructor with assignminHeap as parameter" << endl;
					copyMinHeap.dump();

					cout << endl << "\t--- Goodbye ---" << endl;
					
					break;
				}

				default: //user entered a bad command
				{
					cout << "\t*Unrecognized Command* Please Try Again" << endl;
					break;
				}
			}
		}
	}

	return 0;
}