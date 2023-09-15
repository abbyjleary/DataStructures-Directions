// Abby Leary
// 11.28.22
// CS 3650
// Project 5: Driving Directions

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stack>
#include "node.h"
#include "dijkstra.h"

using namespace std;

/**
 *  Function:   usage
 *              prints usage
 */
void usage();

/**
 *  Function:   fileFail
 *              checks to see if files open successfully
 *
 *  @param fileName - the name of the file being opened
 *  @return - true if the file fails to open, false if it opens successfully
 */
bool fileFail(string fileName);

/**
 *  Function:   loadFile
 *              loads the graph from a file into a adjascency list
 *
 *  @param fileName - the name of the file being read from
 *  @return - a vector with nodes containing the graph information
 */
vector<node *> loadFile(string fileName);

/**
 *  Function:   lower
 *              finds the lowercase equivalent of a word
 *
 *  @param word - the word being transferred to lowercase
 *  @return - the lowercase version of the word passed to the function
 */
string lower(string word);

/**
 *  Function:   exists
 *              finds if a location exists on the graph
 *
 *  @param loc - the location being searched for
 *  @param adj - the vector of nodes containing the graph
 *  @return - true if the location exists on the graph, false if not
 */
bool exists(string loc, vector<node *> &adj);

/**
 *  Function:   listLocs
 *              lists all locations in the graph
 *
 *  @param adj - adjascency list containing the graph
 */
void listLocs(vector<node *> adj);

/**
 *  Function:   findPaths
 *              finds the shortest paths to each location from the source
 *
 *  @param adj - the adjascency list containing the graph
 *  @param source - the source location
 *  @return - a vector of dijkstra nodes with all of the shortest paths
 */
vector<dijkstra *> findPaths(vector<node *> adj, string source);

/**
 *  Function:   allVisited
 *              finds whether or not all of the dijkstra nodes have been visited
 *
 *  @param dijk - the vector of dijkstra nodes
 *  @return - true if all of the locations have been visited, false if not
 */
bool allVisited(vector<dijkstra *> dijk);

/**
 *  Function:   searchLoc
 *              finds the node containing the target location
 *
 *  @param adj - adjascency list containing the graph
 *  @param loc - target location
 *  @return - a pointer to the node containing the location
 */
node *searchLoc(vector<node *> adj, string loc);

/**
 *  Function:   searchDLoc
 *              finds the dijkstra node containing the target location
 *
 *  @param dijk - vector of dijkstra nodes being searched through
 *  @param loc - target location
 *  @return - a pointer to the dijkstra node containing the location
 */
dijkstra *searchDLoc(vector<dijkstra *> dijk, string loc);

/**
 *  Function:   compareDijk
 *              finds the smallest distance of two nodes
 *
 *  @param d1 - the first dijkstra node being compared
 *  @param d2 - the second dijkstra node being compared
 *  @return - true if the distance of the second is larger than the first, false otherwise
 */
bool compareDijk(dijkstra *d1, dijkstra *d2);

/**
 *  Function:   findNextUnvisited
 *              finds the next node in the vector that has not been visited
 *
 *  @param dijk - the vector of dijkstra nodes
 *  @return - the index of the dijkstra node with the lowest distance that has not been visited
 */
int findNextUnvisited(vector<dijkstra *> dijk);

/**
 *  Function:   findOnePath
 *              finds the shortest path from a source to a destination
 *
 *  @param adj - the adjascency list containing the graph
 *  @param source - the source location
 *  @param dest - the destination location
 *  @return - a vector of pairs of the location and the distance it takes to get there from the source
 */
vector<pair<string, int>> findOnePath(vector<node *> adj, string source, string dest);

/**
 *  Function:   printPath
 *              prints the path between a source and a destination
 *
 *  @param path - the vector of pairs containing the path from source to destination
 */
void printPath(vector<pair<string, int>> path);

/**
 *  Function:   code
 *              prints paths to all possible destinations from one source
 *
 *  @param adj - the adjascency list containing the graph
 *  @param source - the source location
 */
void printAllPaths(vector<node *> adj, string source);

