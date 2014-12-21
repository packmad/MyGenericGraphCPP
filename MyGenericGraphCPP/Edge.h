#pragma once
#ifndef EDGE_H
#define EDGE_H

using namespace std;

template <typename V>
class Edge {
	V _source;
	V _destination;
	int _weight;

public:
	V getSource() { return _source; };
	V getDestination() { return _destination; };
	int getWeight() { return _weight; };

	Edge(){} //C2512

	Edge(V source,V destination, int weight)
	{
		_source = source;
		_destination = destination;
		_weight = weight;
	};

	friend ostream& operator<<(ostream& out, Edge e)
	{
		return out << "[" << e.getSource() << "--" << e.getWeight() << "-->" << e.getDestination() << "]" << endl;
	};
	/*
	friend bool operator==(Edge e, Edge y)
	{ 
		return true;
	};
	*/
};

template <typename V>
bool operator==(Edge<V> x, Edge<V> y)
{
	return x.getSource() == y.getSource() && x.getDestination() == y.getDestination() && x.getWeight() == y.getWeight();
};

#endif 