//File: modArray.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog7
//Modified: 02/23/21

#pragma once

#include <cstddef>
#include <iostream>
#include <list>



/*Description
This file contains the declaration and definitions of a modArray. The modArray
is a wrapper for a std::list containter. It allows modular indexing and does
out-of-bounds checking for front(), back(), and pop_back(). Additonally,
subscripting will always be valid if the paramter is any integer and the vector
isn't empty. Lastly, modArray checks for a positive integer if being instantiated
with an int variable. Lastly, ModArray implements its own custom iterator for
going through its list elements.
*/

//Create Namespace for anything array related
namespace modArray
{
	//########################
	//# Declare ModArray     #
	//########################

	template<class T>
	class ModArray
	{
		public:
			class ArrIterator; //forward declaration of the iterator
			typedef ModArray<T>::ArrIterator iterator; //shorter name for iteration

		private:
			typedef std::list<T> containArr; //fun name for the list container that holds elements in ModArray

		public:
			ModArray();
			ModArray(int);
			ModArray(int, bool);
			ModArray(ModArray<T>&);
			ModArray<T>& operator*();
			ModArray<T>& operator=(const ModArray<T>&);
			T& operator[](int);
			const T& operator[](int) const;
			void pop_back();
			void remove(int); //deletes an index
			T front();
			T back();
			int size() const;
			void insert(T);
			bool empty();
			void dump();
			iterator begin() 											{return ArrIterator(this); }; //get an iterator positioned at the first index
			iterator end()  											{return ArrIterator(this, this->size());}; //get an interator positioned at the last index

		private:
			int count; //number of elements in the container
			containArr internalList; //list containter

		public: //declaration and definition for ModArray's iterator
			class ArrIterator
			{
				public:
					ArrIterator()										{indexPos = 0; curModArr = NULL; };					//default constructor
					ArrIterator(ModArray<T> *outterClass)				{indexPos = 0; curModArr = outterClass; };			//parameter constructor, takes pointer to ModArray
					ArrIterator(ModArray<T> *outterClass, int newIndex)	{indexPos = newIndex; curModArr = outterClass; };	//parameter constructor, takes pointer to ModArray and starting index
					const T& operator*() const							{return *curModArr->operator[](indexPos); };		//returns a pointer at an index being iterated over
					T& operator*()										{return curModArr->operator[](indexPos); };			//dereferences a pointer
					operator T*() const									{return curModArr[indexPos]; };						//implicit conversion
					const iterator operator++()							{indexPos++; return *this; };						//increments the index by one
					const iterator operator++(int placeHldr)			{iterator tmp = *this; indexPos++; return tmp; };	//return the itereator then increment the index
					const iterator operator--()							{indexPos--; return *this; };						//decerment the index by one
					const iterator operator--(int placeHldr)			{iterator tmp = *this; indexPos--; return tmp; };	//return the interator then decrement the index
					const iterator operator+(int incrNum) 				{indexPos = indexPos + incrNum; return *this; };	//increment the index by a custom value
					const iterator operator-(int decrNum) 				{indexPos = indexPos - decrNum; return *this; };	//decerment the index by a custom value
					bool operator>(const int numOfPositions) const		{return this->indexPos > numOfPositions; };			//determine if the index is larger than a value
					bool operator<(const int numOfPositions) const		{return this->indexPos < numOfPositions; };			//determine if the index is less than a value
					bool operator>=(const int numOfPositions) const		{return this->indexPos >= numOfPositions; };		//determine if the index is greater than or equal to a value
					bool operator<=(const int numOfPositions) const		{return this->indexPos <= numOfPositions; };		//determine if the index is less than or equal to a value
					bool operator==(const iterator& otherItr) const		{return this->indexPos == otherItr.indexPos; };		//determine if the index is the same as another iterators index
					bool operator!=(const iterator& otherItr) const		{return this->indexPos != otherItr.indexPos; };		//determine if the index is not the same as anonter iterators index

				private:
					int indexPos; //this number could get really large and possibly overflow, could solve by peforming modulous operater on index change, but it might be good to keep track of distance into loop
					ModArray<T> *curModArr; //pointer to a ModArray, allows access to ModArrays' methods and internal lsit
			};
	};



	//########################
	//# DEFINE ModArray      #
	//########################

