/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @file File containing the header for the clickable Class
 *
 * @Date 2014 - 11 - 19
 *
 * @brief Contains the declaration for the clickable class.
*******************************************************************************/
#ifndef _CLICKABLE_H_
#define _CLICKABLE_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
/*******************************************************************************
 *                              CLASS INTERFACE
 ******************************************************************************/
/*!
 * @brief Interface for Clickable classes. Declares click-related functions for
 * use as callbacks.
 *
 * @details Declares virtual functions for mouse event handling.
 */
 class Clickable
{
public:
	virtual void onMouseDown(int button) = 0;
	virtual void onMouseUp(int button) = 0;
	virtual void onMouseEnter() = 0;
	virtual void onMouseLeave() = 0;
	virtual void onMouseScrollUp() = 0;
	virtual void onMouseScrollDown() = 0;
	virtual void onMouseMove(int x, int y, int lx, int ly) = 0;
	virtual bool containsPoint(double x, double y) const = 0;
};

#endif
