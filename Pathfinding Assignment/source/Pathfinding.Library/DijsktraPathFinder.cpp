#include "pch.h"
#include "DijsktraPathFinder.h"


using namespace std;

namespace Library
{
	DijsktraPathFinder::DijsktraPathFinder()
	{
	}

	DijsktraPathFinder::~DijsktraPathFinder()
	{
	}

	deque<shared_ptr<Node>> DijsktraPathFinder::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
	{
		deque<shared_ptr<Node>> result;
		vector<shared_ptr<Node>> frontier;
		map<shared_ptr<Node>, shared_ptr<Node>> parent;

		shared_ptr<Node> current = start;
		parent[current] = nullptr;
		parent[end] = nullptr;
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
					node->SetPathCost((current != nullptr ? current->PathCost() : 0) + 1);

					if (find(frontier.begin(), frontier.end(), node) == frontier.end())
					{
						node->SetHeuristic(0);
						frontier.push_back(node);
						
						sort(frontier.begin(), frontier.end(), [](const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs)
						{
							return lhs->PathCost() < rhs->PathCost();
						});
					}
				}
			}

			if (frontier.size() == 0)
			{
				break;
			}

			current = *frontier.begin();
			for (auto iter = frontier.begin(); iter != frontier.end(); ++iter)
			{
				if (*iter == current)
				{
					frontier.erase(iter);
					break;
				}
			}
			closedSet.insert(current);

		} while (current != end);

		shared_ptr<Node> trail = end;
		while (trail != nullptr)
		{
			if (parent[end] == nullptr)
			{	// We don't bother constructing a path at all because we never reached the end
				break;
			}
			result.push_back(trail);
			trail = parent[trail];
		}

		return result;
	}

	std::string DijsktraPathFinder::ToString()
	{
		return "Dijkstra's Algorithm";
	}
}
