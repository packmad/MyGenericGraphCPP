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
	V* _source = nullptr;
	
	Footprint _localFootprint;
	bool _visitIsEnded;

	void updateVisitedNode();
	void init();

public:
	V visited;

	BreadthFirstVisit() : iterator() {
		_visitIsEnded = true;
	}

	BreadthFirstVisit(Graph<V, E> *const graph, V& source) : iterator()
	{
		_color.reset(new map < V, Color >);
		//_queue.reset(new queue<std::unique_ptr<V>>);
		_queue.reset(new queue<V>);
		_vertexes.reset(new vector<V>);
		_graph = graph;
		_localFootprint = graph->GetVersion();
		_source = &source;
		_visitIsEnded = false;
//		visited = nullptr;
		init();
	};

	/*
	~BreadthFirstVisit()
	{
		delete _color;
		delete _queue;
		delete _vertexes;
		
	}
	*/

	BreadthFirstVisit<V, E>& operator=( BreadthFirstVisit<V, E>& rhs)
	{
		if (this != &rhs) {
			_color = std::move(rhs._color);
			_queue = std::move(rhs._queue);
			_vertexes = std::move(rhs._vertexes);
			_graph = rhs._graph;
			_source = rhs._source;
			_localFootprint = rhs._localFootprint;
			_visitIsEnded = rhs._visitIsEnded;
			visited = std::move(rhs.visited);
		}
		return *this;
	}

	bool operator!=(const BreadthFirstVisit<V, E>& rhs)
	{
		return !(*this == rhs);
	}

	bool operator==(const BreadthFirstVisit<V, E>& rhs)
	{
		return (this->_visitIsEnded == true && rhs._visitIsEnded == true);
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
	(*_color)[*_source] = Color::Gray;
	_queue->push(*_source);
	updateVisitedNode();
}

template <typename V, template<typename V> class E>
void BreadthFirstVisit<V, E>::updateVisitedNode() 
{
	if (_queue->size() != 0) {
		V tmp = _queue->front();
		_queue->pop();
		vector<V> neighbors = _graph->GetNeighbors(tmp);
		if (neighbors.size() != 0) {
			for (V n : neighbors)
			{
				if ((*_color)[n] == Color::White) {
					(*_color)[n] = Color::Gray;
					_queue->push(n);
				}
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