#include "pch.h"
#include "BreadthFirstPathFinder.h"


using namespace std;

namespace Library
{
	BreadthFirstPathFinder::BreadthFirstPathFinder()
	{
	}

	BreadthFirstPathFinder::~BreadthFirstPathFinder()
	{
	}

	deque<shared_ptr<Node>> BreadthFirstPathFinder::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
	{
		deque<shared_ptr<Node>> path;
		queue<shared_ptr<Node>> frontier;
		map<shared_ptr<Node>, shared_ptr<Node>> parent;

		parent[start] = nullptr;	// Used for termination condition for path construction
		parent[end] = nullptr;		// If end never gets assigned, this will early out the path construction
		frontier.push(start);
		closedSet.insert(start);
		
		while (!frontier.empty())
		{
			shared_ptr<Node> current = frontier.front();
			frontier.pop();
			if (current == end)
			{	// Eartly out, we found our path
				break;
			}

			for (weak_ptr<Node> n : current->Neighbors())
			{
				auto node = shared_ptr<Node>(n);
				if (closedSet.find(node) == closedSet.end())
				{	// The node has not previously been visited
					closedSet.insert(node);
					parent[node] = current;
					frontier.push(node);
				}
			}
		}

		shared_ptr<Node> current = end;
		while (current != nullptr)
		{
			if (parent[end] == nullptr)
			{	// We don't bother constructing a path at all because we never reached the end
				break;
			}

			path.push_back(current);
			current = parent[current];
		}

		return path;
	}
}
