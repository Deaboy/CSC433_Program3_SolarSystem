#include "Star.h"

void Star::draw()
{
	// Enable emission
	float emission[4] = { lightColor[0] / 2, lightColor[1] / 2, lightColor[2] / 2, lightColor[3] / 2 };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);

	Planet::draw();

	// Turn emission back off
	emission[0] = emission[1] = emission[2] = emission[3] = 0.0;
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
}