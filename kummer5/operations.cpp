//File: operations.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog5
//Modified: 02/11/21

#include <string>
#include <new>
#include <exception>
#include <iomanip>
#include <iostream>
#include "prototypes.h"



/*
Description: This file defines the function selectOperation, which will perform user chosen actions
				on a modArray.
*/


//define selectOperation, which will perform user selected actions on an vector
//precondition: newArr must be initialized
//postcondition: 
//		vector has any of it's methods performed on it, possibly altering the vector
//		Boolean is returned, which is true unless the user choose 0 to quit the program
bool selectOperation(int opNumber, modArray::ModArray<int>& newArr, std::ifstream* testFile)
{
	int opSelect; //the operation that will be performed, determined by switch statement
	int userIn; //temporary value holder for integers to be inserted into the vector
	int userInTwo;
	bool promptUser = true; //sentinel for determining if operations should still be done the vector

	//determines what operation the user wanted to perform
	switch(opNumber)
	{
		case 1: //first value from the Vector
		{
			try
			{
				std::cout << "\tFirst Value: " << newArr.front() << std::endl << std::endl;
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

		case 2: //last value from the Vector
		{
			try
			{
				std::cout << "\tLast Value: " << newArr.back() << std::endl << std::endl;
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
			
		case 3: //pop last value from the Vector
		{
			try
			{
				std::cout << "\tLast Value [" << newArr.back() << "] Removed. " << std::endl << std::endl;
				newArr.pop_back();			
			}
			catch(const std::length_error &e)
			{
				std::cerr << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
			break;
		}

		case 4: //check the vector size
		{
			std::cout << "\tNumber of Elements: " << newArr.size() << std::endl << std::endl;
			break;
		}

		case 5: //check if vector is empty
		{
			std::string emptyVector = newArr.empty()? "True":"False";
			std::cout << "\tIs the Vector Empty: " << emptyVector << std::endl << std::endl;
			break;			
		}

		case 6: //insert a value into the vector
		{
			try
			{
				std::cout << "\tEnter and interger to insert into the Vector" << std::endl << "\tEnter an Integer: ";
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
				newArr.insert(newArr.begin(),userIn);
			}
			catch(const std::exception& e)
			{
				//possible error of attempting to allocate too much memory
				std::cerr << e.what() << '\n';
			}
			break;
		}

		case 7: //view information about the current Vector and its nodes
		{
			newArr.dump();
			break;
		}

		case 8: //subscript operator to get value at index
		{
			try
			{
				std::cout << "\t### Enter index of value to retrieve ###" << std::endl << "\tEnter an Integer: ";
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
				std::cout << "\tValue at Index [ " << userIn << " ]: " << newArr[userIn] << std::endl << std::endl;
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
				std::cout << "\t### Enter index of value to change ###" << std::endl << "\tEnter an Integer: ";
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

				std::cout << "\t### Enter the new value ###" << std::endl << "\tEnter New Integer Value: ";
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

				newArr[userIn] = userInTwo;
				std::cout << "\tValue at Index [ " << userIn << " ]: " << newArr[userIn] << std::endl << std::endl;
			}
			catch(const std::invalid_argument& e)
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

			std::cout << "\n\n**************************** BEGIN EXIT TESTS ********************************\n\n";
			//display the Vector that the user just manipulated
			std::cout << std::endl << "\t*The original Vector" << std::endl;
			newArr.dump();

			//assign the Vector the user just created to a new Vector and display it
			std::cout << std::endl << "\t*test assignment operator=" << std::endl;
			modArray::ModArray<int> assignVector = modArray::ModArray<int>();
			std::cout << "\t*Variable assignVector Initialized" << std::endl;
			assignVector = newArr;
			std::cout << "\t*Variable assignVector assigned values from newArr" << std::endl;
			assignVector.dump();

			//copy the Vector that was just created into a new Vector and display it
			std::cout << std::endl << "\t*test copy constructor" << std::endl;
			modArray::ModArray<int> copyVector = modArray::ModArray<int>(assignVector);
			std::cout << "\t*Variable copyVector Initialized with copy constructor with assignVector as parameter" << std::endl;
			copyVector.dump();

			//create new vectors with parameter assigments
			std::cout << std::endl << "\t*test parameter constructor" << std::endl;
			modArray::ModArray<int> paramVector = modArray::ModArray<int>(10);
			std::cout << "\t*Variable paramVector Initialized with 10 elements" << std::endl;
			paramVector.dump();

			std::cout << "\t*Inserting Values into paramVector by index paramVector[index] = value" << std::endl;
			std::cout << "-paramVector[-1] = -1;" << std::endl;
			paramVector[-1] = -1;
			std::cout << "-paramVector[1] = 1;" << std::endl;
			paramVector[1] = 1;
			std::cout << "-paramVector[4] = 4;" << std::endl;
			paramVector[4] = 4;
			std::cout << "-paramVector[-15] = -15;" << std::endl;
			paramVector[-15] = -15;
			std::cout << "-paramVector[22] = 22;" << std::endl;
			paramVector[22] = 22;
			paramVector.dump();

			//attempt to create an vector with an invalid parameter
			std::cout << std::endl << "\t*test parameter constructor with bad parameter" << std::endl;
			try
			{
				modArray::ModArray<int> badArr = modArray::ModArray<int>(-3);
				badArr.dump();
			}
			catch(const std::length_error &e)
			{
				std::cerr << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
		
			std::cout << "\n\n**************************** END EXIT TESTS ********************************\n\n";

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