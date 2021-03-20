//File: people.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog7
//Modified: 02/23/21

#include <string>
#include "prototypes.h"



/*
Description:
This file defines the Person class
*/


//Default Constructor
Person::Person()
{
	this->alive = true;
	this->name = "John Doe";
	this->position = 0;
}

//Parameter Constructor: gives the anynonomous person a positon
Person::Person(int placement)
{
	this->alive = true;
	this->name = "John Doe";
	this->position = placement;
}

//Parameter Constructor: gives a person a name and position
Person::Person(std::string givenName, int placement)
{
	this->alive = true;
	this->name = givenName;
	this->position = placement;
}

//retrieves the persons name
std::string Person::getName() const
{
	return name;
}

//sets a persons name
void Person::setName(std::string newName)
{
	this->name = newName;
}

//retrieves the position of a person
int Person::getPosition() const
{
	return this->position;
}

//sets the position of a person
void Person::setPosition(int newPos)
{
	this->position = newPos;
}

//retrieves the persons life status
bool Person::isAlive() const
{
	return this->alive;
}

//changes the persons life status
void Person::toggleLife()
{
	this->alive = alive?false:true;
}

//give the person an output method
std::ostream& operator<<(std::ostream& out, const Person& curPerson)
{
	std::string status = curPerson.isAlive()?"Alive":"Dead";
	out << curPerson.getName() << " (" << status << ")" << " @" << curPerson.getPosition();
	return out;
}