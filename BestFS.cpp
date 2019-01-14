#include <iostream>
#include <stdlib.h>
#include <list>
#include <cmath>
#include <fstream>
#include "Searcher.h"
#include "vector"
using namespace std;
// The Best First Search seach algorithm inherits from the searcher interface.
class BestFS: public Searcher {
    // The members used.
    // Used for grap constrution from the problem matrix.
    int numVertices;
    list<int> *adjacencyList;
    int counter=-1;
    // Used to track the weights of the graph nodes.
    vector<vector<int>> weight;
    vector<int> newWeights;
    int firstwieght;
    int totalweghit=0;
public:
    // Get the total weight of the graph.
    int gettotalweights1(){
        return this->totalweghit;
    }
    // Return the number of nodes in the path.
    int getcounter(){
        return this->counter;
    }
    // The constructor.
    BestFS(int numVertices) {
    this->numVertices = numVertices;
    adjacencyList = new list<int>[numVertices];
    std::vector<int> vec(numVertices);
    this->newWeights = vec;
    }
    // Add an edge to the graph from v to w with a weight wth.
    void addEdge(int v, int w,int wth) {
    adjacencyList[v].push_back(w);
    vector<int> vec;
    newWeights[w]=wth;
    weight.push_back(vec);
    weight[v].push_back(wth);
    }
    // Create the path from the start node to the end node, all nodes are numbered.
    void search(int start,int end) {
    int totalwieght=0;
    bool *visited = new bool[numVertices];
    for(int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }
    list<int> queue;
    visited[start] = true;
    queue.push_back(start);
    list<int>::iterator i;
    while(!queue.empty()) {
        start = queue.front();
        totalwieght=totalwieght+newWeights[start];
        this->counter=this->counter+1;
        queue.pop_front();
        for(i = adjacencyList[start].begin(); i != adjacencyList[start].end(); i++) {
            if(!visited[*i]) {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    this->totalweghit=totalwieght-firstwieght;
    }
    // Create the graph with the given matrix and it's unique identifiers.
    void createGraph(vector<vector<int>> matrix,vector<vector<int>> matrixindexes){
        for(int i = 0; i<matrix.size();i++){
            for(int j = 0; j<matrix.size();j++){
                if(i==0&&j==0){
                    this->firstwieght=matrix[0][0];
                }
                if(matrix[i][j]==-1){
                    continue;
                }
                if(i!=0){
                    addEdge(matrixindexes[i][j],matrixindexes[i-1][j],matrix[i-1][j]);
                }
                if(i!=matrix.size()-1){
                    addEdge(matrixindexes[i][j],matrixindexes[i+1][j],matrix[i+1][j]);
                }
                if(j!=0  ){
                    addEdge(matrixindexes[i][j],matrixindexes[i][j-1],matrix[i][j-1]);
                }
                if(j!=matrix.size()-1){
                    addEdge(matrixindexes[i][j],matrixindexes[i][j+1],matrix[i][j+1]);
                }
            }
        }
    }
};