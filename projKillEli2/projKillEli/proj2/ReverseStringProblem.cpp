//
// Created by david on 1/1/19.
//
#include <bits/stdc++.h>
#include "Solver.h"
// The reverse string problem handles the problem of reversing a string.
// It implements the solve function from the solver interface.
class ReverseStringProblem: public Solver {
public:
    // Solve the problem.
    string solve(string problem) {
         reverse(problem.begin(), problem.end());
         return problem;
    }
};
