#pragma once

#include"sat_solver_base.h"

typedef pair<Variable, int> unit;

class CDCL:public Sat_Solver_Base
{
public:
	explicit CDCL(Term formula);
    void solve() override;
private:

	static Clause resolve(Clause c1, Clause c2, Variable v);
    unit unitPropagation() ;
    Clause solver(int decisionLevel =0);
};

