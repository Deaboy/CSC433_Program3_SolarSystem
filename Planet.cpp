//
//  Planet.cpp
//  CSC433_Program3_SolarSystem
//
//  Created by Daniel Andrus on 2014-11-10.
//  Copyright (c) 2014 Daniel Andrus. All rights reserved.
//

#include "Planet.h"

Planet::Planet(string name, unsigned char red, unsigned char green,
			   unsigned char blue, long double radius,
			   long double rotation_axis, long double rotation_init,
			   long double rotation_velocity, Planet* orbit_target,
			   long double orbit_init, long double orbit_radius,
			   long double orbit_velocity) :
		name(name), radius(radius), rotation_axis(rotation_axis),
		rotation_init(rotation_init), rotation_velocity(rotation_velocity),
		orbit_target(orbit_target), orbit_init(orbit_init),
		orbit_radius(orbit_radius), orbit_velocity(orbit_velocity),
		time(-999999)
{
	this->color[0] = red;
	this->color[1] = green;
	this->color[2] = blue;
	
	position[2] = 0;
}

void Planet::getPosition(long long time, long double& x,
						 long double& y, long double& z)
{
	if (this->time != time)
	{
		if (orbit_target == NULL)
		{
			position[0] = 0;
			position[1] = 1;
			position[2] = 2;
		}
		else
		{
			orbit_target->getPosition(time, position[0], position[1], position[2]);
			orbit_angle = orbit_velocity * time + orbit_init;
			position[0] = position[0] + cosl(orbit_angle) * orbit_radius;
			position[1] = position[1] + sinl(orbit_angle) * orbit_radius;
		}
		this->time = time;
	}

	x = position[0];
	y = position[1];
	z = position[2];
	return;
}

void Planet::update(long long time)
{
	if (this->time != time)
	{
		getPosition(time, position[0], position[1], position[2]);
		rotation_angle = rotation_init + rotation_velocity * time;
	}
}

void Planet::draw()
{
	// Draw a planet at position[] at angle rotation_angle and rotation_axis
	// Texture needs to be determined by something external:
	// wireframe, solid, shaded, and textured
}