int main(int argc, char *argv[])
{
    vector<node *> adjList;
    vector<dijkstra *> paths;
    vector<pair<string, int>> onePath;

    switch (argc)
    {
    // if there is no argument, print the usage
    case 1:
        usage();
        return 0;

    // if there is just the file
    case 2:
        // check if the file is able to be opened
        if (fileFail(argv[1]))
        {
            return -1;
        }

        // load the file into the adjascency list and print all of the possible locations
        adjList = loadFile(argv[1]);
        listLocs(adjList);
        return 0;

    // if there is the file and the source location
    case 3:
        // check if the file is able to be opened
        if (fileFail(argv[1]))
        {
            return -1;
        }
        // load file into adjascency list
        adjList = loadFile(argv[1]);

        // print the shortest path to each location
        printAllPaths(adjList, argv[2]);

        return 0;

    case 4:

        // check if the file can be opened
        if (fileFail(argv[1]))
        {
            return -1;
        }

        // add to the adjascency list
        adjList = loadFile(argv[1]);

        // if the source does not exist, exit
        if (exists(argv[2], adjList) == false)
        {
            cout << endl
                 << "The source location, " << argv[2] << ", does not exist on this graph." << endl;
            listLocs(adjList);
            return -1;
        }

        // if the destination does not exist, exit
        if (exists(argv[3], adjList) == false)
        {
            cout << endl
                 << "The destination location, " << argv[3] << ", does not exist on this graph." << endl;
            listLocs(adjList);
            return -1;
        }

        // find and print the path from the source to the destination
        onePath = findOnePath(adjList, argv[2], argv[3]);
        printPath(onePath);

        break;

    default:
        // error when there is too many arguments
        cout << endl
             << "Too many arguments. See usage for help:" << endl;
        usage();
        return -1;
    }
}

void usage()
{
    cout << endl
         << "directions.cc: uses a graph to determine paths between destinations" << endl
         << endl;
    cout << "Usage: [graph file] [first location] [second location]" << endl;
    cout << "[graph.txt location1 location2] (displays the shortest route, stops, and total distance)" << endl;
    cout << "[graph.txt location1] (displays the shortest route to all other locations)" << endl;
    cout << "[graph.txt] (displays all available locations)" << endl;
}

bool fileFail(string fileName)
{
    // opens files and checks if it fails
    ifstream inStream;
    inStream.open(fileName);
    if (inStream.fail())
    {
        cout << "File was unable to be opened. Please try again." << endl;
        return true;
    }
    return false;
}

vector<node *> loadFile(string fileName)
{
    // opens file and creates vector
    ifstream inStream;
    inStream.open(fileName);
    vector<node *> adj;

    while (!inStream.eof())
    {
        // puts each line into stringstream
        stringstream sstream;
        string str;
        int dist = 0;
        node *cursor;
        getline(inStream, str);
        sstream.str(str);
        sstream >> str;
        // put strings into the vector
        if (str != "")
        {
            cursor = new node(str);
            adj.push_back(cursor);

            // put locations, next nodes, and distances into nodes
            while (!sstream.eof())
            {
                cursor->setNext(new node());
                cursor = cursor->getNext();
                sstream >> dist;
                cursor->setDist(dist);
                sstream >> str;
                cursor->setLoc(str);
            }
        }
    }

    return adj;
}

string lower(string word)
{
    // converts each individual character to lowercase
    for (int i = 0; i < word.length(); i++)
    {
        word[i] = tolower(word[i]);
    }
    return word;
}

bool exists(string loc, vector<node *> &adj)
{
    loc = lower(loc);
    bool exist = false;
    // go through the vector and return true if the location is found
    for (int i = 0; i < adj.size(); i++)
    {
        if (lower(adj[i]->getLoc()) == loc)
        {
            exist = true;
        }
    }
    return exist;
}

void listLocs(vector<node *> adj)
{
    cout << endl
         << "The locations included in this graph are:" << endl
         << endl;

    // go through vector and list all locations
    for (int i = 0; i < adj.size(); i++)
    {
        cout << adj[i]->getLoc() << endl;
    }
    cout << endl;
}

