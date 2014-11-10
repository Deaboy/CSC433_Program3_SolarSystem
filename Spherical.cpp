#include "Spherical.h"

Spherical::Spherical()
{
	radious = 0;
	distance = 0;
	orbit_s = 0;
	rotation_s = 0;
	filled = false;
}

Spherical::Spherical( double radious, double distance, 
		double orbit_s, double rotation_s) : 
	radious(radious), distance(distance), orbit_s(orbit_s), 
		rotation_s(rotation_s)
{
	filled = false;
}

Spherical::~Spherical()
{
}

