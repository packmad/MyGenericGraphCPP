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

public:
	V& visited;

	BreadthFirstVisit() : iterator() , visited(V()) 
	{
		_visitIsEnded = true;
	}

	BreadthFirstVisit(Graph<V, E> *const graph, V& source) : iterator() , visited(source)
	{
		_color.reset(new map < V, Color >);
		_queue.reset(new queue<V>);
		_vertexes.reset(new vector<V>);
		_graph = graph;
		_localFootprint = graph->GetVersion();
		_visitIsEnded = false;
		visited = source;
		init();
	};


	bool operator!=(const BreadthFirstVisit<V, E>& rhs)
	{
		return !(*this == rhs);
	}

	bool operator==(const BreadthFirstVisit<V, E>& rhs)
	{
		return (this->_visitIsEnded && rhs._visitIsEnded )
			|| (this->_graph == rhs._graph && this->visited == rhs.visited);
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
	// visited == source
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