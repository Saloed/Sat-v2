#include "cdcl.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Term readFile(string path) {
	ifstream infile(path);
	string line;

	Term f;

	auto started = false;
	string s;
	int numVars, numClauses = 0;
	auto cnt = 0;
	char ch;
	while (infile.get(ch))
	{
		if (ch == '\n' && !line.empty())
		{

			istringstream iss(line);
			if (!started)
			{
				iss >> s;
				if (s == "c")
				{
					line.clear();
					continue;
				}
				if (s == "p")
				{
					iss >> s; 
					iss >> numVars >> numClauses;
					started = true;
				}
			}
			else {
				Clause c;
				int var;
				while (iss >> var)
				if (var != 0)
					c.insert(var);

				f.add(c);
				cnt++;
			}
			line.clear();
		}
		else
		{
			if (ch != '\n')
				line.push_back(ch);
		}
		if (started && cnt == numClauses)
			break;
	}

	return f;
}

int main(int argc, char *argv[])
{

	if (argc != 2) {
		cout << "USAGE: " << argv[0] << " [.cnf FILE]" << endl;
		return 0;
	}
	auto path = string(argv[1]);
	auto f = readFile(path);
	CDCL sat(f);
	sat.solve();
	sat.printModel();

	return 0;
}
