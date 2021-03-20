//File: operations.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog7
//Modified: 02/23/21

#include <string>
#include <math.h>
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
bool selectOperation(int opNumber, modArray::ModArray<int>& newArr, std::ifstream* testFile, int& numOfPeople, int& startPerson, int& skipNum)
{
	const int MAXSIZE = 10000000;
	std::string tmpInput; //hold user input as string to determine if it is a valid length
	int opSelect; //the operation that will be performed, determined by switch statement
	int userIn; //temporary value holder for integers to be inserted into the ModArray
	int userInTwo;
	bool promptUser = true; //sentinel for determining if operations should still be done the ModArray

	//determines what operation the user wanted to perform
	//(1)Set Number of People; (2)Set Starting Person; (3)Set Move Distance; (4)Begin Executions; (0)Exit
	switch(opNumber)
	{
		case 1: //set number of people
		{
			try
			{
				std::cout << "\n\tEnter the number of people" << std::endl << "\tEnter an Integer: ";
				std::cin.clear();
				if(testFile)
				{
					testFile->operator>>(userIn);
					std::cout << userIn << std::endl;
				}
				else
				{
					std::cin >> tmpInput;
					userIn = stoi(tmpInput, nullptr, 10);
				}

				if(userIn > MAXSIZE)
				{
					std::cout << "\t--- You Must Choose A Number Smaller Than " << MAXSIZE << " ---\n" << std::endl;
				}
				else
				{
					numOfPeople = userIn; //may not need this since it gets initialized right away
					newArr = modArray::ModArray<int>(userIn, true);
				}	
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

		case 2: //set the starting person, person 1 is index 0
		{
			try
			{
				std::cout << "\n\tEnter the starting person" << std::endl << "\tEnter an Integer: ";
				std::cin.clear();
				if(testFile)
				{
					testFile->operator>>(userIn);
					std::cout << userIn << std::endl;
				}
				else
				{
					std::cin >> tmpInput;
					userIn = stoi(tmpInput, nullptr, 10);
				}

				if(userIn > MAXSIZE)
				{
					std::cout << "\t--- You Must Choose A Number Smaller Than " << MAXSIZE << " ---\n" << std::endl;
				}
				else
				{
					startPerson = userIn>0?userIn:0;
				}
			}
			catch(const std::exception &e) //will most likely be a data type error
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
			break;
		}
			
		case 3: //set the number of people to skip
		{
			try
			{
				std::cout << "\n\tEnter the number to skip by" << std::endl << "\tEnter an Integer: ";
				std::cin.clear();
				if(testFile)
				{
					testFile->operator>>(userIn);
					std::cout << userIn << std::endl;
				}
				else
				{
					std::cin >> tmpInput;
					userIn = stoi(tmpInput, nullptr, 10);
				}

				if(userIn > MAXSIZE)
				{
					std::cout << "\t--- You Must Choose A Number Smaller Than " << MAXSIZE << " ---\n" << std::endl;
				}
				else
				{
					skipNum = userIn>0?userIn:0;
				}
			}
			catch(const std::exception &e) //will most likely be a data type error
			{
				std::cerr << "Unknown Exception: " << e.what() << '\n';
			}
			break;
		}

		case 4: //Start Executions
		{
			std::cout << "\n";
			if(numOfPeople > 0 && startPerson > 0 && skipNum >= 0)
			{
				std::cout << "\n\n**************************** Begin Executions ********************************\n\n";

				int removePos = (newArr.size() + (startPerson-1) + skipNum) % newArr.size();
				while(newArr.size()>1)
				{
					std::cout << "Eliminating: " << newArr[removePos] << std::endl;
					newArr.remove(removePos);
					removePos = (newArr.size() + removePos + skipNum) % newArr.size();
				}
				std::cout << "\n\n**************************** End Executions ********************************\n\n";
				
				std::cout << "\t[ The Survivor ]\n";
				std::cout << "The Survivor is at position: " << (newArr[0] + 1) << std::endl;
				std::cout << "\n****************************************************************************\n\n";
				
			}
			else
			{
				std::cout << "\t--- Please Specify the Following First; Number of People, Starting Person, and Skip Number ---\n";
			}
			numOfPeople = newArr.size();
			break;
		}

		case 5: //create array of people
		{
			/*
			int counter = 0;
			while(promptUser)
			{
				try
				{
					std::cout << "\n\tEnter the persons name" << std::endl << "\tEnter an Integer: ";
					std::cin.clear();
					if(testFile)
					{
						testFile->operator>>(userIn);
						std::cout << userIn << std::endl;
					}
					else
					{
						std::cin >> tmpInput;
						userIn = stoi(tmpInput, nullptr, 10);
					}

					if(userIn > MAXSIZE)
					{
						std::cout << "\t--- You Must Choose A Number Smaller Than " << MAXSIZE << " ---\n" << std::endl;
					}
					else
					{
						skipNum = userIn>0?userIn:0;
					}
				}
				catch(const std::exception &e) //will most likely be a data type error
				{
					std::cerr << "Unknown Exception: " << e.what() << '\n';
				}
			}
			promptUser = true;
			*/
			break;
		}

		case 0: //exit the program and run some additional tests
		{
			promptUser = false;
			break;
		}

		default: //user entered a bad command
		{
			std::cout << "\t*Unrecognized Command* Please Try Again\n" << std::endl;
			std::cin.clear();
			std::cin.ignore();
			break;
		}
	}

	return promptUser;
}