	//Default Constructor
	//precondition: none
	//postcondition: modArray object is instantiated with a list of zero size
	template<class T>
	ModArray<T>::ModArray()
	{
		this->count = 0;
		this->internalList = std::list<T>();
	};


	//Parameter Constructor: 
	//precondition: parameter must be non-negative
	//postcondition: list of paramter size is created
	template<class T>
	ModArray<T>::ModArray(int numOfValues)
	{

		if(numOfValues < 0)
		{
			throw std::length_error(" ---[ Exception ]--- : Array must be a non-negative size");
		}

		else
		{
			this->count = numOfValues;
			this->internalList = std::list<T>(numOfValues);
		}
	};


	//Parameter Constructor: creates a list with ints indicating index locations in the list
	//precondition: parameter must be non-negative
	//postcondition: list of paramter size is created, with numbers ascending
	template<class T>
	ModArray<T>::ModArray(int numOfValues, bool ascending)
	{

		if(numOfValues < 0)
		{
			throw std::length_error(" ---[ Exception ]--- : Array must be a non-negative size");
		}

		else if (ascending)
		{
			int tmpCount=0;
			while(tmpCount < numOfValues)
			{
				this->insert(tmpCount++);
			}
		}

		else //descending
		{
			int tmpCount=numOfValues;
			while(tmpCount > 0)
			{
				this->insert(--tmpCount);
			}
		}
	};


	//Copy Constructor
	//precondition: ModArray object must be used as parameter
	//postcondition: ModArray object is instantiated with its own identical values of the param ModArray 
	template<class T>
	ModArray<T>::ModArray(ModArray<T>& arrToCopy)
	{
		this->count = arrToCopy.size();
		this->internalList = std::list<T>(arrToCopy.internalList);
	};


	//Dereference ModArray
	//precondition: none
	//postcondition: ModArray object returned
	template<class T>
	ModArray<T>& ModArray<T>::operator*()
	{
		return *this;
	}


	//Assignment Operator
	//precondition: ModArray object must be on right hand side of operator
	//postcondition: ModArray on left hand side has its list erased and replaced with copied elements of the right hand side
	//				The left hand side is returned allowing multiple assignment operations
	template<class T>
	ModArray<T>& ModArray<T>::operator=(const ModArray<T>& arrToCopy)
	{
		//delete anything in the current modArray
		this->internalList.clear();
		this->internalList = std::list<T>(arrToCopy.internalList);
		this->count = arrToCopy.size();
		return *this;
	}


	//modular indexing subscript operator, allows modification of index.
	//precondition: ModArray must contain elements
	//postcondition: return pointer to index that can be modified
	template<class T>
	T& ModArray<T>::operator[](int indexNum)
	{
		if(!this->empty())
		{
			//prevent multiple calls to size method
			int arrSize = this->size();

			//index is negative, translate the negative value into the correct positive index
			if(indexNum < 0)
			{
				//if the range of the index exceeds the index size, the index will loop back to the start
				int circularIndexing = arrSize-((-1*indexNum) % arrSize);
				//check if the negative index is actually the first index location 0
				int indexLocation = circularIndexing == arrSize ? 0:circularIndexing; //this corrects for difference of range values, allowing negative indexing
				//use list iterator to goto index position
				std::list<int>::iterator it = this->internalList.begin();
				std::advance(it, indexLocation);
				return *it;
			}

			else
			{
				//positive index location, determing index using modulus function to allow looping
				int indexLocation = indexNum % arrSize;
				//use list iterator to goto index position
				std::list<int>::iterator it = this->internalList.begin();
				std::advance(it, indexLocation);
				return *it;
			}
		}

		else
		{
			throw std::invalid_argument(" ---[ Modification Exception ]--- : The index location is not valid");
		}
	}


	//modular indexing subscript operator, allows access to index.
	//precondition: ModArray must contain elements
	//postcondition: returns a pointer to an index that can't be modified
	template<class T>
	const T& ModArray<T>::operator[](int indexNum) const
	{
		if(!this->empty())
		{
			//prevent multiple calls to size method
			int arrSize = this->size();

			//index is negative, translate the negative value into the correct positive index
			if(indexNum < 0)
			{
				//if the range of the index exceeds the index size, the index will loop back to the start
				int circularIndexing = arrSize-((-1*indexNum) % arrSize);
				//check if the negative index is actually the first index location 0
				int indexLocation = circularIndexing == arrSize ? 0:circularIndexing; //this corrects for difference of range values, allowing negative indexing
				//use list iterator to goto index position
				std::list<int>::iterator it = this->internalList.begin();
				std::advance(it, indexLocation);
				return *it;
			}

			else
			{
				//positive index location, determing index using modulus function to allow looping
				int indexLocation = indexNum % arrSize;
				//use list iterator to goto index position
				std::list<int>::iterator it = this->internalList.begin();
				std::advance(it, indexLocation);
				return *it;
			}
		}

		else
		{
			throw std::out_of_range(" ---[ Access Exception ]--- : The index location is not valid");
		}
	}


