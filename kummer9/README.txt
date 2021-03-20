// File: README.txt
// Name: Paul Kummer
// Class: CSIS 252
// Program: prog9
// Modified: 12/02/20


	-[Description]-
prog9 will take and user inputted infix expression and convert it into a postfix expression. Additionally,
the user will have outputted to them the infix expression, postfix expression, and the result of the
expression after evalutaion. The user may continue entering infix expression until they decide to exit
by entering ctrl+d.


	-[Inputs]- (input method : input type : description)
1.) keyboard : string : string entered by the user in the command prompt used to make an infix expression.
	repeat 1.


	-[Outputs]- (output method : output type : description)
1.) display : string : text displayed on monitor showing infix expression, postfix expression, and result


	-[Design]-
This program takes user input and parses it into tokens with a function call. These tokens are placed into 
a queue, preserving the order of the infix expression. Next a function converts the infix queue into a 
postfix expression. During the conversion, the infix queue has it's tokens removed and evaluated to determine 
the postfix order. A token stack is used as an intermediary storage throughout the translation from infix to 
postfix to preserve the order of operations. Afterwards, a thrid function evaluates the postfix queue into
a parse tree of an AbstractNode. This is done by removing all tokens from the postfix queue and making them
a BinaryNode, LeafNode, or UnaryMinusNode, depending on what operation is being evaluated. If the token is
a digit, it will become a LeafNode. If there is an operator, then the first two abstractNodes in the queue
will become the left and right hand sides of the expression. The UnaryMinusNode is currently unused because of
problems with the stream insertion operator making tokens correctly and having the order of operations preserved.
In the code, there are fragments of a partially working design with the UnaryMinusNode. Therefore, expressions
cannot have a minus operator before an expression. Instead, -1 has to be multiplied by the expression. negative
valued tokens do work though.

After each function call in main, the results of that function call are outputted to the user. This is done
by either copying a queue then removing all it's tokens and ouputting to the output stream or just displaying
the returned token of the function to the output stream. After a copied queue has been used it is deleted and
it's pointer is set to null.



	-[Files] (file : function : description)-
main.cpp : main : executes the main line of logic

prototypes.h : declarations : declares the functions to be used in main

token.o : object file for tokens : used for linking while making executable

makefile : compilation & linking : creates and executable of prog10

README.txt : information : gives detailed information about prog10

test.txt : test expressions : expression that were tested

testResults.txt : show results : This text files show the expected and actual results of the make test

/functions/evaluatePostFixExpression.cpp : defines the function : defines the algorithm of how to evaluate a postfix queue

/functions/populateInfixQ.cpp : defines the function : defines the algorithm of how to populate a infix queue

/functions/populatePostfixQ.cpp : defines the function : defines the algorithm of how to populate a postfix queue

/queue/queueType.h : declaration of Class : declares what an ABT queue is

/stack/stackType.h : declaration of Class : declares what an ABT stack is

/token/token.h : declaration of Class : declares what a token object is

/token/token.o : backup of token object : incase the token object gets deleted from the parent directory

/nodes/ch12-1.h : AbstractNodes : this contains the declaration and definition of AbstractNodes


	-[Testing]-
Various infix expressions have been tested, which are located in the test.txt file. They include expressions
with spaces, tokens with negative values, exponents of exponents, stacked parenteses, invalid tokens, stacked
operators, and different combinations of operators.


	-[Bugs]-
1.) Expressions cannot have a negative prefix may cause unexpected results. Instead used "-1 *" to get the negative value

