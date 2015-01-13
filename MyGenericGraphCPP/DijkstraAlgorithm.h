#pragma once
#ifndef DIJKSTRAALGORITHM_H
#define DIJKSTRAALGORITHM_H

#include <limits>
#include "PriorityQueue.h"


template <typename V, template<typename V> class E>
class Graph;

template <typename V, template<typename V> class E>
class DijkstraAlgorithm
{
private:
	std::map<V, unsigned int> _distance;
	std::map<V, E<V>> _nextEdge;
	PriorityQueue<unsigned int, V> _priorityQueue;
	Graph<V, E>* _graph = nullptr;
	Footprint _localFootprint;
	V* _source = nullptr;
	std::vector<E<V>> _minPaths;

	void RunAlgorithm()
	{
		_distance[*_source] = 0;
		vector<V> vertexes = (*_graph).GetVertexes();
		for (auto& v : vertexes)
		{
			if (v != *_source)
				_distance[v] = UINT_MAX;
			_nextEdge[v] = E<V>();
			_priorityQueue.Enqueue(_distance[v], v);
		}
		

		while (!_priorityQueue.IsEmpty())
		{
			V* tmp = _priorityQueue.Dequeue();
			if (_distance[*tmp] == UINT_MAX)
				break;
			std::vector<V> neighbors = (*_graph).GetNeighbors(*tmp);
			for (auto v : neighbors)
			{
				std::vector<E<V>> edges = (*_graph).GetEdges(*tmp, v);
				for (auto e : edges)
				{
					unsigned int alt = _distance[*tmp] + (unsigned int)e.getWeight();
					if (alt < _distance[v])
					{
						_priorityQueue.SafeChangePriority(_distance[v], alt, v);
						_distance[v] = alt;
						if (_nextEdge[v].getWeight() == 0  || e.getWeight() < _nextEdge[v].getWeight())
							_nextEdge[v] = e;
					}
				}
			}
		}
		for (auto it = ++(_nextEdge.begin()); it != _nextEdge.end(); ++it) {
			_minPaths.push_back(it->second);
		}
	}

public:

	DijkstraAlgorithm(Graph<V, E> *const graph, V& source)
	{
		_graph = graph;
		_localFootprint = graph->GetVersion();
		_source = &source;
		RunAlgorithm();
	}

	std::vector<E<V>> GetMinimumPaths() const
	{
		_graph->CheckVersion(_localFootprint);
		return _minPaths;
	}
};

#endif