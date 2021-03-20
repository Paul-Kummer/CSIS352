//File: people.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog7
//Modified: 02/23/21

#pragma once
#include <string>
#include "prototypes.h"

Person::Person();
{
	this->alive = false;
	this->name = "Doe";
	this->position = 0;
}

Person::Person(std::string givenName, int placement);
{
	this->alive = true;
	this->name = givenName;
	this->position = placement;
}

std::string Person::getName()
{
	return name;
}

void Person::setName(std::string newName)
{
	this->name = newName;
}

int Person::getPosition()
{
	return this->position;
}

void Person::setPosition(int newPos)
{
	this->position = newPos;
}

bool Person::isAlive()
{
	return this->alive;
}

void Person::toggleLife()
{
	this->alive = alive?false:true;
}
