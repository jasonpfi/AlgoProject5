/**
 * TEAM: fitsmu
 * Jason Fitch
 * Sam Smucny
 *
 * edge.cpp: contains all of the implementations for member methods in the
 *           edge.h file
 */

#include "edge.h"

edge::edge()
// Constructor, sets edge to invalid, unmarked and unvisited.
{
   setInvalid();
   unMark();
   unVisit();
}

edge::edge(int i, int j, EdgeWeight w)
// Constructor creates an edge with weight w, and marks the edge as valid, unvisited
// and unmarked.
{
   setEdge(i,j,w);
   unMark();
   unVisit();
}

edge::edge(const edge &e)
// Copy constructor.  Also copies visited and marked state.
{
   setEdge(e.source, e.dest, e.getWeight());

   if (e.isValid())
      setValid();
   else
      setInvalid();

   if (e.isVisited())
      visit();
   else
      unVisit();

   if (e.isMarked())
      mark();
   else
      unMark();
}

edge &edge::operator=(const edge &e)
// Overloaded assignment operator
{
   setEdge(e.source, e.dest, e.getWeight());

   if (e.isValid())
      setValid();
   else
      setInvalid();

   if (e.isVisited())
      visit();
   else
      unVisit();

   if (e.isMarked())
      mark();
   else
      unMark();

   return *this;
}

void edge::setEdge(int i, int j, EdgeWeight w = 0)
// Initialize edge with source, destination and weight and mark edge
// as valid.  Do not change visited or marked state.
{
   source = i;
   dest = j;
   weight = w;
   setValid();
}

void edge::setWeight(EdgeWeight w)
// Set edge weight to w.
{
   weight = w;
}

EdgeWeight edge::getWeight() const
// Return edge weight.
{
   return weight;
}

EdgeWeight edge::getSource() const
// Return source node;
{
   return source;
}

EdgeWeight edge::getDest() const
// Return destination node.
{
   return dest;
}

void edge::setValid()
// Set the edge as valid.
{
   valid = true;
}

void edge::setInvalid()
// Set the edge as invalid.
{
   valid = false;
}

bool edge::isValid() const
// Return true if edge is valid.  Otherwise return false;
{
   return valid;
}

void edge::mark()
// Mark edge
{
   marked = true;
}

void edge::unMark()
// Un-mark edge
{
   marked = false;
}

bool edge::isMarked() const
// Return true if edge is marked, and false otherwise.
{
   return marked;
}

void edge::visit()
// Set visited to true;
{
   visited = true;
}

void edge::unVisit()
// Set visited to false;
{
   visited = false;
}

bool edge::isVisited() const
// Return true if edge is visited, and false otherwise.
{
   return visited;
}

ostream &operator<<(ostream &ostr, const edge &e)
// Print all edge information for a valid edge;
{
   cout << "edge (" << e.getSource() << "," << e.getDest() << "): ";
   cout << " weight: " << e.getWeight() << " visited: " << e.isVisited()
	<< " marked " << e.isMarked() << endl;

   return ostr;
}
