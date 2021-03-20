//File: operations.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog6
//Modified: 02/18/21

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


//define selectOperation, which will perform user selected actions on a ModArray
//precondition: newArr must be initialized
//postcondition: 
//		ModArray has any of it's methods performed on it, possibly altering the ModArray
//		Boolean is returned, which is true unless the user choose 0 to quit the program
bool selectOperation(int opNumber, modArray::ModArray<int>& newArr, std::ifstream* testFile)
{
	int opSelect; //the operation that will be performed, determined by switch statement
	int userIn; //temporary value holder for integers to be inserted into the ModArray
	int userInTwo;
	bool promptUser = true; //sentinel for determining if operations should still be done the ModArray

	//determines what operation the user wanted to perform
	switch(opNumber)
	{
		case 1: //first value from the ModArray
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

		case 2: //last value from the ModArray
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
			
		case 3: //pop last value from the ModArray
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

		case 4: //check the ModArray size
		{
			std::cout << "\tNumber of Elements: " << newArr.size() << std::endl << std::endl;
			break;
		}

		case 5: //check if ModArray is empty
		{
			std::string emptyModArray = newArr.empty()? "True":"False";
			std::cout << "\tIs the ModArray Empty: " << emptyModArray << std::endl << std::endl;
			break;			
		}

		case 6: //insert a value into the ModArray
		{
			try
			{
				std::cout << "\tEnter and interger to insert into the ModArray" << std::endl << "\tEnter an Integer: ";
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
				newArr.insert(userIn);
			}
			catch(const std::exception& e)
			{
				//possible error of attempting to allocate too much memory
				std::cerr << e.what() << '\n';
			}
			break;
		}

		case 7: //view information about the current ModArray and its nodes
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

		case 10:
		{
			try
			{
				std::cout << "\t### Enter how many indexs to increment ###" << std::endl << "\tEnter An Integer: ";
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
				
				std::cout << "\t(Stepping values less than one will loop forever)" << std::endl;
				std::cout << "\t### Enter index step value ###" << std::endl << "\tEnter An Integer: ";
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
				
				modArray::ModArray<int>::ArrIterator it = newArr.begin();
				std::cout << "\n( ";
				if(userInTwo < 1)
				{
					for (it; true ; it++)
					{
						std::cout << " " << *it << ",";
					}
				}

				else
				{
					for (it; it < userIn; it + userInTwo)
					{
						std::cout << " " << *it << ",";
					}
				}
				std::cout << ")\n ";
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

		case 11:
		{
			try
			{
				std::cout << "\t### Enter how many indexs to decrement ###" << std::endl << "\tEnter An Integer: ";
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
				
				std::cout << "\t(Stepping values less than one will loop forever)" << std::endl;
				std::cout << "\t### Enter index step value ###" << std::endl << "\tEnter An Integer: ";
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
				
				modArray::ModArray<int>::ArrIterator it = newArr.begin();
				std::cout << "\n( ";				
				if(userInTwo < 1)
				{
					for (it; true ;--it)
					{
						std::cout << " " << *it << ",";
					}
				}

				else
				{
					for (it; it > (-1*userIn); it - userInTwo)
					{
						std::cout << " " << *it << ",";
					}
				}
				std::cout << ")\n ";
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
			}
			break;
		}

		case 0: //exit the program and run some additional tests
		{
			promptUser = false;

			std::cout << "\n\n**************************** BEGIN EXIT TESTS ********************************\n\n";
			//display the ModArray that the user just manipulated
			std::cout << std::endl << "\t*The original ModArray" << std::endl;
			newArr.dump();

			//assign the ModArray the user just created to a new ModArray and display it
			std::cout << std::endl << "\t*test assignment operator=" << std::endl;
			modArray::ModArray<int> assignModArray = * new modArray::ModArray<int>();
			std::cout << "\t*Variable assignModArray Initialized" << std::endl;
			assignModArray = newArr;
			std::cout << "\t*Variable assignModArray assigned values from newArr" << std::endl;
			assignModArray.dump();

			//copy the ModArray that was just created into a new ModArray and display it
			std::cout << std::endl << "\t*test copy constructor" << std::endl;
			modArray::ModArray<int> copyModArray = * new modArray::ModArray<int>(assignModArray);
			std::cout << "\t*Variable copyModArray Initialized with copy constructor with assignModArray as parameter" << std::endl;
			copyModArray.dump();

			//create new ModArrays with parameter assigments
			std::cout << std::endl << "\t*test parameter constructor" << std::endl;
			modArray::ModArray<int> paramModArray = * new modArray::ModArray<int>(10);
			std::cout << "\t*Variable paramModArray Initialized with 10 elements" << std::endl;
			paramModArray.dump();

			std::cout << "\t*Inserting Values into paramModArray by index paramModArray[index] = value" << std::endl;
			std::cout << "-paramModArray[-1] = -1;" << std::endl;
			paramModArray[-1] = -1;
			std::cout << "-paramModArray[1] = 1;" << std::endl;
			paramModArray[1] = 1;
			std::cout << "-paramModArray[4] = 4;" << std::endl;
			paramModArray[4] = 4;
			std::cout << "-paramModArray[-15] = -15;" << std::endl;
			paramModArray[-15] = -15;
			std::cout << "-paramModArray[22] = 22;" << std::endl;
			paramModArray[22] = 22;
			paramModArray.dump();

			//attempt to create a ModArray with an invalid parameter
			std::cout << std::endl << "\t*test parameter constructor with bad parameter" << std::endl;
			try
			{
				modArray::ModArray<int> badArr = * new modArray::ModArray<int>(-3);
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