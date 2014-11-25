/***************************************************************************//**
 * @author Daniel Andrus
 *
 * @Date	11/13/2014
 * @file File containing the declaration for the Pressable class.
 *
 * @brief Contains the declaration for the Pressable class.
*******************************************************************************/
#ifndef _PRESSABLE_H_
#define _PRESSABLE_H_

/***************************************************************************//**
 * @brief The Pressable Class handle keyboard input
*******************************************************************************/
class Pressable
{
public:
	/*!
	 * @brief Resize callback. Executes whenever the keyboard is pressed
	 */
	virtual void keyDown(unsigned char key, int x, int y) = 0;

	/*!
	 * @brief Resize callback. Executes whenever the keyboard is released
	 */
	virtual void keyUp(unsigned char key, int x, int y) = 0;

	/*!
	 * @brief Resize callback. Executes whenever the special keys are pressed
	 *			such as the arrow keys, or enter
	 */
	virtual void keySpecialDown(unsigned char key, int x, int y) = 0;

	/*!
	 * @brief Resize callback. Executes whenever the special keys are released
	 *			such as the arrow keys, or enter
	 */
	virtual void keySpecialUp(unsigned char key, int x, int y) = 0;
};

#endif