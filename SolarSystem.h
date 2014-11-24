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

#include "Stepable.h"
#include <vector>
#include "Planet.h"
#include "Star.h"
#include "Ring.h"
#include "GlutManager.h"
#include "Pressable.h"

using namespace std;

/**************************************************************************//**
 * @brief The SolarSystem class creates and handles the solar system
******************************************************************************/
class SolarSystem : public Stepable, public Pressable
{
private:
	//Planets
	vector<Planet*> planets;
	Planet* subject;
	GlutManager manager;
	long long time;
	int currentPlanet;
	int speed;

public:
	SolarSystem();
	~SolarSystem();

	int run(int argc, char *argv[]);
	void setCameraSubject(int i);

	void keyDown(unsigned char key, int x, int y);
	void keyUp(unsigned char key, int x, int y);
	void keySpecialDown(unsigned char key, int x, int y);
	void keySpecialUp(unsigned char key, int x, int y);

	void step();
	void update(long long time);
};

#endif
