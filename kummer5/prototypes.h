//File: prototypes.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog5
//Modified: 02/11/21

#pragma once

#include "modArray.h"
#include <fstream>


//Declaration of selectOperation function, which performs a user action on modArray
bool selectOperation(int, modArray::ModArray<int>&, std::ifstream*);
