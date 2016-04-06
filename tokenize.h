// tokenize.h
// function definitions to break a line into tokens

#include <string>
#include "Token.h"
#include "typeChecking.h"
#include <vector>

string checkType(string);
vector<string> seperateIntoStrings(string);
Token *createToken(string);
