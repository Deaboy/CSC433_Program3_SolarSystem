//
//  Camera.h
//  CSC433_Program3_SolarSystem
//
//  Created by Daniel Andrus on 2014-11-19.
//  Copyright (c) 2014 Daniel Andrus. All rights reserved.
//

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
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

/***************************************************************************//**
 * @brief The Camera Class handles camera, position, view and movement
 *
 * @details The camera "orbits" a planet, getting all its movement from
 *		the keyboard or the mouse.
*******************************************************************************/
class Camera : public Stepable
{
private:
	ld subject[3]; /*!< position of the planet currently looking at */
	ld target_subject[3]; /* !< the planet we are trying to look at */
	ld position[3];	/* !< position of the camera */
	ld target_pitch;	/* !< pitch the camera is working to achieve */
	ld target_yaw;		/* !< yaw the camera is working to achieve */
	ld target_distance; /* !< distance the camera is working towards*/
	ld pitch; /* !< current pitch */
	ld yaw;	/* !< current yaw */
	ld distance;	/* !< current distance */
	ld min_distance;	/* !< minimum distance from subject */
	ld rot_ease;	/* !< ease into target rotation */
	ld zoom_ease;  /* !< ease into target zoom */
	ld move_ease;  /* !< ease into target location */

public:
	/*!
	 * @brief constructor, creates camera
	 */
	Camera();

	/*!
	 * @brief returns the position
	 */
	void getPosition(ld& x, ld& y, ld& z);

	/*!
	 * @brief returns the subject
	 */
	void getSubject(ld& x, ld& y, ld& z);

	/*!
	 * @brief returns the Pitch
	 */
	ld getPitch();

	/*!
	 * @brief returns the Yaw
	 */
	ld getYaw();

	/*!
	 * @brief returns the distance
	 */
	ld getDistance();

	/*!
	 * @brief returns minimum distance from subject
	 */
	ld getMinimumDistance();

	/*!
	 * @brief sets the subject
	 */
	Camera& setSubject(ld x, ld y, ld z);

	/*!
	 * @brief sets the pitch angle from planet
	 */
	Camera& setPitch(ld pitch);

	/*!
	 * @brief sets the yaw angle from planet
	 */
	Camera& setYaw(ld yaw);

	/*!
	 * @brief sets the distance from planet
	 */
	Camera& setDistance(ld distance);
	
	/*!
	 * @brief sets the minimum distance from subject
	 */
	Camera& setMinimumDistance(ld min_distance);

	/*!
	 * @brief sets the rotation ease
	 */
	Camera& setRotationEasing(ld ease);

	/*!
	 * @brief sets the rotation ease for movement
	 */
	Camera& setZoomEasing(ld ease);

	/*!
	 * @brief sets the movement ease
	 */
	Camera& setMovementEasing(ld ease);

	/*!
	 * @brief moves the camera
	 */
	void step();

	/*!
	 * @brief updates camera during movement and planet changes
	 */
	void update();
};

#endif
