/**
 * TEAM: fitsmu
 * Jason Fitch
 * Sam Smucny
 *
 * graph.cpp: contains all of the implementations for member methods in the
 *            graph.h file
 */

#include "graph.h"

graph::graph()
   :edges(0,0), nodes(0)
// Constructor that creates an empty graph. graph containing n nodes and no edges.
{
   NumEdges = 0;
}

graph::graph(int n)
// Constructor that creates a graph containing n nodes and no edges.
// Edges and nodes are initialized by their constructors.
//
// int n: the number of nodes
{
   for (int i = 0; i < n; i++)
      addNode();

   NumEdges = 0;
}

graph::graph(ifstream &fin)
// Construct a new graph using the data in fin.
//
// ifstream fin: the input file stream to read from file
{
   int n, i, j, w;
   fin >> n;

   // Add nodes.
   for (int i = 0; i < n; i++)
      addNode();

   NumEdges = 0;

   while (fin.peek() != '.')
   {
      fin >> i >> j >> w;
      addEdge(i, j, w);
   }
}

graph::graph(const graph &g)
// Graph copy constructor.
//
// graph g: the graph object whose data members are to be copied into this
//          object
{
   NumEdges = 0;

   // Create a temporary node to pass to nodes::resize to initialize
   // new nodes.  This avoids the exception that is thrown by
   // node::setId which is called by the node copy constructor.  The
   // temporary node is overwritten later in this function.

   node tempNode;
   tempNode.setId(0);

	// Resize matrices to the size of the matrices of the graph parameter
   nodes.resize(g.numNodes(),tempNode);
   edges.resize(g.numNodes(),g.numNodes());

   // Copy the nodes using the overloaded assignment operator.
   for (int i = 0; i < numNodes(); i++)
      nodes[i] = g.nodes[i];

   // Copy the edges using the overloaded assignment operator.
   for (int i = 0; i < numNodes(); i++)
      for (int j = 0; j < numNodes(); j++)
	 edges[i][j] = g.edges[i][j];
}

graph &graph::operator=(const graph &g)
// Graph assignment operator.
//
// Create a temporary node to pass to nodes::resize to initialize
// new nodes.  This avoids the exception that is thrown by
// node::setId which is called by the node copy constructor.  The
// temporary node is overwritten later in this function.
//
// graph g: the graph object whose data members are to be copied into this
//          object. A shallow copy of this object is returned
{

   node tempNode;
   tempNode.setId(0);

   nodes.resize(g.numNodes(),tempNode);
   edges.resize(g.numNodes(), g.numNodes());

   // Copy the nodes.
   for (int i = 0; i < numNodes(); i++)
      nodes[i] = g.nodes[i];

   // Copy the edges.
   for (int i = 0; i < numNodes(); i++)
      for (int j = 0; j < numNodes(); j++)
	 edges[i][j] = g.edges[i][j];

   return *this;
}

int graph::addNode(NodeWeight w)
// Add a new node with weight w.  Also increase the size of the edges
// matrix.  Return the index of the new node.
//
// int w: the weight of the new node to be added
{
   node n;
   n.setNode(numNodes(),w);
   nodes.push_back(n);

	// Increase size of edges matrix
   edges.resize(numNodes(),numNodes());
   return numNodes()-1;
}

int graph::addNode(node n)
	// Add a new node that is a copy of node n (note that the node is
	// passed by value).  Also increase the size of the edges matrix.
	// Return the index of the new node.
{

	nodes.push_back(n);

	edges.resize(numNodes(),numNodes());
	return numNodes() - 1;
}

void graph::addEdge(int i, int j, NodeWeight w)
// Add an edge of weight w from node i to node j.  Throws an exception
// if i or j is too small or large.  Does not allow duplicate edges
// to be added.
//
// int i: the id of the source node
// int j: the id of the destination node
// NodeWeight w: the weight of the new edge between the nodes
{
   if (i < 0 || i >= numNodes() || j < 0 || j >= numNodes())
      throw rangeError("Bad value in graph::addEdge");

   if (!isEdge(i,j))
      edges[i][j] = edge(i,j,w);
   NumEdges++;
}

void graph::removeEdge(int i, int j)
// Remove the edge between node i and node j.  Throws an exception if
// i or j is too large or too small, or if the edge does not exist.
//
// int i: the source node of the edge
// int j: the destination node of the edge
{
	// given id's are too small or too large
   if (i < 0 || i >= numNodes() || j < 0 || j >= numNodes())
      throw rangeError("Bad value in graph::removeEdge");

	// Edge between given nodes does not exist
   if (!isEdge(i,j))
      throw rangeError("Edge does not exist in graph::removeEdge");


   edges[i][j].setInvalid();
   NumEdges--;
}

EdgeWeight graph::getEdgeWeight(int i, int j) const
// Return the weight of the edge between node i and node j. Throws an
// exception if i or j is too small or too large, or if the edge does
// not exist.
//
// int i: the source node of the edge
// int j: the destination node of the edge
{
	// given id's are too small or too large
   if (i < 0 || i >= numNodes() || j < 0 || j >= numNodes())
      throw rangeError("Bad value in graph::getEdgeWeight");

	// Edge between given nodes does not exist
   if (!isEdge(i,j))
      throw rangeError("Edge does not exist in graph::getEdgeWeight");

   return edges[i][j].getWeight();
}

