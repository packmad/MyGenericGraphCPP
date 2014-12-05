#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include "Common.h"
using namespace std;

template <typename V, template<typename V> class E>
class Graph {
	map< V, vector<E<V>> > _vertexToNeighbors;
	unsigned long int _footprint;

	void AddSrcDst(E<V>& edge)
	{
		if (!Contains(edge.getSource()))
			Add(edge.getSource());
		if (!Contains(edge.getDestination()))
			Add(edge.getDestination());
	}

public:
	Graph() {}
	Graph(const int x) {}

	void CheckAccess(int localFootprint) {
		if (_footprint != localFootprint)
			throw; //TODO
	}

	vector<E<V>> getEdges() {
		vector<E<V>> out;
		for (auto kvIter = _vertexToNeighbors.cbegin(); kvIter != _vertexToNeighbors.cend(); ++kvIter) {
			for (auto vIter = kvIter->second.cbegin(); vIter != kvIter->second.cend(); ++vIter) {
				E<V> tmp = *vIter; //TODO remove, just 4 test
				out.push_back(tmp);
			}
		}
		return out;
	}

	vector<V> getVertexes() {
		vector<V> out;
		for (auto kvIter = _vertexToNeighbors.cbegin(); kvIter != _vertexToNeighbors.cend(); ++kvIter) {
			out.push_back(kvIter->first);
		}
		return out;
	}
	
	void Add(V& vertex)
	{
		if (_vertexToNeighbors.count(vertex)==0)
		{
			_vertexToNeighbors.insert(pair<V, vector<E<V>> >(vertex, vector<E<V>>()));
			++_footprint;
		}
	}

	void Add(E<V>& edge)
	{
		if (!Contains(edge)) // no duplicates
		{
			++_footprint;
			AddSrcDst(edge);
			_vertexToNeighbors[edge.getSource()].push_back(edge); //src -> neighbors
		}
	}

	bool Contains(V& vertex)
	{
		return _vertexToNeighbors.find(vertex) != _vertexToNeighbors.end();
	}

	bool Contains(E<V>& edge)
	{
		vector<E<V>> v = getEdges();
		return find(v.begin(), v.end(), edge) != v.end();
	}

	bool Remove(V& vertex)
	{
		map< V, vector<E<V>>>::iterator it = _vertexToNeighbors.find(vertex);
		if (it != _vertexToNeighbors.end()) {
			map< V, vector<E<V>>>::iterator removed = _vertexToNeighbors.erase(it);
			return true;
		}
		return false;
	}

	bool Remove(E<V>& edge)
	{
		if (Contains(edge)) {
			vector<E<V>>& tmpEdges = _vertexToNeighbors[edge.getSource()];
			tmpEdges.erase(
				remove(tmpEdges.begin(), tmpEdges.end(), edge),
				tmpEdges.end()
				);
			return true;
		}
		return false;
	}

	int GetOutDegree(V& vertex)
	{
		return _vertexToNeighbors[vertex].size();
	}

	int GetInDegree(V& vertex)
	{
		vector<E<V>> graphEdges = getEdges();
		int inDegree=0;
		for (auto it = graphEdges.begin(); it != graphEdges.end(); ++it) {
			E<V> tmpEdge = *it;
			if (tmpEdge.getDestination() == vertex)
				++inDegree;
		}
		return inDegree;
	}

	vector<V> GetNeighbors(V vertex)
	{
		unordered_set<V> us;
		vector<E<V>> vEdges = _vertexToNeighbors[vertex];
		for (auto vIter = vEdges.cbegin(); vIter != vEdges.cend(); ++vIter) {
			E<V> tmpEdge = *vIter; //TODO remove, just 4 test
			us.insert(tmpEdge.getDestination());
		}
		vector<V> output(us.begin(), us.end());
		return output;
	}


	vector<E<V>> GetEdges(V vertex)
	{
		return _vertexToNeighbors[vertex]; //TODO new?
	}

	vector<E<V>> GetEdges(V src, V dst)
	{
		vector<E<V>> out = GetEdges(src);
		for (auto vIter = out.cbegin(); vIter != out.cend(); ) {
			E<V> tmpEdge = *vIter;
			if (tmpEdge.getDestination() != dst)
				vIter = out.erase(vIter);
			else
				++vIter;
		}
		return out;
	}


	vector<V> DepthFirstVisit(V& source)
	{
		int localFootprint = _footprint;

		map<V, Color> color;
		stack<V> stack;
		
		vector<V> vertexes = getVertexes();
		vector<V> output;

		for(auto v : vertexes)
		{
			color[v] = Color::White;
		}
		stack.push(source);
		while (stack.size() != 0)
		{
			V tmp = stack.top();
			stack.pop();
			if (color[tmp] == Color::White)
			{
				color[tmp] = Color::Black;
				CheckAccess(localFootprint);
				output.push_back(tmp);
				vector<V> neighbors = GetNeighbors(tmp);
				for(auto n : neighbors)
				{
					stack.push(n);
				}
			}
		}
		return output;
	}


	friend ostream& operator<<(ostream& out, Graph g)
	{
		vector<V> vertexes = getVertexes();
		vector<E<V>> edges = getEdges();
		//TODO
		return endl;
	};
};

#endif // GRAPH_H
/*




protected AGraph(IGraphDataStructureFactory<V, E> dataStructureFactory)
{
if (dataStructureFactory == null)
throw new ArgumentNullException();
_dataStructureFactory = dataStructureFactory; // for getting new edges collection
_vertexToNeighbors = _dataStructureFactory.GetDictionary();
}


public IEnumerable<V> BreadthFirstVisit(V source)
{
if (VertexIsNull(source))
throw new ArgumentNullException();
object localFootprint = _footprint;

Dictionary<V, Color> color = new Dictionary<V, Color>();
Queue<V> queue = new Queue<V>();

foreach (var v in Vertexes)
{
color[v] = Color.White;
}
color[source] = Color.Gray;
queue.Enqueue(source);

while (queue.Count != 0)
{
V tmp = queue.Dequeue();
foreach (var n in GetNeighbors(tmp))
{
if (color[n] == Color.White)
{
color[n] = Color.Gray;
queue.Enqueue(n);
}
}
color[tmp] = Color.Black;
CheckAccess(localFootprint);
yield return tmp;
}
}

*/
