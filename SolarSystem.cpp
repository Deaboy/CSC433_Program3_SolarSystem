#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
	
}

SolarSystem::~SolarSystem()
{
	for (Planet* planet : planets)
	{
		delete planet;
	}
}

void SolarSystem::run(int argc, char *argv[])
{
	// Create planets here
	/*
	Planet(string name, unsigned char color[3], long double radius,
			long double rotation_axis, long double rotation_init,
			long double rotation_velocity, Planet* orbit_target,
			long double orbit_init, long double orbit_radius,
			long double orbit_velocity);
	*/
	/*
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
	*/
	Planet* sun		= new Planet("Sun", 0, 0, 0, 1, 0, 0, 0, NULL, 0, 0, 0);
	Planet* earth	= new Planet("Earth", 0, 0, 0, 1, 0, 0, 0, NULL, 0, 0, 0);
	planets.push_back(sun);
	planets.push_back(earth);
	
	// Register planets with glut manager
	for (Planet* planet : planets)
		manager.drawObject(planet);
	
	manager.run(argc, argv);
}

void SolarSystem::update(long long time)
{
	for (Planet* planet : planets)
	{
		planet->update(time);
	}
}