void graph::setEdgeWeight(int i, int j, EdgeWeight w)
// Sets the weight of the arc/edge from node i to node j to w.  Throws
// an exception if i or j is too small or too large, or if the edge
// does not exist.
//
// int i: the source node of the edge
// int j: the destination node of the edge
// EdgeWeight w: the new weight of the edge
{
   if (i < 0 || i >= numNodes() || j < 0 || j >= numNodes())
      throw rangeError("Bad value in graph::setEdgeWeight");

   edges[i][j].setWeight(w);
}

NodeWeight graph::getNodeWeight(int i) const
// Returns the weight of node i.  Throws an exception if i is too
// small or too large.
//
// int i: the id of the node whose weight is to be retrieved
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::getNodeWeight");

   return nodes[i].getWeight();
}

void graph::setNodeWeight(int i, NodeWeight w)
// Sets the weight of node i to w.  Throws an exception if i is too
// small or too large.
//
// int i: the id of the node whose weight is to be set
// NodeWeight w: the new weight of the node
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::setNodeWeight");

   nodes[i].setWeight(w);
}

NodeWeight graph::getTotalNodeWeight()
// Return all of the weights of the nodes added together
{
   NodeWeight weight = 0;

   for (int i = 0; i < numNodes(); i++)
      weight = weight + nodes[i].getWeight();

   return weight;
}

EdgeWeight graph::getTotalEdgeWeight()
// Return all of the weights of the edges added together
{
   EdgeWeight weight = 0;

   for (int i = 0; i < numNodes(); i++)
      for (int j = 0; j < numNodes(); j++)
         if (isEdge(i,j))
	    weight = weight + edges[i][j].getWeight();

   return weight;
}

bool graph::isEdge(NodeType i, NodeType j) const
// Return true if there is an arc/edge from node i to node j, and
// false otherwise.  Throws an exception if i is too small or too
// large.
//
// NodeType i: the id of the source node
// NodeType j: the id of the destination node
{
   if (i < 0 || i >= numNodes() || j < 0 || j >= numNodes())
      throw rangeError("Bad value in graph::isEdge");

	// Check if valid connection exists
   return edges[i][j].isValid();
}

int graph::numNodes() const
// Return the number of nodes in this graph.
{
   return nodes.size();
}

int graph::numEdges() const
// Return the number of edges in this graph.
{
   return NumEdges;
}

void graph::printNodes() const
// Print all nodes in this graph. Call the overloaded output operator on
// all of the nodes
{
   cout << "Num nodes: " << numNodes() << endl;

   for (int i = 0; i < numNodes(); i++)
      cout << getNode(i);
}

void graph::printEdges() const
// Print edge information about the graph.
{
   cout << "Num edges: " << numEdges() << endl;

   for (int i = 0; i < numNodes(); i++)
      for (int j = 0; j < numNodes(); j++)
      {
	 if (edges[i][j].isValid())
	    cout << getEdge(i,j);
      }
}

ostream &operator<<(ostream &ostr, const graph &g)
// Print all information about the graph.
{
   cout << "------------------------------------------------" << endl;
   g.printNodes();
   cout << endl;
   g.printEdges();
   cout << endl;

   return ostr;
}

node &graph::getNode(int i)
// Return a reference to the ith node.  Throws an exception if i is
// too small or too large.
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::getNode");

   return nodes[i];
}

const node &graph::getNode(int i) const
// Return a reference to the ith node.  Throws an exception if i is
// too small or too large.
//
// int i: The id of the node to be retrieved
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::getNode");

   return nodes[i];
}

edge &graph::getEdge(int i, int j)
// Return a reference to the edge connecting nodes i and j.  If i is
// too small or too large, or if the edge does not exist, throws an
// exception.
//
// int i: the id of the source node of this edge
// int j: the id of the destination node of this edge
{
   if (i < 0 || i >= numNodes() || j < 0 || j >= numNodes())
      throw rangeError("Bad value in graph::getEdge");

   if (!isEdge(i,j))
      throw rangeError("Edge does not exist in graph::getEdge");

   return edges[i][j];
}

const edge &graph::getEdge(int i, int j) const
// Return a constant reference to the edge connecting nodes i and j.  If i is
// too small or too large, or if the edge does not exist, throws an
// exception.
//
// int i: the id of the source node of this edge
// int j: the id of the destination node of this edge
{
   if (i < 0 || i >= numNodes() || j < 0 || j >= numNodes())
      throw rangeError("Bad value in graph::getEdge");

   if (!isEdge(i,j))
      throw rangeError("Edge does not exist in graph::getEdge");

   return edges[i][j];
}

void graph::mark(int i)
// Mark node i.  Throws an exception if i is too large or too small.
//
// int i: the id of the node to be marked
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::getEdge");

   nodes[i].mark();
}

