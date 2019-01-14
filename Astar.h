#ifndef ASTAR_H
#define ASTAR_H
#include <vector>
#include <list>
#include "Searcher.h"
const int kCost1 = 10;
const int kCost2 = 10;
struct Point {
    int x, y;
    int F, G, H;
    Point *parent;
    Point(int _x, int _y) :x(_x), y(_y), F(0), G(0), H(0), parent(NULL) {
    }
};
// The interface for the Astar algorithm.
class Astar : public Searcher {
private:
    int totalweghit=0;
    int numberofnodes=-1;
    std::vector<std::vector<int>> maze;
    std::vector<std::vector<int>> IndexMaze;
    std::list<Point *> openList;
    std::list<Point *> closeList;
public:
    void InitAstar(std::vector<std::vector<int>> &_maze,std::vector<std::vector<int>> &_Indexmaze);
    std::list<Point *> GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
    Point *findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
    std::vector<Point *> getSurroundPoints(const Point *point, bool isIgnoreCorner) const;
    bool isCanreach(const Point *point, const Point *target, bool isIgnoreCorner) const;
    Point *isInList(const std::list<Point *> &list, const Point *point) const;
    Point *getLeastFpoint();
    int calcG(Point *temp_start, Point *point);
    int calcH(Point *point, Point *end);
    int calcF(Point *point);
    void ShowPath(Point,Point);
    void search(int s, int t) override;
    void ConverMatrix();
    int getwegiht();
    int getnumberofnodes();
};
#endif //ASTAR_H