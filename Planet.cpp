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
	lightColor[0]		= 0;
	lightColor[1]		= 0;
	lightColor[2]		= 0;
	lightColor[3]		= 0;
	radius				= 0;
	texture				= NULL;
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

	textureOn			= true;
	wireOn				= false;
}

Planet::~Planet()
{
	if (this->texture != NULL)
		delete[] this->texture;
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
	lightColor[0] = r/255.0f;
	lightColor[1] = g/255.0f;
	lightColor[2] = b/255.0f;
	lightColor[3] = 1;
	return *this;
}

Planet& Planet::setRadius(ld radius)
{
	this->radius = radius * PLANET_SCALE;
	return *this;
}

Planet& Planet::setTexture(string filename, int width, int height)
{
	unsigned char* texture;
	if (GlutManager::LoadBmpFile(filename.c_str(), height, width, texture))
	{
		if (this->texture != NULL)
			delete[] this->texture;
		this->texture = texture;
		this->texture_width = width;
		this->texture_height = height;
	}
	return *this;
}

Planet& Planet::setRotationAxis(ld rotation_axis)
{
	this->rotation_axis = rotation_axis;
	return *this;
}

Planet& Planet::setRotationInitial(ld rotation_init)
{
	this->rotation_init = rotation_init;
	return *this;
}

Planet& Planet::setRotationPeriod(ld rotation_period)
{
	this->rotation_period = rotation_period;
	return *this;
}

Planet& Planet::setRightAscension(ld right_ascension)
{
	this->right_ascension = right_ascension;
	return *this;
}

Planet& Planet::setOrbitTarget(Planet* orbit_target)
{
	this->orbit_target = orbit_target;
	return *this;
}

Planet& Planet::setOrbitInitial(ld orbit_init)
{
	this->orbit_init = orbit_init;
	return *this;
}

Planet& Planet::setOrbitRadius(ld orbit_radius)
{
	this->orbit_radius = orbit_radius * ORBIT_SCALE;
	return *this;
}

Planet& Planet::setOrbitPeriod(ld orbit_period)
{
	this->orbit_period = orbit_period;
	return *this;
}

void Planet::getPosition(long long time, ld& x,
						 ld& y, ld& z)
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
	ld orbit_slicesize = (2 * M_PI) / (orbit_radius / 50);
	if (orbit_slicesize > DEGTORAD(1)) orbit_slicesize = DEGTORAD(1);
	
	// Get our orbitting target's position
	ld target_x, target_y, target_z;
	if (orbit_target != NULL)
		orbit_target->getPosition(time, target_x, target_y, target_z);
	else
		target_x = target_y = target_z = 0.0;
	
	// Draw the orbit without lighting
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_LOOP);
		for (ld theta = 0; theta < 2*M_PI; theta += orbit_slicesize)
			glVertex3d(target_x + cosl(theta) * orbit_radius,
						target_y + sinl(theta) * orbit_radius,
						target_z);
	glEnd();
	glEnable(GL_LIGHTING);
	
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
	
	if (texture != NULL)
	{
		// Texture mapping
		glTexImage2D( GL_TEXTURE_2D, 0, 3, texture_width, texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

		// building mipmaps is not essential, but can improve mapping
		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, texture_width, texture_height, GL_RGB, GL_UNSIGNED_BYTE, texture );
	}
	else
	{
		
	}
	
	// Create and draw sphere
    sphere = gluNewQuadric();

	//Gives the object surface normals for light
	if( wireOn ){
		gluQuadricDrawStyle( sphere, GLU_LINE ); }
	else{ gluQuadricDrawStyle( sphere, GLU_FILL ); }


	gluQuadricNormals( sphere, GLU_SMOOTH ); 

	if( textureOn )
	{
		gluQuadricTexture( sphere, GL_TRUE );
	}
	else { gluQuadricTexture( sphere, GL_FALSE ); };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lightColor );
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightColor );

    gluSphere( sphere, radius, 128, 128 );
    gluDeleteQuadric( sphere );
	
    glPopMatrix();
}

void Planet::setTextureOn( bool On_Off )
{
	textureOn = On_Off;
}

void Planet::setWireON( bool On_Off )
{
	wireOn = On_Off;
}

