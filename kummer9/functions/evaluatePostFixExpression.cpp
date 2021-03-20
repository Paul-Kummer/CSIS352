//File: evaluatePostFixExpression.cpp
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog9
//Modified: 03/10/21

/*
Description:
This function takes in a token queue and builds a parse tree from that queue. Then it outpus the
root node of the expression.
*/


#include "../prototypes.h"


//Precondition: A valid postfix queue of tokens
//Postconditon: The postfix queue has all tokens removed and a newly created abstractNode's pointer will be returned
AbstractNode* evaluatePostFixExpression(queueType<Token>& postfixQ)
{
	//variables
	std::vector<AbstractNode*> evalStack;
	AbstractNode *terminalOne, *terminalTwo, *expr, *curNode, *result = nullptr;
	Token curToken;

	//go through the postfix queue until all tokens are removed
	while(!postfixQ.isEmptyQueue())
	{
		//get the value of what of the token at the front of the queue
		curToken = postfixQ.front();

		//all operands are added as leafs
		if (curToken.IsOperand()) // operands: "23, 1, 50, 92, etc."
		{
			curNode = new LeafNode(curToken);
			evalStack.insert(evalStack.begin(), curNode);
		}

		//check if the token is an operator. If so, take two abstractNodes off the eval stack and make them the left and right values
		//of a new binaryNode
		else if (curToken.IsOperator()) // operators: "+, -, *, /, ^"
		{
			//NOT USED, The commented part is part of the attempt at unaryMinusNode
			if(/*curToken.Operator() != '-' && */evalStack.size() < 2) //The eval stack doesn't have enough values to make a binary node
			{
				throw std::length_error("\n---Exception--- :The expression is missing operands, or you placed an operator in the wrong spot.\n");
			}

			//NOT USED
			/*This was an attempt on making an expression or token by adding a '-' sign in front of it
			if(curToken.Operator() == '-' && evalStack.size() == 1) //This means that the value should be negative
			{
				terminalOne = new UnaryMinusNode(evalStack.front());
				evalStack.erase(evalStack.begin());
				evalStack.insert(evalStack.begin(), terminalOne);
			}
			*/

			else //remove two abstractNodes from the eval stack and make them the left and right values of a new binary node. The new binary node goes on the eval stack
			{
				terminalTwo = evalStack.front();
				evalStack.erase(evalStack.begin());

				terminalOne = evalStack.front();
				evalStack.erase(evalStack.begin());

				expr = new BinaryNode (terminalOne, terminalTwo, curToken);
				evalStack.insert(evalStack.begin(), expr);
			}
		}
		else // the operator isn't valid
		{
			throw std::logic_error("\n---Exception--- :The expression is ill formed, please use only integers and operators (*, /, +, -, ^, %)\n");
		}


		//If there were any parenthesis, they would be ignored since they are not used in postfix evaluation


		//Remove the token from the front of the queue and process the next token.
		if(!postfixQ.isEmptyQueue())
		{
			postfixQ.deleteQueue();
		}
	}

	//The last AbstractNode pointer on evalStack is the root of the tree and returned
	if(evalStack.size() > 0)
	{
		result = evalStack.front();
		evalStack.clear();
	}
	else
	{
		throw std::logic_error("\n--Exception-- :No valid operands\n");
	}
	
	return result;
}