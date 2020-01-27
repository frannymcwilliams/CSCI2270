#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "Graph.hpp"
using namespace std;

/*
class constructor
Purpose: perform all operations necessary to instantiate a class object
Parameters: none
*/
Graph::Graph()
{

}

/*
class destructor
Purpose: free all resources that the object has aquired
Parameters: none
*/
Graph::~Graph()
{

}

/*
Method Name: addEdge
Purpose: Creates an edge between two vertices (using an adjVertex struct)
Param: v1 - vertex at one end of edge
Param: v2 - vertex at opposite end of edge
*/
void Graph::addEdge(std::string v1, std::string v2, int distance)
{
	 for(unsigned int i=0; i<vertices.size(); i++)
	 {
        if(vertices[i].name == v1)
        {
            for(unsigned int j=0; j<vertices.size(); j++)
           	{
                if(vertices[j].name == v2 && i!=j)
                {
                    adjVertex s;
                    s.v = &vertices[j];
                    s.distance = distance;
                    vertices[i].adj.push_back(s);
                }
            }
        }
    }
}

/*
Method Name: addVertex
Purpose: Creates a vertex
Param: name - name of the vertex (city name)
*/
void Graph::addVertex(std::string name)
{
	vertex v;
    v.ID = vertices.size();
    v.name = name;
    v.district = 0;
   	v.visited = false;
    vertices.push_back(v);
}

/*
Method Name: displayEdges
Purpose: print all edges in graph (see writeup for format)
Parameters: none
*/
void Graph::displayEdges()
{
	for (auto const& vertex: vertices)
	{
        std::cout << vertex.district << ":" << vertex.name ;
        if (vertex.adj.size() > 0)
        {
        	std::cout << "-->";
        }
        unsigned int count = 1;
        for (auto const& adj: vertex.adj) 
        {
            std::cout << adj.v->name ;
            std::cout << " (" << adj.distance << " miles)";
            if (vertex.adj.size()>1 && count != vertex.adj.size()) std::cout << "***";
            count++;
        }
        std::cout << "\n";
    }
}


/*
Method Name: assignDistricts
Purpose: Iterate through the vertices, perform BFT to find connected components, and assign to district
Parameters: none
*/
void Graph::assignDistricts()
{
	int count = 0;
    for (auto & vertex: vertices)
    {
        if (!vertex.visited)
        {
        	count++;
            BFTraversalLabel(vertex.name, count);
        }
    }
}

/*
Method Name: findVertex
Purpose: Find and return the vertex of the specified city
Param: name - name of the city vertex to be returned
returns pointer to a vertex
*/
vertex * Graph::findVertex(std::string name)
{
	for (auto & vertex: vertices)
	{
        if (vertex.name == name)
        {
        	return &vertex;
        }
    }
    return NULL;
}

/*
Method Name: BFTraversalLabel
Purpose: Call BFTraversalLabel from within assignDistricts to label the districts. 
		This method should implement a breadth first traversal from the startingCity 
		and assign all cities encountered the distID value
Param: name - name of starting city for breadth first traversal
*/
void Graph::BFTraversalLabel(std::string startingCity, int distID) {
    vertex* v = findVertex(startingCity);
    v->district = distID;

    std::queue<vertex*> queue;
    queue.push(v);

    while (!queue.empty())
    {
        v = queue.front();
        queue.pop();
        for (auto & adj: v->adj)
        {
            if(!adj.v-> visited)
            {
                adj.v-> visited = true;
                adj.v-> district = distID;
                queue.push(adj.v);
            }
        }
    }
}
