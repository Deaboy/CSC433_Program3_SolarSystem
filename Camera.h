//
//  Camera.h
//  CSC433_Program3_SolarSystem
//
//  Created by Daniel Andrus on 2014-11-19.
//  Copyright (c) 2014 Daniel Andrus. All rights reserved.
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <cmath>
#include "Constants.h"

// OpenGL/GLUT includes based on platform
#ifndef OS_X
#include <GL/freeglut.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

class Camera
{
private:
	long double subject[3];
	long double position[3];
	long double pitch;
	long double yaw;
	long double distance;

public:
	Camera();

	void getPosition(long double& x, long double& y, long double& z);
	void getSubject(long double& x, long double& y, long double& z);
	long double getPitch();
	long double getYaw();
	long double getDistance();

	Camera& setSubject(long double x, long double y, long double z);
	Camera& setPitch(long double pitch);
	Camera& setYaw(long double yaw);
	Camera& setDistance(long double distance);

	void update();
};

#endif