void graph::mark(int i, int j)
// Mark edge (i,j).  Throws an exception if an edge between i and j does not
// exist or is not valid
//
// int i: the id of the source node of the edge
// int j: the id of the destination node of the edge
{
   if (!isEdge(i,j))
      throw rangeError("Bad value in graph::mark");

   edges[i][j].mark();
}

void graph::unMark(int i)
// unmark node i.  Throws an exception if i is too large or too small.
//
// int i: the id of the node to be unmarked
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::getEdge");

   nodes[i].unMark();
}

void graph::unMark(int i, int j)
// unmark edge (i,j).  Throws an exception if an edge between node i and node
// j does not exist
//
// int i: the id of the source node of this edge
// int j: the id of the destination node of this edge
{
   if (!isEdge(i,j))
      throw rangeError("Bad value in graph::unMark");

   edges[i][j].unMark();
}

bool graph::isMarked(int i) const
// Return true if node i is marked.  Otherwise return false.  Throws an
// exception if i is too large or too small.
//
// int i: the id of the node to be checked if marked
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::getEdge");

   return nodes[i].isMarked();
}

bool graph::isMarked(int i, int j) const
// Return true if edge (i,j) node is marked.  Otherwise return false.
// Throws an exception if (i,j) is not an edge.
//
// int i: the id of the source node of this edge
// int j: the id of the destination node of this edge
{
   if (!isEdge(i,j))
      throw rangeError("Bad value in graph::isMarked");

   return edges[i][j].isMarked();
}

void graph::clearMark()
// Set all nodes and edges as unmarked.
{
   for (int i = 0; i < numNodes(); i++)
      nodes[i].unMark();

   for (int i = 0; i < numNodes(); i++)
      for (int j = 0; j < numNodes(); j++)
	 if (isEdge(i,j))
	    edges[i][j].unMark();
}

void graph::visit(int i)
// Mark node i as visited.  Throws an exception if i is too large or
// too small.
//
// int i: the id of the node to be marked as visited
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::getEdge");

   nodes[i].visit();
}

void graph::visit(int i, int j)
// Mark edge (i,j) as visited.  Throws an exception (i,j) is not an
// edge.
//
// int i: the id of the source node of this edge
// int j: the id of the destination node of this edge
{
   if (!isEdge(i,j))
      throw rangeError("Bad value in graph::visite");

   edges[i][j].visit();
}

void graph::unVisit(int i)
// Set node i as unvisited.  Throws an exception if i is too large or
// too small.
//
// int i: the id of the node to be unvisited
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::getEdge");

   nodes[i].unVisit();
}

void graph::unVisit(int i, int j)
// Set edge (i,j) as unvisited.  Throws an exception if (i,j) is not
// an edge.
//
// int i: the id of the source node of this edge
// int j: the id of the destination node of this edge
{
   if (!isEdge(i,j))
      throw rangeError("Bad value in graph::unVisit");

   edges[i][j].unVisit();
}

bool graph::isVisited(int i) const
// Return true if node has been visited.  Otherwise return false.  Throws an
// exception if i is too large or too small.
//
// int i: the id of the node to be checked if it is visited
{
   if (i < 0 || i >= numNodes())
      throw rangeError("Bad value in graph::getEdge");

   return nodes[i].isVisited();
}

bool graph::isVisited(int i, int j) const
// Return true if edge (i,j) has been visited.  Otherwise return
// false.  Throws an exception if (i,j) is not an edge.
//
// int i: the id of the source node of this edge
// int j: the id of the destination node of this edge
{
   if (!isEdge(i,j))
      throw rangeError("Bad value in graph::isVisited");

   return edges[i][j].isVisited();
}

void graph::clearVisit()
// Set all nodes and edges as unvisited.
{
   for (int i = 0; i < numNodes(); i++)
      nodes[i].unVisit();

   for (int i = 0; i < numNodes(); i++)
      for (int j = 0; j < numNodes(); j++)
	 if (isEdge(i,j))
   	    unVisit(i,j);
}

bool graph::allNodesVisited()
// Return true if all nodes have been visited.  Otherwise return
// false.
{
   for (int i = 0; i < numNodes(); i++)
      if (!isVisited(i))
	 return false;

   return true;
}

bool graph::dfsR(node & n, const int& targetId, stack<int>& path)
// Recursive function to perform depth first search on graph.
//
// node n: current node
// int targetId: goal node Id
// stack<int> path: used to return the solution once found
{
	n.visit();

	// Goal reached. Short circuit and begin building path.
	if (n.getId() == targetId)
	{
		path.push(n.getId());
		return true;
	}

	// Iterate through unvisited neighbors
	for (int i = 0; i < numNodes(); i++)
	{
		if (isEdge(n.getId(), i) && !getNode(i).isVisited())
		{
			// Recursive call
			if (dfsR(getNode(i), targetId, path))
			{
				// If the function returned true then we
				// short circuiting. Continue building path
				// and return directly to caller.
				path.push(n.getId());
				return true;
			}
		}
	}
	return false;
}

bool graph::allNodesMarked()
// Return true if all nodes have been marked.  Otherwise return
// false.
{
   for (int i = 0; i < numNodes(); i++)
      if (!isMarked(i))
	 return false;

   return true;
}
