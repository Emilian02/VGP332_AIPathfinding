#include "Ai.h"
#include "iostream"
#include <unordered_map>

using namespace std;

void Ai::Astar(Node* start, Node* goal)
{
	astarTracedPath.clear();

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Reset();
		}
	}

	//two lambdas this time one to find the ground cost and another one for the heuristic (estimation)

	auto Heuristic = [](Node* a, Node* b) -> float
		{
			return abs(a->row - b->row) + abs(a->col - b->col);
		};

	// comparison
	auto Compare = [](Node* a, Node* b)
		{
			return a->fCost > b->fCost || (a->fCost == b->fCost && a->hCost > b->hCost);
		};

	priority_queue<Node*, vector<Node*>, decltype(Compare)> openSet(Compare);

	unordered_map<Node*, float> gScore; // cheaptest route from start to each node

	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			gScore[&node] = INFINITY;
		}
	}

	gScore[start] = 0;
	start->hCost = Heuristic(start, goal);// this is right at the beginning
	start->fCost = start->hCost;
	start->visited;
	start->step = 0;
	openSet.push(start);

	while (!openSet.empty())
	{
		Node* current = openSet.top(); openSet.pop();
		current->visited = true;

		if (current->atSameSpot(*goal))
		{
			cout << "Path found" << std::endl;
			while (current != start)
			{
				astarTracedPath.push_back(current);

				current = current->parent;
			}

			reverse(astarTracedPath.begin(), astarTracedPath.end());

			return;
		}

		for (Node* neighbor : GetNeighbors(current))
		{
			if (neighbor->blocked || neighbor->visited)
				continue;

			float tentative_gCost = gScore[current] + 1; //assuming uniform

			if (tentative_gCost < gScore[neighbor])
			{
				gScore[neighbor] = tentative_gCost;
				neighbor->hCost = Heuristic(neighbor, goal);
				neighbor->fCost = gScore[neighbor] + neighbor->hCost;
				neighbor->visited = true;
				neighbor->step = current->step + 1;
				neighbor->parent = current;
				openSet.push(neighbor);
			}
		}
	}
	cout << "Path NOT found" << std::endl;
}