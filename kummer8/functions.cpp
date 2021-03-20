//File: operations.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog8
//Modified: 03/03/21

#include "prototypes.h"

typedef std::map<std::string, std::string> defMap;



/*
Description: 
This file defines any functions that will be used within operations or main
*/


//This function will look for a term in a std::map and return a vector with either two "NULL" strings
//or the string key at index one and the string defintion at index two. Searches are case insensitive
//precondition: defDict must be populated with key value pairs.
//postcondition: vector containing two strings is returned
std::vector<std::string> searchForDef(defMap defDict, std::string searchTerm)
{
	std::vector<std::string> keyVal = {"NULL","NULL"}; //default values
	defMap::iterator searchResult;

	searchResult = defDict.find(allCaps(searchTerm));
	if(searchResult != defDict.end()) //ensure that the value was indeed found
	{
		keyVal[0] = searchResult->first; //first index will be the term
		keyVal[1] = searchResult->second; //second index will be the definition
	}

	return keyVal;
}


//This function will open a file and read a term until the delimter ":" is reached. Then the definition
//is read until the delimiter "#" is reached. The term will then be mapped to the definition in the
//defDict map.
//precondition: defDict must exist and the file name must be valid
//postcondition: terms and definitions are stored in defDict with all terms being converted to all caps
bool populateDict(std::string fileName, defMap& defDict) //throw error if problems with file
{
	bool successful = true; //indicates if key values were mapped successfully
	std::ifstream definitionFile; //the file containing the terms and definitions
	std::string term, definition; //variables for holding the terms and definitions

	//attempt to open the file with read-only
	definitionFile.open(fileName);

	//erase the dictionary if the file successfully opens, indicating that new file is being loaded
	if(definitionFile.is_open())
	{
		defDict.clear();

		while(definitionFile) //go over everyline until the end-of-file
		{
			std::getline(definitionFile, term, ':');
			if(definitionFile) //make sure EOF wasn't reached. and extract the term
			{
				std::getline(definitionFile, definition, '#');
				if(definitionFile) //read until #, allowing multiple definitions on new lines
				{
					defDict[allCaps(term)] = definition;
					definitionFile.ignore(100, '\n'); //remove newlinechar to advance to the next term
				}
				else
				{
					successful = false; //EOF was reached without a definition for a term
				}
			}
		}
	}
	else //File did not open
	{
		successful = false;
	}
	
	definitionFile.close();
	return successful;
}


//This function will print off a term and defition that are passed to it in a vector. The definition
//and/or term can be hidden to only reveal a term or definition.
//precondition: A vectory with a term in index 0 and defintion in index 2 must be passed in
//postcondition: the term and definition are ouputted to the console if the corresponding boolean is true
void showTermDef(std::vector<std::string> termDefPair, bool showKey=true, bool showDef=true)
{
	bool defFound = termDefPair[1] == "NULL"? false:true; //determines if a valid key value pair was submitted to the function
	std::string hiddenTerm = std::string(termDefPair[0].length(), '#'); //determines what the hidden term will look like if it's hidden
	std::string term = showKey?termDefPair[0]:hiddenTerm; //determines if the hidden term should be used or the regular term
	std::string def = showDef?termDefPair[1]:""; //determines if the definitions should be showed or nothing at all

	//Set the divider length based on the string lengths. However, stop at 200 to prevent the string from overflowwing into newlines too much
	int buildDivider =term.length() + def.length() + 10; //extra 10 for "\t" and ": "
	int dividerLen = buildDivider<200?buildDivider:200; //limit the divider to 200 characters

	if(defFound)
	{
		std::cout << "\n\t[ Definition ]\n";
		std::cout << std::string(dividerLen,'=') << std::endl;
		std::cout << "\n    " << term << ": " << def << "\n\n";
		std::cout << std::string(dividerLen,'=') << std::endl;
	}
	else
	{
		std::cout << "\t--- The Key Value Pair Could Not Be Found ---" << std::endl;
	}
}


//This function will convert a string into all capital letters
//precondition: The characters have an uppercase to be converted to in the locale
//postcondition: the string is returned with all characters converted to their capitalized form
std::string allCaps(std::string stringToConvert)
{
	std::locale loc; //the locale of the current machine
	std::string returnString = ""; //the string to have capital characters appended to and returned

	//iterate over every character in the string and concatenate it to the return variable
	for(auto it = stringToConvert.begin(); it != stringToConvert.end(); it++)
	{
		char tmpChar = std::toupper(*it, loc);
		if(tmpChar == ':') //Do not allow this char conversion, since it is used for delimiting
		{
			returnString += "(Null)"; //replace invalid characters with null
		}
		else
		{
			returnString += std::toupper(*it, loc);
		}
	}

	return returnString;
}