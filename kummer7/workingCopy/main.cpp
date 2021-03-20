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
1) go K number of spaces in a list, vector, map, whatever
2) remove item at that index
3) repeat until only one element remains
4) print off that element

Inputs: 
int number of people
int starting index


Output:
int index of surving person


Possible Issues:
-Array out of bounds when calling any method that indexes your chosen container and/or data structure, whether abstract or not
-0 or negative values for the number of people or other arguments
-Initial number of people a ridiculously large size
-Trying to get the next person to kill when there is only one (or less) person(s) left
-Because arrays are 0 indexed, but the problem as stated in the Wikipedia entry assumes standard human language nomenclature 
 of being one-indexed, there's a great possibility for off-by-one errors, so one needs to be especially cognizant of this


*/


//main line of logic the program performs
int main(int argc, char **argv)
{
	int opSelect; //the operation that will be performed, determined by a switch statement in the function selectOperation
	int numOfPeople=0, startPerson=0, skipNumber=0; //values to determine executions
	bool promptUser = true; //sentinel for determining if operations should still be done on the ModArray
	ModArray<int> newArr = * new ModArray<int>(); //the modarray that will be manipulated
	
	
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
		//show commands being entered
		std::cout << "\n[ Setup The Execution Ring ]" << std::endl;
		std::cout << "\t(Number of People: " << newArr.size() << ")\t(Starting Position: " << startPerson << ")\t(Skip Distance: " << skipNumber << ")\n";
		std::cout << "(1)Set Number of People; (2)Set Starting Person; (3)Set Skip Distance; (4)Begin Executions; (5)Create Person Array; (0)Exit\n";

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
				promptUser = selectOperation(opSelect, newArr, &testDoc, numOfPeople, startPerson, skipNumber);
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
			std::cout << "\n[ Setup The Execution Ring ]" << std::endl;
			std::cout << "\t(Number of People: " << numOfPeople << ")\t(Starting Position: " << startPerson << ")\t(Skip Distance: " << skipNumber << ")\n";
			std::cout << "(1)Set Number of People; (2)Set Starting Person; (3)Set Skip Distance; (4)Begin Executions; (5)Create Person Array; (0)Exit\n";
			std::cout << "Enter Selection: ";
			
			while(!(std::cin >> opSelect))
			{
				std::cin.clear();
				std::cin.ignore();
				std::cout << "\n\t-Bad Selection Try Again- \nEnter Selection: ";
			}

			//determines what operation the user wanted to perform
			promptUser = selectOperation(opSelect, newArr, nullptr, numOfPeople, startPerson, skipNumber);
		}
	}

	//inform the user of program closure
	std::cout << std::endl << "\n\t--- Goodbye ---\n" << std::endl;
	return 0;
}