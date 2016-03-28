/* typeChecking.h */

#include <iostream>
#include <regex>
#include <string>
using namespace std;

bool isInt(string);
bool isFloat(string);
//bool isOperator(string); deprecated
bool isVariable(string);
bool isArithOperator(string);
bool isLogicalOperator(string);
bool isAssignmentOperator(string);
bool isSemiColon(string);
bool isKeyword(string);
