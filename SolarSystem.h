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
#include "Constants.h"
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
class SolarSystem : public Stepable, public Pressable, public Clickable
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
	bool			drag;

public:
	SolarSystem();
	~SolarSystem();

	int run(int argc, char *argv[]);
	void setCameraSubject(int i);

	void keyDown(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void keySpecialDown(unsigned char key, int x, int y);
	void keySpecialUp(unsigned char key, int x, int y);
	
	void onMouseDown(int button);
	void onMouseUp(int button);
	void onMouseEnter();
	void onMouseLeave();
	void onMouseScrollUp();
	void onMouseScrollDown();
	void onMouseMove(int x, int y, int lx, int ly);
	bool containsPoint(double x, double y) const;

	void step();
	void update(long long time);
};

#endif
