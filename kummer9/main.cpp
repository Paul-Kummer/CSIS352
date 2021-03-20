//File: main.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog9
//Modified: 03/10/21

/*
Description:
This program will prompt the user to write infix expressions unitl the expression equals 0.
The user must enter a valid infix expression, otherwise the program will terminate. After 
entering a valid infix expression, the program will turn the string into tokens and place
them into an infix queue. Once the infix queue is filled from the input stream, the infix
queue is copied into a temporary queue. The temporary queue has each token extracted in order
and outputted to the user. Then the infix queue has each token removed and placed into a 
postfix queue using an algorithm. When the postfix queue is filled from the infix queue,
The infix queue is copied and the copied queue has its tokens extracted in order. Finally,
a third function is called, which extracts the tokens in the postfix queue and peforms the
desired caculations in the correct order.The results of the calculations are given to the 
token result and is outputted to the user.
*/


#include "prototypes.h"
#include "queue/queueType.h"
#include "stack/stackType.h"
#include "token/token.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//Precondition: None
//Postconditon: Output to screen
int main(int argc, char const *argv[])
{
	//variables
	queueType<Token> infixQ;
	queueType<Token> postfixQ;
	stackType<Token> conversionStack;
	Token infixExpression;
	AbstractNode* result;
	std::string userIn;
	std::ifstream testDoc;
	
	bool usingFile = argc == 2? true:false;

	if(usingFile)
	{
		testDoc.open(argv[1]); //open the file with of the command line argument
	}

	//display information to the user
	cout << endl << endl << string(100, '=') << endl
		<< "This Program will take an infix expression, IE: 1 + 2 * 3 - 4 / 5 + 6,"
		<< endl << "and convert it to a postfix expresion, IE: 1 2 3 * + 4 5 / - 6 +."
		<< endl << "After showing the expression forms, the result will be displayed."
		<< endl << "Note: -(2+2) is not valid, it should be written -1*(2+2)"
		<< endl << "[ Enter ctrl+d exit ]"
		<< endl << string(100, '=') << endl;


		//continously prompt user for infix strings until the result is 0
		do
		{
			try
			{
				if(usingFile && getline(testDoc, userIn))//testDoc >> userIn) //extract commands from the file
				{
					cout <<  endl << string(100, '*') << endl;
					cout << "Enter an infix expression [ctrl+d-Exits]: ";
					cout << userIn << endl;

					
					std::stringstream toStream;
					toStream.str(userIn);
					
					while(toStream >> infixExpression)
					{
						infixQ.addQueue(infixExpression);
					};
				}
				else
				{
					if(usingFile)
					{
						cin.clear();
						usingFile = false;
					}
					
					//prompt user for a valid infix expression
					cout <<  endl << string(100, '*') << endl;
					cout << "Enter an infix expression [ctrl+d-Exits]: ";
					//cin.putback('0'); this will force the token analysis to recognize a leading operator NOT USED
					cin >> infixExpression;
				}

				if(!std::cin.eof())
				{
					if(!usingFile)
					{
						//turn the user input into tokens and add them to the infix queue
						populateInfixQ(infixExpression, infixQ);
					}

					//copy the infix queue so the data doesn't get altered when its outputted to the user
					queueType<Token>* tmpInfix =  new queueType<Token>(infixQ);

					//output the infix queue to the user by extracting every token in the tmpInfix queue
					cout << "INFIX QUEUE" << endl;
					while(!tmpInfix->isEmptyQueue())
					{
						Token tmpTok = tmpInfix->front();
						tmpInfix->deleteQueue();
						cout << tmpTok << " ";
					}
					delete tmpInfix;
					tmpInfix = nullptr;

					//turn the infix queue into a postfix queue
					populatePostfixQ(infixQ, postfixQ, conversionStack);

					//copy the postfix queue so the data doesn't get altered when its outputted to the user
					queueType<Token>* tmpPostfix = new queueType<Token>(postfixQ);
					cout << endl << endl << "POSTFIX QUEUE" << endl;
					while(!tmpPostfix->isEmptyQueue())
					{
						Token tmpTok = tmpPostfix->front();
						tmpPostfix->deleteQueue();
						cout << tmpTok << " ";
					}
					delete tmpPostfix;
					tmpPostfix = nullptr;

					//assignt the result of the evaluation of the postfixQ to the Token result and display it to the user
					result = evaluatePostFixExpression(postfixQ);
					cout << endl << endl << "RESULT: " << result->eval() << endl;
					delete result;
					result = nullptr;
				}
			}
			catch(const std::length_error& e)
			{
				std::cerr << e.what() << '\n';
				cin.clear();
				postfixQ.destroyQueue();
			}
			catch(std::logic_error& e)
			{
				std::cerr << e.what() << '\n';
				cin.clear();
				postfixQ.destroyQueue();
			}
			catch(const std::exception& e)
			{
				std::cerr << e.what() << '\n';
				cin.clear();
				postfixQ.destroyQueue();
			}
		} while (!std::cin.eof()); //quits when user enters ctrl+d

		if(usingFile)
		{
			testDoc.close();
		}
		cout << "\n\t GOODBYE! \n";
	
	return 0;
}

