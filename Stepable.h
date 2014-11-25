/**************************************************************************//**
 * @author Daniel Andrus
 *
 * @Date	11/13/2014
 * @file File containing the declaration for the stepable class.
 *
 * @brief stepable class handles movement
******************************************************************************/

#ifndef _STEPABLE_H_
#define _STEPABLE_H_

/***************************************************************************//**
 * @brief The Stepable Class defines functions for moveing (stepping) objects
 *		across the screen
 *
 * @details adds to Planets draw function
*******************************************************************************/
class Stepable
{
public:
	/*!
	 * @brief Handles movement
	 */
	virtual void step() = 0;
};

#endif
