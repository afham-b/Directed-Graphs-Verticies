// Topological sort of course prerequisites
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <list>
#include "graph.h"
using namespace std;

int main() {
	// Graph of prereq's at NCC
	DiGraph<string> g;
	g.add_edge("math026", "cisc115");
	g.add_edge("cisc115", "cisc125");
	g.add_edge("cisc125", "cisc225");
	g.add_edge("cisc125", "cisc230");
	g.add_edge("math026", "math140");
	g.add_edge("math140", "math180");
	g.add_edge("math180", "math181");
	g.add_edge("math180", "math202");
//	g.add_edge("math202", "cisc230");

	// Initialize in-degree of each vertex
	map<string, int> indegree;
	for (auto v : g.vertices())
		indegree[v] = g.degree_in(v);

	// Initialize queue 
	queue<string> q;

	// Place all vertices with in-degree 0 in queue 
	for (auto v : g.vertices())
		if (indegree[v] == 0)
			q.push(v);

	// Generate the ordering of vertices, using a list 
	list<string> order;
	while (!q.empty()) {
		// Front of queue is next vertex in ordering 
		string v = q.front();
		q.pop();
		order.push_back(v);
		// For each neighbor of v, decrement in-degree and add to queue if zero
		for (auto w : g.neighbors(v))
			if (--indegree[w] == 0)
				q.push(w);
	}

	// If count of order does not match count of vertices, cycle was found
	if (order.size() != g.vertices().size())
		cout << "Cycle found. No possible ordering.\n";
	else {
		cout << "Vertex order:\n";
		for (auto v : order)
			cout << "  - " << v << endl;
	}

	return 0;
}