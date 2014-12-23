#pragma once
#ifndef PLACE_H
#define PLACE_H

#include <string>

using namespace std;

class Place {
public:
	string name;
	Place() { }
	Place(string n) {
		name = n;
	}
	bool operator< (const Place& rhs) const {
		return name < rhs.name;
	}
	bool operator== (const Place& rhs) const {
		return name == rhs.name;
	}
	bool operator!= (const Place& rhs) const {
		return !(name == rhs.name);
	}
};

template<>
class hash <Place> {
public:
	size_t operator()(const Place &place) const {
		return hash<string>()(place.name);
	}
};

class City : public Place
{
public:
	City(string name) : Place(name) { }
};

class Town : public Place
{
public:
	Town(string name) : Place(name) { }
};

#endif