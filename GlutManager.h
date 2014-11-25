/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	10/20/2014
 *
 * @file File containing the declaration for the GlutMangager class.
 *
 * @brief Handles how glut interacts with the program
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
 * @brief The GlutManger Class handle everything to do with glut
 *
 * @details initializes callbacks, handles glut startup initializing and
 *		handles glut events
*******************************************************************************/
class GlutManager : public DrawingManager
{
private:
	int window_width;			/*!< Width of gui window */
	int window_height;			/*!< Height of gui window */
	string window_name;			/*!< Name of the gui window */

	Camera camera;				/*!< view camera */
	vector<Clickable*> clickables;	/*!< clickable objects for mouse events */
	vector<Stepable*> stepables;	/*!< stepable objects for movement events*/
	vector<Pressable*> pressables; /*!< pressable objects for keyboard events*/
	map<int, vector<Drawable*> > drawables; /*!< things glut needs to draw */

	static GlutManager* instance; /*!< instance of itself */

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

	/*!
	* @brief initiates glut main loop
	*/
	void run();

	/*!
	* @brief Gets the width of the view port in the virtual space.
	*/
	double getViewWidth();

	/*!
	* @brief Gets the height of the view port in the virtual space.
	*/
	double getViewHeight();
	
	/*!
	* @brief gets reference to object Camera
	*/
	Camera& getCamera();

	/*!
	* @brief registers possible mouse events
	*/
	void registerClickable(Clickable* clickable);

	/*!
	* @brief removes possible mouse events
	*/
	void unregisterClickable(Clickable* clickable);

	/*!
	* @brief checks if possible mouse events
	*/
	bool isClickableRegistered(Clickable* clickable);
	


	/*!
	* @brief registers possible movement events
	*/
	void registerStepable(Stepable* stepable);

	/*!
	* @brief removes possible movement events
	*/
	void unregisterStepable(Stepable* stepable);

	/*!
	* @brief checks if possible movement events
	*/
	bool isStepableRegistered(Stepable* stepable);
	

	/*!
	* @brief registers possible keyboard events
	*/
	void registerPressable(Pressable* pressable);

	/*!
	* @brief removes possible keyboard events
	*/
	void unregisterPressable(Pressable* pressable);

	/*!
	* @brief checks if possible keyboard events
	*/
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
	
	void menuevent(int selection);

	/*!
	 * @brief sets up glut lighting
	 */
	void initLightModel();
	
	/*!
	* @brief handles movement
	*/
	void step();
	
	// texture stuff

	/*!
	* @brief provided bmp texture load
	*/
	static bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr );

	/*!
	* @brief used by "loadBmpFile
	*/
	static inline int GetNumBytesPerRow( int NumCols );

	/*!
	* @brief used by "loadBmpFile"
	*/
	static short readShort( FILE* infile );

	/*!
	* @brief used by "loadBmpFile"
	*/
	static int readLong( FILE* infile );

	/*!
	* @brief used by "loadBmpFile"
	*/
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

void menuevent(int selection);

/*!
 * @brief step callback, object handles movement
 */
void step(int i);

#endif
