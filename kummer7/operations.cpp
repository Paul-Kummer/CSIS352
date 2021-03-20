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
Description: 
This file defines the function selectOperation, which will perform user chosen actions
on the execution ring
*/


//define selectOperation, which will perform user selected actions on a ModArray
//precondition: newArr must be initialized
//postcondition: 
//		newArr elements will be modified
//		people elements will be modified
//      user will be prompted
//		testFile will be read and incremented
//		numOfPeople will be modified
//		startPerson will be modified
//		skipNum will be modified
bool selectOperation(int opNumber, modArray::ModArray<int>& newArr, std::ifstream* testFile, int& numOfPeople, int& startPerson, int& skipNum, std::vector<Person>& people)
{
	const int MAXSIZE = 10000000; //the maximum size a entry can be
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
				if(testFile && *testFile >> tmpInput)
				{
					userIn = std::stoi(tmpInput);
					std::cout << userIn << std::endl;
				}
				else
				{
					std::cin >> tmpInput;
					userIn = stoi(tmpInput, nullptr, 10); //throws error if string exceeds int maximum
				}

				if(userIn > MAXSIZE) //don't allow values larger than defined maxsize
				{
					std::cout << "\t--- You Must Choose A Number Smaller Than " << MAXSIZE << " ---\n" << std::endl;
				}
				else
				{
					numOfPeople = userIn; //may not need this since it gets initialized right away
					newArr = modArray::ModArray<int>(userIn, true);
					people.clear();

					for(auto it=newArr.begin(); it!=newArr.end(); it++)
					{
						int placement = *it + 1;
						people.emplace_back(Person(placement));
					}
				}	
			}
			catch(const std::length_error &e)
			{
				std::cerr << e.what() << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "--- Exception --- " << e.what() << '\n';
			}
			break;
		}

		case 2: //set the starting person, person 1 is index 0
		{
			try
			{
				std::cout << "\n\tEnter the starting person" << std::endl << "\tEnter an Integer: ";
				std::cin.clear();
				if(testFile && *testFile >> tmpInput)
				{
					userIn = std::stoi(tmpInput);
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
				if(testFile && *testFile >> tmpInput)
				{
					userIn = std::stoi(tmpInput);
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

		case 4: //name a person at an index
		{
			if(people.size() > 0)
			{
				int counter = 0;
				while(promptUser)
				{
					try
					{
						std::cout << "\n\tEnter the persons position (0 stops)" << std::endl << "\tEnter Position: ";
						std::cin.clear();
						if(testFile && *testFile >> tmpInput)
						{
							userIn = std::stoi(tmpInput);
							std::cout << userIn << std::endl;
						}
						else
						{
							std::cin >> tmpInput;
							userIn = stoi(tmpInput, nullptr, 10);
						}

						if(userIn > 0)
						{
							std::cout << "\n\tEnter the persons name" << std::endl << "\tEnter Name: ";
							std::cin.clear();
							if(testFile && *testFile >> tmpInput)
							{
								std::cout << tmpInput << std::endl;
							}
							else
							{
								std::cin.ignore();
								getline(std::cin, tmpInput, '\n');
							}
							people[(userIn-1)].setName(tmpInput); //adjust for index of zero, vectors cannot be indexed backwards, change to modArray in future.
						}
						else if(userIn == 0)
						{
							promptUser = false;
						}
						else
						{
							std::cout << "\t--- The User Position Must Be A Positive Integer ---" << std::endl;
						}
					}
					catch(const std::out_of_range &e)
					{
						std::cerr << e.what() << '\n';
					}
					catch(const std::exception &e) //will most likely be a data type error
					{
						std::cerr << "Unknown Exception: " << e.what() << '\n';
					}
				}
				promptUser = true;
			}
			else
			{
				std::cout << "\t--- There are no People to Name ---" << std::endl;
			}
			
			break;
		}

		case 5: //Start Executions
		{
			std::cout << "\n";
			if(numOfPeople > 0 && startPerson > 0 && skipNum >= 0)
			{
				std::cout << "\n\n************************** Begin Executions ********************************\n\n";

				int removePos = (newArr.size() + (startPerson-1) + skipNum) % newArr.size();
				int indexToKill = newArr[removePos];
				while(newArr.size()>1)
				{	
					Person thePerson = people[indexToKill];
					thePerson.toggleLife();
					std::string alive = thePerson.isAlive()?"True":"False";
					std::cout << "Eliminating: " << thePerson << std::endl;
					newArr.remove(removePos);
					removePos = (newArr.size() + removePos + skipNum) % newArr.size();
					indexToKill = newArr[removePos];
				}
				std::cout << "\n\n**************************** End Executions ********************************\n\n";
				Person oneLuckyPerson = people[newArr[0]];
				std::cout << "\t[ The Survivor ]\n";
				std::cout << "The Survivor: " << oneLuckyPerson << std::endl;
				std::cout << "\n****************************************************************************\n\n";
				oneLuckyPerson.setPosition(1); //carry over the survivor into the next round
				people.clear();
				newArr.clear();
			}
			else
			{
				std::cout << "\t--- Please Specify the Following First; Number of People, Starting Person, and Skip Number ---\n";
			}
			numOfPeople = newArr.size();
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
			break;
		}
	}

	return promptUser;
}