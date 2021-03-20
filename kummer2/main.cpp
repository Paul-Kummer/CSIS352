//File: main.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog2
//Modified: 1/22/21

/*
Description:
this program creates doubly ended queues. The first Deque, the user can interactivly
manipulate the Deque by specifying what command they want to perform. Upon exit, the
assignment operater and copy constructor are tested along with dumps of all deques.
*/


#include "deque.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
		cout <<         "************************************************************" << endl
		     << endl << "           Programmed By: Paul Kummer" << endl 
			 << endl
		     <<         "This program will let you interactivly modify a doubly ended" << endl 
			 <<         "queue. Then it will perform some test operations on exit" << endl 
			 << endl
		     <<         "************************************************************" << endl 
			 << endl;

	bool promptUser = true; //sentinel for determining if operations should still be done the deque
	int dequeOperation; //the operation that will be performed, determined by switch statement
	int valueToPlace; //temporary value holder for integers to be inserted into the deque
	Deque<int> newDeque = Deque<int>(); //the deque that will be manipulated
	cout << "\t*Variable newDeque Initialized" << endl;

	//loop that will allow user to continue executing commands on the deque
	while (promptUser)
	{
		//give the user a list of options
		cout << "Manipulate the Deque:" << endl << "(1)popFront; (2)popBack; (3)front; (4)back; (5)pushFront; (6)pushBack; (7)dump; (0)exit" << endl << "Enter First Unit: ";
		
		//clear the input stream so that the make test can run properly
		cin.clear();
		//make sure that the user enters proper integer
		if(!(cin >> dequeOperation))
		{
			//causes the default case to execute on switch statement
			dequeOperation = -1;
		}

		//determines what operation the user wanted to perform
		switch(dequeOperation)
		{
			case 1: //pop the front value from the deque
			{
				cout << "\tValue removed from the Front: " << newDeque.popFront() << endl;
				break;
			}
				
			case 2: //pop the back value from the deque
			{
				cout << "\tValue removed from the Back: " << newDeque.popRear() << endl;
				break;
			}

			case 3: //view the front value
			{
				cout << "\tValue from the Front: " << newDeque.front() << endl;
				break;
			}

			case 4: //view the back value
			{
				cout << "\tValue from the Back: " << newDeque.rear() << endl;
				break;			
			}

			case 5: //insert a value to the front of the deque
			{
				cout << "\tEnter and interger to insert at the Front" << endl << "\tEnter an Integer: ";
				cin.clear();
				cin >> valueToPlace;
				newDeque.pushFront(valueToPlace);
				break;
			}

			case 6: //insert a value to the rear of the deque
			{
				cout << "\tEnter and interger to insert at the Back" << endl << "\tEnter an Integer: ";
				cin.clear();
				cin >> valueToPlace;
				newDeque.pushRear(valueToPlace);
				break;
			}

			case 7: //view information about the current deque and its nodes
			{
				newDeque.dump();
				break;
			}

			case 0: //exit the program and run some additional tests
			{
				promptUser = false;

				//display the deque that the user just manipulated
				cout << endl << "\t*original Deque created" << endl;
				newDeque.dump();

				//assign the deque the user just created to a new deque and display it
				cout << endl << "\t*test assignment operator=" << endl;
				Deque<int> assignDeque = Deque<int>();
				cout << "\t*Variable assignDeque Initialized" << endl;
				assignDeque = newDeque;
				cout << "\t*Variable assignDeque assigned values from newDeque" << endl;
				assignDeque.dump();

				//copy the deque that was just created into a new deque and display it
				cout << endl << "\t*test copy constructor" << endl;
				Deque<int> copyDeque = Deque<int>(assignDeque);
				cout << "\t*Variable copyDeque Initialized with copy constructor with assignDeque as parameter" << endl;
				copyDeque.dump();

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

	return 0;
}