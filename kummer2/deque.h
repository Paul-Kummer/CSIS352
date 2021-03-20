//File: deque.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog2
//Modified: 1/22/21

#pragma once
#include <cstddef>
#include <iostream>

/*Description
This file contains the declarations and definitions of a doubly linked node struct and
the Deque class, which utilizes nodes to track the position of values.
*/

namespace heap
{
	//node struct for keeping track of values in the deque
	template <class nType>
	struct node
	{
		nType value;
		node<nType>* next = nullptr;
		node<nType>* previous = nullptr;
	};

	//declaration of Deque class
	template<class T>
	class Deque
	{
		public:
			Deque(); //default constructor
			Deque(const Deque<T>&); //copy constructor
			const Deque<T>& operator=(Deque<T>&); //assignment operator
			~Deque(); //destructor
			void pushFront(const T&); //add nodes to the queue front
			void pushRear(const T&); //add nodes to the queue back
			//non destructive
			T front(); //view the value of the first node
			T rear(); //view the value of the last node
			//destructive
			T popFront(); //delete the first node and retireve it's value
			T popRear(); //delete the last node and retrieve it's value
			int dequeSize(); //get the number of nodes in the queue
			bool isEmpty(); //check if the queue has any nodes
			void dump(); //view information and nodes that the queue currently has

		private:
			node<T>* queueFront; //pointer to the node at the front of the queue
			node<T>* queueBack; //pointer to the node at the back of the queue
			int count; //number of nodes in queue
	};
	//end declaration

	//default constructor
	//requires a data type for initialization
	//postcondition: creates a deque with no nodes
	template<class T>
	Deque<T>::Deque()
	{
		this->queueFront = nullptr;
		this->queueBack = nullptr;
		this->count = 0;
	};

	//copy constructor
	//requirement: tmpVal must be a valid data type of T
	//postcondition: creates a deque with copied nodes as the deque parameter
	template<class T>
	Deque<T>::Deque(const Deque<T>& otherDeque)
	{
		//set default values for private members
		this->queueFront = nullptr;
		this->queueBack = nullptr;
		this->count = 0;
		node<T>* curNode = otherDeque.queueFront;

		//go through otherDeque's nodes and copy values
		while(curNode)
		{
			this->pushRear(curNode->value);

			curNode = curNode->next;
		}

		//may need to delete curNode
		//delete curNode;
	};

	//overloaded assignment operator
	//requirement: Deque's must be of same data type
	//postcondition: deque containing nodes of same values as the other
	template<class T>
	const Deque<T>& Deque<T>::operator=(Deque<T>& otherDeque)
	{
		//reinitialize this to defaults, erasing any previous nodes
		while(!this->isEmpty())
		{
			this->popRear();
		}

		this->queueFront = nullptr;
		this->queueBack = nullptr;
		this->count = 0;

		node<T>* curNode = new node<T>; 
		curNode = otherDeque.queueFront;

		//go through otherDeque's nodes and copy values
		while(curNode)
		{
			this->pushRear(curNode->value);

			curNode = curNode->next;
		}

		//may need to delete curNode
		//delete curNode;
	};

	//destructor
	//postcondition: all pointers are set to null and are deleted
	template<class T>
	Deque<T>::~Deque()
	{
		//placeholder for reassigning front node
		node<T>* tmpNode = this->queueFront;

		//go through all nodes and delete pointers and set to null
		while(this->queueFront)
		{
			//temporary store what will be the deques next front
			tmpNode = this->queueFront->next; 

			//set front's pointers to null
			this->queueFront->next = nullptr;
			this->queueFront->previous = nullptr;

			//delete the node
			delete this->queueFront;

			//reassign the front
			this->queueFront = tmpNode;
		}

		//set pointers to null, stopping memory leaks
		tmpNode = nullptr;
		this->queueBack = nullptr;
		this->queueFront = nullptr;

		//delete pointers, stopping dangling pointers
		delete tmpNode;
		delete this->queueBack;
		delete this->queueFront;
	};

	//add to the queue front
	//requirement: tmpVal must be a valid data type of T
	//postcondition: Deque front is changed and another node is added
	template<class T>
	void Deque<T>::pushFront(const T& tmpVal)
	{
		//create a new node to be placed in the front with the value tmpVal
		node<T>* newNode;
		newNode = new node<T>;
		newNode->value = tmpVal;
		newNode->next = nullptr;
		newNode->previous = nullptr;

		//make the new node the front and back if it is the only node
		if(this->isEmpty())
		{
			this->queueFront = newNode;
			this->queueBack = newNode;
		}

		//move the current front node to second position and made the new node first
		else
		{
			this->queueFront->previous = newNode; //set the current front nodes previous pointer to point to newNode, setting it up to be the second node
			newNode->next = this->queueFront; //set the newNode's next pointer to point to the current front node, setting it up to be the first node
			this->queueFront = newNode; //assign the queue's front to be the newNode
		}
		
		//increment the node counter
		this->count++;
	};

