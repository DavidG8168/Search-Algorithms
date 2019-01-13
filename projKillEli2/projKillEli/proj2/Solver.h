//
// Created by david on 1/1/19.
//
#ifndef PROBLEMSOLVER_SOLVER_H
#define PROBLEMSOLVER_SOLVER_H
#include <string>
// The solver namespace, solves the problem.
using namespace std;
class Solver{
public:
    // The solve method.
    virtual string solve(string problem)=0;
};
#endif //PROBLEMSOLVER_SOLVER_H
