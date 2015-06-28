#ifndef SERVER_H
#define SERVER_H

#include "findpoint.h"
#include "Leap.h"

class CustomListener : public Leap::Listener {
 public:
	virtual void onInit(const Leap::Controller&);
	virtual void onConnect(const Leap::Controller&);
	virtual void onDisconnect(const Leap::Controller&);
	virtual void onExit(const Leap::Controller&);
	virtual void onFrame(const Leap::Controller&);
	virtual void onImages(const Leap::Controller&);
};

#endif
