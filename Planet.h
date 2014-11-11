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
#include "Drawable.h"

using namespace std;

class Planet : public Drawable
{
private:
	// Constant stuff
	string			name;
	unsigned char	color[3];
	long double		radius;
	
	// Rotation info
	long double		rotation_axis;
	long double		rotation_init;
	long double		rotation_velocity;
	
	// Orbit info
	Planet*			orbit_target;
	long double		orbit_init;
	long double		orbit_radius;
	long double		orbit_velocity;
	
	// Memorization
	long long		time;
	long double		position[3];
	long double		orbit_angle;
	long double		rotation_angle;
	
public:
	Planet(string name, unsigned char red, unsigned char green,
			unsigned char blue, long double radius,
			long double rotation_axis, long double rotation_init,
			long double rotation_velocity, Planet* orbit_target,
			long double orbit_init, long double orbit_radius,
			long double orbit_velocity);
	void getPosition(long long time, long double& x,
					 long double& y, long double& z);
	void update(long long time);
	void draw();
};

#endif
