//
// Created by david on 1/1/19.
//
#include "CacheManager.h"
#include <map>
#include <string>
using namespace std;
// Holds a map of problems and their solutions for easy access.
class FileCacheManager: public  CacheManager {
    // Map of strings and their reverse.
    map<string,string> solutions;
public:
    // Adds the solution and problem to the map.
    void addSolution(string problem, string solution) {
        solutions.insert(pair<string, string>(problem, solution));
    }
    // Gets the solution from the map.
    string getSolution(string problem) {
        // If solution exists return it.
        if (solutions.count(problem)) {
            return solutions.at(problem);
        }
        // Else return empty string.
        return "None";
    }
    // Return all the current solutions.
    map<string,string> getAllSolutions() {
        return solutions;
    }
};