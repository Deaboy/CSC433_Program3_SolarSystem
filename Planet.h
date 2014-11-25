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
	bool			IsSphere;	/*!< yes planets are spheres */

public:
	/*!
	 * @brief constructor, initiallizes a planet
	 */
	Planet();

	/*!
	 * @brief destructor, dealth stars a planet
	 */
	virtual ~Planet();
	

	/*!
	 * @brief sets the planet's name
	 */
	Planet& setName(string name);

	/*!
	 * @brief sets the planet's color
	 */
	Planet& setColor(unsigned char r, unsigned char g, unsigned char b);

	/*!
	 * @brief sets the planet's radius
	 */
	Planet& setRadius(ld radius);

	/*!
	 * @brief sets the planet's texture
	 */
	Planet& setTexture(string filename, int width, int height);

	/*!
	 * @brief sets the planet's rotation_axis
	 */
	Planet& setRotationAxis(ld rotation_axis);

	/*!
	 * @brief sets the planet's initial possition before roatation
	 */
	Planet& setRotationInitial(ld rotation_init);

	/*!
	 * @brief sets the planet's rotation speed
	 */
	Planet& setRotationPeriod(ld rotation_period);

	/*!
	 * @brief sets the planet's "tilt"
	 */
	Planet& setRightAscension(ld right_ascention);

	/*!
	 * @brief what the planet orbits
	 */
	Planet& setOrbitTarget(Planet* orbit_target);

	/*!
	 * @brief sets the planet's initial position in space
	 */
	Planet& setOrbitInitial(ld orbit_init);

	/*!
	 * @brief sets the planet's radious from orbit target
	 */
	Planet& setOrbitRadius(ld orbit_radius);

	/*!
	 * @brief sets the planet's orbit speed
	 */
	Planet& setOrbitPeriod(ld orbit_period);

	/*!
	 * @brief determines, texture, smoothness and frame
	 */
	Planet& setDrawMode(int mode);

	/*!
	 * @brief toggles between tea party and boring ol' beach ball mode
	 */
	Planet& toggleTeaParty();

	/*!
	 * @brief cycle between set draw mode togglables
	 */
	void cycleDrawMode();
	

	/*!
	 * @brief returns the planet's name
	 */
	string	getName();

	/*!
	 * @brief returns the planet's radius
	 */
	ld		getRadius();

	/*!
	 * @brief returns the planet's distance from orbit target
	 */
	ld		getOrbitRadius();
	

	/*!
	 * @brief returns the planet's location
	 */
	virtual void getPosition(long long time, ld& x,
					 ld& y, ld& z);

	/*!
	 * @brief changes the planet's location
	 */
	virtual void update(long long time);

	/*!
	 * @brief draws the planet
	 */
	virtual void draw();

	
};

#endif
