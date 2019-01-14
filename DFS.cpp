#include<iostream>
#include<list>
#include "Searcher.h"
#include <vector>
using namespace std;
// Graph class represents a directed graph
// using adjacency list representation
class DFS :public Searcher {
    // The members.
    int stop;
    int V;
    // Pointer to an array containing
    // adjacency lists
    list<int> *adj;
    vector<vector<int>> weight;
    vector<int> newWeights;
    int totalWeight;
    int firstV;
    int counter=-1;
public:
    // The constructor.
    DFS(int V) {
    this->stop=1;
    this->V = V;
    totalWeight=0;
    adj = new list<int>[V];
    std::vector<int> vec(V);
    this->newWeights = vec;
    }
    // Return the total weight of the path.
    int gettotalweights1(){
        return this->totalWeight;
    }
    // Return the number of nodes in the path.
    int getcounter(){
        return this->counter;
    }
    // Add an edge to the graph.
    void addEdge(int v, int w,int wgt) {
    vector<int> vec;
    weight.push_back(vec);
    weight[v].push_back(wgt);
    newWeights[w]=wgt;
    adj[v].push_back(w);
    }

    // Marks the visited nodes and prints the path.
    void DFSUtil(int v, bool visited[],int t) {
    // Mark the current node as visited and
    // print it
    visited[v] = true;
    this->counter=this->counter+1;
    totalWeight += newWeights[v];
    if(v == t) {
        totalWeight -= firstV;
        stop=0;
        return;
    }
    // Recur for all the vertices adjacent
    // to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i){

        if (!visited[*i]){
            DFSUtil(*i, visited,t);
        }
        if(stop==0){
            return;
            }
        }
    }
    // DFS traversal of the vertices reachable from v.
    // It uses recursive DFSUtil()
    void search(int v,int t) {
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++){
        visited[i] = false;
        }
    // Call the recursive helper function
    // to print DFS traversal
    DFSUtil(v, visited,t);
    }
    // Create the graph.
    void createGraph(vector<vector<int>> matrix,vector<vector<int>> matrixindexes) {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix.size(); j++) {
                if (matrix[i][j] == -1) {
                    continue;
                }
                if (i != 0) {
                    addEdge(matrixindexes[i][j], matrixindexes[i - 1][j], matrix[i - 1][j]);
                }
                if (i != matrix.size() - 1) {
                    addEdge(matrixindexes[i][j], matrixindexes[i + 1][j], matrix[i + 1][j]);
                }
                if (j != 0) {
                    addEdge(matrixindexes[i][j], matrixindexes[i][j - 1], matrix[i][j - 1]);
                }
                if (j != matrix.size() - 1) {
                    addEdge(matrixindexes[i][j], matrixindexes[i][j + 1], matrix[i][j + 1]);
                }
                firstV=matrix[0][0];
            }
        }
    }
};