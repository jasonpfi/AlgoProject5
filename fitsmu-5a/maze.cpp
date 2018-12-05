
#include "maze.h"

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n.
{
	map[i].at(j) = n;
}

int maze::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
	return map[i].at(j);
}

void maze::reverseMap(int &i, int &j, const int &id) const
// Given a node Id, identifies the row and column it is at.
// The row and column are returned using the reference parameters
// i and j.
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (getMap(r, c) == id)
			{
				i = r;
				j = c;
				return;
			}
		}
	}
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
	fin >> rows;
	fin >> cols;

	char x;

	value.resize(rows, cols);
	for (int i = 0; i <= rows - 1; i++)
		for (int j = 0; j <= cols - 1; j++)
		{
			fin >> x;
			if (x == 'O')
				value[i][j] = true;
			else
				value[i][j] = false;
		}

	map.resize(rows, cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ) const
// Print out a maze, with the goal and current cells marked on the
// board.
{
	cout << endl;

	if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
		throw rangeError("Bad value in maze::print");

	if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
		throw rangeError("Bad value in maze::print");

	for (int i = 0; i <= rows - 1; i++)
	{
		for (int j = 0; j <= cols - 1; j++)
		{
			if (i == goalI && j == goalJ)
				cout << "*";
			else
				if (i == currI && j == currJ)
					cout << "+";
				else
					if (value[i][j])
						cout << " ";
					else
						cout << "X";
		}
		cout << endl;
	}
	cout << endl;
}

bool maze::isLegal(int i, int j) const
// Return the value stored at the (i,j) entry in the maze.
{
	if (i < 0 || i >= rows || j < 0 || j >= cols)
		return false;

	return value[i][j];
}

void maze::mapMazeToGraph(graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
	// Create the nodes for the graph
	int id = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (isLegal(i, j))
			{
				node n;
				n.setNode(id, 1);
				setMap(i, j, id);
				id++;

				g.addNode(n);
			}
		}
	}

	// Add edges between nodes
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (isLegal(i, j))
			{
				node n(g.getNode(getMap(i, j)));

				// Add connected nodes
				if (isLegal(i + 1, j))
				{
					g.addEdge(n.getId(), g.getNode(getMap(i + 1, j)).getId(), 1);
					g.addEdge(g.getNode(getMap(i + 1, j)).getId(), n.getId(), 1);
				}
				if (isLegal(i, j + 1))
				{
					g.addEdge(n.getId(), g.getNode(getMap(i, j + 1)).getId(), 1);
					g.addEdge(g.getNode(getMap(i, j + 1)).getId(), n.getId(), 1);
				}
				if (isLegal(i - 1, j))
				{
					g.addEdge(n.getId(), g.getNode(getMap(i - 1, j)).getId(), 1);
					g.addEdge(g.getNode(getMap(i - 1, j)).getId(), n.getId(), 1);
				}
				if (isLegal(i, j - 1))
				{
					g.addEdge(n.getId(), g.getNode(getMap(i, j - 1)).getId(), 1);
					g.addEdge(g.getNode(getMap(i, j - 1)).getId(), n.getId(), 1);
				}
			}
		}
	}
} // end mapMazeToGraph

void maze::findPathRecursive(graph &g) const
// Uses recursive depth first search to find a path through the maze.
// Prints the solution if found.
{
	// Initialization
	g.clearVisit();
	stack<int> path = stack<int>(); // Used to store solution

	// Call recursive function
	g.dfsR(g.getNode(getMap(0, 0)), getMap(rows - 1, cols - 1), path);

	// Solution found
	printPath(path);
}

void maze::findPathNonRecursive(graph &g) const
// Uses stack based depth first search to find a path through the maze.
// Prints the solution if found.
{
	// Initialization
	g.clearVisit();
	stack<node> history = stack<node>();
	node start(g.getNode(getMap(0, 0)));
	history.push(start);
	start.visit();
	int targetNodeId(getMap(rows - 1, cols - 1));

	// Traverse graph
	while (!history.empty())
	{
		node n(history.top());

		// Short circuit if solution found
		if (n.getId() == targetNodeId)
			break;

		// Look for unvisited neighbors
		for (int i = 0; i < g.numNodes(); i++)
		{
			if (g.isEdge(n.getId(), i) && !g.getNode(i).isVisited())
			{
				g.getNode(i).visit();
				history.push(g.getNode(i));
				break;
			}
		}

		// No unvisited neighbors found. Backtrack.
		if (n.getId() == history.top().getId())
		{
			history.pop();
		}
	}

	// reverse history stack to get it in the correct order for printing
	stack<int> path = stack<int>(); // UIsed to store solution
	while (!history.empty())
	{
		path.push(history.top().getId());
		history.pop();
	}

	// Solution found
	printPath(path);
}

char maze::moveDirection(const int& ii, const int& ij, const int& fi, const int& fj) const
// Given the location of two nodes (initial and final i and j coordinates)
// returns the direction to move in to get to the final node from the initial.
{
	if (ii == fi && (ij + 1) == fj)
		return 'R';
	if ((ii + 1) == fi && ij == fj)
		return 'D';
	if (ii == fi && (ij - 1) == fj)
		return 'L';
	if ((ii - 1) == fi && ij == fj)
		return 'U';

	throw rangeError("Function arguments out of range");
}

void maze::printPath(stack<int>& path) const
// Prints the solution to the maze.
// Each step prints the next move and the resultant
// position on the maze with a plus.
{
	if (!path.empty())
	{
		int i(0), j(0);
		print(rows - 1, cols - 1, i, j);
		path.pop();
		while (!path.empty())
		{
			int toi, toj;
			reverseMap(toi, toj, path.top());
			std::cout << "Move: " << moveDirection(i, j, toi, toj);
			print(rows - 1, cols - 1, toi, toj);
			i = toi;
			j = toj;

			path.pop();
		}
	}
}
