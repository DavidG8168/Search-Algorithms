#ifndef SEARCHABLE_H
#define SEARCHABLE_H
// Interface used to define what is a searchable problem.
class Searchable {
    // Create the searchable state.
    virtual void GetInitialState(const char *buffer)=0;
};
#endif //SEARCHABLE_H
