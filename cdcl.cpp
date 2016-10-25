#include "cdcl.h"

CDCL::CDCL(Term formula) : Sat_Solver_Base(formula)
{
	solved = false;
}

Clause CDCL::resolve(Clause c1, Clause c2, Variable v)
{
	Clause c;

	for (auto it : c1)
		if (it != v && it != -v)
			c.insert(it);

	for (auto it : c2)
		if (it != v && it != -v)
			c.insert(it);

	return c;
}

unit CDCL::unitPropagation()
{
	for (unsigned int i = 0; i < statement.getClauses().size(); i++)
	{
		auto c = statement.getClause(conclusion, i);
		if (c.count(0) > 0) continue;

		if (c.size() == 1)
		{
			auto clause = *c.begin();
			auto var = abs(clause);
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


Clause CDCL::solver(int decisionLevel)
{
	while (true)
	{
		auto clauses = statement.getClauses(conclusion);

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

		auto p = unitPropagation();
		if (p.first != -1)
		{
			auto c = solver(decisionLevel);
			if (c.size() == 0)
			{ // UNSAT
				conclusion.unset(p.first);
				return c;
			}
			if (c.count(0) > 0)
			{ // SAT
				return c;
			}


			conclusion.unset(p.first);

			auto c2 = statement.getClauses()[p.second];

			if (c.count(p.first) > 0 || c.count(-p.first) > 0)
				return resolve(c, c2, p.first);
			return c;
		}


		auto var = 0;
		unsigned int clause_length = 100000;

		for (auto c:clauses)
		{
			if (c.count(0) > 0) continue; // true

			if (c.size() > 0 && c.size() < clause_length)
			{
				clause_length = c.size();
				var = abs(*c.begin());
			}
		}


		bool value = rand() % 2;
		conclusion.set(var, value);

		auto c = solver(decisionLevel + 1);


		if (c.count(0) != 0)
		{ // SAT
			return c;
		}
		if (c.count(var) == 0 && c.count(-var) == 0)

		{
			conclusion.unset(var);
			return c;
		}

		conclusion.unset(var);

		statement.add(c);
	}
}

void CDCL::solve()
{
	if (solved) return;

	while (unitPropagation().first != -1);

	solver();

	solved = true;
}

