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
#include "Stepable.h"

// OpenGL/GLUT includes based on platform
#ifndef OS_X
#include <GL/freeglut.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

class Camera : public Stepable
{
private:
	long double subject[3];
	long double target_subject[3];
	long double position[3];
	long double target_pitch;
	long double target_yaw;
	long double target_distance;
	long double pitch;
	long double yaw;
	long double distance;
	long double rot_ease;
	long double zoom_ease;
	long double move_ease;

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
	Camera& setRotationEasing(long double ease);
	Camera& setZoomEasing(long double ease);
	Camera& setMovementEasing(long double ease);

	void step();
	void update();
};

#endif
