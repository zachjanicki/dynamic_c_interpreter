// tokenize.cpp
// tokenize function implementation


string checkType(string token) {
    if (isInt(token)) {
        return "Int";
    } else if (isFloat(token)) {
        return "Float";
    } else if (isArithOperator(token)) {
        return "Arith Operator";
    } else if (isLogicalOperator(token)) {
        return "Logical Operator";
    } else if (isAssignmentOperator(token)) {
        return "Assignment Operator";
    } else if (isVariable(token)) {
        return "Variable";
    } else if (isSemiColon(token)) {
        return "Semicolon";
    } else if (isKeyword(token)) {
        return "Keyword";
    } else {
        return "Undefined Token Type";
    }
}

vector<string> seperateIntoStrings(string line) {
    //a=1;
    //a = 1;
    struct currentToken {
        string characters;
        string type;
    };
    vector<string> tokenList;
    struct currentToken token;
    int i;
    for (i = 0; i < line.length(); i++) {
        token.type = checkType();
        if (line[i] != ' ') { // dealing with characters right next to each other "aabbas;, a=1, var==var2, ect..."
            token.characters += line[i];
            string tempTypeCheck = token.type;
            token.type = checkType();
            if (token.type != tempTypeCheck && i != 0) { // then we need to add what we have onto the tokenList
                token.characters.pop_back();
                i--;
                tokenList.pushback(token.characters);
                token.characters = "";
                token.type = "";
            }

        } else { //there is a space so we add what we have to the tokenList and reset the struct
            tokenList.pushback(token.characters);
            token.characters = "";
            token.type = "";
        }
    }
    return tokenList;
}