vector<dijkstra *> findPaths(vector<node *> adj, string source)
{
    vector<dijkstra *> dijk;
    vector<pair<string, int>> pairs;
    node *current = nullptr;
    node *cursor;
    dijkstra *tmp;

    // put all nodes in adjascency list into dijkstra nodes
    for (int i = 0; i < adj.size(); i++)
    {
        dijk.push_back(new dijkstra(adj[i]->getLoc()));
        if (lower(adj[i]->getLoc()) == lower(source))
        {
            dijk[i]->visit(true);
            dijk[i]->setDist(0);
        }
    }
    sort(dijk.begin(), dijk.end(), compareDijk);

    int i = 0;

    // go through all dijkstra nodes and find the shortest path to source
    while (!allVisited(dijk))
    {
        current = searchLoc(adj, dijk[i]->getLoc());
        dijk[i]->visit(true);
        cursor = current->getNext();

        // for each location, if a shorter path is found, update the path
        while (cursor != nullptr)
        {
            tmp = searchDLoc(dijk, cursor->getLoc());
            if (tmp->getDist() == INT16_MAX && cursor->getLoc() != dijk[i]->getLoc())
            {
                tmp->setPrev(dijk[i]);
                tmp->setDist(cursor->getDist() + tmp->getPrev()->getDist());
            }
            else
            {
                if (tmp->getPrev() != nullptr && tmp->getPrev()->getDist() + cursor->getDist() < tmp->getDist() && tmp->isVisited() == false && tmp->getPrev()->isVisited() == false)
                {

                    tmp->setPrev(dijk[i]);
                    tmp->setDist(cursor->getDist() + tmp->getPrev()->getDist());
                }
            }
            cursor = cursor->getNext();
        }
        sort(dijk.begin(), dijk.end(), compareDijk);
        i = findNextUnvisited(dijk);
    }

    return dijk;
}

bool allVisited(vector<dijkstra *> dijk)
{
    // if there is a node that hasn't been visited, return false
    for (int i = 0; i < dijk.size(); i++)
    {
        if (dijk[i]->isVisited() == false)
        {
            return false;
        }
    }
    return true;
}

node *searchLoc(vector<node *> adj, string loc)
{
    // search through all nodes and return the node that is being searched for
    for (int i = 0; i < adj.size(); i++)
    {
        if (lower(loc) == lower(adj[i]->getLoc()))
        {
            return adj[i];
        }
    }
    return new node;
}

dijkstra *searchDLoc(vector<dijkstra *> dijk, string loc)
{
    // search through dijkstra nodes and return the node with the matching location
    for (int i = 0; i < dijk.size(); i++)
    {
        if (lower(loc) == lower(dijk[i]->getLoc()))
        {
            return dijk[i];
        }
    }
    return new dijkstra;
}

bool compareDijk(dijkstra *d1, dijkstra *d2)
{
    return (d1->getDist() < d2->getDist());
}

int findNextUnvisited(vector<dijkstra *> dijk)
{
    // find the next lowest node that hasnt been visited
    int i = 0;
    while (i < dijk.size() && dijk[i]->isVisited() != false)
    {
        i++;
    }
    return i;
}

vector<pair<string, int>> findOnePath(vector<node *> adj, string source, string dest)
{
    vector<dijkstra *> dijk = findPaths(adj, source);
    vector<pair<string, int>> path;
    pair<string, int> tmp;
    dijkstra *cursor = searchDLoc(dijk, dest);

    // use a cursor to go through the path from the destination to source and add to vector
    while (cursor != nullptr && cursor->getPrev() != nullptr)
    {
        tmp.first = cursor->getLoc();
        tmp.second = cursor->getDist() - cursor->getPrev()->getDist();
        path.push_back(tmp);
        cursor = cursor->getPrev();
    }
    tmp.first = cursor->getLoc();
    tmp.second = 0;
    path.push_back(tmp);

    return path;
}

void printPath(vector<pair<string, int>> path)
{
    int totalDist = 0;
    // if there is no path between locations
    if (path[0].second == 0)
    {
        cout << endl
             << "There is no way to get between those two locations on this graph. Please try again.";
    }
    else
    {
        // iterate through the vector backwards and print
        cout << endl
             << "The path from " << path[path.size() - 1].first << " to " << path[0].first << " is:" << endl
             << endl;
        cout << path[path.size() - 1].first;
        for (int i = path.size() - 2; i >= 0; i--)
        {
            cout << " (" << path[i].second << ") -> " << path[i].first;
            totalDist += path[i].second;
        }
        cout << endl
             << endl
             << "Total Distance: " << totalDist;
    }
    cout << endl
         << endl;
}

void printAllPaths(vector<node *> adj, string source)
{
    vector<pair<string, int>> path;
    cout << endl;

    // iterate through adjascency list to find all paths
    for (int i = 0; i < adj.size(); i++)
    {
        path = findOnePath(adj, source, adj[i]->getLoc());
        // print each path
        if (path[0].second != 0)
        {
            int totalDist = 0;
            cout << path[path.size() - 1].first;
            for (int i = path.size() - 2; i >= 0; i--)
            {
                cout << " (" << path[i].second << ") -> " << path[i].first;
                totalDist += path[i].second;
            }
            cout << endl
                 << "Total Distance: " << totalDist << endl
                 << endl;
        }
    }
}