//File: main.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog7
//Modified: 02/23/21

#include <fstream>
#include "modArray.h"
#include "prototypes.h"

using namespace modArray;



/*
Description:
Impletment the Josephus problem
1) go K number of spaces and eliminate the element
3) repeat until only one element remains
4) print off that element
*/


//display user options
void showOptions(ModArray<int> newArr, int startPerson, int skipNumber)
{
		std::cout << "\n[ Setup The Execution Ring ]" << std::endl;
		std::cout << "\t(Number of People: " << newArr.size() << ")\t(Starting Position: " << startPerson << ")\t(Skip Distance: " << skipNumber << ")\n";
		std::cout << "(1)Set Number of People; (2)Set Starting Person; (3)Set Skip Distance; (4)Name The People; (5)Begin Executions; (0)Exit\n";
		std::cout << "Enter Selection: ";
}


//main line of logic the program performs
int main(int argc, char **argv)
{
	std::string tmpString; //used for file reading
	int opSelect; //the operation that will be performed, determined by a switch statement in the function selectOperation
	int numOfPeople=0, startPerson=0, skipNumber=0; //values to determine executions
	bool promptUser = true; //sentinel for determining if operations should still be done on the ModArray

	//All elements could be stored in one ModArray of type Person, but the operations design will need to be changed
	//Implemented Option: one list stores index numbers of people who are alive, which get iterated through and removed until there
	//					is one left. Then use that remaining index number to index the vector of all people.
	//Option 1: remove each person from newArr as they are killed, and at the end retrieve the start position from the last Person object
	//Option 2: togglelife on each person object as they are executed and make the iterator ignore people who are not alive

	ModArray<int> newArr = * new ModArray<int>(); //the modarray that will be manipulated holding original index locations
	std::vector<Person> people; //the vector of Person objects, only one will be alive in the end
	
	
				std::cout << "************************************************************" << std::endl;

				std::cout << "\n          The Josephus Problem\n" << std::endl;

			    std::cout << "************************************************************" << std::endl
		     << std::endl << "           Programmed By: Paul Kummer"                        << std::endl 
			 << std::endl
		     <<              "It's a matter of Life and Death, and you want to "            << std::endl 
			 <<              "survive to tell the story.                       "            << std::endl
			 << std::endl
			 <<              "Two combating groups have decided that they are  "            << std::endl
			 <<              "in a stalemate and they will all surely die in   "            << std::endl 
			 <<              "the end. They decide one person should live to   "            << std::endl 
			 <<              "tell the story of the conflict. Everyone else    "            << std::endl
			 <<              "will be executed at random by killing the person "            << std::endl
			 <<              "every K number of positions away from a decided  "            << std::endl
			 <<              "start position. Once the the executioner has     "            << std::endl
			 <<              "killed all but one, he will free them.           "            << std::endl
			 << std::endl
			 <<              "You have devised a way to choose the Lucky spot  "            << std::endl
			 <<              "unbeknownst to your comrades and enemies. Use    "            << std::endl
			 <<              "this knowledge to escape with your life!         "            << std::endl 
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

			while(testDoc >> tmpString)
			{
				try
				{
					opSelect = std::stoi(tmpString);
					//show commands being entered
					showOptions(newArr, startPerson, skipNumber);
					std::cout << "Operation Selected : " << opSelect << std::endl;
					promptUser = selectOperation(opSelect, newArr, &testDoc, numOfPeople, startPerson, skipNumber, people);
				}
				catch(const std::exception& e)
				{
					std::cerr << "--- Exception ---" << e.what() << '\n';
					std::cin.clear();
				}
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
		//loop that will allow user to continue executing commands on the ModArray
		while (promptUser)
		{
			//give the user a list of options
			showOptions(newArr, startPerson, skipNumber);
			
			while(!(std::cin >> opSelect))
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "\n\t-Bad Selection Try Again- \nEnter Selection: ";
			}

			//determines what operation the user wanted to perform
			promptUser = selectOperation(opSelect, newArr, nullptr, numOfPeople, startPerson, skipNumber, people);
		}
	}

	//inform the user of program closure
	std::cout << std::endl << "\n\t--- Goodbye ---\n" << std::endl;
	return 0;
}