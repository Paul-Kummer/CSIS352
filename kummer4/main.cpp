// File: main.cpp
// Name: Paul Kummer
// Class: CSIS 352
// Program: prog4
// Modified: 02/04/21

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "array.h"


/*
Description:
This program will create an array and let the user execute its methods to ensure that it operates correctly,
or the user can run a premade test by executing the program with (make test) or specifying a text document of 
each operation per line at the command prompt
*/


using namespace array;


//declaration of function used by main to select an operation to perform
//should move this to prototypes
bool selectOperation(int, Array<int>&, std::ifstream*);




//main line of logic the program performs
int main(int argc, char **argv)
{
	int opSelect; //the operation that will be performed, determined by a switch statement in selectOperation
	bool promptUser = true; //sentinel for determining if operations should still be done on the array
	Array<int> newArray = Array<int>(); //the array that will be manipulated


			    std::cout << "************************************************************" << std::endl
		     << std::endl << "           Programmed By: Paul Kummer"                        << std::endl 
			 << std::endl
		     <<              "This program will let you interactivly modify an array."      << std::endl 
			 <<              "Then it will perform some test operations on exit"            << std::endl
			 <<              "    *test 1: assignment operator                 "            << std::endl 
			 <<              "    *test 2: copy constructor                    "            << std::endl 
			 <<              "    *test 3: parameter constructor               "            << std::endl 
			 <<              "    *test 4: negative value param constructor    "            << std::endl 
			 << std::endl
		     <<              "************************************************************" << std::endl 
			 << std::endl;


	//run test file if user entered make test or a command line arg
	if(argc == 2)
	{
		try
		{
			std::string fileName = argv[1];
			std::ifstream testDoc;
			testDoc.open(fileName);
			int selection;

			while(!testDoc.eof())
			{
				testDoc >> opSelect;
				std::cout << "\tOperation Selected : " << opSelect << std::endl;
				promptUser = selectOperation(opSelect, newArray, &testDoc);
			}

			testDoc.close();
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

	//use user inputs
	else
	{
		//loop that will allow user to continue executing commands on the Array
		while (promptUser)
		{
			//give the user a list of options
			std::cout << "Manipulate the Array:" << 
			std::endl << "(1)First; (2)Last; (3)Pop; (4)Size; (5)Is_Empty; (6)Insert; (7)Dump; (8)getIndex; (9)insertAtIndex; (0)Exit" << 
			std::endl << "Enter Selection: ";
			
			//clear the input stream so that the make test can run properly
			while(!(std::cin >> opSelect))
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "\n\t-Bad Selection Try Again- \nEnter Selection: ";
			}

			//determines what operation the user wanted to perform
			promptUser = selectOperation(opSelect, newArray, nullptr);
		}
	}

	//inform the user of program closure
	std::cout << std::endl << "\t--- Goodbye ---" << std::endl;
	return 0;
}




//define selectOperation, which will perform user selected actions on an array
//precondition: newArray must be initialized
//postcondition: 
//		array has any of it's methods performed on it, possibly altering the array
//		Boolean is returned, which is true unless the user choosed 0 to quit the program
bool selectOperation(int opNumber, Array<int>& newArray, std::ifstream* testFile)
{
	int opSelect; //the operation that will be performed, determined by switch statement
	int userIn; //temporary value holder for integers to be inserted into the array
	int userInTwo;
	bool promptUser = true; //sentinel for determining if operations should still be done the array

	//determines what operation the user wanted to perform
	switch(opNumber)
	{
		case 1: //top value from the Array
		{
			try
			{
				std::cout << "\tFirst Value: " << newArray.begin() << std::endl << std::endl;
			}
			catch(const std::out_of_range &e)
			{
				std::cerr << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
			break;
		}

		case 2: //top value from the Array
		{
			try
			{
				std::cout << "\tLast Value: " << newArray.end() << std::endl << std::endl;
			}
			catch(const std::out_of_range &e)
			{
				std::cerr << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
			break;
		}
			
		case 3: //pop top value from the Array
		{
			try
			{
				std::cout << "\tFirst Value Removed: " << newArray.pop() << std::endl << std::endl;				
			}
			catch(const std::out_of_range &e)
			{
				std::cerr << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
			break;
		}

		case 4: //check the array size
		{
			std::cout << "\tNumber of Nodes: " << newArray.size() << std::endl << std::endl;
			break;
		}

		case 5: //check if array is empty
		{
			std::string emptyArray = newArray.isEmpty()? "True":"False";
			std::cout << "\tIs the Array Empty: " << emptyArray << std::endl << std::endl;
			break;			
		}

		case 6: //insert a value into the array
		{
			try
			{
				std::cout << "\tEnter and interger to insert into the Array" << std::endl << "\tEnter an Integer: ";
				std::cin.clear();
				if(testFile)
				{
					testFile->operator>>(userIn);
					std::cout << userIn << std::endl;
				}
				else
				{
					std::cin >> userIn;
				}
				newArray.insert(userIn);
			}
			catch(const std::exception& e)
			{
				//possible error of attempting to allocate too much memory
				std::cerr << e.what() << '\n';
			}
			break;
		}

		case 7: //view information about the current Array and its nodes
		{
			newArray.dump();
			break;
		}

		case 8: //get value at index
		{
			try
			{
				std::cout << "\tEnter index of value to retrieve" << std::endl << "\tEnter an Integer: ";
				std::cin.clear();
				if(testFile)
				{
					testFile->operator>>(userIn);
					std::cout << userIn << std::endl;
				}
				else
				{
					std::cin >> userIn;
				}
				std::cout << "\tValue at Index [ " << userIn << " ]: " << newArray[userIn] << std::endl << std::endl;
			}
			catch(const std::out_of_range& e)
			{
				std::cerr << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
			break;
		}

		case 9: //change value at index
		{
			try
			{
				std::cout << "\tEnter index of value to change: " << std::endl;
				std::cin.clear();
				if(testFile)
				{
					testFile->operator>>(userIn);
					std::cout << userIn << std::endl;
				}
				else
				{
					std::cin >> userIn;
				}

				std::cout << "\tEnter the new value: " << std::endl;
				std::cin.clear();
				if(testFile)
				{
					testFile->operator>>(userInTwo);
					std::cout << userInTwo << std::endl;
				}
				else
				{
					std::cin >> userInTwo;
				}

				newArray[userIn] = userInTwo;
				std::cout << "\tValue at Index [ " << userIn << " ]: " << newArray[userIn] << std::endl << std::endl;
			}
			catch(const std::out_of_range& e)
			{
				std::cerr << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
			break;
		}

		case 0: //exit the program and run some additional tests
		{
			promptUser = false;
			
			//display the Array that the user just manipulated
			std::cout << std::endl << "\t*The original Array" << std::endl;
			newArray.dump();

			//assign the Array the user just created to a new Array and display it
			std::cout << std::endl << "\t*test assignment operator=" << std::endl;
			Array<int> assignArray = Array<int>();
			std::cout << "\t*Variable assignArray Initialized" << std::endl;
			assignArray = newArray;
			std::cout << "\t*Variable assignArray assigned values from newArray" << std::endl;
			assignArray.dump();

			//copy the Array that was just created into a new Array and display it
			std::cout << std::endl << "\t*test copy constructor" << std::endl;
			Array<int> copyArray = Array<int>(assignArray);
			std::cout << "\t*Variable copyArray Initialized with copy constructor with assignArray as parameter" << std::endl;
			copyArray.dump();

			//create new arrays with parameter assigments
			std::cout << std::endl << "\t*test parameter constructor" << std::endl;
			Array<int> paramArray = Array<int>(10);
			std::cout << "\t*Variable paramArray Initialized with 10 elements" << std::endl;
			paramArray.dump();

			std::cout << "\t*Inserting Values into paramArray by index paramArray[index] = value" << std::endl;
			paramArray[-1] = -1;
			paramArray[1] = 1;
			paramArray[4] = 4;
			paramArray[-5] = -5;
			paramArray.dump();

			//attempt to create an array with an invalid parameter
			std::cout << std::endl << "\t*test parameter constructor with bad parameter" << std::endl;
			try
			{
				Array<int> badArr = Array<int>(-3);
			}
			catch(const std::bad_array_new_length)
			{
				std::cerr << "The array was not initialized: Bad Parameter" << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
			break;
		}

		default: //user entered a bad command
		{
			std::cout << "\t*Unrecognized Command* Please Try Again" << std::endl;
			std::cin.clear();
			std::cin.ignore();
			break;
		}
	}

	return promptUser;
}