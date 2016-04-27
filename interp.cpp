
#include "interp.h"


using namespace std;

Token* interp(ASTNode *root, env * environment) {

    Token *result;

    if (root -> token -> getType() == "Float") {
        result = root -> token;
    } else if (root -> token -> getType() == "String"){
        result = root -> token;

    } else if (root -> token -> getType() == "Variable") {
        if (environment -> variables[root -> token -> getVal()]) {
            result = environment -> variables[root -> token -> getVal()];
        } else {
            cout << "Variable " << root -> token -> getVal() << " is not defined" << endl;
        }
    } else if (root -> token -> getType() == "AssignmentOperator") {
        environment -> variables[root -> left -> token -> getVal()] = interp(root -> right, environment);
        return NULL;
    } else if (root -> token -> getType() == "ArithOperator") {
        if (root -> token -> getVal() == "+") {
            result = new Token(to_string(stof(interp(root -> left, environment)->getVal()) + stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "-") {
            result = new Token(to_string(stof(interp(root -> left, environment)->getVal()) - stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "*") {
            result = new Token(to_string(stof(interp(root -> left, environment)->getVal()) * stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
        } else if (root -> token -> getVal() == "/") {
            result = new Token(to_string(stof(interp(root -> left, environment)->getVal()) / stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
        }
    } else if (root -> token -> getType() == "LogicalOperator") {
        int logic;
        Token True("1", "Float", 0,0,0), False("0", "Float", 0,0,0);
        if (root -> token -> getVal() == "<") {
            logic = interp(root -> left, environment)->getVal() < interp(root -> right, environment)->getVal();
            if (logic) {
                result = &True;
            }
            else {
                result = &False;
            }
        } else if (root -> token -> getVal() == ">") {
            logic = interp(root -> left, environment)->getVal() > interp(root -> right, environment)->getVal();
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "!=") {
            logic = interp(root -> left, environment)->getVal() != interp(root -> right, environment)->getVal();
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "==") {
            logic = interp(root -> left, environment)->getVal() == interp(root -> right, environment)->getVal();
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "<=") {
            logic = interp(root -> left, environment)->getVal() <= interp(root -> right, environment)->getVal();
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == ">=") {
            logic = interp(root -> left, environment)->getVal() >= interp(root -> right, environment)->getVal();
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        }
    } else if (root -> token -> getType() == "Keyword") {
        if (root -> token -> getVal() == "while") {
            while (true) {
                if (interp(root -> left, environment) -> getVal() == "1") {
                    Token *uselessToken = interp(root -> right, environment);
                } else {
                    break;
                }
            }
            return NULL;
        } else if (root -> token -> getVal() == "if") {
            cout << root -> right -> token -> getVal() << endl;
            if (interp(root -> left, environment) -> getVal() == "1") {
                Token *uselessToken = interp(root -> leftcenter, environment);

            } else if (root -> right -> token -> getVal() == "else") {
                root -> right -> token -> value = "if";
                Token *uselessToken = interp(root -> right, environment);
            }
            return NULL;
        }
    }

    return result;
}
