/**************************************************************************//**
 * @author Daniel Andrus
 *
 * @Date	11/13/2014
 * @file File containing the declaration for the Star class.
 *
 * @brief full extention of Planet, adding emission to the sun
******************************************************************************/
#ifndef _STAR_H_
#define _STAR_H_

#include "Planet.h"

/***************************************************************************//**
 * @brief The Ring Class handle the suns light emission (just glow)
 *
 * @details adds to Planets draw function
*******************************************************************************/
class Star : public Planet
{
public:
	/*!
	 * @brief adds emission and calls planets draw function
	 */
	virtual void draw();
};

#endif