#pragma once
 
#include <iostream>
#include <list>
#include <map>
 
// A directed graph, optionally weighted, with vertices of type T.
template <typename T>
class DiGraph {
private:
	std::map<T, std::map<T, size_t> > adj;
public:
    // Add an edge to the graph from vertex v1 to vertex v2. If either v1 or
    // v2 do not already exist in the the graph, they should be added. Third
    // parameter is the weight. For an unweighted graph, this parameter should
    // be omitted.
	void add_edge(const T& v1, const T& v2, size_t w = 1)
		{ if (!is_edge(v1, v2)) update_edge(v1, v2, w); }
 
    // Adds a vertex to the graph. The added vertex would have no outgoing or
    // incoming edges. If the vertex already exists, this function should do
    // nothing.
	void add_vertex(const T& v) { adj[v]; }
 
    // Returns the inward degree of vertex v.
	size_t degree_in(const T& v) const { return neighbors_in(v).size(); }
 
    // Returns the outward degree of vertex v.
	size_t degree_out(const T& v) const { return neighbors(v).size(); }
 
    // Determine if there is an edge extending from vertex v1 to vertex v2.
    // If either v1 or v2 does not exists in the graph, returns false.
	bool is_edge(const T& v1, const T& v2) const
		{ return is_vertex(v1) && adj.at(v1).find(v2) != adj.at(v1).end(); }
 
    // Determine if v exists as a vertex in the graph.
	bool is_vertex(const T& v) const { return adj.find(v) != adj.end(); }
 
    // Returns a list of vertices that can be reached by travelling from vertex
    // v along a single edge. If vertex v does not exists, returns an empty
    // list.
    std::list<T> neighbors (const T& v) const;
 
    // Returns a list of vertices from which vertex v can be reached by
    // travelling along a single edge. If vertex v does not exists, returns
    // an empty list.
    std::list<T> neighbors_in (const T& v) const;
 
    // Removes vertex v from the graph. All edges connected to vertex v are
    // also removed. If v does not exists in the graph, does nothing.
    void remove (const T& v); // Remove a vertex
 
    // Removed the edge extending from vertex v1 to vertex v2. If the edge
    // does not exist, or if either v1 or v2 does not exist, does nothing.
    void remove_edge (const T& v1, const T& v2);
 
    // Updates the weight of the edge extending from v1 to v2. If no edge
    // exists from v1 to v2, or if either v1 or v2 does not exist, the edge
    // is added with the given weight.
	void update_edge(const T& v1, const T& v2, size_t w)
		{ add_vertex(v2);  adj[v1][v2] = w; }
 
    // Returns a list of vertices in the graph.
	std::list<T> vertices() const;
 
    // Returns the weight of the edge extending from v1 to v2. If the edge
    // does not exists, or if either v1 or v2 does not exist, returns zero.
    size_t weight (const T& v1, const T& v2) const
		{ return is_vertex(v1) && is_edge(v1, v2) ? adj.at(v1).at(v2) : 0; }
};
 
// An undirected graph, optionally weighted, with vertices of type T.
template <typename T>
class Graph : public DiGraph<T> {
public:
    void add_edge (const T& v1, const T& v2, size_t w=1) {
        DiGraph<T>::add_edge(v1, v2, w);
        DiGraph<T>::add_edge(v2, v1, w);
    }
    size_t degree (const T& v) const { return DiGraph<T>::degree_out(v); }
    void remove_edge (const T& v1, const T& v2) {
        DiGraph<T>::remove_edge(v1, v2);
        DiGraph<T>::remove_edge(v2, v1);
    }
    void update_edge (const T& v1, const T& v2, size_t w) {
        DiGraph<T>::update_edge(v1, v2, w);
        DiGraph<T>::update_edge(v2, v1, w);
    }
};

template <typename T>
std::list<T> DiGraph<T>::neighbors(const T& v) const {
	std::list<T> l;
	if (is_vertex(v)) {
		for (auto p : adj.at(v))
			l.push_back(p.first);
	}
	return l;
}

template <typename T>
std::list<T> DiGraph<T>::neighbors_in(const T& v) const {
	std::list<T> l;
	for (auto p : adj) {
		if (p.second.find(v) != p.second.end())
			l.push_back(p.first);
	}
	return l;
}

template <typename T>
std::list<T> DiGraph<T>::vertices() const {
	std::list<T> l;
	for (auto p : adj)
		l.push_back(p.first);
	return l;
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const DiGraph<T>& g) {
	std::list<T> vlist = g.vertices();
	os << "Vertex count: " << vlist.size() << std::endl;
	for (auto v1 : vlist) {
		os << v1 << ":";
		for (auto v2 : vlist) {
			if (g.is_edge(v1, v2))
				os << " " << v2 << "(" << g.weight(v1, v2) << ")";
		}
		os << std::endl;
	}
    return os;
}