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

/***************************************************************************//**
 * @brief The Camera Class handles camera, position, view and movement
 *
 * @details The camera "orbits" a planet, getting all its movement from
 *		the keyboard or the mouse.
*******************************************************************************/
class Camera : public Stepable
{
private:
	long double subject[3]; /*!< position of the planet currently looking at */
	long double target_subject[3]; /* !< the planet we are trying to look at */
	long double position[3];	/* !< position of the camera */
	long double target_pitch;	/* !< pitch the camera is working to achieve */
	long double target_yaw;		/* !< yaw the camera is working to achieve */
	long double target_distance; /* !< distance the camera is working towards*/
	long double pitch; /* !< current pitch */
	long double yaw;	/* !< current yaw */
	long double distance;	/* !< current distance */
	long double rot_ease;	/* !< ease into target rotation */
	long double zoom_ease;  /* !< ease into target zoom */
	long double move_ease;  /* !< ease into target location */

public:
	/*!
	 * @brief constructor, creates camera
	 */
	Camera();

	/*!
	 * @brief returns the position
	 */
	void getPosition(long double& x, long double& y, long double& z);

	/*!
	 * @brief returns the subject
	 */
	void getSubject(long double& x, long double& y, long double& z);

	/*!
	 * @brief returns the Pitch
	 */
	long double getPitch();

	/*!
	 * @brief returns the Yaw
	 */
	long double getYaw();

	/*!
	 * @brief returns the distance
	 */
	long double getDistance();


	/*!
	 * @brief sets the subject
	 */
	Camera& setSubject(long double x, long double y, long double z);

	/*!
	 * @brief sets the pitch angle from planet
	 */
	Camera& setPitch(long double pitch);

	/*!
	 * @brief sets the yaw angle from planet
	 */
	Camera& setYaw(long double yaw);

	/*!
	 * @brief sets the distance from planet
	 */
	Camera& setDistance(long double distance);

	/*!
	 * @brief sets the rotation ease
	 */
	Camera& setRotationEasing(long double ease);

	/*!
	 * @brief sets the rotation ease for movement
	 */
	Camera& setZoomEasing(long double ease);

	/*!
	 * @brief sets the movement ease
	 */
	Camera& setMovementEasing(long double ease);

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