	//call pop_back method on internal list
	//precondition: ModArray must contain elements
	//postcondition: removes last element, ModArray reduces size by one
	template<class T>
	void ModArray<T>::pop_back()
	{
		if(!this->empty())
		{
			//erase the last element in the list
			this->internalList.pop_back();
			this->count--;
		}

		else
		{
			throw std::length_error(" ---[ Exception ]--- : The array is empty");
		}
	}


	//remove an index using lists iterator and methods
	//precondition: ModArray must contain elements
	//postcondition: removes last element, ModArray reduces size by one
	template<class T>
	void ModArray<T>::remove(int indexPos)
	{
		if(!this->empty())
		{
			std::list<int>::iterator it = this->internalList.begin();
			std::advance(it, indexPos);
			this->internalList.erase(it);
			this->count--;
		}

		else
		{
			throw std::length_error(" ---[ Exception ]--- : The array is empty");
		}
	}


	//call front method on internal list
	//precondition: ModArray must contain elements
	//postcondition: retrieve the first element in the list
	template<class T>
	T ModArray<T>::front()
	{
		if(!this->empty())
		{
			//get the first element of the list
			return this->internalList.front();
		}

		else
		{
			throw std::length_error(" ---[ Exception ]--- : The array is empty");
		}
	}


	//call back method on internal list
	//precondition: ModArray must contain elements
	//postcondition: retrieve the last element in the list
	template<class T>
	T ModArray<T>::back()
	{
		if(!this->empty())
		{
			//get the last element in the list
			return this->internalList.back();
		}

		else
		{
			throw std::length_error(" ---[ Exception ]--- : The array is empty");
		}
	}


	//call the size method on internal list
	//precondition: none
	//postcondition: retrieve the size of the list
	template<class T>
	int ModArray<T>::size() const
	{
		return this->internalList.size();
	}


	//call the push_back method on internal list, adding a new value
	//precondition: none
	//postcondition: element added to list, the list expands, and count incremented
	template<class T>
	void ModArray<T>::insert(T insertVal)
	{
		if(this->size()==this->internalList.max_size())
		{
			throw std::length_error(" ---[ Exception ]--- : The vector is full");
		}

		else
		{
			this->internalList.push_back(insertVal);
			this->count++;
		}
	}


	//call the empty method on internal list
	//precondition: none
	//postcondition: bool returned true if elements else false
	template<class T>
	bool ModArray<T>::empty()
	{
		return this->internalList.empty();
	}

/*
	//display the elements in the array
	//precondition: none
	//postcondition: display output stream of element objects
	template<class T>
	void ModArray<T>::print()
	{

	}
*/


	//display info and elements in the ModArray
	//precondition: ModArray shouldn't be empty, exceptions will be caught and handled
	//postcondtion: ModArray information is displayed
	//NOTE: multiple try catches are used so information is still printed out after an exception instead of main handling them
	template<class T>
	void ModArray<T>::dump()
	{
		std::string emptyArr = this->empty()? "True":"False";

		std::cout << "\n--- DUMPING ModArray --- " << std::endl;

		std::cout << "  [ ModArray Info ]" << std::endl;
		std::cout << "ModArray Size: " << this->size() << std::endl;
		std::cout << "ModArray Max_Size: " << this->internalList.max_size() << std::endl;
		std::cout << "ModArray Empty: " << emptyArr << std::endl;

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

		ModArray::iterator it = this->begin();
		for(it; it!=this->end(); it++)
		{
			if((this->end() - 1) == it) //end is one index past the last value, which would go back to the beginning without subtracting one
			{
				std::cout << *it;
			}

			else //show a comma seperator if it isn't the last element
			{
				std::cout << *it << ", ";
			}
		}

		std::cout << " )" << std::endl;

		std::cout << "--- END DUMP ---" << std::endl << std::endl;
	};
}
