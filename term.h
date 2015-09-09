#pragma once

#include <vector>
#include <set>
#include <map>

using namespace std;

typedef int Variable;
typedef set<int> Clause;
typedef vector<Clause> Clauses;
typedef set<Variable> Variables;

class Assigment;  //forward declaration

class Term
{
public:
    Term();


    void add(Clause c);

        Variables& getVariables();

        Clauses& getClauses();

        Clause getClause(Assigment a, int i);
        Clauses getClauses(Assigment a);

     friend int abs(int a);

private:
    vector<Clause> clauses;
    set<Variable> variables;

    map<Variable, int> decisions; // variable, decision level

};


