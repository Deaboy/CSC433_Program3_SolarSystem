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
	mouse_button = -1;
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
void GlutManager::init(int argc, char *argv[])
{
	window_width = (int)window_width;
	window_height = (int)window_height;

	// perform various OpenGL initializations
	glutInit(&argc, argv);

	// Put window in center of screen
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	if (w != 0 && h != 0)
	{
		w = w / 2 - window_width / 2;
		h = h / 2 - window_height / 2;
	}

	// Initialize glut with 32-bit graphics, double buffering, and anti-aliasing
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// Set up the program window
	glutInitWindowSize(window_width, window_height);    // initial window size
	glutInitWindowPosition(w, h);                  // initial window position
	glutCreateWindow(window_name.c_str());         // window title

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Always clear screen to black
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutIgnoreKeyRepeat(1);

	// Register callbacks
	glutDisplayFunc(*::display);
	glutReshapeFunc(*::reshape);
	glutKeyboardFunc(*::keyDown);
	glutMouseFunc(*::mouseclick);
#ifndef OS_X
	glutMouseWheelFunc(*::mousescroll);
#endif
	glutMotionFunc(*::mousedrag);
	glutPassiveMotionFunc(*::mousemove);
	glutTimerFunc(0, *::step, 0);

	// set up illumination-reflectance model
	GlutManager::initLightModel();
	glEnable(GL_LIGHTING);

	// Set up texture parameters
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

int GlutManager::run()
{

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

Camera& GlutManager::getCamera()
{
	return camera;
}

void GlutManager::registerClickable(Clickable* clickable)
{
	if (!isClickableRegistered(clickable) && clickable != NULL)
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

bool GlutManager::isClickableRegistered(Clickable* clickable)
{
	return find(clickables.begin(), clickables.end(), clickable) != clickables.end();
}

void GlutManager::registerStepable(Stepable* stepable)
{
	if (!isStepableRegistered(stepable) && stepable != NULL)
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

bool GlutManager::isStepableRegistered(Stepable* stepable)
{
	return find(stepables.begin(), stepables.end(), stepable) != stepables.end();
}

void GlutManager::registerPressable(Pressable* pressable)
{
	if (!isPressableRegistered(pressable) && pressable != NULL)
	{
		pressables.push_back(pressable);
	}
}

void GlutManager::unregisterPressable(Pressable* pressable)
{
	auto it = find(pressables.begin(), pressables.end(), pressable);
	if (it != pressables.end())
		pressables.erase(it);
}

bool GlutManager::isPressableRegistered(Pressable* pressable)
{
	return find(pressables.begin(), pressables.end(), pressable) != pressables.end();
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Drawing callback. Executes every glut display callaback.
 *		Also calls the draw function of all registerd Drawable objects.
*******************************************************************************/
void GlutManager::display()
{
    // Switch back to (default) model view mode, for transformations
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
	
	//clear the display and set backround to black
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glColor3f( 1.0, 1.0, 1.0 );

	// Update the camera, thus updating the point of view
	camera.update();

	// Update the light's position
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );

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
    glViewport( 0, 0, window_width, window_height );

    glMatrixMode( GL_PROJECTION );		// Use an orthographic projection
    glLoadIdentity();					// Initialize transformation matrix
	
	// Adjust viewport and map to window
	// gluOrtho2D(0, window_width, 0, window_height);
	// glOrtho(-(w/2), (w/2), -(h/2), (h/2), -100, 100);
	gluPerspective(50.0, (double) w/(double) h, 1.0, 1000000000.0);
	
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
	for (Pressable* pressable : pressables)
	{
		pressable->keyDown(key, x, y);
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
	// Camera controls
	if (state == GLUT_UP)
	{
		if (button == mouse_button)
		{
			//glutWarpPointer(mouse_restore_x, mouse_restore_y);
			camera.setRotationEasing(0.125);
			mouse_button = -1;
		}
	}
	else
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			camera.setRotationEasing(1);
			mouse_button = button;
			mouse_restore_x = x;
			mouse_restore_y = y;
		}
	}
}

void GlutManager::mousescroll(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		// Zoom in
		camera.setDistance(camera.getDistance() * 0.75);
	}
	else
	{
		// Zoom out
		camera.setDistance(camera.getDistance() * 1.33333333333);
	}
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
	if (mouse_button == GLUT_LEFT_BUTTON)
	{
		camera.setPitch(camera.getPitch() + (y - mouse_restore_y) / 4.0);
		camera.setYaw(camera.getYaw() + ((mouse_restore_x - x) / 4.0));
		mouse_restore_x = x;
		mouse_restore_y = y;
		//glutWarpPointer(mouse_restore_x, mouse_restore_y);
	}
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
	mousemove(x, y);
}

/***************************************************************************//**
 * @author Dr. Weiss
 * 
 * @par Description: sets up "lighting" in the 3-D space
*******************************************************************************/
void GlutManager::initLightModel()
{
    // specify light source properties
    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[] = { 0.4f, 0.4f, 0.4f, 1.0 };       // ambient light
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };       // diffuse light
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 0.0 };      // highlights

    glEnable( GL_LIGHT0 );      // enable one light source
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

    // glShadeModel( GL_FLAT );    // start with flat shading (smooth is default)
	glShadeModel( GL_SMOOTH );

    glEnable( GL_DEPTH_TEST );  // enable depth buffer for hidden-surface elimination
    glEnable( GL_NORMALIZE );   // automatic normalization of normals
    glEnable( GL_CULL_FACE );   // eliminate backfacing polygons
    glCullFace( GL_BACK );
    // glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE );   // render back faces

    glClearColor( 0.0, 0.0, 0.0, 1.0 );     // black background
}

