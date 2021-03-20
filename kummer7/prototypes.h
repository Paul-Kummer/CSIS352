//File: prototypes.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog7
//Modified: 02/23/21

#pragma once

#include "modArray.h"
#include <fstream>
#include <vector>



/*
Description:
Declarations of the Person class and selectOperation function
*/


class Person
{
	public:
		Person();
		Person(int);
		Person(std::string, int);
		std::string getName() const ;
		void setName(std::string);
		int getPosition() const ;
		void setPosition(int);
		bool isAlive() const;
		void toggleLife();
		friend std::ostream& operator<<(std::ostream&, const Person&);

	private:
		bool alive;
		std::string name;
		int position;
};

//Declaration of selectOperation function, which performs a user action on modArray
bool selectOperation(int, modArray::ModArray<int>&, std::ifstream*,int&, int&, int&,std::vector<Person>&);