/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	11/7/2014
 *
 * @file File containing the implementation of the Fractals class.
 *
 * @brief implementation for handeling callbacks
*******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "GlutManager.h"

GlutManager* GlutManager::instance = NULL;

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Constructor, initializes data, registers data with other
 *	classes, and creates instances of subClasses
*******************************************************************************/
GlutManager::GlutManager()
: window_width(400 /*arbitrary*/), window_height(300 /*arbitrary*/),
window_name("Solar System")
{
	instance = this;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Destructor, destroys subclasses
*******************************************************************************/
GlutManager::~GlutManager()
{
	//delete current_program;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Begins running the program. Initializes OpenGL, registers
 *		events, instantiates objects, and runs the game. Beware when
 *		calling this function, as it enters the OpenGL main loop, only
 *		to return at end of program execution.
 *
 * @returns Status code of the program. 0 means no problems.
*******************************************************************************/
int GlutManager::run( int argc, char *argv[] )
{
	window_width = (int) window_width;
	window_height = (int) window_height;

	// perform various OpenGL initializations
    glutInit( &argc, argv );

	// Put window in center of screen
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	if (w != 0 && h != 0)
	{
		w = w / 2 - window_width / 2;
		h = h / 2 - window_height / 2;
	}

	// Initialize glut with 32-bit graphics, double buffering, and anti-aliasing
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set up the program window
    glutInitWindowSize( window_width, window_height);    // initial window size
    glutInitWindowPosition( w, h );                  // initial window position
    glutCreateWindow( window_name.c_str() );         // window title

	// Always clear screen to black
	glClearColor( 1.0, 1.0, 1.0, 1.0 );

	glutIgnoreKeyRepeat(1);

    // Register callbacks
    glutDisplayFunc( *::display );
    glutReshapeFunc( *::reshape );
    glutMouseFunc( *::mouseclick );
	glutMotionFunc( *::mousedrag );
	glutPassiveMotionFunc( *::mousemove );
	glutTimerFunc(0, *::step, 0);

	// set up illumination-reflectance model
    GlutManager::initLightModel();

	/* ****This might go in solarsystem ****
    // generate GLU quadric object with surface normals
    object = gluNewQuadric( );
    gluQuadricNormals( object, GLU_SMOOTH );
    gluQuadricDrawStyle( object, GLU_LINE );
	*/

    // Go into OpenGL/GLUT main loop
    glutMainLoop();

    return 0;

}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Function to get the current instance of the program.
 *
 * @returns Pointer to the current instance of the program.
*******************************************************************************/
GlutManager* GlutManager::getInstance()
{
	return instance;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the width of the view port in the virtual space.
 * 
 * @returns The width of the view port in pixels.
*******************************************************************************/
double GlutManager::getViewWidth()
{
	return window_width;
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Gets the height of the view port in the virtual space.
 *
 * @returns The height of the view port in pixels.
*******************************************************************************/
double GlutManager::getViewHeight()
{
	return window_height;
}

void GlutManager::registerClickable(Clickable* clickable)
{
	if (!isRegistered(clickable) && clickable != NULL)
	{
		clickables.push_back(clickable);
	}
}

void GlutManager::unregisterClickable(Clickable* clickable)
{
	auto it = find(clickables.begin(), clickables.end(), clickable);
	if (it != clickables.end())
		clickables.erase(it);
}

bool GlutManager::isRegistered(Clickable* clickable)
{
	return find(clickables.begin(), clickables.end(), clickable) != clickables.end();
}

void GlutManager::registerStepable(Stepable* stepable)
{
	if (!isRegistered(stepable) && stepable != NULL)
	{
		stepables.push_back(stepable);
	}
}

void GlutManager::unregisterStepable(Stepable* stepable)
{
	auto it = find(stepables.begin(), stepables.end(), stepable);
	if (it != stepables.end())
		stepables.erase(it);
}

bool GlutManager::isRegistered(Stepable* stepable)
{
	return find(stepables.begin(), stepables.end(), stepable) != stepables.end();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Drawing callback. Executes every glut display callaback.
 *		Also calls the draw function of all registerd Drawable objects.
*******************************************************************************/
void GlutManager::display()
{
	//clear the display and set backround to black
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glColor3f( 1.0, 1.0, 1.0 );

	draw();

	// Flush graphical output
	glutSwapBuffers();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Resize callback. Executes whenever the window is resized.
 *
 * @param[in]	w - The window's new width in pixels.
 * @param[in]	h - The window's new height in pixels.
*******************************************************************************/
void GlutManager::reshape(int w, int h)
{
	// store new window dimensions globally
    window_width = w;
    window_height = h;

    glMatrixMode( GL_PROJECTION );		// Use an orthographic projection
    glLoadIdentity();					// Initialize transformation matrix
	
	// Adjust viewport and map to window
	//gluOrtho2D(0, window_width, 0, window_height);
	glOrtho(-(w/2), (w/2), -(h/2), (h/2), -100, 100);
    glViewport( 0, 0, window_width, window_height );

    // Switch back to (default) model view mode, for transformations
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key down callback. Executes whenever a typical key is
 *		pressed.
 *
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void GlutManager::keyDown(unsigned char key, int x, int y)
{
    switch ( key )
    {
        case 27:		// Escape
            exit( 0 );
            break;

		default:		// Everything else, forward to game manager
			/*current_program::function( key ); */
            break;
    }
}

/***************************************************************************//**
 * @author Johnny Ackerman, Daniel Andrus
 * 
 * @par Description: Mouse click callback. Executes whenever a mouse button is
 *		either clicked or released.
 *  
 * @param[in]	button - The button whose state was changed.
 * @param[in]	state - The new state of the button.
 * @param[in]	x - The x coordinate of the mouse at the time the button
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the button
 *				was pressed.
*******************************************************************************/
void GlutManager::mouseclick(int button, int state, int x, int y)
{
	double vx;	// view x
	double vy;	// view y

	// Correct for coordinate system
	vx = x;
    vy = window_height - y;

	// Correct for scaling
	/*
	vx *= view_width / window_width;
	vy *= view_height / window_height;

	vx -= view_x;
	vy -= view_y;
	*/

	//if needed
	/*current_program::function*/
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Mouse movement callback. Executes when the mouse is moved
 *		inside the program window.
 *
 * @param[in]	x - New x position of the mouse.
 * @param[in]	y - New y position of the mouse.
*******************************************************************************/
void GlutManager::mousemove(int x, int y)
{
	double vx;	// view x
	double vy;	// view y

	// Correct for coordinate system
	vx = x;
    vy = window_height - y;

	/*
	// Correct for scaling
	vx *= view_width / window_width;
	vy *= view_height / window_height;

	vx -= view_x;
	vy -= view_y;

	*/

	//if needed
	/*current_program::function */
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Mouse movement callback. Executes when the mouse is moved
 *		inside the program window while a button is pressed.
 *
 * @param[in]	x - New x position of the mouse.
 * @param[in]	y - New y position of the mouse.
*******************************************************************************/
void GlutManager::mousedrag(int x, int y)
{
	double vx;	// view x
	double vy;	// view y

	// Correct for coordinate system
	vx = x;
    vy = window_height - y;

	/*I
	// Correct for scaling
	vx *= view_width / window_width;
	vy *= view_height / window_height;

	vx -= view_x;
	vy -= view_y;
	*/

	//f needed
	/* current_program::function */
}

/***************************************************************************//**
 * @author Dr. Weiss
 * 
 * @par Description: sets up "lighting" in the 3-D space
*******************************************************************************/
void GlutManager::initLightModel()
{
    // specify material reflectivity
    GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 };     // blue ambient reflectivity
    GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };     // green diffuse reflectivity
    GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 };    // red highlights
    GLfloat mat_shininess = { 100.0 };
    
    glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse );
    glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess );
    
    // specify light source properties
    GLfloat light_position[] = { 10.0, 10.0, 10.0, 1.0 };
    GLfloat light_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0 };       // ambient light
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };       // diffuse light
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };      // highlights

    glEnable( GL_LIGHT0 );      // enable one light source
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

    glShadeModel( GL_FLAT );    // start with flat shading (smooth is default)

    glEnable( GL_DEPTH_TEST );  // enable depth buffer for hidden-surface elimination
    glEnable( GL_NORMALIZE );   // automatic normalization of normals
    glEnable( GL_CULL_FACE );   // eliminate backfacing polygons
    glCullFace( GL_BACK );
    // glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );   // render back faces

    glClearColor( 0.0, 0.0, 0.0, 1.0 );     // black background
    glColor3d ( 0.8, 0.8, 0.0 );            // draw in yellow
}

void GlutManager::step()
{
	for (Stepable* stepable : stepables)
	{
		stepable->step();
	}
}

/*******************************************************************************
 *                         GLUT CALLBACK FUNCTIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Drawing callback. Executes every glut display callaback.
 *		Also calls the draw function of all registerd Drawable objects.
*******************************************************************************/
void display()
{
	GlutManager::getInstance()->display();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Resize callback. Executes whenever the window is resized.
 *
 * @param[in]	w - The window's new width in pixels.
 * @param[in]	h - The window's new height in pixels.
*******************************************************************************/
void reshape(int w, int h)
{
	GlutManager::getInstance()->reshape(w, h);
}

/***************************************************************************//**
 * @author Johnny Ackerman
 * 
 * @par Description: Mouse click callback. Executes whenever a mouse button is
 * 		either clicked or released.
 *  
 * @param[in]	button - The button whose state was changed.
 * @param[in]	state - The new state of the button.
 * @param[in]	x - The x coordinate of the mouse at the time the button
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the button
 *				was pressed.
*******************************************************************************/
void mouseclick(int button, int state, int x, int y)
{
	GlutManager::getInstance()->mouseclick(button, state, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Mouse movement callback. Executes when the mouse is moved
 *		inside the program window.
 *
 * @param[in]	x - New x position of the mouse.
 * @param[in]	y - New y position of the mouse.
*******************************************************************************/
void mousemove(int x, int y)
{
	GlutManager::getInstance()->mousemove(x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Mouse movement callback. Executes when the mouse is moved
 *		inside the program window while a button is pressed.
 *
 * @param[in]	x - New x position of the mouse.
 * @param[in]	y - New y position of the mouse.
*******************************************************************************/
void mousedrag(int x, int y)
{
	GlutManager::getInstance()->mousedrag(x, y);
}

void step(int i)
{
	// FPS, or technically "milliseconds per frame"
#ifdef MSPF
	static unsigned int fps_delay = MSPF;
#else
	static unsigned int fps_delay = 1000 / 60;
#endif
	
	// Reset the timer
	glutTimerFunc(fps_delay, *::step, 0);
	
	// Call step function
	GlutManager::getInstance()->step();

	// Redraw the screen after frame's been processed.
	glutPostRedisplay();
}
