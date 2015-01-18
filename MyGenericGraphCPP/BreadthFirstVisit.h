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

	static void DeepCopyBFS(const BreadthFirstVisit<V, E>& src, BreadthFirstVisit<V, E>& dst)
	{
		*(dst._color) = *(src._color);
		*(dst._queue) = *(src._queue);
		*(dst._vertexes) = *(src._vertexes);
		*(dst._graph) = *(src._graph);
		dst._localFootprint = src._graph->GetVersion();
		dst.visited = src.visited;
		dst._visitIsEnded = src._visitIsEnded;
	}

	static void SwapAndFreeSrcBFS(BreadthFirstVisit<V, E>& src, BreadthFirstVisit<V, E>& dst)
	{
		dst._color.reset(src._color.release());
		dst._queue.reset(src._queue.release());
		dst._vertexes = std::move(src._vertexes);
		dst._graph = src._graph;
		src._graph = nullptr;
		dst._localFootprint = src._localFootprint;
		dst._visitIsEnded = src._visitIsEnded;
		dst.visited = std::move(src.visited);
		src._visitIsEnded = true;
	}

public:
	V visited;

	// Default constructor
	BreadthFirstVisit() : iterator()
	{
		_visitIsEnded = true;
	}

	BreadthFirstVisit(Graph<V, E> *const graph, const V& source) : iterator(), visited(source)
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
		SwapAndFreeSrcBFS(bfv, *this);
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
		SwapAndFreeSrcBFS(rhs, *this);
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

	V& operator*()
	{
		_graph->CheckVersion(_localFootprint);
		return this->visited;
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