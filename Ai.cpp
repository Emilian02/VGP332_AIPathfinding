#include "Ai.h"
#include <vector>
#include <iostream>

using namespace std;


void Ai::Main()
{
    InitWindow(1000, 500, "AI - Pathfinding");

    Start();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        UpdateAndDraw();

        EndDrawing();
    }

    CloseWindow();
}

void Ai::Start()
{
    // re-create the nodes
    grid.clear();

    for (int row = 0; row < ROWS; row++)
    {
        float y = NODE_SIZE * row;
        vector<Node> rowNodes;
        for (int col = 0; col < COLS; col++)
        {
            float x = NODE_SIZE * col;
            Node node = { row, col, Vector2{x, y}, DARKGRAY, LIGHTGRAY }; // fill, stroke
            rowNodes.push_back(node);
        }
        grid.push_back(rowNodes);
    }



    // take some (e.g., 5, 10, or 20) from sqaures randomly and put in blockd ones
    for (int i = 0; i < 20; i++)
    {
        randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
        grid[randRow][randCol].blocked = true;
    }


    // choose a random home and dest from squares
    randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    pointA = grid[randRow][randCol];
    pointA.costText = "A";
    pointA.fillColor = GREEN;
    pointA.blocked = true; // this just so the color renders

    randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    pointB = grid[randRow][randCol];
    pointB.costText = "B";
    pointB.fillColor = BLUE;
    pointB.blocked = true; // this just so the color renders

    randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);

    hotspot = grid[randRow][randCol];
    hotspot.fillColor = RED;
    hotspot.weight = 5;
    hotspot.costText = "5";


    queue<Node*> openSet;

    openSet.push(&hotspot); 

    hotspot.visited = true;

    while (!openSet.empty())
    {
        Node* current = openSet.front();
        openSet.pop();
        for (int i = 1; i < 3; ++i)
        {
            for (Node* neighbor : GetNeighbors(current))
            {
                if (neighbor->blocked || neighbor->visited)
                    continue;

                neighbor->visited = true;
                neighbor->parent = current;
                neighbor->fillColor = Color{ 200, 100, 100, 100 };
                neighbor->weight = hotspot.weight - i;
                neighbor->step = hotspot.weight - i;
            }
        }
    }

    //BFS(&pointA, &pointB);
    //DFS(&pointA, &pointB);
    
}

void Ai::UpdateAndDraw()
{
    for (int i = 0; i < (int)(grid.size()); i++)
        for (int j = 0; j < (int)(grid[i].size()); j++)
            grid[i][j].Draw();

    hotspot.Draw();
    
    for (Node* node : dfsTracedPath)
    {
        node->DrawPath(dfsColor);
    }

        // Check if the "R" key is pressed
    if (IsKeyPressed(KEY_R)) { Start(); } // RESTART



    // draw home and dest. Reset 
    pointA.step = -1; pointA.Draw();
    pointB.step = -1; pointB.Draw();
}





