#include "pch.h"
#include "BreadthFirstPathFinder.h"
#include "GreedyBestFirstPathFinder.h"
#include "DijsktraPathFinder.h"
#include "AStarPathFinder.h"


using namespace std;

void Init();
void Cleanup();
void Update(sf::RenderWindow& window);
void Render(sf::RenderWindow& window);
void ApplyBaseGridColors();
void ApplyPathColors(const deque<shared_ptr<Library::Node>>& path);

const int WindowSize = 800;
const int ConsoleWidth = 325;

enum State
{
	ChoosingAlgorithm,
	DisplayingPath
};
State state;

std::map<int, shared_ptr<Library::IPathFinder>> SearchAlgorithms =
{
	{ 1, make_shared<Library::BreadthFirstPathFinder>() },
	{ 2, make_shared<Library::GreedyBestFirstPathFinder>() },
	{ 3, make_shared<Library::DijsktraPathFinder>() },
	{ 4, make_shared<Library::AStarPathFinder>() }
};

string gridFilePath;
Library::Graph graph;
sf::RectangleShape** displayGrid;
sf::RectangleShape consoleBG;
sf::Font* font;
sf::Text consoleText;
bool displayingInstructions = true;

int main(int argc, char* argv[])
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	gridFilePath = (argc > 1) ? argv[1] : "Grid.grid";

	Init();
	sf::RenderWindow window(
		sf::VideoMode(WindowSize + ConsoleWidth, WindowSize), 
		"Dale Diaz - Pathfinding", 
		sf::Style::Titlebar | sf::Style::Close);
	consoleBG.setSize(sf::Vector2f(static_cast<float>(ConsoleWidth), static_cast<float>(window.getSize().y)));
	consoleBG.setFillColor(sf::Color(32, 32, 32));
	consoleBG.setOutlineColor(sf::Color(0, 128, 128));
	consoleBG.setOutlineThickness(-4);
	consoleBG.setPosition(sf::Vector2f(0, 0));

	while (window.isOpen())
	{
		Update(window);
		Render(window);
	}

	Cleanup();
	return 0;
}

/// Initialize all values
void Init()
{
	font = new sf::Font();
	if (!font->loadFromFile("Hack-Regular.ttf"))
	{
		throw new exception("Error Loading Font File");
	}
	consoleText.setFont(*font);
	consoleText.setCharacterSize(16);
	consoleText.setPosition(10, 10);
	consoleText.setFillColor(sf::Color(0, 196, 196));
	consoleText.setString("\
Choose a pathfinding option:\n \
1) Breadth-First Search     \n \
2) Greedy Best-First Search \n \
3) Dijsktra's Algorithm		\n \
4) A* Pathfinding			\n \
		");

	graph = Library::GridHelper::LoadGridFromFile(gridFilePath);
	auto begin = graph.At(Library::Point(0, 0));
	auto end = graph.At(Library::Point(9, 9));

	// TODO: Start timer
	deque<shared_ptr<Library::Node>> path = SearchAlgorithms[1].get()->FindPath(begin, end);
	// TODO: End timer

	ApplyBaseGridColors();
	ApplyPathColors(path);
}

/// Cleanup memory for all allocated values
void Cleanup()
{
	delete font;

	auto gridSize = sqrt(graph.Nodes().size());
	for (int i = 0; i < gridSize; i++)
	{
		delete[] displayGrid[i];
	}
	delete displayGrid;
}

void Update(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}
	}
}

void Render(sf::RenderWindow& window)
{
	window.clear();

	auto gridSize = sqrt(graph.Nodes().size());
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			window.draw(displayGrid[i][j]);
		}
	}

	window.draw(consoleBG);
	if (displayingInstructions)
	{
		window.draw(consoleText);
	}

	window.display();
}

void ApplyBaseGridColors()
{
	auto nodes = graph.Nodes();
	auto gridSize = sqrt(nodes.size());

	auto cellSize = WindowSize / gridSize;
	displayGrid = new sf::RectangleShape*[static_cast<int>(gridSize)];
	for (int i = 0; i < gridSize; i++)
	{
		displayGrid[i] = new sf::RectangleShape[static_cast<int>(gridSize)];
		for (int j = 0; j < gridSize; j++)
		{
			sf::Vector2f position(static_cast<float>(ConsoleWidth + (i * cellSize)), static_cast<float>(j * cellSize));
			displayGrid[i][j].setPosition(position);
			displayGrid[i][j].setSize(sf::Vector2f(static_cast<float>(cellSize), static_cast<float>(cellSize)));
			displayGrid[i][j].setFillColor(sf::Color(196, 196, 196));
			displayGrid[i][j].setOutlineColor(sf::Color(64, 64, 64));
			displayGrid[i][j].setOutlineThickness(-2);
		}
	}

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			Library::Point index(i, j);
			assert(graph.Contains(index));
			sf::Color color;

			switch (nodes[index]->Type())
			{
			case Library::NodeType::Normal:
				color = sf::Color(196, 196, 196);
				break;

			case Library::NodeType::Wall:
				color = sf::Color(64, 64, 64);
				break;
			}
			displayGrid[i][j].setFillColor(color);
		}
	}
}

void ApplyPathColors(const deque<shared_ptr<Library::Node>>& path)
{
	for (auto iter = path.begin(); iter != path.end(); ++iter)
	{
		auto position = iter->get()->Location();
		displayGrid[position.X()][position.Y()].setFillColor(sf::Color(0, 196, 196));
	}
}