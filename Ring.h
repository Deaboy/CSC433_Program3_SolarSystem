/**************************************************************************//**
 * @author Daniel Andrus
 *
 * @Date	11/13/2014
 * @file File containing the declaration for the Ring class.
 *
 * @brief extends from Planet, primarly overwrites draw function to make a ring
******************************************************************************/
#ifndef _RING_H_
#define _RING_H_

#include "Planet.h"

/***************************************************************************//**
 * @brief The Ring Class handle saturns rings
 *
 * @details based heavily off the planet class, with use of many of its major
 *		functions
*******************************************************************************/
class Ring : public Planet
{
public:
	/*!
	 * @brief gets the position of the rings, slightly different from parent
	 */
	virtual void getPosition(long long time, ld& x, ld& y, ld& z);

	/*!
	 * @brief Draws rings and defines custom texture map points
	 */
	virtual void draw();
};

#endif