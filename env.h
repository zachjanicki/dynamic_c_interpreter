//
//  env.h
//
//
//  Created by Pierce Cunneen on 3/15/16. Updated by John Joyce on 4/2/16.
//
//
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Token.h"

using namespace std;

#ifndef ENV_H
#define ENV_H
typedef void (*func)(void);


class env {
    public:
    env() {
        //push keywords -- i know its more than we will need but just pushed a lot to be thorough.
        keywords.push_back("boolean"); keywords.push_back("break"); keywords.push_back("do");
        keywords.push_back("case"); keywords.push_back("false");
        keywords.push_back("char"); keywords.push_back("float"); keywords.push_back("const");
        keywords.push_back("continue"); keywords.push_back("for");
        keywords.push_back("default"); keywords.push_back("delete"); keywords.push_back("function");
        keywords.push_back("if"); keywords.push_back("in"); keywords.push_back("new");
        keywords.push_back("switch"); keywords.push_back("return");  keywords.push_back("true");
        keywords.push_back("var");  keywords.push_back("void"); keywords.push_back("while");

        //push operators with functions -- not sure exactly how we want to do this
        operators["+"] = &add;
        operators["-"] = &sub;
        operators["*"] = &mult;
        operators["/"] = &div;
        operators["%"] = &mod;
        operators["++"] = &plusPlus;
        operators["--"] = &minusMinus;
        operators["+="] = &plusEquals;
        operators["-="] = &minusEquals;
        operators["*="] = &timesEquals;
        operators["/="] = &divideEquals;

        //push booleans
        booleans["true"] = true;
        booleans["false"] = false;

    }
    vector <string> keywords;
    map <string, Variable> variables;
    map <string, Function> user_defined_functions;
    map <string, func> operators;
    map <string, BOOL> booleans;

    private:



    template <typename T>
    T add(T term1, T term2) {
        return term1+term2;

    }
    template <typename T>
    T sub(T term1, T term2) {
        return term1-term2;
    }

    template <typename T>
    T mult(T term1, T term2) {
        return term1*term2;
    }

    template <typename T>
    T div(T term1, T term2) {
        return term1/term2;
    }

    template <typename T>
    T mod(T term1, T term2) {
        return term1%term2;
    }

    template <typename T>
    T plusPlus(T term) {
        return term += 1;
    }

    template <typename T>
    T minusMinus(T term) {
        return term -= 1;
    }

    template <typename T>
    T plusEquals(T term1, T term2) {
        return term1 += term2;
    }

    template <typename T>
    T minusEquals(T term1, T term2) {
        return term1 -= term2;
    }

    template <typename T>
    T timesEquals(T term1, T term2) {
        return term1 *= term2;
    }

    template <typename T>
    T divideEquals(T term1, T term2) {
        return term1 /= term2;
    }


};
