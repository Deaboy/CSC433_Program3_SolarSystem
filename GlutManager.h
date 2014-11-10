/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the declaration for the Fractals class.
 *
 * @brief Contains the declaration for the Fractals class, the core class of the
 *      entire program.
*******************************************************************************/
#ifndef _GLUTMANAGER_H_ //makes sure class is not declared twice
#define _GLUTMANAGER_H_

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class GlutManager;

#include <iostream>
#include <string>
#include <GL/freeglut.h>
#include <vector>

using namespace std;

/***************************************************************************//**
 * @brief The Fractals class is in charge of window management, drawing
 *      all the parts of the screen, and running the other classes. It also
 *      handles the interaction between glut and the program and event
 *      management.
 *
 * @details This class essentially provides a base for the rest of the program.
 *      It handles drawing functions, forwards OpenGL events, generates a
 *      framerate, and standardizes various aspects of the program.
*******************************************************************************/
class GlutManager
{
private:
	static GlutManager* instance; /*!< reference to main instance */

	int window_width;			/*!< Width of gui window */
	int window_height;			/*!< Height of gui window */
	string window_name;			/*!< Name of the gui window */

	//Rotation Variables
	double spinInc;
	GLdouble theta[3];
	GLint axis;


public:

	/*!
	* @brief Constructor, allocates pointers for Initiator, generator and Fractal
	*		views as well as initializes private data.
	*/
	GlutManager();

	/*!
	* @brief Destructor, removes pointers.
	*/
	~GlutManager();

	/*!
	* @brief Function to get the current instance of the program.
	*/
	int run( int argc, char *argv[] );

	/*!
	* @brief Function to get the current instance of the program.
	*/
	static GlutManager* getInstance( );

	/*!
	* @brief Gets the width of the view port in the virtual space.
	*/
	double getViewWidth();

	/*!
	* @brief Gets the height of the view port in the virtual space.
	*/
	double getViewHeight();

	/*!
	 * @brief Drawing function. Calls superclass functions.
	 */
	void draw();

	/*!
	* @brief Drawing callback. Executes every glut display callaback. Also
	*      calls the draw function of all registerd Drawable objects.
	*/
	void display();

	/*!
	* @brief Resize callback. Executes whenever the window is resized.
	*/
	void reshape( int w, int h );

	/*!
	* @brief Key down callback. Executes whenever a typical key is pressed.
	*/
	void keyDown(unsigned char key, int x, int y);

	/*!
	* @brief Key up callback. Executes whenever a typical key is released.
	*/
	void keyUp(unsigned char key, int x, int y);

	/*!
	* @brief Special key down callback. Executes whenever a "special" key
	*      such as an arrow key is pressed.
	*/
	void keySpecialDown(int key, int x, int y);

	/*!
	* @brief Special key up callback. Executes whenever a "special" key
	*      such as an arrow key is released.
	*/
	void keySpecialUp(int key, int x, int y);

	/*!
	* @brief Mouse click callback. Executes whenever a mouse button is
	*      either clicked or released.
	*/
	void mouseclick( int button, int state, int x, int y );
	
	/*!
	 * @brief Mouse movement callback. Executes whenever a mouse is moved
	 *		inside the program window.
	 */
	void mousemove(int x, int y);

	/*!
	 * @brief Mouse drag callback. Executes whenever a mouse is moved inside
	 *		the program window while a button is pressed.
	 */
	void mousedrag(int x, int y);

	/*!
	 * @brief Glut Idle callback that spins the object around and axis
	 */
	void spinObject();

	/*!
	 * @brief sets up glut lighting
	 */
	void initLightModel();
	
};



/*******************************************************************************
 *                         GLUT CALLBACK FUNCTIONS
*******************************************************************************/
/*!
 * @brief Drawing callback. Executes every glut display callaback. Also
 *      calls the draw function of all registerd Drawable objects.
 */
void display();

/*!
 * @brief Resize callback. Executes whenever the window is resized.
 */
void reshape( int w, int h );

/*!
 * @brief Key down callback. Executes whenever a typical key is pressed.
 */
void keyDown(unsigned char key, int x, int y);

/*!
 * @brief Key up callback. Executes whenever a typical key is released.
 */
void keyUp(unsigned char key, int x, int y);

/*!
 * @brief Special key down callback. Executes whenever a "special" key
 *      such as an arrow key is pressed.
 */
void keySpecialDown(int key, int x, int y);

/*!
 * @brief Special key up callback. Executes whenever a "special" key
 *      such as an arrow key is released.
 */
void keySpecialUp(int key, int x, int y);

/*!
 * @brief Mouse click callback. Executes whenever a mouse button is
 *      either clicked or released.
 */
void mouseclick(int button, int state, int x, int y );

/*!
 * @brief Mouse movement callback. Executes whenever a mouse is moved
 *		inside the program window.
 */
void mousemove(int x, int y);

/*!
 * @brief Mouse drag callback. Executes whenever a mouse is moved inside
 *		the program window while a button is pressed.
 */
void mousedrag(int x, int y);

/*!
 * @brief glut Idle callback, spins a given object
 */
void spinObject( );

#endif
