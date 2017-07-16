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
		UNREFERENCED_PARAMETER(start);
		UNREFERENCED_PARAMETER(end);
		UNREFERENCED_PARAMETER(closedSet);
		deque<shared_ptr<Node>> result;
		return result;
	}
}
