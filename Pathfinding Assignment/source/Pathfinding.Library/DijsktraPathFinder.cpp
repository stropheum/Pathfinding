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
		UNREFERENCED_PARAMETER(start);
		UNREFERENCED_PARAMETER(end);
		UNREFERENCED_PARAMETER(closedSet);
		deque<shared_ptr<Node>> result;
		return result;
	}
}
