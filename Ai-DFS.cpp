#include "Ai.h"
#include <queue>
#include <iostream>
#include <stack>

using namespace std;

void Ai::DFS(Node* start, Node* goal)
{
    dfsTracedPath.clear();

    // resetting the nodes in the grid
    for (auto& row : grid)
    {
        for (auto& node : row)
        {
            node.Reset();
        }
    }

    stack<Node*> openSet; 

    openSet.push(start);
    start->visited = true;

    while (!openSet.empty())
    {
        Node* current = openSet.top();
        openSet.pop();

        //if (current->visited) continue;

        if (current->atSameSpot(*goal))
        {
            cout << "Reached the goal";

            while (current != start)
            {
                dfsTracedPath.push_back(current);
                current = current->parent;
            }
            reverse(dfsTracedPath.begin(), dfsTracedPath.end());
            return;
        }

        for (Node* neigbor : GetNeighbors(current))
        {
            if (neigbor->blocked || neigbor->visited) continue;

            neigbor->parent = current;
            neigbor->visited = true;

            neigbor->step = current->step + 1;

            openSet.push(neigbor);
        }
    }

    cout << "No paht found" << endl;
}