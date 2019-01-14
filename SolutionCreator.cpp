#include <string>
#include <vector>
#include "MatrixProblem.cpp"
#include "BFS.cpp"
#include "BestFS.cpp"
#include "DFS.cpp"
#include "Astar.h"
#include "CacheManager.h"
#include <string>
#include "GlobalCache.h"
#include "Solver.h"
using namespace std;
// Runs all possible solution the the problem using all the search algorith,s
class SolutionCreator: public Solver{
private:
    string bigstr="";
    CacheManager* cacheManager;
public:
    // Solve the problem using all search algoriths and write them to the given file.
    void solve(string str){
        // Run all search algorithms on all the matrices.
        vector<string> splitedvector=splitExpression(str);
        for(int i=0;i<splitedvector.size();i+=2){
            MatrixProblem* mp = new MatrixProblem();
            mp->GetInitialState(splitedvector[i].c_str());
            BFS * bfs = new BFS(mp->getSize());
            bfs->createGraph(mp->getMatrix(),mp->getIndexMatrix());
            bfs->search(mp->getStartPoint(),mp->getEndPoint());
            DFS * dfs = new DFS (mp->getSize());
            dfs->createGraph(mp->getMatrix(),mp->getIndexMatrix());
            dfs->search(mp->getStartPoint(),mp->getEndPoint());
            BestFS* bestfs = new BestFS(mp->getSize());
            bestfs->createGraph(mp->getMatrix(),mp->getIndexMatrix());
            bestfs->search(mp->getStartPoint(),mp->getEndPoint());
            vector<vector<int>> maze = mp->getMatrix();
            vector<vector<int>> indexmaze = mp->getIndexMatrix();
            Astar astar;
            astar.InitAstar(maze,indexmaze);
            Point start(mp->getStart()[0], mp->getStart()[1]);
            Point end(mp->getEnd()[0], mp->getEnd()[1]);
            astar.ShowPath(start,end);
            // Create the solution by mixing all the total weights and amount of nodes in paths,
            bigstr= std::to_string(bfs->gettotalweights1())+","+std::to_string(bfs->getcounter())+'\n';
            bigstr+=std::to_string(dfs->gettotalweights1())+","+std::to_string(dfs->getcounter())+'\n';
            bigstr+=std::to_string(bestfs->gettotalweights1() )+","+std::to_string(bestfs->getcounter())+'\n';
            bigstr+=std::to_string(astar.getwegiht()  )+","+std::to_string(astar.getnumberofnodes())+'\n';
            // Update the global cache with the problem and solution.
            globalcache->addSolution(mp->makeProblem(), bigstr);
            // Write the solution to the file.
            ofstream newFile(splitedvector[i+1], std::ios_base::app);
            if(newFile.is_open()) {
                newFile << bfs->gettotalweights1() << "," << bfs->getcounter() << "\n";
                newFile << dfs->gettotalweights1() << "," << dfs->getcounter() << "\n";
                newFile << bestfs->gettotalweights1() << "," << bestfs->getcounter() << "\n";
                newFile << astar.getwegiht() << "," << astar.getnumberofnodes() << "\n";

            }
            else {
                perror("Error opening file.");
            }
            newFile.close();
        }
        // Exit.
        exit(1);
    }
    // Split the buffer by the ',' char to get the values.
    vector<string> splitExpression(string str) {
        // If we start with a ',' get rid of it.
        if (str[0] == ',') {
            str.erase(0,1);
        }
        std::vector<std::string> splittedString;
        int startIndex = 0;
        int endIndex = 0;
        while ((endIndex = str.find(',', startIndex)) < str.size()) {
            std::string val = str.substr(startIndex, endIndex - startIndex);
            splittedString.push_back(val);
            startIndex = endIndex + 1;
        }
        if (startIndex < str.size()) {
            std::string val = str.substr(startIndex);
            splittedString.push_back(val);
        }
        return splittedString;
    }
    // Return solution,
    string getstr(){
        return this->bigstr;
    }
    // Set the cache.
    void setCache(CacheManager* cm) {
        this->cacheManager = cm;
    }
    // Get the cache.
    CacheManager* getCache() {
        return this->cacheManager;
    }
};