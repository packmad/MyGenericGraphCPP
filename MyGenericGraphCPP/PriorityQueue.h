#pragma once
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <algorithm>
#include <vector>

template <typename TV>
class PQelem
{
public:
	unsigned int priority;
	TV value;

	PQelem(){}

	PQelem(unsigned int p, TV v) : priority{ p } {
		value = v;
	};

	bool operator==(const PQelem<TV>& rhs) {
		return this->priority == rhs.priority;
	}

	bool operator!=(const PQelem<TV>& rhs) {
		return !(*this == rhs);
	}

	bool operator< (const PQelem<TV>& rhs) const {
		return this->priority > rhs.priority;
	}
};


template <typename TV>
class PriorityQueue
{
private:
	std::vector<PQelem<TV>> _pq;
	

	void SortPQ() {
		std::sort(_pq.begin(), _pq.end());
	}

public:
	

	bool Contains(TV value)
	{
		for (auto e : _pq)
		{
			if (e.value == value)
				return true;
		}
		return false;
	}

	void Enqueue(unsigned int priority, TV value) {
		if (Contains(value)) // no duplicated values
			return;
		_pq.push_back(PQelem<TV>(priority, value));
		SortPQ();
	}

	TV Top() {
		return _pq[_pq.size() - 1].value;
	}

	TV Dequeue() {
		//if (_pq.size() == 0) TODO
		TV out = _pq[_pq.size()-1].value;
		_pq.pop_back();
		return out;
	}

	bool IsEmpty() {
		return _pq.size() == 0;
	}

	void SafeChangePriority(unsigned int oldPriority, unsigned int newPriority, TV value) {
		for (auto& e : _pq)
		{
			if (e.value == value && e.priority == oldPriority) {
				e.priority = newPriority;
				SortPQ();
				return;
			}
		}
	}
	 

};

#endif