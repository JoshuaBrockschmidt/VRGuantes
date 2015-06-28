#ifndef TRACKDOTS_H
#define TRACKDOTS_H

#include <vector>
#include "Leap.h"

class Coord {
 public:
	int x, y;

	Coord(int x_new=0, int y_new=0);
	void add(Coord &add_);
	void div(int div);
	double getDist(Coord &co);
};

class Dot {
 public:
	static const double r;
	static const unsigned char thres;
	Coord pos;

	Dot(Coord pos_);
};

class BigDot {
 public:
	std::vector<Dot> dots;
	int value;

	BigDot(void);
	void add(Dot dot);
	void merge(BigDot &m);
	Coord getCenter(void);
};

class BigDotList {
 public:
	std::vector<BigDot> bigDots;
	int value;

	BigDotList(Leap::Image &img)
	BigDot* getBest(void);
};

#endif
