#pragma once
#ifndef DEPTHFIRSTVISIT_H
#define DEPTHFIRSTVISIT_H

#include <iterator>

using namespace std;

template <typename V, template<typename V> class E>
class Graph;

template <typename V, template<typename V> class E>
class DepthFirstVisit : public iterator<input_iterator_tag, V>
{
private:
	Graph<V, E>* _graph = nullptr;
	map<V, Color>* _color = nullptr;
	stack<V>* _stack = nullptr;
	vector<V>* _vertexes = nullptr;
	V* _source = nullptr;

	void updateVisitedNode();
	void init();

public:
	V* visited = nullptr;;

	
	DepthFirstVisit() : iterator() {} //C2512

	DepthFirstVisit(Graph<V, E> *const graph, V& source) : iterator() {
		_graph = graph;
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
		//this->visited == rhs.visited
		return (this->visited == nullptr &&  rhs.visited == nullptr);
	}
	
	DepthFirstVisit<V, E>& operator++() {
		updateVisitedNode();
		return *this;
	}
	
	DepthFirstVisit<V, E>& operator*() {
		return *this;
	}
	
	//destructor!!

};

#include "Graph.h" 

/*
template <typename V, template<typename V> class E>
DepthFirstVisit<V, E>& DepthFirstVisit<V, E>::operator++() { 
	return *this; 
}
*/
template <typename V, template<typename V> class E>
void DepthFirstVisit<V, E>::init() {
	*_vertexes = _graph->getVertexes();
	for (auto v : *_vertexes)
	{
		(*_color)[v] = Color::White;
	}
	_stack->push(*_source);
	//visited = &_source;
	updateVisitedNode();
}

template <typename V, template<typename V> class E>
void DepthFirstVisit<V, E>::updateVisitedNode() {
	//Graph<V, E> npgraph = *_graph;
	if (_stack->size() != 0) {
		V* tmp = new V(_stack->top());
		_stack->pop();
		if ((*_color)[*tmp] == Color::White)
		{
			(*_color)[*tmp] = Color::Black;
			//CheckAccess(localFootprint);
			//output.push_back(tmp);
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