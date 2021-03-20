//File: main.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog6
//Modified: 02/18/21

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
	bool promptUser = true; //sentinel for determining if operations should still be done on the ModArray
	ModArray<int> newArr = * new ModArray<int>(); //the modarray that will be manipulated
	newArr.insert(11); newArr.insert(22); newArr.insert(33); newArr.insert(44); newArr.insert(55); 
	newArr.insert(4); newArr.insert(4); newArr.insert(3); newArr.insert(2); newArr.insert(1);
	
	
				std::cout << "************************************************************" << std::endl;

				std::cout << "\nModArray Preloaded With: [ 11, 22, 33, 44, 55, 5, 4, 3, 2, 1 ]\n" << std::endl;

			    std::cout << "************************************************************" << std::endl
		     << std::endl << "           Programmed By: Paul Kummer"                        << std::endl 
			 << std::endl
		     <<              "This program will let you interactivly modify a ModArray."    << std::endl 
			 <<              "Then it will perform some test operations on exit"            << std::endl
			 <<              "    *test 1: assignment operator                 "            << std::endl 
			 <<              "    *test 2: copy constructor                    "            << std::endl 
			 <<              "    *test 3: parameter constructor               "            << std::endl 
			 <<              "    *test 4: subscript operations on last ModArray "          << std::endl
			 <<              "    *test 5: negative value param constructor    "            << std::endl 
			 << std::endl
		     <<              "************************************************************" << std::endl 
			 << std::endl;


	//run test file if user entered make test or a command line arg
	if(argc == 2)
	{
		//give the user a list of options
		std::cout << "\t[ Operation List ]\n";
		std::cout << "(1)First; (2)Last; (3)Pop; (4)Size; (5)Is_Empty; (6)Insert; (7)Dump; (8)getIndex; (9)insertAtIndex;\n";
		std::cout << "(10)Forward Iterate; (11)Backward Iterate; (0)Exit\n\n";

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
		//loop that will allow user to continue executing commands on the ModArray
		while (promptUser)
		{
			//give the user a list of options
			std::cout << "Manipulate the ModArray:" << 
			std::endl << "(1)First; (2)Last; (3)Pop; (4)Size; (5)Is_Empty; (6)Insert; (7)Dump; (8)getIndex; (9)insertAtIndex; (0)Exit\n";
			std::cout << "(10)Forward Iterate; (11)Backward Iterate; (0)Exit\n\n"; 
			std::cout << "Enter Selection: ";
			
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