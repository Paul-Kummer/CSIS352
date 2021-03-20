//File: prototypes.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog9
//Modified: 03/10/21

#pragma once

#include "queue/queueType.h"
#include "stack/stackType.h"
#include "token/token.h"
#include "nodes/ch12-1.h"
#include <vector>
#include <stdexcept>

void populateInfixQ(Token userIn, queueType<Token>& preFixQ);
void populatePostfixQ(queueType<Token>& prefixQ, queueType<Token>& postFixQ, stackType<Token>& conversionStack);
AbstractNode* evaluatePostFixExpression(queueType<Token>& postfixQ);