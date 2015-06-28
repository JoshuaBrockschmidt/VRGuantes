#include <math.h>
#include "trackdots.h"

Coord::Coord(int x_new, int y_new)
{
	x = x_new;
	y = y_new;
}

void Coord::add(Coord &add_)
{
	x += add_.x;
	y += add_.y;
}

void Coord::div(int div_)
{
	x /= div_;
	y /= div_;
}

double Coord::getDist(Coord &co)
{
	double val_x = x - co.x;
	double val_y = y - co.y;
	return sqrt(val_x*val_x + val_y*val_y);
}


const double Dot::r = 15.0;
const unsigned char Dot::thres = 200;

Dot::Dot(Coord pos_) {
	pos = pos_;
}


BigDot::BigDot(void) : dots()
{
	value = 0;
}

void BigDot::add(Dot dot)
{
	dots.push_back(dot);
	value += 1;
}

void BigDot::merge(BigDot &m)
{
	std::vector<Dot> d;
	for (std::vector<Dot>::iterator d = m.dots.begin();
	     d != m.dots.end(); ++d)
		dots.push_back(*d);
}

Coord BigDot::getCenter(void)
{
	Coord c(0, 0);
	std::vector<Dot> d;
	for (std::vector<Dot>::iterator d = dots.begin();
	     d != dots.end(); ++d)
		c.add(d->pos);
	c.div(dots.size());
	return c;
}

BigDotList::BigDotList(Leap::Image &img) : bigDots()
{
	value = 0;
	const unsigned char *imgData = img.data();
	for (int i = 0; i < img.width()*img.height(); i++) {
		if (imgData[i] < Dot::thres)
			continue;
		int y = i/img.width();
		Dot newDot(Coord(i-y, y));
		bool groupFound = true;
		/* Check if dot belongs to another group */
		std::vector<BigDot> bd;
		std::vector<Dot> d;
		for (std::vector<BigDot>::iterator bd = bigDots.begin();
		    bd != bigDots.end(); ++bd) {
			for (std::vector<Dot>::iterator d = bd->dots.begin();
			     d != bd->dots.begin(); ++d) {
				if (newDot.pos.getDist(d->pos) < Dot::r) {
					bd->add(newDot);
					groupFound = true;
					break;
				}
			}
			if (groupFound) break;
		}
	}
}

BigDot* BigDotList::getBest(void)
{
	if (bigDots.size() == 0)
		return NULL;
	BigDot *best = &bigDots[0];
	std::vector<BigDot> d;
	for (std::vector<BigDot>::iterator d = bigDots.begin();
	     d != bigDots.end(); ++d) {
		if (d->value > best->value)
			best = &(*d);
	}
	return best;
}
