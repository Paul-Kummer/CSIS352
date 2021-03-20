//File: main.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog8
//Modified: 03/01/21

#include "prototypes.h"




/*
Description:
This provides the main interface to the program and provides output to help users understand the program
*/


//This function outputs options to the user that they can use
//precondition: none
//postcondition: string output to console
void showOptions(std::string fileName)
{
		std::cout << "\n\t[ Select an Option ]\t" << "Current File: " << fileName << std::endl;
		std::cout << "(1)Choose File; (2)Get Definition; (3)Match Terms To Definitions; (4)Go Over All Terms; (0)Exit\n"; //future versions may have (3)Add Definition; (4)Change Definition
		std::cout << "Enter Selection: ";
}


//This is the main entry point of the program
//precondition: none
//postcondition: program exits with value 0 and memory is freed
int main(int argc, char **argv)
{
	//Variables
	std::string tmpString, fileName="studyTerms.txt"; //used for file reading
	int opSelect; //the operation that will be performed, determined by a switch statement in the function selectOperation
	bool promptUser = true; //sentinel for determining if operations should still be done on the ModArray
	std::map<std::string, std::string> defDict; //the vector of Person objects, only one will be alive in the end

	//get terms and definitions stored to defDict
	populateDict(fileName, defDict);
	
	//Show the main purpose of the program to the user
	std::cout << "************************************************************" << std::endl;

	std::cout << "\n          Definition Search Machine\n" << std::endl;

	std::cout << "************************************************************" << std::endl
	<< std::endl << "           Programmed By: Paul Kummer"                        << std::endl 
	<< std::endl
	<<              "This program will allow the user to enter a query in order  " << std::endl 
	<<              "to find its definition. The definitions should be stored in " << std::endl
	<<              "a text file that the user can define. After searching for a " << std::endl
	<<              "definition, the user will be able to continue searching for " << std::endl
	<<              "more definitions until they enter 0 to stop.                " << std::endl
	<< std::endl
	<<              "************************************************************" << std::endl 
	<< std::endl;


	//run test file if the user entered one, but primarily for running make test
	if(argc == 2)
	{
		try
		{
			std::string fileName = argv[1]; //get the game of the command line argument
			std::ifstream testDoc; //declare the file
			testDoc.open(fileName); //open the file with of the command line argument
			int selection; //the option extracted from the opened file

			while(testDoc >> tmpString) //extract commands from the file
			{
				try
				{
					opSelect = std::stoi(tmpString); //convert the string to an integer
					showOptions(fileName); //display the options
					std::cout << "Operation Selected : " << opSelect << std::endl; //show commands being entered
					promptUser = selectOperation(opSelect, &testDoc, fileName, defDict); //perform the operation selected
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
			std::cerr << "--- Exception ---" << e.what() << '\n';
		}
	}

	//use user inputs
	else
	{
		//loop that will allow user to continue executing commands
		while (promptUser)
		{
			//clear input stream if eof, which can occur if user enters ctrl+d from within the operations
			std::cin.clear();
			
			//give the user a list of options
			showOptions(fileName);
			
			while(!(std::cin >> opSelect)) //continue prompting for an input until a valid input is given
			{
				std::cin.clear();
				std::cin.ignore(100, '\n');
				std::cout << "\n\t-Bad Selection Try Again- \nEnter Selection: ";
			}

			//determines what operation the user wanted to perform
			promptUser = selectOperation(opSelect, nullptr, fileName, defDict);
		}
	}

	//inform the user of program closure
	std::cout << std::endl << "\n\t--- Goodbye ---\n" << std::endl;
	return 0;
}