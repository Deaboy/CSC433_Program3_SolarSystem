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
	target_pitch = 0;
	target_yaw = 0;
	target_distance = 0;
	pitch = 0;
	yaw = 0;
	distance = 0;
	ease = 1;
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
	return RADTODEG(target_pitch);
}

long double Camera::getYaw()
{
	return RADTODEG(target_yaw);
}

long double Camera::getDistance()
{
	return target_distance;
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
	if (pitch > 89) pitch = 89;
	if (pitch < -89) pitch = -89;
	this->target_pitch = DEGTORAD(pitch);
	return *this;
}

Camera& Camera::setYaw(long double yaw)
{
	this->target_yaw = DEGTORAD(yaw);
	return *this;
}

Camera& Camera::setDistance(long double distance)
{
	this->target_distance = distance;
	return *this;
}

Camera& Camera::setEasing(long double ease)
{
	this->ease = (ease > 1 ? 1 : ease < 0 ? 0 : ease);
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

void Camera::step()
{
	if (ease == 1)
	{
		pitch = target_pitch;
		yaw = target_yaw;
		distance = target_distance;
	}
	else
	{
		if (fabs(pitch - target_pitch) > 0.00390625)
			pitch += (target_pitch - pitch) * ease;
		else
			pitch = target_pitch;

		if (fabs(yaw - target_yaw) > 0.00390625)
			yaw += (target_yaw - yaw) * ease;
		else
			yaw = target_yaw;

		if (fabs(distance - target_distance) > 0.125)
			distance += (target_distance - distance) * ease;
		else
			distance = target_distance;
	}
}
