#include <raylib.h>
#include <vector>
#include <string>
#include <float.h> // FOR FLT MAX
#include <stdio.h> // FOR FLT MAX

using namespace std;




// Standalone Node Struct
struct Node
{
    int row, col;
    Vector2 position;
    Color fillColor, outlineColor;
    bool blocked = false;
    int weight = 0;

    int step = -1; // we keep this -1 for A and B and set costText Manually
    string costText = "";

    // Constructor for convenience
    Node(int row = 0, int col = 0, Vector2 position = {},
         Color fillColor = BLACK, Color outlineColor = BLACK, bool blocked = false)
        : row(row), col(col), position(position), fillColor(fillColor), outlineColor(outlineColor), blocked(blocked) {}

    // Draw the node on the screen
    void Draw()
    {
        if (blocked)
            DrawRectangleV(position, Vector2{50, 50}, fillColor);
        else if(weight > 0)
            DrawRectangleV(position, Vector2{ 50, 50 }, fillColor);
        else
            DrawRectangleLines(position.x, position.y, 50, 50, outlineColor);



        // Draw Number
        if (step != -1)
            costText = to_string(static_cast<int>(step));
        
        
        // Measure the text size to center it
        int textWidth = MeasureText(costText.c_str(), 20);
        int textHeight = 20;  // Font size is 20
        
        // Calculate the center position for the text
        Vector2 textPosition = { position.x + 25 - textWidth / 2, position.y + 25 - textHeight / 2 };

        // Draw the text in the center of the rectangle
        DrawText(costText.c_str(), textPosition.x, textPosition.y, 20, BLACK);
    }

    

    void DrawPath (Color color)
    {
        DrawRectangleV(position, Vector2{ 50, 50 }, color);
    }

    // A* related costs
    float gCost = FLT_MAX; // ground cost from the start node to the current node,
    float hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
    float fCost = FLT_MAX; // final total cost (gCost + hCost)

    Node* parent = nullptr;
    bool visited = false; // Add this flag to your Node structure

    void Reset ()
    {
        parent = nullptr;
        visited = false;
        
        gCost = FLT_MAX; // ground cost from the start node to the current node,
        hCost = FLT_MAX; // heuristic estimated cost from the current node to the end node
        fCost = FLT_MAX; // final total cost (gCost + hCost)
    }


    // New member function to check if this node is at the same position as another node
    bool atSameSpot(const Node& other) const
    {
        return this->row == other.row && this->col == other.col;
    }

};
