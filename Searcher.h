#ifndef SEARCHER_H
#define SEARCHER_H
// The searcher interface encompasses all the search algorithm.
class Searcher {
public:
    // Searches the graph created for the problem matrix.
    virtual void search(int s, int t)=0;
};
#endif //SEARCHER_H
