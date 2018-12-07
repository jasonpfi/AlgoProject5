/**
 * TEAM: fitsmu
 * Jason Fitch
 * Sam Smucny
 *
 * node.h: Contains the class definitions of the node, including the private
 *         data members and public methods
 */

#include <iostream>
#include <fstream>
#include "d_except.h"

using namespace std;
typedef int NodeWeight;

// Represents the node class
// Contains the unique identification of the node, the weight of the node,
// whether the node has been marked, and whether the node has been visited
class node
{
public:
	node();
	node(const node &);
	node &operator=(const node &);
	friend bool operator>(const node lhs, const node rhs);

	void setId(int i);
	int getId() const;

	void setWeight(NodeWeight);
	NodeWeight getWeight() const;

	void setNode(int id, NodeWeight w = 0, bool m = false, bool v = false);

	void mark();
	void unMark();
	bool isMarked() const;

	void visit();
	void unVisit();
	bool isVisited() const;

	friend ostream &operator<<(ostream &ostr, const node &n);

private:
	int id;
	NodeWeight weight;
	bool marked;
	bool visited;
};
