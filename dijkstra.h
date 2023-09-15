// Abby Leary
// 11.28.22
// CS 3650
// Project 5: Driving Directions

#include <iostream>

using namespace std;

class dijkstra
{
public:
    dijkstra()
    {
        location = "";
        distance = INT16_MAX;
        prev = nullptr;
        visited = false;
    }
    dijkstra(string loc)
    {
        location = loc;
        distance = INT16_MAX;
        prev = nullptr;
        visited = false;
    }
    void setLoc(string loc) { location = loc; }
    string getLoc() { return location; }
    int getDist() { return distance; }
    void setDist(int dist) { distance = dist; }
    void setPrev(dijkstra *newPrev) { prev = newPrev; }
    dijkstra *getPrev() { return prev; }
    void visit(bool yn) { visited = yn; }
    bool isVisited() { return visited; }

private:
    string location;
    int distance;
    dijkstra *prev;
    bool visited;
};