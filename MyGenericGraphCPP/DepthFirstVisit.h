#pragma once
#ifndef DEPTHFIRSTVISIT_H
#define DEPTHFIRSTVISIT_H

#include "Common.h"
using namespace std;

template <typename V, template<typename> class E>
class DepthFirstVisit : public std::iterator<input_iterator_tag, V>
{
private:
	Graph<V, E<V>> _graph;
public:
	DepthFirstVisit() {}
	DepthFirstVisit(const Graph<V, E> graph) {
		_graph = graph;
	};
	/*
	DepthFirstVisit(const DepthFirstVisit<V, E<V>>& dfs)  {};
	bool operator!=(const DepthFirstVisit<V, E<V>>& rhs) { return true; }
	bool operator==(const DepthFirstVisit<V, E<V>>& rhs) { return true; }
	DepthFirstVisit<V, E<V>>& operator++() { return *this; }
	DepthFirstVisit<V, E<V>>& operator*() { return *this; }
	*/
};

#endif