#include "Ai.h"
#include <queue>
#include <iostream>

using namespace std;

void Ai::BFS(Node* start, Node* goal)
{
    bfsTracedPath.clear();

    // resetting the nodes in the grid
    for (auto& row : grid)
    {
        for (auto& node : row)
        {
            node.Reset();
        }
    }

    // openset is every node we still have to examine
    queue<Node*> openSet;

    openSet.push(start);    // We begin by pushing the start into it

    start->visited = true;

    while (!openSet.empty())
    {
        Node* current = openSet.front();    // get the first node of the queue
        openSet.pop();

        if (current->atSameSpot(*goal))
        {
            // we have reached the goal
            while (current != start)
            {
                bfsTracedPath.push_back(current);

                current = current->parent;
            }

            reverse(bfsTracedPath.begin(), bfsTracedPath.end());

            cout << "Path found";
            return;
        }

        //add the neighbors to the open set

        for (Node* neighbor : GetNeighbors(current))
        {
            if (neighbor->blocked || neighbor->visited)
                continue;

            neighbor->visited = true;
            neighbor->parent = current;

            neighbor->step = current->step + 1;

            openSet.push(neighbor);
        }
    }

    cout << "No path found";
}