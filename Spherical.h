/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	11/9/2014
 *
 * @file File containing the declaration for the Sphearical Class.
 *
 * @brief this subclass is responisble for creating a "planet"
******************************************************************************/
#ifndef _SPHEARICAL_H_
#define _SPHEARICAL_H_

/******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
******************************************************************************/
class Spherical;

#include "Drawable.h"

/***************************************************************************//**
 * @brief The sphearical class holds the information needed to create a planet
 *	like object
*******************************************************************************/
class Spherical
{
public:
	Spherical();
	Spherical( double radious, double distance, 
		double orbit_s, double rotation_s);
	~Spherical();

private:
	double radious;
	double distance;
	double orbit_s;
	double rotation_s;
	bool filled;

};

#endif
