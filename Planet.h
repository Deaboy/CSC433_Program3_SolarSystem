/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	11/11/2014
 *
 * @file File containing the declaration for the Planet class.
 *
 * @brief This Class creates a given planet, texture maps it, and draws it
******************************************************************************/

#ifndef _PLANET_H_
#define _PLANET_H_

/******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
******************************************************************************/
#include <cmath>
#include <string>
#include "Constants.h"
#include "Drawable.h"
#include "GlutManager.h"

using namespace std;
typedef long double ld;

/**************************************************************************//**
 * @brief The Planet Class handles a sole planet
******************************************************************************/
class Planet : public Drawable
{
protected:
	// Constant stuff
	string			name; /*!< name of the planet*/
	unsigned char	color[3];	/*!< array of colors for planet */
	GLfloat			lightColor[4]; /*!< reflected color of planet */
	ld				radius;	/*!< radius of planet */
	GLuint			texture_name; /*!< name of texture file for .bmp */
	
	// Rotation info
	ld				rotation_axis; /*!< axis of rotation */
	ld				rotation_init; /*!< initial position before rotation */
	ld				rotation_period; /*!< "day of a planet" */
	ld				right_ascension; /*!< tilt of axis */
	
	// Orbit info
	Planet*			orbit_target; /*!< what the planet is orbiting */
	ld				orbit_init;	  /*!< initial orbit position */
	ld				orbit_radius; /*!< radius of orbit */
	ld				orbit_period; /*!< "year of planet" */
	
	// Memorization
	long long		time;		  /*!< time of solar system */
	ld				position[3];  /*!< coordinates of planet */
	ld				orbit_angle;  /*!< position from starting orbit */
	ld				rotation_angle; /*!< position from 
												starting rotation position */
	GLUquadricObj	*sphere;	  /*!< sphere object used by glut to draw */
	int				draw_mode;	/*!< current draw mode, determines 
													texture, shading, model*/

public:
	Planet();
	virtual ~Planet();
	
	Planet& setName(string name);
	Planet& setColor(unsigned char r, unsigned char g, unsigned char b);
	Planet& setRadius(ld radius);
	Planet& setTexture(string filename, int width, int height);
	Planet& setRotationAxis(ld rotation_axis);
	Planet& setRotationInitial(ld rotation_init);
	Planet& setRotationPeriod(ld rotation_period);
	Planet& setRightAscension(ld right_ascention);
	Planet& setOrbitTarget(Planet* orbit_target);
	Planet& setOrbitInitial(ld orbit_init);
	Planet& setOrbitRadius(ld orbit_radius);
	Planet& setOrbitPeriod(ld orbit_period);
	Planet& setDrawMode(int mode);
	void cycleDrawMode();
	
	string	getName();
	ld		getRadius();
	ld		getOrbitRadius();
	
	virtual void getPosition(long long time, ld& x,
					 ld& y, ld& z);
	virtual void update(long long time);
	virtual void draw();
};

#endif
