/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @file File containing the implementation for the Camera Class
 *
 * @Date 2014 - 11 - 19
 *
 * @brief Contains the implementation for the Camera class.
*******************************************************************************/


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
	min_distance = 0;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: returns coordinant location of camera
 *
 * @param[in,out]	ld x - x coordinant of camera
 * @param[in,out]	ld y - y coordinant of camera
 * @param[in,out]	ld z - z ciordinant of camera
*******************************************************************************/
void Camera::getPosition(ld& x, ld& y, ld& z)
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
 * @param[in,out]	ld x - x coordinant of Planet
 * @param[in,out]	ld y - y coordinant of Planet
 * @param[in,out]	ld z - z ciordinant of Planet
*******************************************************************************/
void Camera::getSubject(ld& x, ld& y, ld& z)
{
	x = target_subject[0];
	y = target_subject[1];
	z = target_subject[2];
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: returns vertical angle
*******************************************************************************/
ld Camera::getPitch()
{
	return RADTODEG(target_pitch);
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: return angle along XY-plane
*******************************************************************************/
ld Camera::getYaw()
{
	return RADTODEG(target_yaw);
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: return current distance from subject
*******************************************************************************/
ld Camera::getDistance()
{
	return target_distance;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: return minimum allowed distance from subject
*******************************************************************************/
ld Camera::getMinimumDistance()
{
	return min_distance;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: sets the coordinate that is the subject of the camera
 *
 * @param[in]	ld x - x coordinate of subject
 * @param[in]	ld y - y coordinate of subject
 * @param[in]	ld z - z coordinate of subject
*******************************************************************************/
Camera& Camera::setSubject(ld x, ld y, ld z)
{
	target_subject[0] = x;
	target_subject[1] = y;
	target_subject[2] = z;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: sets the vertical angle from the subject
 *
 * @param[in]	ld pitch - the vertical height
*******************************************************************************/
Camera& Camera::setPitch(ld pitch)
{
	if (pitch > 89) pitch = 89;
	if (pitch < -89) pitch = -89;
	target_pitch = DEGTORAD(pitch);
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: sets the horizontal angle
 *
 * @param[in]	ld yaw - horizontal angle in relation to the subject
*******************************************************************************/
Camera& Camera::setYaw(ld yaw)
{
	target_yaw = DEGTORAD(yaw);
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: sets the distance from the subject
 *
 * @param[in]	ld distance - radius from planet
*******************************************************************************/
Camera& Camera::setDistance(ld distance)
{
	target_distance = (distance > min_distance ? distance : min_distance);
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: sets the minimum distance from the subject
 *
 * @param[in]	ld min_distance - minimum distance from subject
*******************************************************************************/
Camera& Camera::setMinimumDistance(ld min_distance)
{
	min_distance = min_distance > 0 ? min_distance : 0;
	this->min_distance		= min_distance;
	this->target_distance	= target_distance < min_distance ?
									min_distance : target_distance;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: slows the rotation to a stop
 *
 * @param[in]	ld ease - 1 means snap, 0 means no movement
*******************************************************************************/
Camera& Camera::setRotationEasing(ld ease)
{
	rot_ease = (ease > 1 ? 1 : ease < 0 ? 0 : ease);
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: slows the zoom to a stop
 *
 * @param[in]	ld ease - 1 means snap, 0 means no movement
******************************************************************************/
Camera& Camera::setZoomEasing(ld ease)
{
	this->zoom_ease = (ease > 1 ? 1 : ease < 0 ? 0 : ease);
	return *this;
}

/**************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: slows the movement to a stop
 *
 * @param[in]	ld ease - 1 means snap, 0 means no movement
******************************************************************************/
Camera& Camera::setMovementEasing(ld ease)
{
	this->move_ease = (ease > 1 ? 1 : ease < 0 ? 0 : ease);
	return *this;
}

/***************************************************************************//*
 * @author Daniel Andrus
 * 
 * @par Description:updates the camera when moved or while moving with a planet
******************************************************************************/
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

/***************************************************************************//*
 * @author Daniel Andrus
 * 
 * @par Description: steps camera as it is moved
******************************************************************************/
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
