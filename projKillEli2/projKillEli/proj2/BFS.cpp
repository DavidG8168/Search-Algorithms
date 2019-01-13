//
// Created by david on 1/7/19.
//
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include<stdlib.h>
#include "Searcher.h"
using namespace std;
// The Breadth First Search search algorith,
class BFS : public Searcher{
    // The members.
    int V;
    vector<int> *adj;
    vector<int> *wgt;
    vector<int> links;
    vector<int> nodes;
    int *prev;
    int counter=-1;
    int totalweights1=0;
// The constructor.
public:
    BFS(int V) {
        this->V = V;
        adj = new vector<int>[V];
        wgt = new vector<int>[V];
        prev = new int[V];
    }
    // Get the total weight of the path.
    int gettotalweights1() {
        return this->totalweights1;
    }
    // The number of nodes in the path.
    int getcounter() {
        return this->counter;
    }
    // Add an edge from v to w in the graph.
    void addEdge(int v, int w, int wt) {
        adj[v].push_back(w);
        wgt[v].push_back(wt);
        adj[w].push_back(v);
        wgt[w].push_back(wt);

    }
    // Search for a path from s to t.
    void search(int s, int t) {
        bool *visited = new bool[V];
        if(s == t) {
            cout <<s <<endl;
            return;
        }
        for (int i = 0; i < V; ++i) {
            visited[i] = false;
        }
        list<int> queue;
        int current;
        visited[s] = true;
        prev[s] = -1;
        queue.push_back(s);
        vector<int>::iterator i;
        while(!queue.empty()) {
            current = queue.front();
            queue.pop_front();
            for (i = adj[current].begin(); i != adj[current].end(); i++) {
                if(!visited[*i]) {
                    prev[*i] = current;
                    visited[*i] = true;
                    if(*i == t) {
                        cout<<"found"<<endl;
                        displayPath(t);
                    }
                    queue.push_back(*i);
                }
            }
        }
    }
    // Display the path.
    void displayPath(int f) {
        int p = f;
        int q;
        int pos;
        int pathweight = 0;
        cout<<"Path is: ";
        while(p!=-1) {
            this->counter=this->counter+1;
            cout<<" <- "<<p;
            q = prev[p];
            if(q!=-1) {
                pos = find(adj[p].begin(), adj[p].end(), q) - adj[p].begin();
                pathweight = pathweight + wgt[p].at(pos);
            }
            p = q;
        }
        cout<<endl;
        cout<<"path weight : "<<pathweight <<endl;
        cout<<"number of nodes:"<<this->counter <<endl;
        this->totalweights1=pathweight;
        cout<<endl;
    }
    // Create the graph.
    void createGraph(vector<vector<int>> matrix,vector<vector<int>> matrixindexes){
        for(int i = 0; i<matrix.size();i++){
            for(int j = 0; j<matrix.size();j++){
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