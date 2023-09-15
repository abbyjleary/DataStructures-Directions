// Abby Leary
// 11.28.22
// CS 3650
// Project 5: Driving Directions

#include <vector>
#include <iostream>

using namespace std;

class node
{
public:
    node()
    {
        next = nullptr;
        location = "";
        distance = 0;
    }
    node(string loc)
    {
        location = loc;
        distance = 0;
        next = nullptr;
    }
    void setLoc(string loc) { location = loc; }
    string getLoc() { return location; }
    int getDist() { return distance; }
    void setDist(int dist) { distance = dist; }
    void setNext(node *newNext) { next = newNext; }
    node *getNext() { return next; }

private:
    node *next;
    string location;
    int distance;
};