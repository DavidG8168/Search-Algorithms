#pragma  once
#include "Searchable.h"
#include <vector>
#include <fstream>
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
#include <sstream>
using namespace std;
// Used to transform the text file according to the given format to a matrix, the start point and end point.
class MatrixProblem: public Searchable {
private:
    // The members of the class.
    int size;
    vector<vector<int>>Matrix;
    vector<vector<int>>IndexMatrix;
    vector<int>start;
    vector<int>end;
    int startPoint;
    int endPoint;
public:
    // Create the matrix.
    void GetInitialState(const char *buffer) override {
        vector<vector<string>> lines = getLines(buffer);
        int counter =0;
        for (int i = 0; i <lines.size() ; ++i) {
            // Stop reading the lines when we reach end.
            if(lines[i][0]=="end"){
                break;
            }
            vector<int> vec;
            vector<int>vectIndexes;
            for (int j = 0; j < lines[i].size(); ++j) {
                vec.push_back(stoi(lines[i][j]));
                vectIndexes.push_back(counter);
                counter++;
            }
            // Push the value to the vector and update the vector index using the counter.
            Matrix.push_back(vec);
            IndexMatrix.push_back(vectIndexes);

        }
        // Get the start and end points.
        start=Matrix[Matrix.size()-2];
        end =Matrix[Matrix.size()-1];
        Matrix.resize(Matrix.size()-2);
        IndexMatrix.resize(IndexMatrix.size()-2);
        startPoint=IndexMatrix[start[0]][start[1]];
        endPoint=IndexMatrix[end[0]][end[1]];
        size = Matrix.size()*Matrix[0].size();
    }
    // Get the start vector.
    const vector<int> &getStart() const {
        return start;
    }
    // Get the end vector.
    const vector<int> &getEnd() const {
        return end;
    }
    // Get the  start point.
    int getStartPoint() const {
        return startPoint;
    }
    // Set the start point.
    void setStartPoint(int startPoint) {
        MatrixProblem::startPoint = startPoint;
    }
    // Get the end point.
    int getEndPoint() const {
        return endPoint;
    }
    // Get the matrix.
    const vector<vector<int>> &getMatrix() const {
        return Matrix;
    }
    // Get the size of the matrix.
    int getSize() const {
        return size;
    }
    // Get the index vector.
    const vector<vector<int>> &getIndexMatrix() const {
        return IndexMatrix;
    }
    // Get the lines from the vector.
    vector <vector<string>> getLines(const char *buffer){
        std::ifstream file(buffer);
        vector <vector<string>> v2;
        if (file.is_open()) {
            std::string line;
            while (getline(file, line)) {
                vector<string>v1 = split(line,',');
                v2.push_back(v1);
            }
        }
        return v2;
    }
    // Split the the strings.
    std::vector<std::string> split(string s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
    // Transform the matrix to a unique identifier.
    std::string makeProblem() {
        string problem = "";
        vector<vector<int>> m = this->getMatrix();
        for (int i = 0; i < m.size(); ++i) {
            for (int j = 0; j < m[i].size(); ++j) {
                problem += to_string(m[i][j]);
            }
        }
        return problem;
    }
};