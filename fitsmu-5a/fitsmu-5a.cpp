// Project 5

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "graph.h"

using namespace std;

class maze
{
public:
	maze(ifstream &fin);
	void print(int, int, int, int) const;
	bool isLegal(int i, int j) const;

	void setMap(int i, int j, int n);
	int getMap(int i, int j) const;
	void reverseMap(int& i, int& j, const int& id) const;
	void mapMazeToGraph(graph &g);

	void findPathRecursive(graph &g) const;
	char moveDirection(const int& ii, const int& ij, const int& fi, const int& fj) const;

private:
	int rows; // number of rows in the maze
	int cols; // number of columns in the maze

	matrix<bool> value;
	matrix<int> map;      // Mapping from maze (i,j) values to node index values
};

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
{
	g.clearVisit();

	stack<int> path = stack<int>();
	g.dfs(g.getNode(getMap(0, 0)), getMap(rows - 1, cols - 1), path);

	// Solution found
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

char maze::moveDirection(const int& ii, const int& ij, const int& fi, const int& fj) const
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


int main()
{
	char x;
	ifstream fin;

	// Read the maze from the file.
	string fileName = "Data/maze1.txt";

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{

		graph g;
		while (fin && fin.peek() != 'Z')
		{
			maze m(fin);
			m.mapMazeToGraph(g);
			m.print(0,0,0,0);
			g.printNodes();
			g.printEdges();

			m.findPathRecursive(g);
		}


	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
	catch (rangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
}
