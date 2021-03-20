// File: main.cpp
// Name: Paul Kummer
// Class: CSIS 352
// Program: prog5
// Modified: 02/09/21

#include <fstream>
#include "modArray.h"
#include "prototypes.h"

using namespace modArray;



/*
Description:
This program will create a vector/modularArray and let the user execute its methods to ensure that it operates correctly,
or the user can run a premade test by executing the program with (make test) or specifying a text document of 
each operation per line at the command prompt
*/


//main line of logic the program performs
int main(int argc, char **argv)
{
	int opSelect; //the operation that will be performed, determined by a switch statement in the function selectOperation
	bool promptUser = true; //sentinel for determining if operations should still be done on the vector
	ModArray<int> newArr = ModArray<int>(); //the vector that will be manipulated


			    std::cout << "************************************************************" << std::endl
		     << std::endl << "           Programmed By: Paul Kummer"                        << std::endl 
			 << std::endl
		     <<              "This program will let you interactivly modify an vector."     << std::endl 
			 <<              "Then it will perform some test operations on exit"            << std::endl
			 <<              "    *test 1: assignment operator                 "            << std::endl 
			 <<              "    *test 2: copy constructor                    "            << std::endl 
			 <<              "    *test 3: parameter constructor               "            << std::endl 
			 <<              "    *test 4: subscript operations on last vector "            << std::endl
			 <<              "    *test 5: negative value param constructor    "            << std::endl 
			 << std::endl
		     <<              "************************************************************" << std::endl 
			 << std::endl;


	//run test file if user entered make test or a command line arg
	if(argc == 2)
	{
		//give the user a list of options
		std::cout << "\t[ Operation List ]\n";
		std::cout << "(1)First; (2)Last; (3)Pop; (4)Size; (5)Is_Empty; (6)Insert; (7)Dump; (8)getIndex; (9)insertAtIndex; (0)Exit\n\n";

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
				promptUser = selectOperation(opSelect, newArr, &testDoc);
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
		//loop that will allow user to continue executing commands on the Vector
		while (promptUser)
		{
			//give the user a list of options
			std::cout << "Manipulate the Vector:" << 
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
			promptUser = selectOperation(opSelect, newArr, nullptr);
		}
	}

	//inform the user of program closure
	std::cout << std::endl << "\t--- Goodbye ---" << std::endl;
	return 0;
}