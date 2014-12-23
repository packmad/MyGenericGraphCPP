#pragma once
#ifndef EDGE_H
#define EDGE_H


template <typename V>
class Edge {
	V _source;
	V _destination;
	int _weight = 0;

public:
	V getSource() { return _source; };
	V getDestination() { return _destination; };
	int getWeight() { return _weight; };

	Edge(){}

	Edge(const V& source,const V& destination, int weight)
	{
		_source = source;
		_destination = destination;
		_weight = weight;
	};

	friend std::ostream& operator<<(std::ostream& out, Edge e)
	{
		return out << "[" << e.getSource() << "--" << e.getWeight() << "-->" << e.getDestination() << "]" << endl;
	};

};

template <typename V>
bool operator==(Edge<V> x, Edge<V> y)
{
	return x.getSource() == y.getSource() && x.getDestination() == y.getDestination() && x.getWeight() == y.getWeight();
};

#endif 