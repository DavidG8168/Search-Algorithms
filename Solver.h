#ifndef SOLVER_H
#define SOLVER_H
#include <string>
// The solver namespace, solves the problem.
using namespace std;
class Solver{
public:
    // The solve method.
    virtual void solve(string problem)=0;
};
#endif //SOLVER_H
