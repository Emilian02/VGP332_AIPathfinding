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

void Ai::BFSInit(Node* start, Node* goal)
{
    bfsTracedPath.clear();

    // Resetting all nodes
    for (auto& row : grid)
        for (auto& node : row)
            node.Reset();

    // Initialize BFS
    while (!bfsOpenSet.empty()) bfsOpenSet.pop(); 
    bfsOpenSet.push(start);
    start->visited = true;
    currentBfsNode = nullptr;
    bfsRunning = true; 
}

void Ai::BFSUpdate(Node* goal)
{
    if (!bfsRunning || bfsOpenSet.empty()) return; 

    if (currentBfsNode == nullptr)
    {
        currentBfsNode = bfsOpenSet.front(); 
        bfsOpenSet.pop();
    }

    if (currentBfsNode->atSameSpot(*goal))
    {
        // Reached the goal, trace the path
        while (currentBfsNode != nullptr)
        {
            bfsTracedPath.push_back(currentBfsNode);
            currentBfsNode = currentBfsNode->parent;
        }

        reverse(bfsTracedPath.begin(), bfsTracedPath.end());
        cout << "Path found\n";
        bfsRunning = false; // Stop BFS
        return;
    }

    // Explore neighbors
    for (Node* neighbor : GetNeighbors(currentBfsNode))
    {
        if (neighbor->blocked || neighbor->visited) continue;

        neighbor->visited = true;
        neighbor->parent = currentBfsNode;
        neighbor->step = currentBfsNode->step + 1;
        bfsOpenSet.push(neighbor);
    }

    currentBfsNode = nullptr;
}

void Ai::UpdateAndDrawBFS()
{
    for (int i = 0; i < (int)(grid.size()); i++)
        for (int j = 0; j < (int)(grid[i].size()); j++)
            grid[i][j].Draw();

    for (Node* node : bfsTracedPath)
        node->DrawPath(bfsColor);

    // Start BFS with the 'B' key
    if (IsKeyPressed(KEY_B))
    {
        BFSInit(&pointA, &pointB);  // Initialize BFS
    }

    if (bfsRunning)
    {
        BFSUpdate(&pointB);  // Process BFS each frame
    }

    // Restart the grid with the 'R' key
    if (IsKeyPressed(KEY_R))
    {
        Start();
    }

    // Draw start and goal
    pointA.step = -1; pointA.Draw();
    pointB.step = -1; pointB.Draw();
}