void GlutManager::step()
{
	for (Stepable* stepable : stepables)
	{
		stepable->step();
	}
	camera.step();
}

/* ********************************************************************
 *  LoadBmpFile
 *  Read into memory an RGB image from an uncompressed BMP file.
 *  Return true for success, false for failure.
 *  Author: Sam Buss December 2001.
 **********************************************************************/
bool GlutManager::LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr )
{

    FILE* infile = fopen( filename, "rb" );		// Open for reading binary data
    if ( !infile )
    {
        fprintf( stderr, "LoadBmpFile(): unable to open file: %s\n", filename );
        return false;
    }

    bool fileFormatOK = false;
    int bChar = fgetc( infile );
    int mChar = fgetc( infile );
    if ( bChar == 'B' && mChar == 'M' )
    {			// If starts with "BM" for "BitMap"
        skipChars( infile, 4 + 2 + 2 + 4 + 4 );			// Skip 4 fields we don't care about
        NumCols = readLong( infile );
        NumRows = readLong( infile );
        skipChars( infile, 2 );					// Skip one field
        int bitsPerPixel = readShort( infile );
        skipChars( infile, 4 + 4 + 4 + 4 + 4 + 4 );		// Skip 6 more fields

        if ( NumCols > 0 && NumCols <= 100000 && NumRows > 0 && NumRows <= 100000
                && bitsPerPixel == 24 && !feof( infile ) )
        {
            fileFormatOK = true;
        }
    }

    if ( !fileFormatOK )
    {
        fclose ( infile );
        fprintf( stderr, "Not a valid 24-bit bitmap file: %s.\n", filename );
        return false;
    }

    // Allocate memory
    ImagePtr = new unsigned char[ NumRows * GetNumBytesPerRow( NumCols ) ];
    if ( !ImagePtr )
    {
        fclose ( infile );
        fprintf( stderr, "Unable to allocate memory for %i x %i bitmap: %s.\n",
                 NumRows, NumCols, filename );
        return false;
    }

    unsigned char* cPtr = ImagePtr;
    for ( int i = 0; i < NumRows; i++ )
    {
        int j;
        for ( j = 0; j < NumCols; j++ )
        {
            *( cPtr + 2 ) = fgetc( infile );	// Blue color value
            *( cPtr + 1 ) = fgetc( infile );	// Green color value
            *cPtr = fgetc( infile );		// Red color value
            cPtr += 3;
        }
        int k = 3 * NumCols;					// Num bytes already read
        for ( ; k < GetNumBytesPerRow( NumCols ); k++ )
        {
            fgetc( infile );				// Read and ignore padding;
            *( cPtr++ ) = 0;
        }
    }

    if ( feof( infile ) )
    {
        fclose ( infile );
        fprintf( stderr, "Premature end of file: %s.\n", filename );
        return false;
    }

    fclose( infile );	// Close the file

    return true;
}

// Rows are word aligned
inline int GlutManager::GetNumBytesPerRow( int NumCols )
{
    return ( ( 3 * NumCols + 3 ) >> 2 ) << 2;
}


// read a 16-bit integer from the input file
short GlutManager::readShort( FILE* infile )
{
    unsigned char lowByte, hiByte;
    lowByte = fgetc( infile );			// Read the low order byte (little endian form)
    hiByte = fgetc( infile );			// Read the high order byte

    // Pack together
    short ret = hiByte;
    ret <<= 8;
    ret |= lowByte;
    return ret;
}

// read a 32-bit integer from the input file
int GlutManager::readLong( FILE* infile )
{
    unsigned char byte0, byte1, byte2, byte3;
    byte0 = fgetc( infile );			// Read bytes, low order to high order
    byte1 = fgetc( infile );
    byte2 = fgetc( infile );
    byte3 = fgetc( infile );

    // Pack together
    int ret = byte3;
    ret <<= 8;
    ret |= byte2;
    ret <<= 8;
    ret |= byte1;
    ret <<= 8;
    ret |= byte0;
    return ret;
}

// skip over given number of bytes in input file
void GlutManager::skipChars( FILE* infile, int numChars )
{
    for ( int i = 0; i < numChars; i++ )
    {
        fgetc( infile );
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
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key down callback. Executes whenever a typical key is
 *		pressed. Simply forwards to Pong class' identical function.
 *
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
void keyDown(unsigned char key, int x, int y)
{
	GlutManager::getInstance()->keyDown(key, x, y);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Key up callback. Executes whenever a typical key is
 *		released. Simply forwards to Pong class' identical function.
 * 
 * @param[in]	key - ASCII-encoded char of the key that was pressed.
 * @param[in]	x - The x coordinate of the mouse at the time the key
 *				was pressed. Measured in integers.
 * @param[in]	y - The y coordinate of the mouse at the time the key
 *				was pressed.
*******************************************************************************/
//void keyUp(unsigned char key, int x, int y)
//{
//	GlutManager::getInstance()->keyUp(key, x, y);
//}

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

void mousescroll(int button, int dir, int x, int y)
{
	GlutManager::getInstance()->mousescroll(button, dir, x, y);
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
	static unsigned int fps_delay = (int) MSPF;
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
