#pragma once
#include <math.h>
#include "../token/token.h"
#include <stdexcept>


/*
Description:
These classes and subclasses are the basses of the parse tree of an expression to be evaluated
	-AbstractNode is a pure virtual class. It cannot be instantiated
	-LeafNode is a terminal symbol and holds the value of a double
	-UnaryMinusNode is nonterminal that holds another abstract node, and makes the value negative
	-BinaryNode is a nonterminal that 
*/
class AbstractNode 
{
	public:
		virtual double eval() = 0;
		AbstractNode() {};
		virtual ~AbstractNode() {};
};

class LeafNode : public AbstractNode 
{
	private:
		Token value;
	public:
		LeafNode(Token d) : value(d) {};
		~LeafNode() {};
		double eval() 
		{
			return value.Operand();
		};
};

class UnaryMinusNode : public AbstractNode 
{
	private:
		AbstractNode * child = nullptr;
	public:
		UnaryMinusNode(AbstractNode * c) : child(c) {};
		~UnaryMinusNode() {delete child;};
		virtual double eval() 
		{
			return ((-1.0)*child->eval());
		};
};

class BinaryNode : public AbstractNode 
{
	private:
		AbstractNode * left = nullptr;
		AbstractNode * right = nullptr;
		Token op;
	public:
		BinaryNode(AbstractNode * l,AbstractNode * r,Token o) : left(l), right(r), op(o) {};
		~BinaryNode() 
		{
			delete left; 
			delete right;
		};
		virtual double eval() 
		{
			if(!left && !right)
			{
				throw std::logic_error("\n--Exception-- :The expression contains an invalid operand\n");
			}
			else
			{
				switch(op.Operator()) 
				{
					case '+':
						return left->eval()+right->eval();
					case '-':
						return left->eval()-right->eval();
					case '*':
						return left->eval()*right->eval();
					case '/':
						return left->eval()/right->eval();
					case '%': //added in from original
						return fmod(left->eval(), right->eval());
					case '^': //added in from original
						return pow(left->eval(), right->eval());
					default:
						return 0;
				};
			}
		};
};
