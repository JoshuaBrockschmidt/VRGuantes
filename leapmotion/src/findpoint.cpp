#include <math.h>
#include "findpoint.h"

Coord::Coord(int x_new, int y_new)
{
	x = x_new;
	y = y_new;
}

void Coord::set(Coord &set_)
{
	x = set_.x;
	y = set_.y;
}

void Coord::add(Coord &add_)
{
	x += add_.x;
	y += add_.y;
}

void Coord::mul(int mul_)
{
	x *= mul_;
	y *= mul_;
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


Dot::Dot(void) : pos()
{
	value = 0;
}

void Dot::add(Coord c)
{
	if (value == 0) {
		pos = c;
		value++;
	} else {
		/* Get new average */
		pos.mul(value);
		pos.add(c);
		pos.div(++value);
	}
}


const double Cluster::r = 15.0;

Cluster::Cluster(void) : dots() {}

void Cluster::add(Coord c)
{
	/* See if coordinate fits in any dots */
	for (int d = 0; d < dots.size(); d++) {
		if (c.getDist(dots[d].pos) <= Cluster::r) {
			/* Within radius of dot. Add to dot. */
			dots[d].add(c);
			return;
		}
	}
	/* Make new dot for this coordinate */
	Dot newDot = Dot();
	newDot.add(c);
	dots.push_back(newDot);
}

Dot* Cluster::findBest(void)
{
	Dot temp = Dot();
	Dot *best = &temp;
	if (dots.size() == 0)
		return best;
	for (int d = 0; d < dots.size(); d++) {
		if (dots[d].value > best->value)
			best = &dots[d];
	}
	return best;
}


const unsigned char Tracker::minDiff = 5;

Tracker::Tracker(void) : pos()
{
	img = NULL;
}

bool Tracker::compare(Leap::Image *compare)
{
	if (img == NULL)
		return false;
	int w = (img->width() < compare->width()) ?
		img->width() : compare->width();
	int h = (img->height() < compare->height()) ?
		img->height() : compare->height();
	const unsigned char *imgData1 = img->data();
	const unsigned char *imgData2 = compare->data();
	Cluster clust = Cluster();
	for (int i = 0; i < w*h; i++) {
		if (abs(imgData1[i]-imgData2[i]) >= minDiff) {
			/* Add to cluster */
			int y = i/w;
			clust.add(Coord(i-y, y));
			continue;
		}
	}
	img = compare;
	Dot *best = clust.findBest();
	if(best->value == 0) {
		return false;
	} else {
		track.pos.set(best->pos);
		return true;
	}
}
