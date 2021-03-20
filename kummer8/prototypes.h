//File: prototypes.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog8
//Modified: 03/03/21

#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <new>
#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <cwctype>
#include <locale>
#include <algorithm>
#include <cctype>

typedef std::map<std::string, std::string> defMap;


/*
Description:
Declarations of operations and functions
*/

bool selectOperation(int opNumber, std::ifstream* testFile, std::string& fileName, defMap& defDict);
std::vector<std::string> searchForDef(defMap defDict, std::string searchTerm);
bool populateDict(std::string fileName, defMap& defDict);
std::string allCaps(std::string stringToConvert);
void showTermDef(std::vector<std::string> termDefPair, bool showKey, bool showDef);