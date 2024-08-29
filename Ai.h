#include <raylib.h>
#include <vector>
#include <string>
#include <float.h> // FOR FLT MAX
#include <stdio.h> // FOR FLT MAX
#include "Node.h"
#include "queue"

#ifndef AIPATH_H
#define AIPATH_H

using namespace std;


// Ai Class
class Ai
{
public:
#define ROWS 10
#define COLS 20
#define NODE_SIZE 50

    vector<vector<Node>> grid;
    Node pointA, pointB;

    void Main();
    void Start();
    void UpdateAndDraw();


    //Get the neighbors
    vector<Node*> GetNeighbors(Node* node)
    {
        vector<Node*> neighbors;

        auto isWithinGrid = [&](int row, int col) -> bool
            {
                return row >= 0 &&
                    col >= 0 &&
                    row < ROWS &&
                    col < COLS;
            };

        //Check north
        if (isWithinGrid(node->row - 1, node->col))
            neighbors.push_back(&grid[node->row - 1][node->col]);

        //Check south
        if (isWithinGrid(node->row + 1, node->col))
            neighbors.push_back(&grid[node->row + 1][node->col]);

        //Check east
        if (isWithinGrid(node->row, node->col - 1))
            neighbors.push_back(&grid[node->row][node->col - 1]);

        //Check west
        if (isWithinGrid(node->row, node->col + 1))
            neighbors.push_back(&grid[node->row][node->col + 1]);

        return neighbors;
    }

    Node hotspot;
    int randRow;
    int randCol;

    // SEARCH ALGORITHMS
    void BFS(Node* start, Node* goal);
    vector<Node*> bfsTracedPath;
    Color bfsColor = Color{ 0, 200, 0, 100 };

    void DFS(Node* start, Node* goal);
    vector<Node*> dfsTracedPath;
    Color dfsColor = Color{ 0, 200, 0, 100 };
};

#endif