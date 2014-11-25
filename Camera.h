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

typedef long double ld;

class Camera : public Stepable
{
private:
	ld		subject[3];
	ld		target_subject[3];
	ld		position[3];
	ld		target_pitch;
	ld		target_yaw;
	ld		target_distance;
	ld		pitch;
	ld		yaw;
	ld		distance;
	ld		rot_ease;
	ld		zoom_ease;
	ld		move_ease;
	ld		min_distance;

public:
	Camera();

	void	getPosition(ld& x, ld& y, ld& z);
	void	getSubject(ld& x, ld& y, ld& z);
	ld		getPitch();
	ld		getYaw();
	ld		getDistance();
	ld		getMinimumDistance();

	Camera&	setSubject(ld x, ld y, ld z);
	Camera&	setPitch(ld pitch);
	Camera&	setYaw(ld yaw);
	Camera&	setDistance(ld distance);
	Camera&	setMinimumDistance(ld min_distance);
	Camera&	setRotationEasing(ld ease);
	Camera&	setZoomEasing(ld ease);
	Camera&	setMovementEasing(ld ease);

	void step();
	void update();
};

#endif
