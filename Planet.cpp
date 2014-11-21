//
//  Planet.cpp
//  CSC433_Program3_SolarSystem
//
//  Created by Daniel Andrus on 2014-11-10.
//  Copyright (c) 2014 Daniel Andrus. All rights reserved.
//

#include "Planet.h"

Planet::Planet()
{
	name				= "";
	color[0]			= 0;
	color[1]			= 0;
	color[2]			= 0;
	radius				= 0;
	rotation_axis		= 0;
	rotation_init		= 0;
	rotation_period		= 0;
	right_ascension		= 0;
	orbit_target		= NULL;
	orbit_init			= 0;
	orbit_radius		= 0;
	orbit_period		= 0;
	time				= -999999;
	position[0]			= 0;
	position[1]			= 0;
	position[2]			= 0;
}
	
Planet& Planet::setName(string name)
{
	this->name = name;
	return *this;
}

Planet& Planet::setColor(unsigned char r, unsigned char g, unsigned char b)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
	return *this;
}

Planet& Planet::setRadius(long double radius)
{
	this->radius = radius * PLANET_SCALE;
	return *this;
}

Planet& Planet::setRotationAxis(long double rotation_axis)
{
	this->rotation_axis = rotation_axis;
	return *this;
}

Planet& Planet::setRotationInitial(long double rotation_init)
{
	this->rotation_init = rotation_init;
	return *this;
}

Planet& Planet::setRotationPeriod(long double rotation_period)
{
	this->rotation_period = rotation_period;
	return *this;
}

Planet& Planet::setRightAscension(long double right_ascension)
{
	this->right_ascension = right_ascension;
	return *this;
}

Planet& Planet::setOrbitTarget(Planet* orbit_target)
{
	this->orbit_target = orbit_target;
	return *this;
}

Planet& Planet::setOrbitInitial(long double orbit_init)
{
	this->orbit_init = orbit_init;
	return *this;
}

Planet& Planet::setOrbitRadius(long double orbit_radius)
{
	this->orbit_radius = orbit_radius * ORBIT_SCALE;
	return *this;
}

Planet& Planet::setOrbitPeriod(long double orbit_period)
{
	this->orbit_period = orbit_period;
	return *this;
}

void Planet::getPosition(long long time, long double& x,
						 long double& y, long double& z)
{
	if (this->time != time)
	{
		if (orbit_target != NULL)
		{
			orbit_target->getPosition(time,
					position[0], position[1], position[2]);
			if (orbit_period != 0)
			{
				orbit_angle = 360 * (time / orbit_period) + orbit_init;
			
			}
			else
			{
				orbit_angle = orbit_init;
			}
			position[0] = position[0] + cosl(DEGTORAD(orbit_angle)) * orbit_radius;
			position[1] = position[1] + sinl(DEGTORAD(orbit_angle)) * orbit_radius;
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
		if (rotation_period != 0)
		{
			rotation_angle =  360 * (time / rotation_period) + rotation_init;
		}
		else
		{
			rotation_angle = rotation_init;
		}
	}
}

void Planet::draw()
{
    glPushMatrix();
	
	// Set the color
    glColor3ub( color[0], color[1], color[2] );
	//double radius = 8;	// TESTING
	
	// Draw orbit first
	// Pre-calculate the slice size (in radians)
	long double orbit_slicesize = (2 * M_PI) / (orbit_radius / 10);
	if (orbit_slicesize > DEGTORAD(1)) orbit_slicesize = DEGTORAD(1);
	
	// Get our orbitting target's position
	long double target_x, target_y, target_z;
	if (orbit_target != NULL)
		orbit_target->getPosition(time, target_x, target_y, target_z);
	else
		target_x = target_y = target_z = 0.0;
	
	// Build the orbit
	glBegin(GL_LINE_LOOP);
		for (long double theta = 0; theta < 2*M_PI; theta += orbit_slicesize)
			glVertex3d(target_x + cosl(theta) * orbit_radius,
						target_y + sinl(theta) * orbit_radius,
						target_z);
	glEnd();
	
	// Draw a planet at position[] at angle rotation_angle and rotation_axis
	// Texture needs to be determined by something external:
	// wireframe, solid, shaded, and textured
	GLUquadricObj *sphere;
	
	// Move into orbit position
    glTranslated( position[0], position[1], position[2] );
	
	// Adjust for right ascention
	glRotated( right_ascension, 0.0, 0.0, 1.0);
	
	// Show planet's axis
	glRotated( rotation_axis, 0.0, 1.0, 0.0);
	
	// Rotate according to planet's rotation
	glRotated( rotation_angle, 0.0, 0.0, 1.0 );
	
	// Create and draw sphere
    sphere = gluNewQuadric();

	//Gives the object surface normals for light
	gluQuadricNormals( sphere, GLU_SMOOTH );
	gluQuadricDrawStyle( sphere, GLU_LINE );

    gluSphere( sphere, radius, (int) (radius), (int) (radius) );
    gluDeleteQuadric( sphere );
	
    glPopMatrix();
}
