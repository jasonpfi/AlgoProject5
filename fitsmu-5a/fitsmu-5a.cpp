/**
* Team: fitsmu
* Jason Fitch
* Sam Smucny
*
* fitsmu-5a.cpp: main file. entry point into program.
*/

#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include "d_matrix.h"
#include "maze.h"

int main()
{
	char x;
	ifstream fin;

	// Read the maze from the file.
	string fileName[] = { "Data/maze1.txt", "Data/maze2.txt", "Data/maze3.txt" };

	for (int i = 0; i < 3; i++)
	{
		fin.open(fileName[i].c_str());
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
				// Initialization
				maze m(fin);
				m.mapMazeToGraph(g);
				m.print(0, 0, 0, 0);
				g.printNodes();
				g.printEdges();

				// Solve
				m.findPathRecursive(g);
				m.findPathNonRecursive(g);
				m.findShortestPath1(g);
				m.findShortestPath2(g);
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
		fin.close();
	}
}
