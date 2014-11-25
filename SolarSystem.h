/**************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 *
 * @Date	11/9/2014
 *
 * @file File containing the declaration for the SolarSystem class.
 *
 * @brief This Class is responsible for creating the solar system
******************************************************************************/
#ifndef _SOLARSYSTEM_H_
#define _SOLARSYSTEM_H_

/******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
******************************************************************************/
class SolarSystem;

#include <vector>
#include <string>
#include "Constants.h"
#include "Drawable.h"
#include "Stepable.h"
#include "Planet.h"
#include "Star.h"
#include "Ring.h"
#include "GlutManager.h"
#include "Pressable.h"
#include "Clickable.h"

using namespace std;

/**************************************************************************//**
 * @brief The SolarSystem class creates and handles the solar system
******************************************************************************/
class SolarSystem : public Drawable, public Stepable, public Pressable,
public Clickable
{
private:
	//Planets
	vector<Planet*>	planets;
	Planet*			subject;
	GlutManager		manager;
	long long		time;
	ld				min_zoom;
	int				currentPlanet;
	int				speed;
	int				menu;
	bool			drag;
	bool			help;

public:
	/*!
	 * @brief constructor, creates solar system
	 */
	SolarSystem();

	/*!
	 * @brief destructor, more than apocolyptic destruction
	 */
	~SolarSystem();


	/*!
	 * @brief sets planet data, calls camera functions, starts glut
	 */
	int run(int argc, char *argv[]);

	/*!
	 * @brief determines what camera is looking at
	 */
	void setCameraSubject(int i);

	/*!
	 * @brief keyboard callback. Executes whenever the keyboard is pressed
	 */
	void keyDown(unsigned char key, int x, int y);

	/*!
	 * @brief keyboard callback. Executes whenever the keyboard is released
	 */
	void keyUp(unsigned char key, int x, int y);

	/*!
	 * @brief Resize callback. Executes whenever the special keys are pressed
	 */
	void keySpecialDown(unsigned char key, int x, int y);

	/*!
	 * @brief Resize callback. Executes whenever the special keys are released
	 */
	void keySpecialUp(unsigned char key, int x, int y);
	
	
	/*!
	 * @brief mouse callback. Executes whenever the mouse is clicked
	 */
	void onMouseDown(int button);

	/*!
	 * @brief mouse callback. Executes whenever the mouse is unclicked
	 */
	void onMouseUp(int button);

	/*!
	 * @brief mouse callback. Executes whenever the mouse hovers over clickable
	 */
	void onMouseEnter();

	/*!
	 * @brief mouse callback. Executes whenever the mouse leaves clickable
	 */
	void onMouseLeave();

	/*!
	 * @brief mouse callback. Executes whenever the mouse wheel is rolled up
	 */
	void onMouseScrollUp();

	/*!
	 * @brief mouse callback. Executes whenever the mouse wheel is rolled down
	 */
	void onMouseScrollDown();

	/*!
	 * @brief mouse callback. Executes whenever the mouse moves
	 */
	void onMouseMove(int x, int y, int lx, int ly);

	/*!
	 * @brief determines if mouse coordinates are in solar system
	 */
	bool containsPoint(double x, double y) const;


	/*!
	 * @brief handles movement
	 */
	void step();

	/*!
	 * @brief updates universe
	 */
	void update(long long time);
	
	/*!
	 * @brief draws simulation speed or help
	 */
	void draw();
};

#endif
