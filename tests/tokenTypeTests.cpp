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


void testIsOperator(){


}


void testIsVariable(){



}


void testIsKeyword(){



}
