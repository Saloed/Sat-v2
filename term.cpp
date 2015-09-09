#include "term.h"
#include "assigment.h"

Term::Term()
{

}

void Term::add(Clause c) {
	clauses.push_back(c);
	for (auto it = c.begin(); it != c.end(); it++) {
		variables.insert(abs(*it));
	}
}

Variables& Term::getVariables() {
	return variables;
}

Clauses& Term::getClauses() {
	return clauses;
}

Clause Term::getClause(Assigment a, int i) {
	Clause c;
	bool addClause = true;
	for (auto it = clauses[i].begin(); it != clauses[i].end(); it++)
	{
		int var = abs(*it);
		if (!a.isSet(var))
		{
			c.insert(*it);
			continue;
		}
		if ((*it > 0 && a.isTrue(var)) || (*it < 0 && a.isFalse(var)))
		{
			addClause = false;
			break;
		}
		else if ((*it > 0 && a.isFalse(var)) || (*it < 0 && a.isTrue(var)))
			continue;
		else
			c.insert(*it);
	}
	if (addClause)
		return c;

	c.clear();
	c.insert(0);

	return c;
}

Clauses Term::getClauses(Assigment a) {
	Clauses cs;
	for (unsigned int i = 0; i < clauses.size(); i++)
	{
		Clause c;
		bool addClause = true;
		for (auto it = clauses[i].begin(); it != clauses[i].end(); it++)
		{
			int var = abs(*it);
			if (!a.isSet(var))
			{
				c.insert(*it);
				continue;
			}
			if ((*it > 0 && a.isTrue(var)) || (*it < 0 && a.isFalse(var)))
			{
				addClause = false;
				break;
			}
			else if ((*it > 0 && a.isFalse(var)) || (*it < 0 && a.isTrue(var)))
				continue;
			else
				c.insert(*it);
		}
		if (addClause)
			cs.push_back(c);
		else
		{
			c.clear();
			c.insert(0);
			cs.push_back(c);
		}
	}

	return cs;
}


int abs(int a) {
	return (a > 0) ? a : -a;
}