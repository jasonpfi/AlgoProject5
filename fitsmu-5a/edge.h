/**
 * TEAM: fitsmu
 * Jason Fitch
 * Sam Smucny
 *
 * edge.h: Contains the class definitions of the edge, including the private
 *         data members and public methods
 */

#include <iostream>
#include <fstream>
#include "d_except.h"

using namespace std;
typedef int EdgeWeight;

class edge
{
   public:
      edge();
      edge(int, int, EdgeWeight = 0);
      edge(const edge &);
      edge &operator=(const edge &);

      void setWeight(EdgeWeight);
      EdgeWeight getWeight() const;

      int getSource() const;
      int getDest() const;

      void setValid();
      void setInvalid();
      bool isValid() const;

      void mark();
      void unMark();
      bool isMarked() const;

      void visit();
      void unVisit();
      bool isVisited() const;

		friend ostream &operator<<(ostream &ostr, const edge &e);

		void setEdge(int, int, EdgeWeight);

   private:
      int source;
      int dest;
      EdgeWeight weight;

		// Equals true if this edge is valid, otherwise the edge is invalid
		bool valid;
      bool visited;
      bool marked;
};
