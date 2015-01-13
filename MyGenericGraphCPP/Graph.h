#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <functional>
#include <deque>
#include <exception>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include <map>
#include "Color.h"
#include "Footprint.h"
#include "DepthFirstVisit.h"
#include "BreadthFirstVisit.h"

template <typename V, template<typename V> class E>
class DepthFirstVisit;

template <typename V, template<typename V> class E>
class BreadthFirstVisit;

class GraphException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Generic Graph Exception";
	}
};

class GraphVersionException : GraphException
{
public:
	virtual const char* what() const throw()
	{
		return "Graph versions are different!";
	}
} graphVersionException;

class VertexBelongException : GraphException
{
public:
	virtual const char* what() const throw()
	{
		return "The vertex doesn't belong to the graph!";
	}
} vertexBelongException;


template <typename V, template<typename V> class E>
class Graph {
	std::map< V, std::vector<E<V>> > _vertexToNeighbors;
	Footprint _footprint;
	
	void AddSrcDst(E<V>& edge)
	{
		if (!Contains(edge.getSource()))
			Add(edge.getSource());
		if (!Contains(edge.getDestination()))
			Add(edge.getDestination());
	}


public:
	Graph() {}

	Footprint GetVersion() {
		return _footprint;
	}

	void CheckVersion(Footprint localFootprint) const 
	{
		if (_footprint != localFootprint)
			throw graphVersionException;
	}

	std::vector<E<V>> GetEdges() const
	{
		vector<E<V>> out;
		for (const auto &kv : _vertexToNeighbors) {
			for (const auto &v : kv.second) {
				out.push_back(v);
			}
		}
		return out;
	}

	std::vector<V> GetVertexes() const
	{
		vector<V> out;
		for (const auto &kv : _vertexToNeighbors) {
			//const V* x = &kv.first;
			out.push_back(kv.first);
		}
		return out;
	}
	
	void Add(const V& vertex)
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
			AddSrcDst(edge);
			_vertexToNeighbors[edge.getSource()].push_back(edge); //src -> neighbors
			++_footprint;
		}
	}

	bool Contains(const V& vertex) const
	{
		return _vertexToNeighbors.find(vertex) != _vertexToNeighbors.end();
	}

	bool Contains(const E<V>& edge) const
	{
		vector<E<V>> v = GetEdges();
		return find(v.begin(), v.end(), edge) != v.end();
	}

	bool Remove(const V& vertex)
	{
		map<V, vector<E<V>>>::iterator it = _vertexToNeighbors.find(vertex);
		if (it != _vertexToNeighbors.end()) {
			map<V, vector<E<V>>>::iterator removed = _vertexToNeighbors.erase(it);
			++_footprint;
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
			++_footprint;
			return true;
		}
		return false;
	}

	unsigned int GetOutDegree(const V& vertex) const
	{
		auto vIt = _vertexToNeighbors.find(vertex);
		if (vIt == _vertexToNeighbors.end())
			throw vertexBelongException;
		return vIt->second.size();
	}

	unsigned int GetInDegree(const V& vertex) const
	{
		if (!Contains(vertex))
			throw vertexBelongException;
		vector<E<V>> graphEdges = GetEdges();
		int inDegree = 0;
		for (auto &edge : graphEdges) {
			if (edge.getDestination() == vertex)
				++inDegree;
		}
		return inDegree;

	}

	std::vector<V> GetNeighbors(const V& vertex) const
	{
		auto vIt = _vertexToNeighbors.find(vertex);
		if (vIt == _vertexToNeighbors.end())
			throw vertexBelongException;

		unordered_set<V> us;
		vector<E<V>> vEdges = vIt->second;
		for (auto &edge : vEdges) {
			us.insert(edge.getDestination());
		}
		vector<V> output(us.begin(), us.end());
		return output;
	}


	std::vector<E<V>> GetEdges(const V& vertex) const
	{
		auto vIt = _vertexToNeighbors.find(vertex);
		if (vIt == _vertexToNeighbors.end())
			throw vertexBelongException;
		return vIt->second;
	}

	std::vector<E<V>> GetEdges(const V& src, const V& dst) const
	{
		if (!(Contains(src) && Contains(dst))) //tnx De Morgan :-)
			throw vertexBelongException;
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
		if (!Contains(source))
			throw vertexBelongException;
		return DepthFirstVisit<V, E>(this, source);
	}

	DepthFirstVisit<V, E> endDFS()
	{
		return DepthFirstVisit<V, E>();
	}


	BreadthFirstVisit<V, E> beginBFS(V& source)
	{
		if (!Contains(source))
			throw vertexBelongException;
		return BreadthFirstVisit<V, E>(this, source);
	}
	
	BreadthFirstVisit<V, E> endBFS()
	{
		return BreadthFirstVisit<V, E>();
	}

};

#endif // GRAPH_H
