#ifndef _RING_H_
#define _RING_H_

#include "Planet.h"

class Ring : public Planet
{
public:
	virtual void getPosition(long long time, ld& x, ld& y, ld& z);
	virtual void draw();
};

#endif