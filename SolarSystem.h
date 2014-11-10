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

#include "Sphearical.h"

using namespace std;

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
	Spearical Sun;
	Spearical Mercury;
	Spearical Venus;
	Spearical Earth;
	Spearical Mars;
	Spearical Jupiter;
	Spearical Saturn;
	Spearical Uranus;
	Spearical Neptune;

	// celestrial bodies
	Spearical Moon;

	static SolarSystem* instance; /*!< reference to main instance */

};

#endif


SolarSystem::SolarSystem()
{
	//initialize objects in solar system
	Spearical Sun( 696000, 0, 0, 25 );
	Spearical Mercury( 2439, 58, 88, 1416 );
	Spearical Venus( 6052, 108, 225, 5832 );
	Spearical Earth( 6378, 150, 365, 24 );
	Spearical Mars( 3394, 228, 687, 24.6 );
	Spearical Jupiter( 71398, 779, 4332, 9.8);
	Spearical Saturn( 60270, 1424, 10761, 10.2 );
	Spearical Uranus( 25550, 2867, 30682, 15.5 );
	Spearical Neptune( 24750, 4492, 60195, 15.8 );
	Spearical Moon( 1738, 0.384, 27.3, 27.3 );

	instance = this;
}

SolarSystem::~SolarSystem()
{
//delete Sun, Mercury, Venus, Earth, Mars, Jupiter, Saturn, Uranus, Neptune;
//delete Moon;
}

void SolarSystem::draw()
{
}

void SolarSystem::spinObject()
{

}

SolarSystem* SolarSystem::getInstance()
{
	return instance;
}
