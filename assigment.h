#pragma once

#include "term.h"
#include <map>

using namespace std;

class Assigment
{
public:
    Assigment();

    void set(Variable var, bool b);
    void unset(Variable var);

    bool isSet(Variable var) const;
    bool isTrue(Variable var);
    bool isFalse(Variable var);
private:
    map<Variable, bool> data;

};

