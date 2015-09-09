#include "sat_solver_base.h"


Sat_Solver_Base::Sat_Solver_Base(Term formula):statement(formula)
{}

bool Sat_Solver_Base::isSatisfiable(){
    if (!solved)
        solve();
    return satisfiable;
}

Assigment Sat_Solver_Base::getModel(){
    if (!solved)
        solve();
    return conclusion;
}

bool Sat_Solver_Base::isModel(){
   Clauses clauses = statement.getClauses(conclusion);
    for (int i = 0; i < clauses.size(); i++) {
        if (clauses[i].count(0) == 0) // ==
            return false;
    }
    return true;
}


void Sat_Solver_Base::printModel() {
    if (!solved) solve();
    if (!satisfiable) {
        cout << "not satisfiable" << endl;
        return;
    }
    if (!isModel()) {
        cout << "ERROR!!!" << endl;
        return;
    }
    cout << "satisfiable" << endl;

    cout << "model:" << endl;
    for (auto it = statement.getVariables().begin(); it != statement.getVariables().end(); it++) {
        if (conclusion.isTrue(*it))
            cout << "set " << *it << " to true" << endl;
        else
            cout << "set " << *it << " to false" << endl;
    }
}
