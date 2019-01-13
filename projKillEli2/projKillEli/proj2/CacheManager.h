//
// Created by david on 1/1/19.
//
#ifndef PROBLEMSOLVER_CACHEMANAGER_H
#define PROBLEMSOLVER_CACHEMANAGER_H
#include <string>
#include <map>
using namespace std;
// The cache mangager interface defines the behaviour of the solution storage cache.
class CacheManager{
public:
    // Adds the solution to the cache.
    virtual void addSolution(string problem, string solution)=0;
    // Gets the solution to the problem from the cache.
    virtual string getSolution(string problem)=0;
    virtual map<string,string> getAllSolutions()=0;
    };
#endif //PROBLEMSOLVER_CACHEMANAGER_H
