#include "Ai.h"
#include "iostream"

void Ai::Djikstra(Node* start, Node* goal)
{
	// clear the path
	djikstraTracedPath.clear();

	// rest everyone
	for (auto& row : grid)
	{
		for (auto& node : row)
		{
			node.Reset();
		}
	}

	auto Compare = [](Node* a, Node* b)
		{
			return a->gCost > b->gCost; //nodes with lower cost have a higher prioity
		};

	priority_queue < Node*, vector<Node*>, decltype (Compare) > openSet(Compare);
	//a list of the nodes that when you call to get the top of it, it always gives you the one with the highest priority

	// we begin all of nodes at infinity cost
	start->gCost = 0;
	openSet.push(start);

	while (!openSet.empty())
	{
		// I have to get the current element of the open set

		Node* current = openSet.top(); openSet.pop();

		if (current->atSameSpot(*goal))
		{
			std::cout << "Path found" << std::endl;
			while (current != start)
			{
				djikstraTracedPath.push_back(current);

				current = current->parent;
			}

			reverse(djikstraTracedPath.begin(), djikstraTracedPath.end());

			return;
		}
		
		for (Node* neighbor : GetNeighbors(current))
		{
			if (neighbor->blocked || neighbor->visited)
				continue;

			//calculate the tenetative cost
			float tentative_cost = current->gCost + 1; // assuming a uniform cost

			if (tentative_cost < neighbor->gCost) // this path to the neighbor is better
			{
				neighbor->gCost = tentative_cost;
				neighbor->parent = current;
				neighbor->visited = true;
				neighbor->step = current->step + 1;

				openSet.push(neighbor);
			}
		}
	}
	std::cout << "Path not found" << std::endl;
}