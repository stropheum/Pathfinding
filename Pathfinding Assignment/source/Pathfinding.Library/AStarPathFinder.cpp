#include "pch.h"
#include "AStarPathFinder.h"


using namespace std;

namespace Library
{
	AStarPathFinder::AStarPathFinder()
	{
	}

	AStarPathFinder::~AStarPathFinder()
	{
	}

	deque<shared_ptr<Node>> AStarPathFinder::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<std::shared_ptr<Node>>& closedSet)
	{
		UNREFERENCED_PARAMETER(start);
		UNREFERENCED_PARAMETER(end);
		UNREFERENCED_PARAMETER(closedSet);
		deque<shared_ptr<Node>> result;
		return result;
	}
}
