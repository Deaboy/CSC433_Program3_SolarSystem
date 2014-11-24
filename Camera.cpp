//
//  Camera.cpp
//  CSC433_Program3_SolarSystem
//
//  Created by Daniel Andrus on 2014-11-19.
//  Copyright (c) 2014 Daniel Andrus. All rights reserved.
//

#include "Camera.h"

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Constuctor, Initializes the camera
 *
*******************************************************************************/
Camera::Camera()
{
	subject[0] = 0;
	subject[1] = 0;
	subject[2] = 0;
	target_subject[0] = 0;
	target_subject[1] = 1;
	target_subject[2] = 2;
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	target_pitch = 0;
	target_yaw = 0;
	target_distance = 0;
	pitch = 0;
	yaw = 0;
	distance = 0;
	rot_ease = 1;
	zoom_ease = 1;
	move_ease = 1;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: returns coordinant location of camera
 *
 * @param[in,out]	long double x - x coordinant of camera
 * @param[in,out]	long double y - y coordinant of camera
 * @param[in,out]	long double z - z ciordinant of camera
*******************************************************************************/
void Camera::getPosition(long double& x, long double& y, long double& z)
{
	x = position[0] + subject[0];
	y = position[1] + subject[1];
	z = position[2] + subject[2];
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: returns coordinant location of the planet the camera is
 *		looking at
 *
 * @param[in,out]	long double x - x coordinant of Planet
 * @param[in,out]	long double y - y coordinant of Planet
 * @param[in,out]	long double z - z ciordinant of Planet
*******************************************************************************/
void Camera::getSubject(long double& x, long double& y, long double& z)
{
	x = target_subject[0];
	y = target_subject[1];
	z = target_subject[2];
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: returns angle of height in comparison to a planet
*******************************************************************************/
long double Camera::getPitch()
{
	return RADTODEG(target_pitch);
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: return angle of horizontal in comparison to a planet
*******************************************************************************/
long double Camera::getYaw()
{
	return RADTODEG(target_yaw);
}


/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: return radius from orbiting planet
*******************************************************************************/
long double Camera::getDistance()
{
	return target_distance;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: determins the planet being orbited
 *
 * @param[in]	long double x - x coordinant of Planet
 * @param[in]	long double y - y coordinant of Planet
 * @param[in]	long double z - z ciordinant of Planet
*******************************************************************************/
Camera& Camera::setSubject(long double x, long double y, long double z)
{
	target_subject[0] = x;
	target_subject[1] = y;
	target_subject[2] = z;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: sets the hieght angle from the planet
 *
 * @param[in]	long double pitch - the angle of height
*******************************************************************************/
Camera& Camera::setPitch(long double pitch)
{
	if (pitch > 89) pitch = 89;
	if (pitch < -89) pitch = -89;
	this->target_pitch = DEGTORAD(pitch);
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: sets the horizontal angle
 *
 * @param[in]	long double yaw - horizontal angle in relation to the planet
*******************************************************************************/
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

Camera& Camera::setRotationEasing(long double ease)
{
	this->rot_ease = (ease > 1 ? 1 : ease < 0 ? 0 : ease);
	return *this;
}

Camera& Camera::setZoomEasing(long double ease)
{
	this->zoom_ease = (ease > 1 ? 1 : ease < 0 ? 0 : ease);
	return *this;
}

Camera& Camera::setMovementEasing(long double ease)
{
	this->move_ease = (ease > 1 ? 1 : ease < 0 ? 0 : ease);
	return *this;
}

void Camera::update()
{
	// Temporary storing this number
	position[2] = cosl(pitch) * distance;
	
	position[0] = cosl(yaw) * position[2];
	position[1] = sinl(yaw) * position[2];
	position[2] = sinl(pitch) * distance;
	
	gluLookAt(position[0], position[1], position[2],
				0.0, 0.0, 0.0,
				0.0, 0.0, 0.1);
	glTranslated(-subject[0], -subject[1], -subject[2]);
}

void Camera::step()
{
	if (rot_ease == 1)
	{
		pitch = target_pitch;
		yaw = target_yaw;
	}
	else
	{
		if (fabs(pitch - target_pitch) > rot_ease/256)
			pitch += (target_pitch - pitch) * rot_ease;
		else
			pitch = target_pitch;

		if (fabs(yaw - target_yaw) > rot_ease/256)
			yaw += (target_yaw - yaw) * rot_ease;
		else
			yaw = target_yaw;
	}

	if (zoom_ease == 1)
	{
		distance = target_distance;
	}
	else
	{
		if (fabs(distance - target_distance) > zoom_ease / 8)
			distance += (target_distance - distance) * zoom_ease;
		else
			distance = target_distance;
	}

	if (move_ease == 1)
	{
		subject[0] = target_subject[0];
		subject[1] = target_subject[1];
		subject[2] = target_subject[2];
	}
	else
	{
		for (int i = 0; i < 3; i++)
		if (fabs(subject[i] - target_subject[i]) > move_ease/256)
			subject[i] += (target_subject[i] - subject[i]) * move_ease;
		else
			subject[i] = target_subject[i];
	}
}
