//File: array.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog4
//Modified: 02/04/21

#pragma once
#include <cstddef>
#include <iostream>
#include <cmath>


/*Description
This file contains the declarations and definitions of a doubly linked Node struct and
the Array class, which utilizes nodes to track the position of values.
*/


//Create Namespace for anything array related
namespace array
{
	//#########################
	//# Define & Declare Node #
	//#########################

	//Node struct for keeping track of values in the array
	template <class nType>
	struct Node
	{
		nType value;
		Node<nType>* left = nullptr;
		Node<nType>* right = nullptr;

		//---------------------------------------------------------------------------Change
		Node<nType> operator=(nType tmpVal)
		{
			this->value = tmpVal;
		};

		friend std::ostream& operator<<(std::ostream &out, const Node &tmpNode)
		{
			out << tmpNode.value;
			return out;
		};
	};




	//########################
	//# DECLARATION of Array #
	//########################

	//declaration of Array class
	template<class T>
	class Array
	{
		public:
			Array(); //default constructor
			Array(int); //param constructor
			Array(const Array<T>&); //copy constructor
			const Array<T>& operator=(Array<T>&); //assignment operator
			//const T& operator[](int); //access: get value at index
			Node<T>& operator[](int); //assign: set value at index
			~Array(); //destructor
			void insert(const T); //add nodes to back of array
			T end(); //view the value of the last node
			T begin(); //view the value of the first Node
			T pop(); //view and remove the first node
			int size(); //get the number of nodes in the queue
			bool isEmpty(); //check if the queue has any nodes
			void print(); //print all nodes in the tree
			void dump(); //view information and nodes that the queue currently has

		private:
			void destroyNode(Node<T>*); //set node pointers to null and delete node
			void copyNodes(Node<T> *); //copy node values from one array to another
			Node<T>* first; //location of the last node on array
			Node<T>* last; //location for the next node to be added
			int count; //number of nodes in queue
	};




	//########################
	//# DEFINE Array CLASS  #
	//########################

	//default constructor
	//precondition: none
	//postcondition: creates a Array with no nodes
	template<class T>
	Array<T>::Array()
	{
		this->first = nullptr;
		this->last = nullptr;
		this->count = 0;
	};


	//parameter constructor
	//precondition: numOfNodes paramter must be non-negative integer within the memory limits
	//postcondition: creates a Array with empty value nodes
	template<class T>
	Array<T>::Array(int numOfNodes)
	{
		if(numOfNodes < 0)
		{
			throw std::bad_array_new_length();
		}

		Node<T>* tmpNode;

		this->first = nullptr;
		this->last = nullptr;
		this->count = 0;

		for(int ct=0; ct<numOfNodes; ct++)
		{
			Node<T>* newNode = new Node<T>;

			if(ct == 0)
			{
				newNode->left = nullptr;
				this->first = newNode;
			}

			else
			{
				tmpNode->right = newNode;
				newNode->left = tmpNode;
			}
			
			newNode->value = 0;
			newNode->right = nullptr;
			this->last = newNode;
			tmpNode = newNode;
			this->count++;
		}
	};


	//copy constructor
	//requirement: otherArray must be a valid data type of T
	//postcondition: creates a Array with copied nodes as the Array parameter
	template<class T>
	Array<T>::Array(const Array<T>& otherArray)
	{
		//set default values for private members
		this->first = nullptr;
		this->last = nullptr;
		this->count = 0;

		//now go through nodes and insert them
		this->copyNodes(otherArray.first);
	};


	//overloaded assignment operator
	//requirement: otherArray must be of same data type
	//postcondition: Array containing only nodes of same values as otherArray
	template<class T>
	const Array<T>& Array<T>::operator=(Array<T>& otherArray)
	{
		//erase any nodes that might be exist on this
		while(this->first)
		{
			this->destroyNode(this->first);
		}

		//reinitialize this
		this->first = nullptr;
		this->last = nullptr;
		this->count = 0;

		//copy nodes from other array to this
		this->copyNodes(otherArray.first);
	};


	//find the node at a specified index. reverse index is allowed
	//precondtions: index must be within range of values
	//postcondtion: node at given index is returned
	template<class T>
	Node<T>& Array<T>::operator[](int indexLoc)
	{
		if(indexLoc < (-1 * this->size()) || indexLoc >= this->size())
		{
			throw std::out_of_range(" ---[ Exception ]--- : The index location is not valid");
		}

		int curIndex;
		Node<T>* nodeAtIndex;

		//find node from front of array
		if(indexLoc >= 0)
		{
			curIndex = 0;
			nodeAtIndex = this->first;

			while(curIndex != indexLoc)
			{
				nodeAtIndex = nodeAtIndex->right;
				curIndex++;
			}
		}

		//find node from back of array
		else
		{
			nodeAtIndex = this->last;

			for(int i=-1; i > indexLoc; i--)
			{
				nodeAtIndex = nodeAtIndex->left;
				curIndex++;
			}
		}

		return *nodeAtIndex;
	}


	//destructor
	//precondition: none
	//postcondition: all pointers are set to null and are deleted
	template<class T>
	Array<T>::~Array()
	{
		Node<T>* nextNode = this->first;
		while(!this->isEmpty())
		{
			nextNode = nextNode->right;
			this->destroyNode(this->first);
			this->first = nextNode;
		}
	}


