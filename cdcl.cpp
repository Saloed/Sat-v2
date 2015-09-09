#include "cdcl.h"

CDCL::CDCL(Term formula) :Sat_Solver_Base(formula){
	solved = false;
}

Clause CDCL::resolve(Clause c1, Clause c2, Variable v) {

	Clause c;
	bool pos = false;
	bool found = false;
	for (auto it = c1.begin(); it != c1.end(); it++)
	{
		if (*it == v)
		{
			pos = true;
			found = true;
		}
		else if (*it == -v)
		{
			pos = false;
			found = true;
		}
		else c.insert(*it);
	}

	found = false;
	for (auto it = c2.begin(); it != c2.end(); it++)
	{
		if (*it == v)
		{
			found = true;
		}
		else if (*it == -v)
		{
			found = true;
		}
		else c.insert(*it);
	}
	return c;
}

unit CDCL::unitPropagation() {

	
	for (unsigned int i = 0; i < statement.getClauses().size(); i++)
	{
		Clause c = statement.getClause(conclusion, i);
		if (c.count(0) > 0) continue;

		if (c.size() == 1)
		{
			int clause = *c.begin();
			Variable var = abs(clause);
			if (clause > 0)
			{
				conclusion.set(var, true);
			}
			else if (clause < 0)
			{
				conclusion.set(var, false);
			}

			return make_pair(var, i);
		}
	}
	return make_pair(-1, -1);
}


Clause CDCL::solver(int decisionLevel) {
	while (true)
	{
		
		Clauses clauses = statement.getClauses(conclusion);

		satisfiable = true;
		for (unsigned int i = 0; i < clauses.size(); i++)
		{

			if (clauses[i].count(0) == 0)
				satisfiable = false;


			if (clauses[i].size() == 0)
			{
				// start learning

				return statement.getClauses()[i];
			}
		}
		if (satisfiable)
		{
			Clause c;
			c.insert(0);
			return c;
		}

		unit p = unitPropagation();
		if (p.first != -1)
		{
			Clause c = solver(decisionLevel);
			if (c.size() == 0)
			{ // UNSAT
				conclusion.unset(p.first);
				return c;
			}
			else if (c.count(0) > 0)
			{  // SAT
				return c;
			}

			
			conclusion.unset(p.first);

			Clause c2 = statement.getClauses()[p.second];

			if ((c.count(p.first) > 0) || (c.count(-p.first) > 0))
			{
				return resolve(c, c2, p.first);
			}
			else
			{
				return c;
			}
		}


		Variable var = 0;
		unsigned int clause_length = 100000;
		for (unsigned int i = 0; i < clauses.size(); i++)
		{
			Clause c = clauses[i];
			if (c.count(0) > 0) continue; // true

			if ((c.size() > 0) && (c.size() < clause_length))
			{
				clause_length = c.size();
				var = abs(*c.begin());
			}
		}



		bool value = rand() % 2;
		conclusion.set(var, value);

		Clause c = solver(decisionLevel + 1);


		if (c.count(0) != 0)
		{ // SAT
			return c;
		}
		else if ((c.count(var) == 0) && (c.count(-var) == 0))
		{
			conclusion.unset(var);
			return c;
		}

		conclusion.unset(var);

		statement.add(c);




	}
}

void CDCL::solve(){

	if (solved) return;

	while (unitPropagation().first != -1);

	solver();

	solved = true;
}

