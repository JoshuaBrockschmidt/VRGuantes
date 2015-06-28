#ifndef FINDPOINT_H
#define FINDPOINT_H

#include <vector>
#include "Leap.h"
#include "server.h"

class Coord {
 public:
	int x, y;

	Coord(int x_new=0, int y_new=0);
	void set(Coord &set_);
	void add(Coord &add_);
	void mul(int mul_);
	void div(int div_);
	double getDist(Coord &co);
};


class Dot {
 public:
	Coord pos;
	int value;

	Dot(void);
	void add(Coord c);
};


class Cluster {
 public:
	static const double r;
	std::vector<Dot> dots;

	Cluster(void);
	void add(Coord c);
	Dot* findBest(void);
};


class Tracker {
 public:
	static const unsigned char minDiff;
	Leap::Image *img;
	Coord pos;

	Tracker(void);
	bool compare(Leap::Image *compare);
};

extern Tracker track;

#endif
