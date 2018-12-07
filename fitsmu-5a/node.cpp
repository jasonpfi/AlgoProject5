/**
 * TEAM: fitsmu
 * Jason Fitch
 * Sam Smucny
 *
 * node.cpp: contains all of the implementations for member methods in the
 *           node.h file
 */

#include "node.h"

node::node()
// Constructor, creates a new, uninitialized node. id is initialized
// elsewhere (by the graph constructor).
{
	unMark();
	unVisit();
	setWeight(0);
}

node::node(const node &n)
// Copy constructor
//
// const node n: the node object whose data is being copied into this node
{
	setNode(n.getId(), n.getWeight(), n.isMarked(), n.isVisited());
}

bool operator>(const node lhs, const node rhs)
// Overloaded comparison operator, used for building heap structure in
// priority queue
{
	return lhs.getWeight() > rhs.getWeight();
}

node &node::operator=(const node &n)
// Overloaded assignment operator.
//
// const node n: the node object whose data is being used to create this object
// A shallow copy of this object is returned
{
	setNode(n.getId(), n.getWeight(), n.isMarked(), n.isVisited());
	return *this;
}

NodeWeight node::getWeight() const
// Return node's weight
{
	return weight;
}

void node::setWeight(NodeWeight w)
// Set node's weight to w.
//
// NodeWeight w: the new weight of this node
{
	weight = w;
}

void node::setId(int i)
// Set node's id to i.  Throws an exception if i < 0.
//
// int i: this node's id
{
	if (i < 0)
		throw rangeError("Bad value in node::setId");

	id = i;
}

int node::getId() const
// Return node's id
{
	return id;
}

void node::setNode(int id, NodeWeight w/*=0*/, bool m/*=false*/,
	bool v/*=false*/)
	// Initialize a node
	//
	// int id: the new id of this node
	// NodeWeight w: the new weight of this node. If passed nothing, the new weight
	//               is 0.
	// bool m: The boolean value determining if this node has been marked. Default
	//         to false
	// bool v: The boolean value determining if this node has been visited. Default
	//         to false
{
	setId(id);
	setWeight(w);

	if (m)
		mark();
	else
		unMark();

	if (v)
		visit();
	else
		unVisit();
}

void node::mark()
// Mark node, set this.marked to true
{
	marked = true;
}

void node::unMark()
// Un-mark node, set this.marked to false
{
	marked = false;
}

bool node::isMarked() const
// Return true if node is marked, and false otherwise.
{
	return marked;
}

void node::visit()
// Set visited to true;
{
	visited = true;
}

void node::unVisit()
// Set visited to false;
{
	visited = false;
}

bool node::isVisited() const
// Return true if node is visited, and false otherwise.
{
	return visited;
}


ostream &operator<<(ostream &ostr, const node &n)
// Overloaded output operator for the node class,
{
	ostr << "node: " << n.getId() << " weight: " << n.getWeight()
		<< " visited: " << n.isVisited() << " marked " << n.isMarked() << endl;

	return ostr;
}
