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
#include "GlutManager.h"

using namespace std;
typedef long double ld;

class Planet : public Drawable
{
protected:
	// Constant stuff
	string			name;
	unsigned char	color[3];
	GLfloat			lightColor[4];
	ld				radius;
	unsigned char*	texture;
	int				texture_width;
	int				texture_height;
	
	// Rotation info
	ld				rotation_axis;
	ld				rotation_init;
	ld				rotation_period;
	ld				right_ascension;
	
	// Orbit info
	Planet*			orbit_target;
	ld				orbit_init;
	ld				orbit_radius;
	ld				orbit_period;
	
	// Memorization
	long long		time;
	ld				position[3];
	ld				orbit_angle;
	ld				rotation_angle;
	
	// toggles
	bool			textureOn;
	bool			wireOn;
	bool			definition;

public:
	Planet();
	~Planet();
	
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
	
	virtual void getPosition(long long time, ld& x,
					 ld& y, ld& z);
	virtual void update(long long time);
	virtual void draw();

	void setTextureOn( bool On_Off);
	void setWireON( bool On_Off );
	void setdefinition( );
};

#endif
