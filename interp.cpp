
#include "interp.h"
#include <typeinfo>


using namespace std;

Token* interp(ASTNode *root, env * environment) {

    Token *result;
    if (!root) {
        return NULL;
    }

    if (root -> token -> getType() == "Float") {
        result = root -> token;
    } else if (root -> token -> getType() == "String"){
        result = root -> token;
    } else if (root -> token -> getType() == "Variable") {
        if (environment -> variables[root -> token -> getVal()]) {
            result = environment -> variables[root -> token -> getVal()];
        } else {
            cout << "Variable " << root -> token -> getVal() << " is not defined" << endl;
            return NULL;
        }
    } else if (root -> token -> getType() == "AssignmentOperator") {
        delete environment -> variables[root -> left -> token -> getVal()]; 
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
        } else if (root -> token -> getVal() == "%") {
            double a = stof(interp(root -> left, environment) -> getVal());
            double b = stof(interp(root -> right, environment) -> getVal());
            double modResult;
            while (a > b) {
                a = a - b;
            }
            modResult = a;
            result = new Token(to_string(modResult), "Float", 0, 0, 0);
        }
        else if (root->token->getVal() == "+=") {
            delete environment -> variables[root -> left -> token -> getVal()];
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(stof(interp(root -> left, environment)->getVal()) + stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0); 
            return NULL;
        }
        else if (root->token->getVal() == "-=") {
            delete environment -> variables[root -> left -> token -> getVal()];
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(stof(interp(root -> left, environment)->getVal()) - stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
            return NULL; 
        }
        else if (root->token->getVal() == "*=") {
            delete environment -> variables[root -> left -> token -> getVal()];
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(stof(interp(root -> left, environment)->getVal()) * stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
            return NULL; 
        }
        else if (root->token->getVal() == "/=") {
            delete environment -> variables[root -> left -> token -> getVal()];
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(stof(interp(root -> left, environment)->getVal()) / stof(interp(root -> right, environment)->getVal())), "Float", 0, 0, 0);
            return NULL;
        }
        else if (root->token->getVal() == "--") {
            delete environment -> variables[root -> left -> token -> getVal()];
            float newVal = stof(interp(root -> left, environment)->getVal()) - 1.0; 
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(newVal), "Float", 0, 0, 0);
            return NULL;
        }
        else if (root->token->getVal() == "++") {
            delete environment -> variables[root -> left -> token -> getVal()];
            float newVal = stof(interp(root -> left, environment)->getVal()) + 1.0; 
            environment -> variables[root -> left -> token -> getVal()] = new Token(to_string(newVal), "Float", 0, 0, 0);
            return NULL; 
        }
    } else if (root -> token -> getType() == "LogicalOperator") {
        int logic;
        Token True("1", "Float", 0,0,0), False("0", "Float", 0,0,0);
        Token *left, *right;
        left = interp(root -> left, environment);
        right = interp(root -> right, environment);
        if (root -> token -> getVal() == "<") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) < stof(right -> getVal());
            } else {
                logic = left -> getVal() < right -> getVal();
            }
            if (logic) {
                result = &True;
            }
            else {
                result = &False;
            }
        } else if (root -> token -> getVal() == ">") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) > stof(right -> getVal());
            } else {
                logic = left -> getVal() > right -> getVal();
            }
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "!=") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) != stof(right -> getVal());
            } else {
                logic = left -> getVal() != right -> getVal();
            }
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "==") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) == stof(right -> getVal());
            } else {
                logic = left -> getVal() == right -> getVal();
            }
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == "<=") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) <= stof(right -> getVal());
            } else {
                logic = left -> getVal() <= right -> getVal();
            }
            if (logic) {
                result = &True;
            } else {
                result = &False;
            }
        } else if (root -> token -> getVal() == ">=") {
            if (left -> getType() == "Float" && right -> getType() == "Float") {
                logic = stof(left -> getVal()) >= stof(right -> getVal());
            } else {
                logic = left -> getVal() >= right -> getVal();
            }
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
            cout << endl;
            if (interp(root -> left, environment) -> getVal() == "1") {
                Token *uselessToken = interp(root -> leftcenter, environment);
            } else if (root -> right) {
                Token *uselessToken = interp(root -> right, environment);
            }
            return NULL;
        } else if (root -> token -> getVal() == "for") {
            Token *variable = interp(root -> left, environment);
            while (true) {
                if (interp(root -> leftcenter, environment) -> getVal() == "1") {
                    Token *uselessToken = interp(root -> right, environment);
                    Token *increment = interp(root -> rightcenter, environment);
                } else {
                    break;
                }
            }
            return NULL;
        }
    }

    return result;
}
