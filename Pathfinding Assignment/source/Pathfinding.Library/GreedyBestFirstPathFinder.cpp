#include "pch.h"
#include "GreedyBestFirstPathFinder.h"


using namespace std;

namespace Library
{
	GreedyBestFirstPathFinder::GreedyBestFirstPathFinder()
	{
	}

	GreedyBestFirstPathFinder::~GreedyBestFirstPathFinder()
	{
	}

	deque<shared_ptr<Node>> GreedyBestFirstPathFinder::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
	{
		deque<shared_ptr<Node>> result;
		set<shared_ptr<Node>> frontier;
		map<shared_ptr<Node>, shared_ptr<Node>> parent;

		shared_ptr<Node> current = start;
		parent[current] = nullptr;
		closedSet.insert(current);

		do
		{
			for (weak_ptr<Node> n : current->Neighbors())
			{
				shared_ptr<Node> node = shared_ptr<Node>(n);
				if (closedSet.find(node) != closedSet.end())
				{	// If the node is in the closed set, we check another node
					continue;
				}
				else
				{
					parent[node] = current;
					if (frontier.find(node) == frontier.end())
					{
						// Computer neighbor heuristic
						auto endX = end->Location().X();
						auto endY = end->Location().Y();
						auto nodeX = node->Location().X();
						auto nodeY = node->Location().Y();
						int difX = abs(endX - nodeX);
						int difY = abs(endY - nodeY);
						//						int difX = abs(end->Location().X() - node->Location().X());
						//						int difY = abs(end->Location().Y() - node->Location().Y());
						node->SetHeuristic(static_cast<float>(difX + difY));
						// add neighbor to frontier
						frontier.insert(node);
					}
				}
			}

			if (frontier.size() == 0)
			{
				break;
			}

			shared_ptr<Node> lowestHeuristicNode = *frontier.begin();
			for (auto iter = frontier.begin(); iter != frontier.end(); ++iter)
			{
				shared_ptr<Node> candidate(*iter);
				auto candidateHeuristic = candidate->Heuristic();
				auto currentLowestHeuristic = lowestHeuristicNode->Heuristic();
				if (candidateHeuristic < currentLowestHeuristic)
				{
					lowestHeuristicNode = candidate;
				}
			}

			current = lowestHeuristicNode;
			frontier.erase(current);
			closedSet.insert(current);

		} while (current != end);

		shared_ptr<Node> trail = end;
		while (trail != nullptr)
		{
			result.push_back(trail);
			trail = parent[trail];
		}

		return result;
	}
}
