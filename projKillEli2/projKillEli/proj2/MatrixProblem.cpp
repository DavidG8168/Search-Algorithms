#pragma  once
#include "Searchable.h"
#include <vector>
#include <fstream>
#include <iostream>   // std::cout
#include <string>     // std::string, std::stoi
#include <sstream>
using namespace std;
class MatrixProblem: public Searchable {

private:
    vector<vector<int>>Matrix;
    vector<vector<int>>IndexMatrix;
    int size;
    vector<int>start;
    vector<int>end;
    int startPoint;
    int endPoint;

public:
    void GetInitialState(const char *buffer) override {
        vector<vector<string>> lines = getLines(buffer);
        int counter =0;
        for (int i = 0; i <lines.size() ; ++i) {
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
            Matrix.push_back(vec);
            IndexMatrix.push_back(vectIndexes);

        }
        start=Matrix[Matrix.size()-2];
        end =Matrix[Matrix.size()-1];
        Matrix.resize(Matrix.size()-2);
        IndexMatrix.resize(IndexMatrix.size()-2);
        startPoint=IndexMatrix[start[0]][start[1]];
        endPoint=IndexMatrix[end[0]][end[1]];
        size = Matrix.size()*Matrix[0].size();


    }

    const vector<int> &getStart() const {
        return start;
    }

    const vector<int> &getEnd() const {
        return end;
    }

    int getStartPoint() const {
        return startPoint;
    }

    void setStartPoint(int startPoint) {
        MatrixProblem::startPoint = startPoint;
    }

    int getEndPoint() const {
        return endPoint;
    }


    const vector<vector<int>> &getMatrix() const {
        return Matrix;
    }

    int getSize() const {
        return size;
    }

    const vector<vector<int>> &getIndexMatrix() const {
        return IndexMatrix;
    }



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
    std::vector<std::string> split(string s, char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }

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