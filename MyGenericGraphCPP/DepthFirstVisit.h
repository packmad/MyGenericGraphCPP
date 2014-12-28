#pragma once
#ifndef DEPTHFIRSTVISIT_H
#define DEPTHFIRSTVISIT_H

#include <iterator>
#include "Footprint.h"


template <typename V, template<typename V> class E>
class Graph;

template <typename V, template<typename V> class E>
class DepthFirstVisit : public std::iterator<std::input_iterator_tag, V>
{
private:
	std::map<V, Color>* _color = nullptr;
	std::stack<V>* _stack = nullptr;
	std::vector<V>* _vertexes = nullptr;
	Graph<V, E>* _graph = nullptr;
	V* _source = nullptr;
	Footprint _localFootprint;

	void updateVisitedNode();
	void init();

public:
	V* visited = nullptr;;

	
	DepthFirstVisit() : iterator() {} //C2512

	DepthFirstVisit(Graph<V, E> *const graph, V& source) : iterator() {
		_graph = graph;
		_localFootprint = graph->GetVersion();
		_source = &source;
		_color = new map < V, Color >;
		_stack = new stack<V>;
		_vertexes = new vector<V>;
		visited = nullptr;

		init();
	};
	
	~DepthFirstVisit() {
		delete _color;
		delete _stack;
		delete _vertexes;
	}

	
	bool operator!=(const DepthFirstVisit<V, E>& rhs) {
		return !(*this == rhs);
	}
	
	bool operator==(const DepthFirstVisit<V, E>& rhs) {
		return (this->visited == nullptr &&  rhs.visited == nullptr);
	}
	
	DepthFirstVisit<V, E>& operator++() {
		updateVisitedNode();
		return *this;
	}
	
	DepthFirstVisit<V, E>& operator*() {
		_graph->CheckVersion(_localFootprint);
		return *this;
	}

};

#include "Graph.h" 


template <typename V, template<typename V> class E>
void DepthFirstVisit<V, E>::init() {
	*_vertexes = _graph->getVertexes();
	for (auto v : *_vertexes)
	{
		(*_color)[v] = Color::White;
	}
	_stack->push(*_source);
	updateVisitedNode();
}

template <typename V, template<typename V> class E>
void DepthFirstVisit<V, E>::updateVisitedNode() {
	if (_stack->size() != 0) {
		V* tmp = new V(_stack->top());
		_stack->pop();
		if ((*_color)[*tmp] == Color::White)
		{
			(*_color)[*tmp] = Color::Black;
			visited = tmp;
			vector<V> neighbors = _graph->GetNeighbors(*tmp);
			if (neighbors.size() != 0) {
				for (auto n : neighbors)
				{
					_stack->push(n);
				}
			}
		}
	}
	if (_stack->size() == 0) {
		visited = nullptr;
	}
}


#endif