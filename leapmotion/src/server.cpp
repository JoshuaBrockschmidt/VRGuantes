#include <cstring>
#include <iostream>
#include <string>
#include <GL/gl.h>
#include <math.h>
#include "exportppm.h"
#include "Leap.h"
#include "server.h"

using std::cout;
using std::endl;

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
	const float finalH = 400;
	const float finalW = 400;
	static int imgCnt = 0;
	static unsigned char final[(int)(finalW*finalH)];
	//DEBUG
	if (imgCnt > 1) return;
	//EOF DEBUG
	cout << "Images: " << ctrl.images().count() << endl;
	Leap::ImageList images = ctrl.images();
	for (int i; i < 2; i++, imgCnt++) {
		Leap::Image img = images[i];
		const unsigned char *imgData = img.data();
		const float *dist = img.distortion();
		const int distW = img.distortionWidth();
		const int distH = img.distortionHeight();
		const int w = img.width();
		const int h = img.height();
		struct ppm_image outImg = {
			img.width(), img.height(), img.data(),
			img.bytesPerPixel()*img.width()*img.height()
		};
		const std::string filename = "test"+std::to_string(imgCnt)+".ppm";
		if (ppm_save(outImg, filename) == (size_t)NULL) {
			cout << "Could not create image file " <<
				filename << endl;
		} else {
			cout << filename << " created" << endl;
		}
	}
}
