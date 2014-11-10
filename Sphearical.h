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
class Spearical;

#include "Drawable.h"

using namespace std;



/***************************************************************************//**
 * @brief The sphearical class holds the information needed to create a planet
 *	like object
*******************************************************************************/
class Spearical
{
public:
	Spearical();
	Spearical( double radious, double distance, 
		double orbit_s, double rotation_s);
	~Spearical();

private:
	double radious;
	double distance;
	double orbit_s;
	double rotation_s;
	bool filled;

};

#endif

Spearical::Spearical()
{
	radious = 0;
	distance = 0;
	orbit_s = 0;
	rotation_s = 0;
	filled = false;
}

Spearical::Spearical( double radious, double distance, 
		double orbit_s, double rotation_s) : 
	radious(radious), distance(distance), orbit_s(orbit_s), 
		rotation_s(rotation_s)
{
	filled = false;
}

Spearical::~Spearical()
{
}
