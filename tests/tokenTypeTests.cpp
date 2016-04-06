#include <iostream>
#include <assert.h>
#include "tokenTypeTests.h"
using namespace std;


void testIsInt(){
    assert(isInt("3") == true);
    assert(isInt("5") == true);
    assert(isInt("4.3") == false);
    assert(isInt(".4") == false);
    assert(isInt("0") == true);
    assert(isInt("0 1") == false);


}


void testIsFloat(){
    assert(isFloat("2") == false);
    assert(isFloat("2.") == true);
    assert(isFloat("2.3") == true);
    assert(isFloat(".12") == true);
    assert(isFloat(".2 12") == false);




}


void testIsArithOperator(){
    assert(isArithOperator("+") == true);
    assert(isArithOperator("-") == true);
    assert(isArithOperator("*") == true);
    assert(isArithOperator("/") == true);
    assert(isArithOperator("++") == true);
    assert(isArithOperator("--") == true);
    assert(isArithOperator("%") == true);
    assert(isArithOperator("<") == false);
    assert(isArithOperator(">") == false);
    assert(isArithOperator("=") == false);
    assert(isArithOperator("==") == false);
    assert(isArithOperator("3") == false);
    assert(isArithOperator("2.3") == false);
    assert(isArithOperator("") == false);
    assert(isArithOperator(" ") == false);

}

void testIsLogicalOperator(){
    assert(isLogicalOperator("<") == true);
    assert(isLogicalOperator(">") == true);
    assert(isLogicalOperator(">=") == true);
    assert(isLogicalOperator("<=") == true);
    assert(isLogicalOperator("==") == true);
    assert(isLogicalOperator("&&") == true);
    assert(isLogicalOperator("||") == true);
    assert(isLogicalOperator("!") == true);
    assert(isLogicalOperator("!=") == true);

    assert(isLogicalOperator("=") == false);
    assert(isLogicalOperator("<<=") == false);
    assert(isLogicalOperator(">>=") == false);
    assert(isLogicalOperator("2.3") == false);
    assert(isLogicalOperator("!&&") == false);
    assert(isLogicalOperator("!<=") == false);

}

void testIsAssignmentOperator(){
    assert(isAssignmentOperator("=") == true);
    assert(isAssignmentOperator("*=") == true);
    assert(isAssignmentOperator("+=") == true);
    assert(isAssignmentOperator("/=") == true);
    assert(isAssignmentOperator("-=") == true);
    assert(isAssignmentOperator("%=") == true);


}
void testIsVariable(){



}


void testIsKeyword(){



}
