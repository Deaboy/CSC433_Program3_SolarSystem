/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @file File containing the implementation for the Planet Class
 *
 * @Date 2014 - 11 - 19
 *
 * @brief Contains the implementation for the Planet class.
*******************************************************************************/

#include "Planet.h"

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: constructor - sets default values for planet
*******************************************************************************/
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
	texture_name		= 0;
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
	IsSphere			= true;

	// Create and draw sphere
    sphere = gluNewQuadric();
	setDrawMode(0);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: uses death star on planet
*******************************************************************************/
Planet::~Planet()
{
    gluDeleteQuadric( sphere );
	if (texture_name != 0) glDeleteTextures(1, &texture_name);
}
	
/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: names the planet
 *
 * @param[in]	string name - name of planet
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setName(string name)
{
	this->name = name;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: sets color of planet
 *
 * @param[in]	unsigned char r - red bit
 * @param[in]	unsigned char g - green bit
 * @param[in]	unsigned char b - blue bit
 *
 * @return this - the current planet
*******************************************************************************/
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

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: set size of planet
 *
 * @param[in]	ld radius - size of planet
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setRadius(ld radius)
{
	this->radius = radius * PLANET_SCALE;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: set texture file
 *
 * @param[in]	string filename - name of file
 * @param[in]	int width		- columns
 * @param[in]	int height		- rows
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setTexture(string filename, int width, int height)
{
	unsigned char* texture;

	if (GlutManager::LoadBmpFile(filename.c_str(), height, width, texture))
	{
		// Build texture
		//glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height,
		//			0, GL_RGB, GL_UNSIGNED_BYTE, texture);

		// Delete previously generated texture
		if (texture_name != 0)
			glDeleteTextures(1, &texture_name);

		// Generate new texture name
		glGenTextures(1, &texture_name);

		// Bind texture to name, save to class
		glBindTexture(GL_TEXTURE_2D, texture_name);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height,
					0, GL_RGB, GL_UNSIGNED_BYTE, texture);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
                       GL_RGB, GL_UNSIGNED_BYTE, texture);
		
		// Delete array of pixels
		delete[] texture;
	}

	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: set the axis of rotation
 *
 * @param[in]	ld rotation_axis - sets the axis of rotation
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setRotationAxis(ld rotation_axis)
{
	this->rotation_axis = rotation_axis;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: set the rotation start position
 *
 * @param[in]	ld rotation_init - initial rotation position
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setRotationInitial(ld rotation_init)
{
	this->rotation_init = rotation_init;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: set speed of the rotation 
 *
 * @param[in]	ld rotation_period - speed of the rotation
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setRotationPeriod(ld rotation_period)
{
	this->rotation_period = rotation_period;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: sets the "tilt" of the planet
 *
 * @param[in]	ld right_ascension - "tilt"
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setRightAscension(ld right_ascension)
{
	this->right_ascension = right_ascension;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: telss planet what object to orbit
 *
 * @param[in]	Planet* orbit_target - object being orbited
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setOrbitTarget(Planet* orbit_target)
{
	this->orbit_target = orbit_target;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: set location of the orbit start position
 *
 * @param[in]	ld orbit_itit - initial position in orbit
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setOrbitInitial(ld orbit_init)
{
	this->orbit_init = orbit_init;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: sets orbital distance
 *
 * @param[in]	ld orbit_radius - distance from orbital target
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setOrbitRadius(ld orbit_radius)
{
	this->orbit_radius = orbit_radius * ORBIT_SCALE;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: set the orbital speed
 *
 * @param[in]	ld orbit_period - orbit speed
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setOrbitPeriod(ld orbit_period)
{
	this->orbit_period = orbit_period;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: set the draw mode style
 *
 * @param[in]	int mode - list of drawing modes
 *
 * @return this - the current planet
*******************************************************************************/
Planet& Planet::setDrawMode(int mode)
{
	draw_mode = mode % 4;
	switch (draw_mode)
	{
	case 0:	// Textured mode
		gluQuadricDrawStyle( sphere, GLU_FILL );
		gluQuadricTexture( sphere, GL_TRUE );
		gluQuadricNormals( sphere, GLU_SMOOTH ); 
		break;

	case 1:	// Smooth shading
		gluQuadricDrawStyle( sphere, GLU_FILL );
		gluQuadricTexture( sphere, GL_FALSE );
		gluQuadricNormals( sphere, GLU_SMOOTH );
		break;

	case 2:	// Flat shading
		gluQuadricDrawStyle( sphere, GLU_FILL );
		gluQuadricTexture( sphere, GL_FALSE );
		gluQuadricNormals( sphere, GLU_FLAT );
		break;

	case 3:	// Wireframe
		gluQuadricDrawStyle( sphere, GLU_LINE );
		gluQuadricTexture( sphere, GL_FALSE );
		gluQuadricNormals( sphere, GLU_FLAT );
		break;


	default:
		break;
	}

	return *this;
}

Planet& Planet::toggleTeaParty()
{
	IsSphere = !IsSphere;
	return *this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: changes drawing style
*******************************************************************************/
void Planet::cycleDrawMode()
{
	setDrawMode(draw_mode + 1);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: pointer to planet's name
 *
 * @return name - name of planet
*******************************************************************************/
string Planet::getName()
{
	return name;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: pointer to radius
 *
 * @return radius - size of planet
*******************************************************************************/
ld Planet::getRadius()
{
	return radius;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: pointer to orbit_radius
 *
 * @return orbit_radius - distance from orbital target
*******************************************************************************/
ld Planet::getOrbitRadius()
{
	return orbit_radius;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: gets the position of the planet
 *
 * @param[in]	long long time - time of solar system
 * @param[in,out]	x - The x coordinate of the planet
 * @param[in,out]	y - The y coordinate of the planet
 * @param[in,out]	z - the z coordinate of the planet
*******************************************************************************/
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

			// Calculate poition
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

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: updates planets location based on time
 *
 * @param[in]	long long time - time of the solar system
*******************************************************************************/
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

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Draws planet based on texture option and given info
*******************************************************************************/
void Planet::draw()
{
	static const float WHITE[4] = { 1, 1, 1, 1 };

    glPushMatrix();
	
	// Set the color
    glColor3ubv( color );
	//double radius = 8;	// TESTING
	
	// Draw orbit first
	// Pre-calculate the slice size (in radians)
	ld orbit_slicesize = (2 * M_PI) / 360;//(orbit_radius / 50);
	if (orbit_slicesize > DEGTORAD(1)) orbit_slicesize = DEGTORAD(1);
	
	// Get our orbitting target's position
	ld target_x, target_y, target_z;
	if (orbit_target != NULL)
		orbit_target->getPosition(time, target_x, target_y, target_z);
	else
		target_x = target_y = target_z = 0.0;
	
	// Draw the orbit without lighting
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINE_STRIP);
		for (ld theta = 0, cur = DEGTORAD(orbit_angle);
			theta < 2*M_PI;
			theta += orbit_slicesize)
			glVertex3d(target_x + cosl(cur+theta) * orbit_radius,
						target_y + sinl(cur+theta) * orbit_radius,
						target_z);
		glVertex3d(target_x + cosl(DEGTORAD(orbit_angle))*orbit_radius,
					target_y + sinl(DEGTORAD(orbit_angle))*orbit_radius,
					target_z);
	glEnd();
	glEnable(GL_LIGHTING);
	
	// Move into orbit position
    glTranslated( position[0], position[1], position[2] );
	
	// Adjust for right ascention
	glRotated( right_ascension, 0.0, 0.0, 1.0);
	
	// Show planet's axis
	glRotated( rotation_axis, 0.0, 1.0, 0.0);
	
	// Rotate according to planet's rotation
	glRotated( rotation_angle, 0.0, 0.0, 1.0 );
	
	// Gives the object surface normals for light
	// Also apply texture if enabled
	switch (draw_mode)
	{
	case 3: // Wireframe
		glDisable(GL_LIGHTING);

	case 2:	// Flat shading
		glShadeModel( GL_FLAT );
		break;

	case 0:	// Textured mode
		glEnable( GL_TEXTURE_2D );
		if (texture_name != 0)
			glBindTexture(GL_TEXTURE_2D, texture_name);

	case 1: // Smooth shading
		glShadeModel( GL_SMOOTH );
		break;
	
	default:
		break;
	}
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, draw_mode ? lightColor : WHITE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, draw_mode ? lightColor : WHITE);

	if( IsSphere ) //all planets are spheres
	{
		gluSphere( sphere, radius, PLANET_DETAIL, PLANET_DETAIL );
	}
	else // what else could be a planet??
	{
		if( draw_mode == 3 )
		{
			glFrontFace( GL_CW );
			glutWireTeapot( radius );
			glFrontFace( GL_CCW );
		}
		else
		{
            glFrontFace( GL_CW );
            glutSolidTeapot( radius );
            glFrontFace( GL_CCW );
		}
	}
	
	// Display name label
	glLoadIdentity();
	glPopMatrix();
	glPushMatrix();
	
	// Translate to appear to right of planet
    glTranslated( position[0], position[1], position[2] );
    glRotated( GlutManager::getInstance()->getCamera().getYaw() + 90, 0, 0, 1);
    glTranslated( radius * 1.25, 0, 0 );
    
    // Draw text without lighting or texture effects
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3ubv(color);
	glRasterPos3d(0,0,0);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,
					(const unsigned char *) (IsSphere ? name.c_str() :
									("Tea Time! (" + name + ")").c_str()) );
	
	// Restore settings
    glPopMatrix();
	glEnable(GL_LIGHTING);
	glDisable( GL_TEXTURE_2D );
}



