
#ifndef PROJKILLELI2_ASTAR_H
#define PROJKILLELI2_ASTAR_H


#pragma once
/*
//A*算法对象类
*/
#include <vector>
#include <list>
#include "Searcher.h"

const int kCost1 = 10; //直移一格消耗
const int kCost2 = 10; //斜移一格消耗

struct Point
{
    int x, y; //点坐标，这里为了方便按照C++的数组来计算，x代表横排，y代表竖列
    int F, G, H; //F=G+H
    Point *parent; //parent的坐标，这里没有用指针，从而简化代码
    Point(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL)  //变量初始化
    {
    }
};


class Astar : public Searcher
{
public:
    void InitAstar(std::vector<std::vector<int>> &_maze,std::vector<std::vector<int>> &_Indexmaze);
    std::list<Point *> GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
    Point *findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
    std::vector<Point *> getSurroundPoints(const Point *point, bool isIgnoreCorner) const;
    bool isCanreach(const Point *point, const Point *target, bool isIgnoreCorner) const; //判断某点是否可以用于下一步判断
    Point *isInList(const std::list<Point *> &list, const Point *point) const; //判断开启/关闭列表中是否包含某点
    Point *getLeastFpoint(); //从开启列表中返回F值最小的节点
    //计算FGH值
    int calcG(Point *temp_start, Point *point);
    int calcH(Point *point, Point *end);
    int calcF(Point *point);
//    int CalcWeight(list<Point *> path);
    void ShowPath(Point,Point);
    void search(int s, int t) override;
    void ConverMatrix();
    int getwegiht();
    int getnumberofnodes();


private:
    int totalweghit=0;
    int numberofnodes=-1;
    std::vector<std::vector<int>> maze;
    std::vector<std::vector<int>> IndexMaze;

    std::list<Point *> openList;  //开启列表
    std::list<Point *> closeList; //关闭列表
};

#endif //PROJKILLELI2_ASTAR_H