	//add tot he queue back
	//requirement: tmpVal must be a valid data type of T
	//postcondition: Deque rear is changed and another node is added
	template<class T>
	void Deque<T>::pushRear(const T& tmpVal)
	{
		//create a new node to be placed in the front with the value tmpVal
		node<T>* newNode;
		newNode = new node<T>;
		newNode->value = tmpVal;
		newNode->next = nullptr;
		newNode->previous = nullptr;

		//make the new node the front and back if it is the only node
		if(this->isEmpty())
		{
			this->queueFront = newNode;
			this->queueBack = newNode;
		}

		//move the current back node to second to last position and made the new node last
		else
		{
			this->queueBack->next = newNode; //set the current last node's next pointer to newNode, setting it up to be second to last
			newNode->previous = this->queueBack; //set the newNode's previous pointer to the current last node, setting it up to be last
			this->queueBack = newNode; //assing the queue's back to be the newNode
		}
		
		//increment the node count
		this->count++;
	};

	//view front node's value
	//requirement: the deque should have nodes
	//postcondition: value of the rear node's data type is returned
	template<class T>
	T Deque<T>::front()
	{
		//display random value if no nodes exist
		if(this->isEmpty())
		{
			std::cout << "!!! Empty Queue !!!" << std::endl;
			T garbageVar;
			return garbageVar;
		}

		//show the value of the front node
		else
		{
			return queueFront->value;
		}	
	};

	//view back node's value
	//requirement: the deque should have nodes
	//postcondition: value of the front node's data type is returned
	template<class T>
	T Deque<T>::rear()
	{
		//display random value if no nodes exist
		if(this->isEmpty())
		{
			std::cout << "!!! Empty Queue !!!" << std::endl;
			T garbageVar;
			return garbageVar;
		}

		//show the value of the front node
		else
		{
			return queueBack->value;
		}	
	};

	//remove the front node and return its value
	//requirement: the deque should have nodes
	//postcondition: Deque front is changed and front node is removed
	template<class T>
	T Deque<T>::popFront()
	{
		//display random value if no nodes exist
		if(this->isEmpty())
		{
			std::cout << "!!! Empty Queue !!!" << std::endl;
			T garbageVar;
			return garbageVar;
		}

		//remove the front value and return it's value. Then make the next node the front node
		else
		{
			T returnVal = this->queueFront->value; //holds value of the front node so it can be deleted
			this->queueFront = this->queueFront->next; //reassign the front node
			delete this->queueFront->previous; //delete the former front node
			this->queueFront->previous = nullptr; //set the pointer to the former front node to null
			this->count--; //decrement the node count
			return returnVal;
		}
	};

	//remove the last node and return its value
	//requirement: the deque should have nodes
	//postcondition: Deque rear is changed and rear node is removed
	template<class T>
	T Deque<T>::popRear()
	{
		//display random value if no nodes exist
		if(this->isEmpty())
		{
			std::cout << "!!! Empty Queue !!!" << std::endl;
			T garbageVar;
			return garbageVar;
		}

		//remove the last node and return it's value. Then make the second to last node the last node
		else
		{
			T returnVal = this->queueBack->value; //holds the value of the last node so it can be deleted
			this->queueBack = this->queueBack->previous; //reassign the back node
			delete this->queueBack->next; //delete the former last node
			this->queueBack->next = nullptr; //set the pointer to the former last nod to null
			this->count--; //decrement the node count
			return returnVal;
		}
	};

	//return the queues size
	template<class T>
	int Deque<T>::dequeSize()
	{
		return this->count;
	};

	//return whether the queue is empty or not
	//postcondition: true returned if Deque has no nodes and false if it has nodes
	template<class T>
	bool Deque<T>::isEmpty()
	{
		return this->count == 0? true : false;
	};

	//display info and nodes in the queue
	//requirement: the deque should have nodes or invalid values will occur
	template<class T>
	void Deque<T>::dump()
	{
		node<T>* tmpPtr = this->queueFront;
		int nodeCount = 0;
		std::string emptyDeque = this->isEmpty()? "True":"False";

		std::cout << "--- DUMPING DEQUE --- " << std::endl;

		std::cout << "  [ Deque Info ]" << std::endl;
		std::cout << "Deque Size: " << this->dequeSize() << std::endl;
		std::cout << "Deque Empty: " << emptyDeque << std::endl;
		std::cout << "Front Value: " << this->front() << std::endl;
		std::cout << "Back Value: " << this->rear() << std::endl;

		std::cout << "  [ Nodes ]" << std::endl;
		while(tmpPtr)
		{
			std::cout << "node [" << nodeCount << "] value: " << tmpPtr->value << std::endl;
			tmpPtr = tmpPtr->next;
			nodeCount++;
		}

		std::cout << "--- END DUMP ---" << std::endl << std::endl;
	};
}
