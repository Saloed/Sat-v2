#include "assigment.h"

Assigment::Assigment()
{

}

void Assigment::set(Variable var, bool b) {
    data[var] = b;
}
void Assigment::unset(Variable var) {
    data.erase(var);
}

bool Assigment::isSet(Variable var) {
    return data.count(var) > 0;
}
bool Assigment::isTrue(Variable var) {
    return isSet(var) && data[var];
}
bool Assigment::isFalse(Variable var) {
    return isSet(var) && !data[var];
}

