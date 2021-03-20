//File: operations.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog8
//Modified: 03/03/21

#include "prototypes.h"

typedef std::map<std::string, std::string> defMap;



/*
Description: 
This file defines the function selectOperation, which will perform user chosen actions
on the execution ring
*/


//define selectOperation, which will perform user selected actions, essentially motor of the program supplying power to whatever wheel needs to turn
//precondition: fileName must be a valid file text file and formatted correctly, (IE: Word to Define Here: Definition will be Here)
//				defDict must be initialized
//postcondition: defDict may be modified, files are opened and read, fileName is modified, and many user prompts
bool selectOperation(int opNumber, std::ifstream* testFile, std::string& fileName, defMap& defDict)
{
	std::string userInput; //hold user input as string to determine if it is a valid length
	std::vector<std::string> searchResult; //holds the current term in index 0 and definition at index 1
	bool promptUser = true; //sentinel for determining if operations should still be done
	int tmpInt;

	//determines what operation the user wanted to perform
	//(1)Choose File; (2)Get Definition; (3)Match Term To Definition; (0)Exit
	switch(opNumber)
	{
		case 1: //choose file
		{
			try
			{
				std::cout << "\n\tWhat is the file name with prefix?" << std::endl << "\tEnter the File Name: ";
				std::cin.clear();
				if(testFile && *testFile >> fileName) //make sure the file is valid first, then extract and input
				{
					std::cout << userInput << std::endl;
				}
				else
				{
					std::cin >> userInput;
				}

				if(!populateDict(userInput, defDict))
				{
					std::cout << "\t--- An Error Occured While Reading The File ---" << std::endl;
				}
				else
				{
					fileName = userInput; //the file has been succesfully change, so change the name of the open file
				}
			}
			catch(const std::length_error &e)//catch error of bad file name
			{
				std::cerr << "--- The File is Not Valid ---" << '\n';
			}
			catch(const std::exception &e)
			{
				std::cerr << "\t--- Exception --- " << e.what() << '\n';
			}
			break;
		}

		case 2: //get definition of a term
		{
			try
			{
				do //keep looping until a definition is found 
				{
					std::cout << "\n\tWhat do you want defined? (0 stops)" << std::endl << "\tEnter Search Term: ";
					std::cin.clear(); //clears any errors that may have be present in the input stream
					if(testFile && *testFile >> userInput) //make sure the file is valid first, then extract and input
					{
						std::cout << userInput << std::endl;
					}
					else
					{
						std::cin >> userInput;
					}

					if(userInput != "0") //User decided to exit, do not perform a search
					{
						searchResult = searchForDef(defDict, userInput);
						showTermDef(searchResult, true, true);
					}
				} while (userInput != "0" && std::cin.eof()); // && !defFound);
			}
			catch(const std::exception &e) //Not sure of the exceptions yet
			{
				std::cerr << "\t--- Unknown Exception --- " << e.what() << '\n';
			}
			if(!testFile) //if a file isn't being used, pause the program to let the user read the output
			{
				std::cout << "\n\t*Press Enter to Continue*";
				std::cin.ignore(100, '\n');
				std::cin.get();
			}
			break;
		}

		case 3: //user must match term to provided definition
		{
			try
			{
				if(!testFile)
				{
					std::cin.ignore(100, '\n');
				}

				std::map<std::string, std::string>::iterator it = defDict.begin();
			
				do //keep looping until a definition is found 
				{
					std::string term = it->first;
					searchResult = searchForDef(defDict, term);
					showTermDef(searchResult, false, true);
					
					std::cout << "\n\tWhat term matches the definition? (0) stops; (1) show answer and skip" << std::endl << "\tEnter The Term: ";
					std::cin.clear();
					if(testFile) // && *testFile >> userInput) when running a test file, the term will always be guessed correctly. This allows for multiple files to be used
					{
						userInput = term;
						std::cout << term << std::endl;
					}
					else
					{
						std::cin >> userInput;
						userInput = allCaps(userInput);
					}


					if(userInput == term) //we have a very intelligent user, and answered the term correctly
					{
						std::cout << "\n\t---<<<| CORRECT |>>>---\n\n";
						it++;
					}
					else if(std::isdigit(userInput[0])) //check if the user entered a command
					{
						tmpInt = std::stoi(userInput); //convert the string to an iteger, allowing for use of switch statement
						switch(tmpInt)
						{
							case 1: //the user is stumpped and needs to be shown the answer
							{
								std::cout << "\n\t[ ANSWER ]" << "\n    --->>> " << term << " <<<---" << std::endl;
								it++;
								break;
							}
							case 0: //user wants to exit
							{
								it = defDict.end();
								break;
							}
							default: //we don't know what the user entered, but it isn't correct
							{
								std::cout << "\n\t--- Unrecognized Command ---\n\n";
								break;
							}
						}
					}
					else if(userInput != term && !std::cin.eof()) //user entered wrong answer and didn't signal end of file
					{
						std::cout << "\n\t---<<<| TRY AGAIN |>>>---\n\n";
						
					}

					//if a file isn't being used, or the end of the file is reached, pause the program to let the user read the output
					if(!testFile && it != defDict.end()) 
					{
						std::cout << "\n\t*Press Enter to Continue*\n";
						std::cin.ignore(100, '\n');
						std::cin.get();
					}
				} while (it != defDict.end() && !std::cin.eof()); //exit when no more key value pairs or user signals end-of-file(ctrl+d)
				std::cout << "\n\t---Back To Main---\n\n";
			}
			catch(const std::exception &e) //Not sure of the exceptions yet
			{
				std::cerr << "\t--- Unknown Exception --- " << e.what() << '\n';
			}
			break;
		}

		case 4: //go through all terms
		{
			try
			{
				std::cout << "\nPress Enter to Progress to the Next Term: Ctrl+d to stop\n";

				if(!testFile) //clear the lines of input so the user doesn't have to hit enter a bunch of times, only if not useing a test file
				{
					std::cin.ignore(100, '\n');
				}

				std::map<std::string, std::string>::iterator it = defDict.begin();
				do //keep looping through terms until end-of-file or there are no more terms
				{
					std::string term = it->first;
					searchResult = searchForDef(defDict, term);
					showTermDef(searchResult, true, true);
					it++;
					
					if(!testFile) //make the user pause between terms to avoid them all being printed at once, only if not useing a test file
					{
						std::cin.get();
					}
				} while (it != defDict.end() && !std::cin.eof());
				std::cout << "\n\t---Back To Main---\n\n";
			}
			catch(const std::exception &e) //Not sure of the exceptions yet
			{
				std::cerr << "\t--- Unknown Exception --- " << e.what() << '\n';
			}
			break;
		}

		case 0: //exit the program
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