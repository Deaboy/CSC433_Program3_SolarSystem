#include "SolarSystem.h"

SolarSystem* SolarSystem::instance = NULL;


SolarSystem::SolarSystem()
{
	//initialize objects in solar system
	Spherical Sun( 696000, 0, 0, 25 );
	Spherical Mercury( 2439, 58, 88, 1416 );
	Spherical Venus( 6052, 108, 225, 5832 );
	Spherical Earth( 6378, 150, 365, 24 );
	Spherical Mars( 3394, 228, 687, 24.6 );
	Spherical Jupiter( 71398, 779, 4332, 9.8);
	Spherical Saturn( 60270, 1424, 10761, 10.2 );
	Spherical Uranus( 25550, 2867, 30682, 15.5 );
	Spherical Neptune( 24750, 4492, 60195, 15.8 );
	Spherical Moon( 1738, 0.384, 27.3, 27.3 );

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
