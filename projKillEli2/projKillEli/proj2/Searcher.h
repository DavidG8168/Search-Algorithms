//
// Created by david on 1/7/19.
//
#ifndef PROBLEMSOLVER_SEARCHER_H
#define PROBLEMSOLVER_SEARCHER_H
// The searcher interface encompasses all the search algorithm.
class Searcher {
public:
    // Searches the graph created for the problem matrix.
    virtual void search(int s, int t)=0;
};
#endif //PROBLEMSOLVER_SEARCHER_H
