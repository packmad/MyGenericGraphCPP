#pragma once
#ifndef FOOTPRINT_H
#define FOOTPRINT_H

class Footprint {
public:
	bool operator==(const Footprint &other) const {
		return this == &other;
	}
};

#endif 