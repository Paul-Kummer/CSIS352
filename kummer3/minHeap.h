//File: MinHeap.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog2
//Modified: 1/29/21

#pragma once
#include <cstddef>
#include <iostream>
#include <cmath>

/*Description
This file contains the declarations and definitions of a doubly linked Node struct and
the MinHeap class, which utilizes nodes to track the position of values.
*/


//Create Namespace for anything heap related
namespace heap
{
	//Node struct for keeping track of values in the heap
	template <class nType>
	struct Node
	{
		nType value;
		int nodeLevel = 0;
		Node<nType>* parent = nullptr;
		Node<nType>* left = nullptr;
		Node<nType>* right = nullptr;
	};
	//End Node struct



	//declaration of MinHeap class
	template<class T>
	class MinHeap
	{
		public:
			MinHeap(); //default constructor
			MinHeap(const MinHeap<T>&); //copy constructor
			const MinHeap<T>& operator=(MinHeap<T>&); //assignment operator
			~MinHeap(); //destructor
			void insert(const T); //add nodes to the heap
			T top(); //view the value of the top Node
			T pop(); //view and remove the top node
			int size(); //get the number of nodes in the queue
			bool isEmpty(); //check if the queue has any nodes
			void printNodes(Node<T>*); //print all nodes in the tree
			void dump(); //view information and nodes that the queue currently has

		private:
			bool findLastNode(Node<T> *); //finds the rightmost node at the base of the tree and assings it to lastNode
			void destroyNode(Node<T>*); //set node pointers to null and delete node
			void compareAndSwap(Node<T>*); //check if inserted node is greater than it's parents, otherwise values are swapped
			void reverseCompareAndSwap(Node<T> *); //check if the root is the smallest value, otherwise swap with children
			void copyNodes(Node<T> *); //copy node values from one heap to another
			bool findNextParent(Node<T> *); //find the leftmost available branch available for the next node, assign nextNodeParent
			Node<T>* lastNode; //location of the last node on heap
			Node<T>* nextNodeParent; //location for the next node to be added
			Node<T>* root; //pointer to the Node at the top of the binary tree
			int count; //number of nodes in queue
			int treeHeight; //current tree level
	};
	//end declaration





	//########################
	//# DEFINE MinHeap CLASS #
	//########################

	//default constructor
	//requires a data type for initialization
	//postcondition: creates a MinHeap with no nodes
	template<class T>
	MinHeap<T>::MinHeap()
	{
		this->treeHeight = 0;
		this->lastNode = nullptr;
		this->nextNodeParent = nullptr;
		this->root = nullptr;
		this->count = 0;
	};



	//copy constructor
	//requirement: otherMinHeap must be a valid data type of T
	//postcondition: creates a MinHeap with copied nodes as the MinHeap parameter
	template<class T>
	MinHeap<T>::MinHeap(const MinHeap<T>& otherMinHeap)
	{
		//set default values for private members
		this->treeHeight = 0;
		this->lastNode = nullptr;
		this->nextNodeParent = nullptr;
		this->root = nullptr;
		this->count = 0;

		//now go through nodes and insert them
		this->copyNodes(otherMinHeap.root);
	};



	//copy nodes from one heap to another. Not the most efficient since every node is delted and added again
	template<class T>
	void MinHeap<T>::copyNodes(Node<T> * tmpNode)
	{
		//make sure the node isn't null
		if(tmpNode)
		{
			//add the value to tree
			this->insert(tmpNode->value);

			//explore left branches
			if(tmpNode->left)
			{
				this->copyNodes(tmpNode->left);
			}

			//explore right branches
			if(tmpNode->right)
			{
				this->copyNodes(tmpNode->right);
			}
		}
	}



	//add a new node to the tree
	//precondition: tmpVal must be same dataType as other nodes
	//postcondition: 	count increased by one, 
	//					new node added to tree, 
	//					values shifted to keep min value integrity
	//					nextNodeParent is assigned a new node if both branches have nodes
	//					treeHeight is changed if it goes onto another level
	template<class T>
	void MinHeap<T>::insert(const T tmpVal)
	{
		//increment node count
		++this->count;
		
		//redefine node count if necessary
		this->treeHeight = (int) log2(this->count);

		//create a new node to be inserted
		Node<T>* newNode = new Node<T>;
		newNode->nodeLevel = this->treeHeight;
		newNode->value = tmpVal;
		newNode->parent = this->nextNodeParent; //will be null if no other nodes exist
		newNode->left = nullptr;
		newNode->right = nullptr;

		//insert the node and swap values if needed
		if(this->root && this->nextNodeParent) //ensure that the pointer isn't null
		{
			if(this->nextNodeParent->left)
			{
				this->nextNodeParent->right = newNode;
				this->compareAndSwap(newNode);
			}
			
			else
			{
				this->nextNodeParent->left = newNode;
				this->compareAndSwap(newNode);
			}
		}

		else
		{
			newNode->parent = nullptr;
			this->root = newNode;
		}

		this->findNextParent(this->root);
	}



