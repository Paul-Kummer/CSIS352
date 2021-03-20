//File: prototypes.h
//Name: Paul Kummer
//Class: CSIS 352
//Program: prog1
//Modified: 01/15/21

#pragma once

#include "queue/queueType.h"
#include "stack/stackType.h"
#include "token/token.h"

void populateInfixQ(Token userIn, queueType<Token>& preFixQ);
void populatePostfixQ(queueType<Token>& prefixQ, queueType<Token>& postFixQ, stackType<Token>& conversionStack);
Token evaluatePostFixExpression(queueType<Token>& postfixQ, stackType<Token>& evalStack);