#pragma once
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <algorithm>
#include <vector>

template <typename TP, typename TV>
class PQelem
{
public:
	TP priority;
	TV* value;

	PQelem(){}

	PQelem(TP p, TV& v) : priority{ p } 
	{
		value = &v;
	};

	bool operator==(const PQelem<TP, TV>& rhs) const
	{
		return this->priority == rhs.priority;
	}

	bool operator!=(const PQelem<TP, TV>& rhs) const
	{
		return !(*this == rhs);
	}

	bool operator< (const PQelem<TP,TV>& rhs) const 
	{
		return this->priority > rhs.priority;
	}
};

/**
 * DISCLAIMER:
 * this isn't the proper way to implement a priority queue! 
 * Unfortunately the std::priority_queue lacks of a method for change objects' priority.
 * Moreover I need that it contains no duplicated values.
 * So, this little project is focused on graphs with generic content, 
 * so I chosed an easy way, but inefficient.
 */

template <typename TP, typename TV>
class PriorityQueue
{
private:
	std::vector<PQelem<TP, TV>> _pq;
	Footprint _footprint = 0;
	Footprint _lastSortFootprint = 0;

	// O(n logn)
	void SortPQ() 
	{
		if (_lastSortFootprint != _footprint) {
			std::sort(_pq.begin(), _pq.end());
			_lastSortFootprint = _footprint;
		}
	}

public:
	
	// O(n)
	bool Contains(const TV& value)
	{
		for (auto e : _pq)
		{
			if (*(e.value) == value)
				return true;
		}
		return false;
	}

	// O(n)
	void Enqueue(TP priority, TV& value) 
	{
		if (Contains(value)) // no duplicated values
			return;
		_pq.push_back(PQelem<TP, TV>(priority, value));
		++_footprint;
	}

	// O(n logn)
	TV* Top() 
	{
		SortPQ();
		return _pq[_pq.size() - 1].value;
	}

	// O(n logn)
	TV* Dequeue() 
	{
		if (_pq.size() == 0)
			return nullptr;
		SortPQ();
		TV* out = _pq[_pq.size()-1].value;
		_pq.pop_back(); //queue remains ordered
		return out;
	}

	bool IsEmpty() const
	{
		return _pq.size() == 0;
	}

	// O(n)
	void SafeChangePriority(TP oldPriority, TP newPriority, const TV& value) 
	{
		for (auto& e : _pq)
		{
			if (*(e.value) == value && e.priority == oldPriority) {
				e.priority = newPriority;
				++_footprint;
				return;
			}
		}
	}
	 
};

#endif