
#include "interp.h"


using namespace std;

/*
Token interp(ASTNode *root, env * environment){
    if (root -> token -> getType() == "AssignmentOperator") {
        // creation of a new variable or updating of a variable that exists
        if (environment.count(root -> left -> getValue())) {
            // set the existing variable equal to result of the parse tree
        } else {
            // create new variable and interpret tree
            return interpArithmeticExpression(root -> right, environment);
        }
    } else if (root -> token -> getType() == "LogicalOperator") {

        if (root -> token -> getVal() == "==") {
            return (interpArithmeticExpression(root -> left, environment) == interpArithmeticExpression(root -> right, environment));
        } else if (root -> token -> getVal() == "<=") {
            return (interpArithmeticExpression(root -> left, environment) <= interpArithmeticExpression(root -> right, environment));
        } else if (root -> token -> getVal() == ">=") {
            return (interpArithmeticExpression(root -> left, environment) >= interpArithmeticExpression(root -> right, environment));
        } else if (root -> token -> getVal() == "<") {
            return (interpArithmeticExpression(root -> left, environment) < interpArithmeticExpression(root -> right, environment));
        } else if (root -> token -> getVal() == ">") {
            return (interpArithmeticExpression(root -> left, environment) > interpArithmeticExpression(root -> right, environment));
        }

    }
}


Token interpArithmeticExpression(ASTNode *root, env * environment) {
    if ((root -> left -> token -> getType() == "Float" || root -> left -> token -> getType() == "Variable") &&
    (root -> right -> token -> getType() == "Float" || root -> right -> token -> getType() == "Variable")) {
        // this is our base case so at this point we evalute accoring to wahtever operator is the root and return it
        if (root -> token -> getVal() == "+") {
            // return a token with the value = to the answer of the arithmetic expression
            //cout << stof(root -> left -> token -> getVal());
            return Token(to_string(stof(root -> left -> token -> getVal()) + stof(root -> right -> token -> getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "-") {
            return Token(to_string(stof(root -> left -> token -> getVal()) - stof(root -> right -> token -> getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "*") {
            return Token(to_string(stof(root -> left -> token -> getVal()) * stof(root -> right -> token -> getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "/") {
            return Token(to_string(stof(root -> left -> token -> getVal()) / stof(root -> right -> token -> getVal())), "Float", 0, 0, 0);
        }
    } else {
        // to the right we have an operator so we need to go down the tree
        if (root -> token -> getVal() == "+") {
            cout << "Here" << root -> right -> token -> getVal() << endl;
            return Token(to_string(stof(root -> left -> token -> getVal()) + stof(interpArithmeticExpression(root -> right, environment).getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "-") {
            return Token(to_string(stof(root -> left -> token -> getVal()) - stof(interpArithmeticExpression(root -> right, environment).getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "*") {
            return Token(to_string(stof(root -> left -> token -> getVal()) * stof(interpArithmeticExpression(root -> right, environment).getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "/") {
            return Token(to_string(stof(root -> left -> token -> getVal()) / stof(interpArithmeticExpression(root -> right, environment).getVal())), "Float", 0, 0, 0);
        }
    }
}
*/
Token interp(ASTNode *root, env * environment) {
    if (root -> token -> getType() == "Float") {
        return *root -> token;
    } else if (root -> token -> getType() == "ArithOperator") {
        if (root -> token -> getVal() == "+") {
            return Token(to_string(stof(interp(root -> left, environment).getVal()) + stof(interp(root -> right, environment).getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "-") {
            return Token(to_string(stof(interp(root -> left, environment).getVal()) - stof(interp(root -> right, environment).getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "*") {
            return Token(to_string(stof(interp(root -> left, environment).getVal()) * stof(interp(root -> right, environment).getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "/") {
            return Token(to_string(stof(interp(root -> left, environment).getVal()) / stof(interp(root -> right, environment).getVal())), "Float", 0, 0, 0);
        }
    }
}
