#pragma once
#ifndef BREADTHFIRSTVISIT_H
#define BREADTHFIRSTVISIT_H

#include <iterator>
#include <queue>
using namespace std;

template <typename V, template<typename V> class E>
class Graph;

template <typename V, template<typename V> class E>
class BreadthFirstVisit : public std::iterator<input_iterator_tag, V>
{
private:
	std::map<V, Color>* _color = nullptr;
	std::queue<V>* _queue = nullptr;
	std::vector<V>* _vertexes = nullptr;
	Graph<V, E>* _graph = nullptr;
	V* _source = nullptr;

	void updateVisitedNode();
	void init();

public:
	V* visited = nullptr;;


	BreadthFirstVisit() : iterator() {
	}

	BreadthFirstVisit(Graph<V, E> *const graph, V& source) : iterator() {
		_graph = graph;
		_source = &source;
		_color = new map < V, Color >;
		_queue = new queue<V>;
		_vertexes = new vector<V>;
		visited = nullptr;

		init();
	};

	~BreadthFirstVisit() {
		delete _color;
		delete _queue;
		delete _vertexes;
	}


	bool operator!=(const BreadthFirstVisit<V, E>& rhs) {
		return !(*this == rhs);
	}

	bool operator==(const BreadthFirstVisit<V, E>& rhs) {
		return (this->visited == nullptr &&  rhs.visited == nullptr);
	}

	BreadthFirstVisit<V, E>& operator++() {
		updateVisitedNode();
		return *this;
	}

	BreadthFirstVisit<V, E>& operator*() {
		return *this;
	}

};


#include "Graph.h" 

template <typename V, template<typename V> class E>
void BreadthFirstVisit<V, E>::init() {
	*_vertexes = (*_graph).getVertexes();
	for (auto v : *_vertexes)
	{
		(*_color)[v] = Color::White;
	}
	(*_color)[*_source] = Color::Gray;
	(*_queue).push(*_source);
	updateVisitedNode();
}

template <typename V, template<typename V> class E>
void BreadthFirstVisit<V, E>::updateVisitedNode() {

	if ((*_queue).size() != 0) {
		V* tmp = new V((*_queue).front());
		(*_queue).pop();
		vector<V> neighbors = (*_graph).GetNeighbors(*tmp);
		if (neighbors.size() != 0) {
			for (auto n : neighbors)
			{
				if ((*_color)[n] == Color::White) {
					(*_color)[n] = Color::Gray;
					(*_queue).push(n);
				}
			}
		}
		(*_color)[*tmp] = Color::Black;
		visited = tmp;
	}
	else {
		visited = nullptr;
	}
}

#endif