	//insert a new value into the array
	//precondition: tmpVal must be same dataType as other nodes
	//postcondition: 
	//		count increased by one
	//		new node added to the array
	//		the array's first and last values are changed if it's the first node
	//		the array's last value is changed if other nodes exist on the array
	template<class T>
	void Array<T>::insert(const T tmpVal)
	{
		//increment node count
		++this->count;

		//create a new node to be inserted
		Node<T>* newNode = new Node<T>;
		newNode->value = tmpVal;
		newNode->left = nullptr;
		newNode->right = nullptr;

		//insert the node
		if(this->isEmpty())
		{
			this->first = newNode;
			this->last = newNode;
		}

		else
		{
			newNode->left = this->last;
			this->last->right = newNode;
			this->last = newNode;
		}
	}


	//view back Node's value
	//preconditon: array must not be empty
	//postcondition: value of the rear Node's data type is returned
	template<class T>
	T Array<T>::end()
	{
		//display random value if no nodes exist
		if(this->isEmpty())
		{
			throw std::out_of_range(" ---[ Exception ]--- : The array is empty");
		}

		//show the value of the first Node
		else
		{
			return this->last->value;
		}
	};


	//view front Node's value
	//precondition: array must not be empty
	//postcondition: value of the rear Node's data type is returned
	template<class T>
	T Array<T>::begin()
	{
		//display random value if no nodes exist
		if(this->isEmpty())
		{
			throw std::out_of_range(" ---[ Exception ]--- : The array is empty");
		}

		//show the value of the first Node
		else
		{
			return this->first->value;
		}
	};


	//remove the front Node and return its value
	//precondition: array must not be empty
	//postcondition: if nodes exist, the value of the first node is returned and the 
	//		new first node is the old first node's right. The former first node is destroyed
	template<class T>
	T Array<T>::pop()
	{
		//display random value if no nodes exist
		if(this->isEmpty())
		{
			throw std::out_of_range(" ---[ Exception ]--- : The array is empty");
		}

		//remove the first value and return it's value.
		else
		{
			//hold the value of the current first
			T returnVal = this->first->value;

			if(this->first == this->last)
			{
				std::cout << " ---[ Last Value ]--- : ";
				this->destroyNode(this->first);
				this->first = nullptr;
				this->last = nullptr;
			}

			else if (this->first->right)
			{
				this->first = this->first->right;
				this->destroyNode(this->first->left);
				this->first->left = nullptr;
			}

			--this->count;

			return returnVal;
		}
	};


	//get the size of the array
	//precondition: none
	//postcondition: an int showing the number of nodes is returned
	template<class T>
	int Array<T>::size()
	{
		return this->count;
	};


	//determine if the array is empty or now
	//precondition: none
	//postcondition: true returned if Array has no nodes and false if it has nodes
	template<class T>
	bool Array<T>::isEmpty()
	{
		return this->count == 0 || !this->first || !this->last ? true : false;
	};


	//Travereses every node in the array and prints it's value
	//precondtion: none
	//postcondition: string displayed
	template<class T>
	void Array<T>::print()
	{
		Node<T>* tmpNode = this->first;

		std::cout << "[";
		while(tmpNode)
		{
			if(tmpNode->right)
			{
				std::cout << " " << tmpNode->value << ",";
			}

			else
			{
				std::cout << " " << tmpNode->value;
			}
			
			tmpNode = tmpNode->right;
		}
		std::cout << " ]" << std::endl;
	}


	//display info and nodes in the array
	//precondition: array shouldn't be empty, exceptions will be caught and handled
	//postcondtion: array information is displayed
	//NOTE: multiple try catches are used so information is still printed out after an exception
	template<class T>
	void Array<T>::dump()
	{
		Node<T>* tmpPtr = this->first;
		int nodeCount = 0;
		std::string emptyArray = this->isEmpty()? "True":"False";

		std::cout << "--- DUMPING Array --- " << std::endl;

		std::cout << "  [ Array Info ]" << std::endl;
		std::cout << "Array Size: " << this->size() << std::endl;
		std::cout << "Array Empty: " << emptyArray << std::endl;

		try
		{
			std::cout << "First Value: " << this->begin() << std::endl;
		}
		catch(const std::out_of_range& e)
		{
			std::cerr << e.what() << '\n';
		}
		
		try
		{
			std::cout << "Last Value: " << this->end() << std::endl;
		}
		catch(const std::out_of_range& e)
		{
			std::cerr << e.what() << '\n';
		}
		
		std::cout << "  [ Nodes ]" << std::endl;
		this->print();

		std::cout << "--- END DUMP ---" << std::endl << std::endl;
	};


	//copy nodes from one array to another
	//precondtion: pointer parameter should be a node
	//postcondition: The node values from tmpNode are inserted into the new array as new nodes
	template<class T>
	void Array<T>::copyNodes(Node<T> * tmpNode)
	{
		//make sure the node isn't null
		if(tmpNode)
		{
			//add the value to array
			this->insert(tmpNode->value);

			//if a right node exists, keep adding the right node's value
			while(tmpNode->right)
			{
				tmpNode = tmpNode->right;
				this->insert(tmpNode->value);
			}
		}
	};


	//Sets a nodes pointers to null and deletes all pointers
	//precondition: nodeBeGone should be a node from the current array
	//postconditon: nodeBeGone has all it's pointers set to null and deleted along with itself
	template<class T>
	void Array<T>::destroyNode(Node<T> * nodeBeGone)
	{
		if(nodeBeGone)
		{
			nodeBeGone->value = 0;
			delete nodeBeGone->right;
			delete nodeBeGone->left;	
			nodeBeGone->left = nullptr;
			nodeBeGone->right = nullptr;
		}

		delete nodeBeGone;
		nodeBeGone = nullptr;
	}
}
