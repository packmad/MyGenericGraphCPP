#pragma once
#ifndef DEPTHFIRSTVISIT_H
#define DEPTHFIRSTVISIT_H

#include <iterator>
#include <memory> 
#include <stack>
#include "Footprint.h"


template <typename V, template<typename V> class E>
class Graph;

template <typename V, template<typename V> class E>
class DepthFirstVisit : public std::iterator<std::input_iterator_tag, V>
{
private:
	std::unique_ptr< std::map<V, Color> > _color = nullptr;
	std::unique_ptr< std::stack<V> > _stack = nullptr;
	std::unique_ptr< std::vector<V> > _vertexes = nullptr;
	Graph<V, E>* _graph = nullptr;

	Footprint _localFootprint;
	bool _visitIsEnded;

	void updateVisitedNode();
	void init();

	void DeepCopyBFS(const DepthFirstVisit<V, E>& src, DepthFirstVisit<V, E>& dst)
	{
		*(dst._color) = *(src._color);
		*(dst._stack) = *(src._stack);
		*(dst._vertexes) = *(src._vertexes);
		*(dst._graph) = *(src._graph);
		dst._localFootprint = src._graph->GetVersion();
		dst.visited = src.visited;
		dst._visitIsEnded = src._visitIsEnded;
	}

	void SwapBFS(DepthFirstVisit<V, E>& src, DepthFirstVisit<V, E>& dst)
	{
		src._color = std::move(dst._color);
		src._stack = std::move(dst._stack);
		src._vertexes = std::move(dst._vertexes);
		src._graph = dst._graph;
		src._localFootprint = dst._localFootprint;
		src._visitIsEnded = dst._visitIsEnded;
		src.visited = std::move(dst.visited);
	}

public:
	V& visited;

	// Default constructor
	DepthFirstVisit() : iterator(), visited(V())
	{
		_visitIsEnded = true;
	}

	DepthFirstVisit(Graph<V, E> *const graph, V& source) : iterator(), visited(source)
	{
		_color.reset(new map < V, Color >);
		_stack.reset(new stack<V>);
		_vertexes.reset(new vector<V>);
		_graph = graph;
		_localFootprint = graph->GetVersion();
		_visitIsEnded = false;
		init();
	};

	// Copy constructor
	DepthFirstVisit<V, E>(const DepthFirstVisit<V, E>& bfv) : DepthFirstVisit(bfv._graph, bfv.visited)
	{
		DeepCopyBFS(bfv, *this);
	}

	// Move constructor
	DepthFirstVisit<V, E>(DepthFirstVisit<V, E>&& bfv) : DepthFirstVisit(bfv._graph, bfv.visited)
	{
		SwapBFS(bfv, *this);
	}

	// Copy assignment operator
	DepthFirstVisit<V, E>& operator=(const DepthFirstVisit<V, E>& rhs)
	{
		if (this != &rhs) {
			DeepCopyBFS(rhs, *this);
		}
		return *this;
	}

	// Move assignment operator
	DepthFirstVisit<V, E>& operator=(DepthFirstVisit<V, E>&& rhs)
	{
		SwapBFS(rhs, dst);
		return *this;
	}

	// Destructor allowing subtype polymorphism
	virtual ~DepthFirstVisit<V, E>() {}

	bool operator!=(const DepthFirstVisit<V, E>& rhs)
	{
		return !(*this == rhs);
	}

	bool operator==(const DepthFirstVisit<V, E>& rhs)
	{
		return (this->_graph == rhs._graph && this->visited == rhs.visited)
			|| (this->_visitIsEnded && rhs._visitIsEnded);
	}

	DepthFirstVisit<V, E>& operator++()
	{
		updateVisitedNode();
		return *this;
	}

	DepthFirstVisit<V, E>& operator*()
	{
		_graph->CheckVersion(_localFootprint);
		return *this;
	}
};

#include "Graph.h" 


template <typename V, template<typename V> class E>
void DepthFirstVisit<V, E>::init()
{
	*_vertexes = _graph->GetVertexes();
	for (const auto v : *_vertexes)
	{
		(*_color)[v] = Color::White;
	}
	_stack->push(visited);
	updateVisitedNode();
}

template <typename V, template<typename V> class E>
void DepthFirstVisit<V, E>::updateVisitedNode()
{
	if (_stack->size() != 0) {
		V tmp = _stack->top();
		_stack->pop();
		if ((*_color)[tmp] == Color::White)
		{
			(*_color)[tmp] = Color::Black;
			visited = tmp;
			vector<V> neighbors = _graph->GetNeighbors(tmp);
			if (neighbors.size() != 0) {
				for (const auto n : neighbors)
				{
					_stack->push(n);
				}
			}
		}
	}
	if (_stack->size() == 0) {
		_visitIsEnded = true;
	}
}


#endif