#pragma once
#ifndef DEPTHFIRSTVISIT_H
#define DEPTHFIRSTVISIT_H

#include "Common.h"
using namespace std;

template <typename V, template<typename V> class E>
class DepthFirstVisit : public iterator<input_iterator_tag, V>
{
private:
	Graph<V, E> _graph;
public:
	DepthFirstVisit() : iterator() {}
	
	DepthFirstVisit(const Graph<V, E> graph) : iterator() {
		_graph = graph;
	};
	
	DepthFirstVisit(const DepthFirstVisit<V, E>& dfs)  {};
	bool operator!=(const DepthFirstVisit<V, E>& rhs) { return true; }
	bool operator==(const DepthFirstVisit<V, E>& rhs) { return true; }
	DepthFirstVisit<V, E>& operator++() { return *this; }
	DepthFirstVisit<V, E>& operator*() { return *this; }
	
};

#endif