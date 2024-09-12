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

Node* Ai::GetRandomNode()
{
    randRow = GetRandomValue(0, (int)(grid.size()) - 1);
    randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    while (grid[randRow][randCol].currentState == NodeState::Blocked ||
        grid[randRow][randCol].currentState == NodeState::Start ||
        grid[randRow][randCol].currentState == NodeState::Goal)
    {
        randRow = GetRandomValue(0, (int)(grid.size()) - 1);
        randCol = GetRandomValue(0, (int)(grid[randRow].size()) - 1);
    }

    return &grid[randRow][randCol];
}

Node* Ai::GetGoalNode()
{
    for (int i = 0; i < (int)(grid.size()); i++)
    {
        for (int j = 0; j < (int)(grid[i].size()); j++)
        {
            if (grid[i][j].currentState == NodeState::Goal)
                return &grid[i][j];
        }
    }

    return nullptr;
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
            Node node = { row, col, Vector2{x, y} };
            node.SetState(NodeState::Idle);
            rowNodes.push_back(node);
        }
        grid.push_back(rowNodes);
    }


    for (int i = 0; i < 20; i++)
    {
        GetRandomNode()->SetState(NodeState::Blocked);
    }

    GetRandomNode()->SetState(NodeState::Start);
    GetRandomNode()->SetState(NodeState::Goal);

}

void Ai::UpdateAndDraw()
{
    for (int i = 0; i < (int)(grid.size()); i++)
        for (int j = 0; j < (int)(grid[i].size()); j++)
            grid[i][j].Draw();

    ////hotspot.Draw();
    //
    //for (Node* node : bfsTracedPath)
    //{
    //    node->DrawPath(bfsColor);
    //}

    // Check if the "R" key is pressed
    if (IsKeyPressed(KEY_R)) { Start(); } // RESTART

    // Check if the "B" key is pressed
    if (IsKeyPressed(KEY_B))
    {
        GetGoalNode()->SetState(NodeState::Idle, 99, true);
        GetRandomNode()->SetState(NodeState::Goal, 99);
    }

}





