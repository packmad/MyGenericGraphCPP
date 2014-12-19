#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <functional>
#include <deque>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include <map>
#include "Color.h"
#include "DepthFirstVisit.h"
#include "BreadthFirstVisit.h"

using namespace std;

template <typename V, template<typename V> class E>
class DepthFirstVisit;

template <typename V, template<typename V> class E>
class BreadthFirstVisit;

template <typename V, template<typename V> class E>
class Graph {
	map< V, vector<E<V>> > _vertexToNeighbors;
	unsigned long int _footprint;
	

	void AddSrcDst(E<V>& edge)
	{
		if (!Contains(edge.getSource()))
			Add(edge.getSource());
		if (!Contains(edge.getDestination()))
			Add(edge.getDestination());
	}

public:
	Graph() {}
	Graph(const int x) {

	}

	void CheckAccess(int localFootprint) {
		if (_footprint != localFootprint)
			throw; //TODO
	}

	vector<E<V>> getEdges() {
		vector<E<V>> out;
		for (auto kvIter = _vertexToNeighbors.cbegin(); kvIter != _vertexToNeighbors.cend(); ++kvIter) {
			for (auto vIter = kvIter->second.cbegin(); vIter != kvIter->second.cend(); ++vIter) {
				E<V> tmp = *vIter; //TODO remove, just 4 test
				out.push_back(tmp);
			}
		}
		return out;
	}

	vector<V> getVertexes() {
		vector<V> out;
		for (auto kvIter = _vertexToNeighbors.cbegin(); kvIter != _vertexToNeighbors.cend(); ++kvIter) {
			out.push_back(kvIter->first);
		}
		return out;
	}
	
	void Add(V& vertex)
	{
		if (_vertexToNeighbors.count(vertex)==0)
		{
			_vertexToNeighbors.insert(pair<V, vector<E<V>> >(vertex, vector<E<V>>()));
			++_footprint;
		}
	}

	void Add(E<V>& edge)
	{
		if (!Contains(edge)) // no duplicates
		{
			++_footprint;
			AddSrcDst(edge);
			_vertexToNeighbors[edge.getSource()].push_back(edge); //src -> neighbors
		}
	}

	bool Contains(V& vertex)
	{
		return _vertexToNeighbors.find(vertex) != _vertexToNeighbors.end();
	}

	bool Contains(E<V>& edge)
	{
		vector<E<V>> v = getEdges();
		return find(v.begin(), v.end(), edge) != v.end();
	}

	bool Remove(V& vertex)
	{
		map< V, vector<E<V>>>::iterator it = _vertexToNeighbors.find(vertex);
		if (it != _vertexToNeighbors.end()) {
			map< V, vector<E<V>>>::iterator removed = _vertexToNeighbors.erase(it);
			return true;
		}
		return false;
	}

	bool Remove(E<V>& edge)
	{
		if (Contains(edge)) {
			vector<E<V>>& tmpEdges = _vertexToNeighbors[edge.getSource()];
			tmpEdges.erase(
				remove(tmpEdges.begin(), tmpEdges.end(), edge),
				tmpEdges.end()
				);
			return true;
		}
		return false;
	}

	int GetOutDegree(V& vertex)
	{
		return _vertexToNeighbors[vertex].size();
	}

	int GetInDegree(V& vertex)
	{
		vector<E<V>> graphEdges = getEdges();
		int inDegree=0;
		for (auto it = graphEdges.begin(); it != graphEdges.end(); ++it) {
			E<V> tmpEdge = *it;
			if (tmpEdge.getDestination() == vertex)
				++inDegree;
		}
		return inDegree;
	}

	vector<V> GetNeighbors(V vertex)
	{
		unordered_set<V> us;
		vector<E<V>> vEdges = _vertexToNeighbors[vertex];
		for (auto vIter = vEdges.cbegin(); vIter != vEdges.cend(); ++vIter) {
			E<V> tmpEdge = *vIter; //TODO remove, just 4 test
			us.insert(tmpEdge.getDestination());
		}
		vector<V> output(us.begin(), us.end());
		return output;
	}


	vector<E<V>> GetEdges(V vertex)
	{
		return _vertexToNeighbors[vertex];
	}

	vector<E<V>> GetEdges(V src, V dst)
	{
		vector<E<V>> out = GetEdges(src);
		for (auto vIter = out.cbegin(); vIter != out.cend(); ) {
			E<V> tmpEdge = *vIter;
			if (tmpEdge.getDestination() != dst)
				vIter = out.erase(vIter);
			else
				++vIter;
		}
		return out;
	}

	DepthFirstVisit<V, E> beginDFS(V& source)
	{
		return DepthFirstVisit<V, E>(this, source);
	}

	DepthFirstVisit<V, E> endDFS()
	{
		return DepthFirstVisit<V, E>();
	}


	BreadthFirstVisit<V, E> beginBFS(V& source)
	{
		return BreadthFirstVisit<V, E>(this, source);
	}
	
	BreadthFirstVisit<V, E> endBFS()
	{
		return BreadthFirstVisit<V, E>();
	}


	friend ostream& operator<<(ostream& out, Graph g)
	{
		vector<V> vertexes = getVertexes();
		vector<E<V>> edges = getEdges();
		//TODO
		return endl;
	};
};

#endif // GRAPH_H
