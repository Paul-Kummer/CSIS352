//File: prototypes.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog6
//Modified: 02/18/21

#pragma once

#include "modArray.h"
#include <fstream>


//Declaration of selectOperation function, which performs a user action on modArray
bool selectOperation(int, modArray::ModArray<int>&, std::ifstream*);
