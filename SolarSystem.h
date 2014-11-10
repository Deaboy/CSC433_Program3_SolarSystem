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

#include "Spherical.h"

/**************************************************************************//**
 * @brief The SolarSystem class creates and handles the solar system
******************************************************************************/
class SolarSystem
{
public:
	SolarSystem();
	~SolarSystem();
	void draw();
	void spinObject();
	static SolarSystem* getInstance();

private:
	//Planets
	Spherical Sun;
	Spherical Mercury;
	Spherical Venus;
	Spherical Earth;
	Spherical Mars;
	Spherical Jupiter;
	Spherical Saturn;
	Spherical Uranus;
	Spherical Neptune;

	// celestrial bodies
	Spherical Moon;

	static SolarSystem* instance; /*!< reference to main instance */

};

#endif
