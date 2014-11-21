//
//  Camera.cpp
//  CSC433_Program3_SolarSystem
//
//  Created by Daniel Andrus on 2014-11-19.
//  Copyright (c) 2014 Daniel Andrus. All rights reserved.
//

#include "Camera.h"


Camera::Camera()
{
	subject[0] = 0;
	subject[1] = 0;
	subject[2] = 0;
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	pitch = 0;
	yaw = 0;
	distance = 0;
}

void Camera::getPosition(long double& x, long double& y, long double& z)
{
	x = position[0];
	y = position[1];
	z = position[2];
}

void Camera::getSubject(long double& x, long double& y, long double& z)
{
	x = subject[0];
	y = subject[1];
	z = subject[2];
}

long double Camera::getPitch()
{
	return RADTODEG(pitch);
}

long double Camera::getYaw()
{
	return RADTODEG(yaw);
}

long double Camera::getDistance()
{
	return distance;
}

Camera& Camera::setSubject(long double x, long double y, long double z)
{
	subject[0] = x;
	subject[1] = y;
	subject[2] = z;
	return *this;
}

Camera& Camera::setPitch(long double pitch)
{
	this->pitch = DEGTORAD(pitch > 90 ? 90 : pitch < -90 ? -90 : pitch);
	return *this;
}

Camera& Camera::setYaw(long double yaw)
{
	for (; yaw < 0; yaw += 360);
	for (; yaw >= 360; yaw -= 360);
	this->yaw = DEGTORAD(yaw);
	return *this;
}

Camera& Camera::setDistance(long double distance)
{
	this->distance = distance;
	return *this;
}

void Camera::update()
{
	// Temporary storing this number
	position[2] = cosl(pitch) * distance;
	
	position[0] = subject[0] + cosl(yaw) * position[2];
	position[1] = subject[1] + sinl(yaw) * position[2];
	position[2] = subject[2] + sinl(pitch) * distance;
	
	gluLookAt(position[0], position[1], position[2],
				subject[0], subject[1], subject[2],
				0.0, 0.0, 0.1);
}
