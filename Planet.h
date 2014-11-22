//
//  Planet.h
//  CSC433_Program3_SolarSystem
//
//  Created by Daniel Andrus on 2014-11-10.
//  Copyright (c) 2014 Daniel Andrus. All rights reserved.
//

#ifndef _PLANET_H_
#define _PLANET_H_

#include <cmath>
#include <string>
#include "Constants.h"
#include "Drawable.h"

using namespace std;

class Planet : public Drawable
{
protected:
	// Constant stuff
	string			name;
	unsigned char	color[3];
	GLfloat			lightColor[4];
	long double		radius;
	
	// Rotation info
	long double		rotation_axis;
	long double		rotation_init;
	long double		rotation_period;
	long double		right_ascension;
	
	// Orbit info
	Planet*			orbit_target;
	long double		orbit_init;
	long double		orbit_radius;
	long double		orbit_period;
	
	// Memorization
	long long		time;
	long double		position[3];
	long double		orbit_angle;
	long double		rotation_angle;
	
public:
	Planet();
	
	Planet& setName(string name);
	Planet& setColor(unsigned char r, unsigned char g, unsigned char b);
	Planet& setRadius(long double radius);
	Planet& setRotationAxis(long double rotation_axis);
	Planet& setRotationInitial(long double rotation_init);
	Planet& setRotationPeriod(long double rotation_period);
	Planet& setRightAscension(long double right_ascention);
	Planet& setOrbitTarget(Planet* orbit_target);
	Planet& setOrbitInitial(long double orbit_init);
	Planet& setOrbitRadius(long double orbit_radius);
	Planet& setOrbitPeriod(long double orbit_period);
	
	void getPosition(long long time, long double& x,
					 long double& y, long double& z);
	void update(long long time);
	virtual void draw();
};

#endif
