//File: prototypes.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog7
//Modified: 02/23/21

#pragma once

#include "modArray.h"
#include <fstream>
#include <vector>


class Person
{
	public:
		Person();
		Person(std::string, int);
		std::string getName();
		void setName(std::string);
		std::string getPosition();
		void setPosition(int);
		bool isAlive();
		void toggleLife();

	private:
		bool alive;
		std::string name;
		int position;
};

//Declaration of selectOperation function, which performs a user action on modArray
bool selectOperation(int, modArray::ModArray<int>&, std::ifstream*,int&, int&, int&);