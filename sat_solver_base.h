#pragma once

#include <iostream>


#include "term.h"
#include "assigment.h"

using namespace std;

class Sat_Solver_Base
{
public:
    Sat_Solver_Base(Term formula);
    virtual void solve() = 0;
    bool isSatisfiable();
    Assigment getModel();

    void printModel();


protected:
    bool isModel();

    Term statement;
    Assigment conclusion;

    bool solved;
    bool satisfiable;
};

