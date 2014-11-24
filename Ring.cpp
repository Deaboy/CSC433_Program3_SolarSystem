#include "Ring.h"


void Ring::getPosition(long long time, ld& x, ld& y, ld& z)
{
	if (orbit_target == NULL)
	{
		x = y = z = 0.0;
	}
	else
	{
		orbit_target->getPosition(time, x, y, z);
	}
}

void Ring::draw()
{
	glPushMatrix();
	
	// Set the color
    glColor3ub( color[0], color[1], color[2] );
	//double radius = 8;	// TESTING
	
	// Draw a ring at position[] at angle rotation_angle and rotation_axis
	// Texture needs to be determined by something external:
	// wireframe, solid, shaded, and textured
	GLUquadricObj *disk;
	
	// Move into orbit position
    glTranslated( position[0], position[1], position[2] );
	
	// Adjust for right ascention
	glRotated( right_ascension, 0.0, 0.0, 1.0);
	
	// Show ring's axis
	glRotated( rotation_axis, 0.0, 1.0, 0.0);
	
	// Rotate according to ring's rotation
	glRotated( rotation_angle, 0.0, 0.0, 1.0 );
	
	// Create and draw sphere
    disk = gluNewQuadric();

	//Gives the object surface normals for light
	gluQuadricNormals( disk, GLU_SMOOTH );
	gluQuadricDrawStyle( disk, GLU_FILL );
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lightColor );
	glMaterialfv(GL_FRONT, GL_SPECULAR, lightColor );

    gluDisk( disk, orbit_radius, radius, 128, 128 );

	// Draw back side
	glRotated( 180, 1.0, 0.0, 0.0 );
	gluDisk( disk, orbit_radius, radius, 128, 128 );

    gluDeleteQuadric( disk );
	
    glPopMatrix();
}
