/***************************************************************************//**
 * @file 
 *
 * @mainpage Program 2 - Fractals
 * 
 * @section course_section Course Information 
 *
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @date Oct 24, 2014
 * 
 * @par Professor: 
 *         Dr. Weiss
 * 
 * @par Course: 
 *         CSC-433 - M001-2014FA -  9:00-9:50 AM MWF
 * 
 * @par Location: 
 *         McLaury-311
 *
 * @section program_section Program Information 
 * 
 * @details This program simulates the solar system. It creates 8 planets, the
 *			sun, the moon, and the rings of Saturn. The Planets rotate the sun
 *			and the moon orbits the earth. '+', '-', and the mouse wheel handle
 *			zoom. The camera "orbits" what it is looking at and can be moved 
 *			by left click and drag or by 'wasd'. Tab switches camera mode
 *			including textures
 *
 *
 * Assumptions - All Planets orbits are coplaner and circlular, Pluto was 
 *			not added to solar system. speed of solar system Will start at
 *			standard speed. All planets are assumed to be perfect spheres.
 *			Planet axis are constant. Sizes are to scale. At time = 0, Planets
 *			are perfectly alined, planet surfaces do not change.
 *
 *
 * Controls
 *		0 through 9 -> individual planet toggles, 0 is the sun, 9 is neptune, 
 *					the moon is next to earth
 *		q and e -> previous and next planet
 *		wasd -> movement controls for camera
 *		TAB -> goes to next draw mode
 *		'-' and '+' -> zooms in and out
 *		[ and ] -> decresses, incresses speed -- default is real time
 *		H		-> Help
 *		Left Click and Drag -> mouse camera Movement
 *		Scroll Wheel -> mouse controlled zoom
 *		z -> set camra to default view of sun
 *		space -> sets speed to 1 (real time)
 *		t -> probably shouldn't press that one
 *
 *
 * Extras  Each Planet, sun and moon included, has a number key that they are
 *		bound to. Also 'q' and 'e' are previous and next between planets.
 *		many optimizations to improve fps and "smooth mouse controls"
 *		Made planets based on a time and not using an idle function
 *		DO NOT PRESS T
 *
 * GLUT and OpenGL are the libraries used for gui management.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions: 
 *      Build and Run
 * 
 * @par Make:
   @vertbatim
   > make fractals
   @endverbatim
 * 
 * @par Usage: 
   @verbatim  
   > solar
   @endverbatim 
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug	-	Possible performance issues on computers running Windows.
 *
 * 
 * @par Modifications and Development Timeline: 
   @verbatim 
   Date          Modification 
   ----------   ---------------------------------------------------------------
   11-08-2014	Created GitHub repo
				Added program components and several classes
   11-09-2014	attempted to make old code 3-D compatable
   11-10-2014	Added most of the overall classes ~ not much working
   11-20-2014	added camera class, solar system visable
   11-21-2014	Added zoom functionality and camera movement, turned on lights
				added rings to saturn, made sun glow, toggles between planets
   11-22-2014	fined tuned, and fixed bugs
   11-23-2014	Added textures, tab for view modes
   11-27-2014	fine tuning and last minute fixes, also all of the doxygen
				including this...
   @endverbatim
 *
 ******************************************************************************/

/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include <iostream>
#include <fstream>
#include "SolarSystem.h"

using namespace std;

/**************************************************************************//**
 * @author Johnny Ackerman, Danial Andrus
 * 
 * @par Description:
 * Main function of the program. Passes control to the SolarSystem Class
 * 
 * 
 * @param[in]      argc - Number of aurments from the command line
 * @param[out]     argv - An array of command line aurgments
 * 
 * @returns 0 - program ran successfully.
 *****************************************************************************/
int main( int argc, char *argv[] )
{
	// Initialize program's core class
	SolarSystem solarsystem;

	// Run everything through the Fractals class
	return solarsystem.run( argc, argv);
}
