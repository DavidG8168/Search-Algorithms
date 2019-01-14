#include "Astar.h"
#include <math.h>
#include "Astar.h"
#include<iostream>
using namespace std;
// The A Star search algorithm.
void Astar::InitAstar(std::vector<std::vector<int>> &_maze, std::vector<std::vector<int>> &__Indexmaze) {
    maze = _maze;
    IndexMaze = __Indexmaze;
}
int Astar::calcG(Point *temp_start, Point *point) {
    int extraG = (abs(point->x - temp_start->x) + abs(point->y - temp_start->y)) == 1 ? kCost1 : kCost2;
    int parentG = point->parent == NULL ? 0 : point->parent->G;
    return parentG + extraG;
}
void Astar::search(int s, int t) {
}
int Astar::calcH(Point *point, Point *end) {
    return sqrt((double)(end->x - point->x)*(double)(end->x - point->x) + (double)(end->y - point->y)*(double)(end->y - point->y))*kCost1;
}
int Astar::calcF(Point *point) {
    return point->G + point->H;
}
Point *Astar::getLeastFpoint() {
    if (!openList.empty()) {
        auto resPoint = openList.front();
        for (auto &point : openList)
            if (point->F<resPoint->F)
                resPoint = point;
        return resPoint;
    }
    return NULL;
}
Point *Astar::findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner) {
    openList.push_back(new Point(startPoint.x, startPoint.y));
    while (!openList.empty()) {
        auto curPoint = getLeastFpoint();
        openList.remove(curPoint);
        closeList.push_back(curPoint);
        auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
        for (auto &target : surroundPoints) {
            if (!isInList(openList, target)) {
                target->parent = curPoint;

                target->G = calcG(curPoint, target);
                target->H = calcH(target, &endPoint);
                target->F = calcF(target);

                openList.push_back(target);
            }
            else {
                int tempG = calcG(curPoint, target);
                if (tempG<target->G) {
                    target->parent = curPoint;

                    target->G = tempG;
                    target->F = calcF(target);
                }
            }
            Point *resPoint = isInList(openList, &endPoint);
            if (resPoint)
                return resPoint;
        }
    }
    return NULL;
}
std::list<Point *> Astar::GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner) {
    Point *result = findPath(startPoint, endPoint, isIgnoreCorner);
    std::list<Point *> path;
    while (result) {
        path.push_front(result);
        result = result->parent;
    }
    openList.clear();
    closeList.clear();
    return path;
}
Point *Astar::isInList(const std::list<Point *> &list, const Point *point) const {
    for (auto p : list)
        if (p->x == point->x&&p->y == point->y)
            return p;
    return NULL;
}
bool Astar::isCanreach(const Point *point, const Point *target, bool isIgnoreCorner) const {
    if (target->x<0 || target->x>maze.size() - 1
        || target->y<0 || target->y>maze[0].size() - 1
        || maze[target->x][target->y] == 1
        || target->x == point->x&&target->y == point->y
        || isInList(closeList, target))
        return false;
    else {
        if (abs(point->x - target->x) + abs(point->y - target->y) == 1) //非斜角可以
            return true;
        else {
            if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0)
                return true;
            else
                return isIgnoreCorner;
        }
    }
}
std::vector<Point *> Astar::getSurroundPoints(const Point *point, bool isIgnoreCorner) const {
    std::vector<Point *> surroundPoints;
    for (int x = point->x - 1; x <= point->x + 1; x++)
        for (int y = point->y - 1; y <= point->y + 1; y++)
            if (isCanreach(point, new Point(x, y), isIgnoreCorner))
                surroundPoints.push_back(new Point(x, y));

    return surroundPoints;
}
void Astar::ShowPath(Point start,Point end) {
    ConverMatrix();
    list<Point *> path = GetPath(start, end, false);
    int weight = 0;
    for (auto &p : path) {
        weight+= maze[p->x][p->y]-2;
    }
    weight-=maze[0][0]-2;
    totalweghit=weight;
    numberofnodes=path.size()-1;
}
void Astar::ConverMatrix() {
    for (int i = 0; i <maze.size() ; ++i) {
        for (int j = 0; j <maze[i].size() ; ++j) {
            maze[i][j]+=2;
        }
    }
}
//get the number of nodes
int Astar::getnumberofnodes() {
    return this->numberofnodes;
}
//get the total weghit of the nodes
int Astar::getwegiht() {
    return this->totalweghit;
}
