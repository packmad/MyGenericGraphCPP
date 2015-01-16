#pragma once
#ifndef BREADTHFIRSTVISIT_H
#define BREADTHFIRSTVISIT_H

#include <iterator>
#include <memory> 
#include <queue>
#include "Footprint.h"

template <typename V, template<typename V> class E>
class Graph;

template <typename V, template<typename V> class E>
class BreadthFirstVisit : public std::iterator<std::input_iterator_tag, V>
{
private:

	std::unique_ptr< std::map<V, Color> > _color = nullptr;
	std::unique_ptr< std::queue<V> > _queue = nullptr;
	std::unique_ptr< std::vector<V> > _vertexes = nullptr;
	Graph<V, E>* _graph = nullptr;
	
	Footprint _localFootprint;
	bool _visitIsEnded;

	void updateVisitedNode();
	void init();

	void DeepCopyBFS(const BreadthFirstVisit<V, E>& src, BreadthFirstVisit<V, E>& dst)
	{
		*(dst._color) = *(src._color);
		*(dst._queue) = *(src._queue);
		*(dst._vertexes) = *(src._vertexes);
		*(dst._graph) = *(src._graph);
		dst._localFootprint = src._graph->GetVersion();
		dst.visited = src.visited;
		dst._visitIsEnded = src._visitIsEnded;
	}

	void SwapBFS(BreadthFirstVisit<V, E>& src, BreadthFirstVisit<V, E>& dst)
	{
		src._color = std::move(rhs._color);
		src._queue = std::move(rhs._queue);
		src._vertexes = std::move(rhs._vertexes);
		src._graph = rhs._graph;
		src._localFootprint = rhs._localFootprint;
		src._visitIsEnded = rhs._visitIsEnded;
		src.visited = std::move(rhs.visited);
	}

public:
	V& visited;

	// Default constructor
	BreadthFirstVisit() : iterator(), visited(V()) 
	{
		_visitIsEnded = true;
	}

	BreadthFirstVisit(Graph<V, E> *const graph, V& source) : iterator(), visited(source)
	{
		_color.reset(new map < V, Color >);
		_queue.reset(new queue<V>);
		_vertexes.reset(new vector<V>);
		_graph = graph;
		_localFootprint = graph->GetVersion();
		_visitIsEnded = false;
		init();
	};

	// Copy constructor
	BreadthFirstVisit<V, E>(const BreadthFirstVisit<V, E>& bfv) : BreadthFirstVisit(bfv._graph, bfv.visited)
	{
		DeepCopyBFS(bfv, *this);
	}

	// Move constructor
	BreadthFirstVisit<V, E>(BreadthFirstVisit<V, E>&& bfv) : BreadthFirstVisit(bfv._graph, bfv.visited)
	{
		SwapBFS(bfv, *this);
	}

	// Copy assignment operator
	BreadthFirstVisit<V, E>& operator=(const BreadthFirstVisit<V, E>& rhs)
	{
		if (this != &rhs) {
			DeepCopyBFS(rhs, *this);
		}
		return *this;
	}

	// Move assignment operator
	BreadthFirstVisit<V, E>& operator=(BreadthFirstVisit<V, E>&& rhs)
	{
		SwapBFS(rhs, dst);
		return *this;
	}

	// Destructor allowing subtype polymorphism
	virtual ~BreadthFirstVisit<V, E>() {}

	bool operator!=(const BreadthFirstVisit<V, E>& rhs)
	{
		return !(*this == rhs);
	}

	bool operator==(const BreadthFirstVisit<V, E>& rhs)
	{
		return (this->_graph == rhs._graph && this->visited == rhs.visited)
			|| (this->_visitIsEnded && rhs._visitIsEnded);
	}

	BreadthFirstVisit<V, E>& operator++()
	{
		updateVisitedNode();
		return *this;
	}

	BreadthFirstVisit<V, E>& operator*()
	{
		_graph->CheckVersion(_localFootprint);
		return *this;
	}

};


#include "Graph.h" 


template <typename V, template<typename V> class E>
void BreadthFirstVisit<V, E>::init() {
	*_vertexes = _graph->GetVertexes();
	for (auto v : *_vertexes)
	{
		(*_color)[v] = Color::White;
	}
	// here visited == source
	(*_color)[visited] = Color::Gray;
	_queue->push(visited);
	updateVisitedNode();
}

template <typename V, template<typename V> class E>
void BreadthFirstVisit<V, E>::updateVisitedNode() 
{
	if (_queue->size() != 0) {
		V tmp = _queue->front();
		_queue->pop();
		vector<V> neighbors = _graph->GetNeighbors(tmp);
		for (V n : neighbors)
		{
			if ((*_color)[n] == Color::White) {
				(*_color)[n] = Color::Gray;
				_queue->push(n);
			}
		}
		(*_color)[tmp] = Color::Black;
		visited = tmp;
	}
	else {
		_visitIsEnded = true;
	}
}

#endif