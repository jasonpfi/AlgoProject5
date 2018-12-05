
#include <iostream>
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
	void findPathNonRecursive(graph &g) const;
	char moveDirection(const int& ii, const int& ij, const int& fi, const int& fj) const;
	void printPath(stack<int>&) const;

private:
	int rows; // number of rows in the maze
	int cols; // number of columns in the maze

	matrix<bool> value;
	matrix<int> map;      // Mapping from maze (i,j) values to node index values
};
