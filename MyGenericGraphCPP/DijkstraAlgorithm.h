#pragma once
#ifndef DIJKSTRAALGORITHM_H
#define DIJKSTRAALGORITHM_H

#include <limits>
#include <queue>

template <typename V, template<typename V> class E>
class Graph;

template <typename V, template<typename V> class E>
class DijkstraAlgorithm
{
private:
	std::map<V, unsigned int> _distance;
	std::map<V, E> _nextEdge;
	std::priority_queue<unsigned int, V> _priorityQueue;
	Graph<V, E>* _graph = nullptr;
	V* _source = nullptr;


	void RunAlgorithm()
	{
		_distance[*_source] = 0;
		vector<V> vertexes = (*_graph).getVertexes();
		for (auto v : vertexes)
		{
			if (v == *_source)
				_distance[v] = UINT_MAX;
			//_nextEdge[v] = default(E);
			_priorityQueue.Enqueue(_distance[v], v);
		}
		//IList<E> path = new List<E>();

		while (!_priorityQueue.empty())
		{
			V* tmp = _priorityQueue.top();
			_priorityQueue.pop();
			if (_distance[*tmpu] == UINT_MAX)
				break;
			std::vector<V> neighbors = (*_graph).GetNeighbors(*tmp);
			foreach(auto v : neighbors)
			{
				std::vector<E<V>> edges = (*_graph).GetEdges(*tmp, v);
				for (auto e : edges)
				{
					unsigned int alt = _distance[*tmp] + (unsigned int)e.getWeight();
					if (alt < _distance[v])
					{
						//TODO _priorityQueue.SafeChangePriority(_distance[v], alt, v);
						_distance[v] = alt;
						if (/*Equals(_nextEdge[v], default(E)) ||*/ e.getWeight() < _nextEdge[v].e.getWeight())
							_nextEdge[v] = e;
					}
				}
			}
		}
		for (_nextEdge::iterator it = _nextEdge.begin(); it != _nextEdge.end(); ++it) {
			path.push_back(it->second);
		}
	}



public:
	std::vector<E<V>> path;

	DijkstraAlgorithm(Graph<V, E> *const graph, V& source)
	{
		_graph = graph;
		_source = &source;
		RunAlgorithm();
	}

	/*
	public IReadOnlyCollection<E> GetPathToDestination(V destination)
	{
		var p = new List<E>();
		V tmp = destination;
		while (!tmp.Equals(_source))
		{
			foreach(var e in Paths)
			{
				if (e.Destination.Equals(tmp))
				{
					p.Add(e);
					tmp = e.Source;
					break;
				}
			}
		}
		p.Reverse();
		return new ReadOnlyCollection<E>(p);
	}

	*/

};

#endif