	//finds the next location for inserting a node
	//precondtion: tmpNode must be a valid node of the current heap
	//postconditio: the next parent node pointer for node insertion is updated
	template<class T>
	bool MinHeap<T>::findNextParent(Node<T> * tmpNode)
	{
		int numOfNodesPlusOne = this->count + 1;
		int searchLevel = (int)(log2(numOfNodesPlusOne)); //level that the parent should be at
		bool isFound = false; //stop the searching through the tree

		if(this->root)
		{
			if(!isFound)
			{
				//search the left branch
				if(tmpNode && tmpNode->left)
				{
					isFound = findNextParent(tmpNode->left);
				}

				else //node left is null, now check if it's on the right level
				{
					if(tmpNode && tmpNode->nodeLevel < searchLevel)
					{
						this->nextNodeParent = tmpNode;
						isFound = true;
					}
				}
			}

			if(!isFound)
			{
				//search the right branch
				if(tmpNode && tmpNode->right)
				{
					isFound = findNextParent(tmpNode->right);
				}

				else //node right is null, now check if it's on the right level
				{
					if(tmpNode && tmpNode->nodeLevel < searchLevel)
					{
						this->nextNodeParent = tmpNode;
						isFound = true;
					}
				}
			}
		}

		//root node
		else
		{
			this->nextNodeParent = nullptr;
		}

		return isFound;
	}



	//swaps values from tree base to root
	//precondition: evalNode must be in the same heap as calling method
	//postconditon: inserted node is bubbled up until its parent is smaller
	template<class T>
	void MinHeap<T>::compareAndSwap(Node<T> * evalNode)
	{
		Node<T> * tmpNode = new Node<T>;

		//ensure that the parent isn't null
		if(evalNode->parent)
		{
			//swap the values and move up the tree
			if(evalNode->value < evalNode->parent->value)
			{
				tmpNode->value = evalNode->parent->value;
				evalNode->parent->value = evalNode->value;
				evalNode->value = tmpNode->value;

				destroyNode(tmpNode);

				//only continue if the node isn't root
				if(evalNode->parent)
				{
					compareAndSwap(evalNode->parent);
				}
			}
		}
	}



	//swaps values from the tree root down
	//precondition: evalNode must be of the same heap calling it
	//postconditon: root is sifted down until it's children are not smaller than it
	template<class T>
	void MinHeap<T>::reverseCompareAndSwap(Node<T> * evalNode)
	{
		if(!this->isEmpty())
		{
			//make the root the 
			Node<T> * tmpNode = new Node<T>;

			//left branch exists, and parent node is greater. Swap with left child
			if(evalNode->left && evalNode->value > evalNode->left->value)
			{
				tmpNode->value = evalNode->value;
				evalNode->value = evalNode->left->value;
				evalNode->left->value = tmpNode->value;
				this->reverseCompareAndSwap(evalNode->left);
			}

			//right branch exists, and parent node is greater. Swap with right child
			if(evalNode->right && evalNode->value > evalNode->right->value)
			{
				tmpNode->value = evalNode->value;
				evalNode->value = evalNode->right->value;
				evalNode->right->value = tmpNode->value;
				this->reverseCompareAndSwap(evalNode->right);
			}
			
			this->destroyNode(tmpNode);
		}
	}


	//finds the next location for inserting a node
	//precondtion: tmpNode must be of the same heap calling it
	//postconditon: pointer to the bottom rightmost node is assinged to lastNode
	template<class T>
	bool MinHeap<T>::findLastNode(Node<T> * tmpNode)
	{
		//the last node is on the highest level and is farthest right
		int numOfNodes = this->count;
		int searchLevel = (int)(log2(numOfNodes));
		bool isFound = false;

		if(!isFound)
		{
			if(tmpNode->right)
			{
				isFound = findLastNode(tmpNode->right);
			}

			else //node left is null, now check if it's on the right level
			{
				if(tmpNode->nodeLevel == searchLevel)
				{
					this->lastNode = tmpNode;
					isFound = true;
				}
			}
		}

		if(!isFound)
		{
			if(tmpNode->left)
			{
				isFound = findLastNode(tmpNode->left);
			}

			else
			{
				if(tmpNode->nodeLevel == searchLevel)
				{
					this->lastNode = tmpNode;
					isFound = true;
				}
			}
		}

		return isFound;
	}


	//Travesrses the tree and prints node information
	//precondtion: evalNode should start with root to display all the nodes
	template<class T>
	void MinHeap<T>::printNodes(Node<T>* evalNode)
	{
		//ensure evalNode isn't null
		if(evalNode) 
		{
			//if it has no parent
			if(!evalNode->parent)
			{
				std::cout << "[ Root ] level: " << evalNode->nodeLevel << " | value: " << evalNode->value <<std::endl;
			}

			//if it isn't root and has empty branches
			else if(!evalNode->left && !evalNode->right)
			{
				std::cout << "[ Leaf ] level: " << evalNode->nodeLevel << " | value: " << evalNode->value << " |  parent value: " << evalNode->parent->value <<std::endl;
			}

			//must have parent and children
			else
			{
				std::cout << "[ Node ] level: " << evalNode->nodeLevel << " | value: " << evalNode->value << " |  parent value: " << evalNode->parent->value <<std::endl;
			}
			
			//left branch exists, and will be traversed
			if(evalNode->left)
			{
				printNodes(evalNode->left);
			}

			//right branch exists, and will be traversed
			if(evalNode->right)
			{
				printNodes(evalNode->right);
			}
		}
	}



