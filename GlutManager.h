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


#define _CRT_SECURE_NO_WARNINGS


/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
class GlutManager;

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <stdio.h>
#include "Clickable.h"
#include "DrawingManager.h"
#include "Stepable.h"
#include "Pressable.h"
#include "Camera.h"

// OpenGL/GLUT includes based on platform
#ifndef OS_X
#include <GL/freeglut.h>
#else
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#endif

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
class GlutManager : public DrawingManager
{
private:
	int window_width;			/*!< Width of gui window */
	int window_height;			/*!< Height of gui window */
	string window_name;			/*!< Name of the gui window */

	Camera camera;
	vector<Clickable*> clickables;
	vector<Stepable*> stepables;
	vector<Pressable*> pressables;
	map<int, vector<Drawable*> > drawables;
	
	// Camera control variables
	int mouse_restore_x;
	int mouse_restore_y;
	int mouse_button;

	static GlutManager* instance;

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
	 * @brief Gets the main instance of this glut manager.
	 */
	static GlutManager* getInstance();

	/*!
	* @brief Function to get the current instance of the program.
	*/
	void init( int argc, char *argv[] );

	void run();

	/*!
	* @brief Gets the width of the view port in the virtual space.
	*/
	double getViewWidth();

	/*!
	* @brief Gets the height of the view port in the virtual space.
	*/
	double getViewHeight();
	
	Camera& getCamera();

	void registerClickable(Clickable* clickable);
	void unregisterClickable(Clickable* clickable);
	bool isClickableRegistered(Clickable* clickable);
	
	void registerStepable(Stepable* stepable);
	void unregisterStepable(Stepable* stepable);
	bool isStepableRegistered(Stepable* stepable);
	
	void registerPressable(Pressable* pressable);
	void unregisterPressable(Pressable* pressable);
	bool isPressableRegistered(Pressable* pressable);

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
	
	void mousescroll(int button, int dir, int x, int y);
	
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
	 * @brief sets up glut lighting
	 */
	void initLightModel();
	
	void step();
	
	// texture stuff
	static bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr );
	static inline int GetNumBytesPerRow( int NumCols );
	static short readShort( FILE* infile );
	static int readLong( FILE* infile );
	static void skipChars( FILE* infile, int numChars );
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

void mousescroll(int button, int dir, int x, int y);

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

void step(int i);

#endif
