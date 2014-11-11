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

#include <list>
#include "Planet.h"
#include "GlutManager.h"

using namespace std;

/**************************************************************************//**
 * @brief The SolarSystem class creates and handles the solar system
******************************************************************************/
class SolarSystem
{
private:
	//Planets
	list<Planet*> planets;
	GlutManager manager;
	long long time;

public:
	SolarSystem();
	~SolarSystem();
	void run(int argc, char *argv[]);
	void update(long long time);
};

#endif