	//overloaded assignment operator
	//requirement: MinHeap's must be of same data type
	//postcondition: MinHeap containing nodes of same values as the other
	template<class T>
	const MinHeap<T>& MinHeap<T>::operator=(MinHeap<T>& otherMinHeap)
	{
		this->copyNodes(otherMinHeap.root);
	};



	//destructor
	//postcondition: all pointers are set to null and are deleted
	template<class T>
	MinHeap<T>::~MinHeap()
	{
		while(this->root)
		{
			this->pop();
		}
		
		this->nextNodeParent = nullptr;
		this->lastNode = nullptr;
		this->root = nullptr;

		delete this->nextNodeParent;
		delete this->lastNode;
		delete this->root;
	}



	//view front Node's value
	//requirement: the MinHeap should have nodes
	//postcondition: value of the rear Node's data type is returned
	template<class T>
	T MinHeap<T>::top()
	{
		//display random value if no nodes exist
		if(this->isEmpty())
		{
			std::cout << "!!! Empty Heap !!!" << std::endl;
			T garbageVar;
			return garbageVar;
		}

		//show the value of the top Node
		else
		{
			return this->root->value;
		}	
	};


	//remove the front Node and return its value
	//requirement: the MinHeap should have nodes
	//postcondition: MinHeap root is changed and root Node is removed
	template<class T>
	T MinHeap<T>::pop()
	{
		//display random value if no nodes exist
		if(this->isEmpty())
		{
			this->count = 0;
			std::cout << "!!! Empty Heap !!!" << std::endl;
			T garbageVar;
			return garbageVar;
		}

		//remove the front value and return it's value. Then make last node root and sift it down
		else
		{
			//hold the value of the current root for returning
			T returnVal = this->root->value;

			//get the last node in heap
			this->findLastNode(this->root);

			//make sure the last node isn't the root node, if so set values to null and destroy root
			if(this->lastNode == this->root) 
			{
				this->destroyNode(this->root);
				this->root = nullptr;
				this->lastNode = nullptr;
			}

			//make the root value the value of the last node
			else
			{
				this->root->value = this->lastNode->value;

				if (this->lastNode->parent->left == this->lastNode)
				{
					this->lastNode->parent->left = nullptr;
				}

				else
				{
					this->lastNode->parent->right = nullptr;
				}

				this->destroyNode(this->lastNode);
			}
			
			--this->count;

			
			if(this->root)
			{
				this->reverseCompareAndSwap(this->root);
			}

			return returnVal;
		}
	};


	//Sets a nodes pointers to null and deletes all pointers
	//precondition: nodeBeGone should be a node from the current heap
	//postconditon: nodeBeGone has all it's pointers set to null and delete along with itself
	template<class T>
	void MinHeap<T>::destroyNode(Node<T> * nodeBeGone)
	{
		if(nodeBeGone)
		{
			nodeBeGone->value = 0;
			nodeBeGone->nodeLevel = 0;
			nodeBeGone->parent = nullptr;
			nodeBeGone->left = nullptr;
			nodeBeGone->right = nullptr;
			
			delete nodeBeGone->parent;
			delete nodeBeGone->right;
			delete nodeBeGone->left;
			
			nodeBeGone = nullptr;
		}

		delete nodeBeGone;
	}



	//return the heap size
	template<class T>
	int MinHeap<T>::size()
	{
		return this->count;
	};

	//return whether the heap is empty or not
	//postcondition: true returned if MinHeap has no nodes and false if it has nodes
	template<class T>
	bool MinHeap<T>::isEmpty()
	{
		return this->count == 0 || !this->root? true : false;
	};

	//display info and nodes in the heap
	//requirement: the MinHeap should have nodes or invalid values will occur
	template<class T>
	void MinHeap<T>::dump()
	{
		Node<T>* tmpPtr = this->root;
		int nodeCount = 0;
		std::string emptyMinHeap = this->isEmpty()? "True":"False";

		std::cout << "--- DUMPING MinHeap --- " << std::endl;

		std::cout << "  [ MinHeap Info ]" << std::endl;
		std::cout << "MinHeap Size: " << this->size() << std::endl;
		std::cout << "MinHeap Empty: " << emptyMinHeap << std::endl;
		std::cout << "Top Value: " << this->top() << std::endl;
		
		std::cout << "  [ Nodes ]" << std::endl;
		this->printNodes(this->root);

		std::cout << "--- END DUMP ---" << std::endl << std::endl;
	};
}
