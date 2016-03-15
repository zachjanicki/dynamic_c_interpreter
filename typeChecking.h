/* typeChecking.h */

#include <iostream>
#include <regex>
#include <string>
#include "token.h"

bool isInt(Token);
bool isFloat(Token);
bool isOperator(Token);
bool isVariable(Token);
bool isKeyword(Token);
