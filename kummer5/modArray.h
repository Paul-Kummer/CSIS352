//File: modArray.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog5
//Modified: 02/09/21

#pragma once

#include <cstddef>
#include <iostream>
#include <vector>



/*Description
This file contains the declaration and definitions of a modArray. The modArray
is essentially an extension of std::vector. It allows modular indexing and does
out-of-bounds checking for front(), back(), and pop_back(). Additonally,
subscripting will always be valid if the paramter is any integer and the vector
isn't empty. Lastly, modArray checks for a positive integer if being instantiated
with an int variable.

Note: Insert will expand the vector
*/


//Create Namespace for anything array related
namespace modArray
{
	//########################
	//# Declare ModArray     #
	//########################

	template<class T>
	class ModArray : public std::vector<T>
	{
		public:
			using std::vector<T>::vector;
			ModArray(int);
			T& operator[](int);
			const T& operator[](int) const;
			using std::vector<T>::pop_back;
			void pop_back();
			using std::vector<T>::front;
			T front();
			using std::vector<T>::back;
			T back();
			void dump();
			
			//enabling this will prevent vector resizing on insert
			//using std::vector<T>::insert;
			//T insert();
	};


	//########################
	//# DEFINE ModArray      #
	//########################

	//parameter constructor: parent default constructor called then child parameterized constructor 
	//precondition: parameter must be non-negative
	//postcondition: vector of paramter size is created
	template<class T>
	ModArray<T>::ModArray(int numOfValues)
	{

		if(numOfValues < 0)
		{
			throw std::length_error(" ---[ Exception ]--- : Array must be a non-negative size");
		}

		else
		{
			this->resize(numOfValues);
		}
	};


	//modular indexing subscript operator, allows modification of index.
	//precondition: vector must contain elements
	//postcondition: return pointer to index that can be modified
	template<class T>
	T& ModArray<T>::operator[](int indexNum)
	{
		if(!this->empty())
		{
			//prevent multiple calls to size method
			int vectorSize = this->size();

			//index is negative, translate the negative value into the correct positive index
			if(indexNum < 0)
			{
				//if the range of the index exceeds the index size, the index will loop back to the start
				int circularIndexing = vectorSize-((-1*indexNum) % vectorSize);
				//check if the negative index is actually the first index location 0
				int indexLocation = circularIndexing == vectorSize ? 0:circularIndexing; //this corrects for difference of range values, allowing negative indexing
				//call base classes indexing operator
				return std::vector<T>::operator[](indexLocation);
			}

			else
			{
				//positive index location, determing index using modulus function to allow looping
				return std::vector<T>::operator[](indexNum % vectorSize);
			}
		}

		else
		{
			throw std::invalid_argument(" ---[ Modification Exception ]--- : The index location is not valid");
		}
	}


	//modular indexing subscript operator, allows access to index.
	//precondition: vector must contain elements
	//postcondition: returns a pointer to an index that can't be modified
	template<class T>
	const T& ModArray<T>::operator[](int indexNum) const
	{
		if(!this->empty())
		{
			//prevent multiple calls to size method
			int vectorSize = this->size();

			//index is negative, translate the negative value into the correct positive index
			if(indexNum < 0)
			{
				//if the range of the index exceeds the index size, the index will loop back to the start
				int circularIndexing = vectorSize-((-1*indexNum) % vectorSize);
				//check if the negative index is actually the first index location 0
				int indexLocation = circularIndexing == vectorSize ? 0:circularIndexing; //this corrects for difference of range values, allowing negative indexing
				//call base classes indexing operator
				return std::vector<T>::operator[](indexLocation);
			}

			else
			{
				//positive index location, determing index using modulus function to allow looping
				return std::vector<T>::operator[](indexNum % vectorSize);
			}
		}

		else
		{
			throw std::out_of_range(" ---[ Access Exception ]--- : The index location is not valid");
		}
	}


	//overload base method pop_back that removes the last element
	//precondition: vector must contain elements
	//postcondition: removes last element, vector size does not change
	template<class T>
	void ModArray<T>::pop_back()
	{
		if(!this->empty())
		{
			//call base class pop_back method if not empty
			this->std::vector<T>::pop_back();

			//enable this if you want the array to dynamically resize
			//this->std::vector<T>::shrink_to_fit();
		}

		else
		{
			throw std::length_error(" ---[ Exception ]--- : The array is empty");
		}
	}


	//overload base base method front accesses the first element
	//precondition: vector must contain elements
	//postcondition: retrieve the first element
	template<class T>
	T ModArray<T>::front()
	{
		if(!this->empty())
		{
			//call the base class front method if not emepty
			return this->std::vector<T>::front();
		}

		else
		{
			throw std::length_error(" ---[ Exception ]--- : The array is empty");
		}
	}


	//overload base base method back accesses the last element
	//precondition: vector must contain elements
	//postcondition: retrieve the last element
	template<class T>
	T ModArray<T>::back()
	{
		if(!this->empty())
		{
			//call the base class back method if not empty
			return this->std::vector<T>::back();
		}

		else
		{
			throw std::length_error(" ---[ Exception ]--- : The array is empty");
		}
	}


	//display info and elements in the vector
	//precondition: vector shouldn't be empty, exceptions will be caught and handled
	//postcondtion: vector information is displayed
	//NOTE: multiple try catches are used so information is still printed out after an exception instead of main handling them
	template<class T>
	void ModArray<T>::dump()
	{
		std::string emptyVec = this->empty()? "True":"False";

		std::cout << "\n--- DUMPING ModArray --- " << std::endl;

		std::cout << "  [ ModArray Info ]" << std::endl;
		std::cout << "ModArray Size: " << this->size() << std::endl;
		std::cout << "ModArray Max_Size: " << this->max_size() << std::endl;
		std::cout << "ModArray Capacity: " << this->capacity() << std::endl;
		std::cout << "ModArray Empty: " << emptyVec << std::endl;

		try
		{
			std::cout << "First Value: " << this->front() << std::endl;
		}
		catch(const std::length_error& e)
		{
			std::cerr << e.what() << '\n';
		}
		
		try
		{
			std::cout << "Last Value: " << this->back() << std::endl;
		}
		catch(const std::length_error& e)
		{
			std::cerr << e.what() << '\n';
		}
		
		std::cout << "  [ Elements ]" << std::endl;
		std::cout << "( ";
		for(int i = 0; i < this->size(); i++)
		{
			if (i+1 == this->size())
			{
				std::cout << "i[" << i << "]: " << this->operator[](i);
			}

			else
			{
				std::cout << " i[" << i << "]: " << this->operator[](i) << ", ";
			}
		}
		std::cout << " )" << std::endl;

		std::cout << "--- END DUMP ---" << std::endl << std::endl;
	};


//Enable this to prevent vector from resizing on insert
/*
	template<class T>
	ModArray::insert(T insertVal)
	{
		if(this->size()==this->capacity())
		{
			throw std::length_error(" ---[ Exception ]--- : The vector is full");
		}

		else
		{
			std::vector::insert(insertVal);
		}
	}
*/
}
