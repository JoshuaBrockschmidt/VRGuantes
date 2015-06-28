#include <cstring>
#include <iostream>
#include <string>
#include <GL/gl.h>
#include <math.h>
#include "exportppm.h"
#include "findpoint.h"
#include "Leap.h"
#include "server.h"

using std::cout;
using std::endl;

Tracker track = Tracker();

int main(void)
{
	CustomListener lstn;
	Leap::Controller ctrl(lstn);
	ctrl.setPolicy(Leap::Controller::POLICY_IMAGES);

	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	ctrl.removeListener(lstn);

	return 0;
}

void CustomListener::onInit(const Leap::Controller &ctrl)
{
	cout << "Initialized" << endl;
}

void CustomListener::onConnect(const Leap::Controller &ctrl)
{
	cout << "Connected" << endl;
}

void CustomListener::onDisconnect(const Leap::Controller &ctrl)
{
	cout << "Disconnected" << endl;
}

void CustomListener::onExit(const Leap::Controller &ctrl)
{
	cout << "Exited" << endl;
}

void CustomListener::onFrame(const Leap::Controller &ctrl)
{
	return;
}

void CustomListener::onImages(const Leap::Controller &ctrl)
{
	Leap::ImageList images = ctrl.images();
	for (int i; i < 2; i++) {
		Leap::Image img = images[i];
		if (track.compare(&img)) {
			/* Announce that position of point has changed */
			Coord &pos = track.pos;
			cout << "(" << pos.x << ", " << pos.y << ")" << endl;
		}
	}
}
