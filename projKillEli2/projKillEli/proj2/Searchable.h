//
// Created by david on 1/7/19.
//
#ifndef PROBLEMSOLVER_SEARCHABLE_H
#define PROBLEMSOLVER_SEARCHABLE_H
// Interface used to define what is a searchable problem.
class Searchable {
    virtual void GetInitialState(const char *buffer)=0;
};
#endif //PROBLEMSOLVER_SEARCHABLE_H
