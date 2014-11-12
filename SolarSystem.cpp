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
	Planet& setName(string name);
	Planet& setColor(unsigned char r, unsigned char g, unsigned char b);
	Planet& setRadius(long double radius);
	Planet& setRotationAxis(long double rotation_axis);
	Planet& setRotationInitial(long double rotation_init);
	Planet& setRotationPeriod(long double rotation_period);
	Planet& setOrbitTarget(Planet* orbit_target);
	Planet& setOrbitInitial(long double orbit_init);
	Planet& setOrbitRadius(long double orbit_radius);
	Planet& setOrbitPeriod(long double orbit_period);
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
	
	Planet* sun;
	Planet* earth;
	Planet* temp;
	
	// Sun
	temp = new Planet;
	(*temp).setName("Sun")
			.setColor(254, 250, 152)
			.setRadius(696342)
			.setRotationAxis(7.25)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(12 + 60*(7 + 60*(9 + 24*(25)))) )
			.setOrbitTarget(NULL)
			.setOrbitInitial(0)
			.setOrbitRadius(0)
			.setOrbitPeriod(0);
	planets.push_back(temp);
	sun = temp;
	
	// Mercury
	temp = new Planet;
	(*temp).setName("Mercury")
			.setColor(154, 107, 55)
			.setRadius(2439.7)
			.setRotationAxis(2.11 / 60.0)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(0 + 60*(30 + 60*(1407))) )
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(57909050)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(87.969)))) );
	planets.push_back(temp);
	
	// Venus
	temp = new Planet;
	(*temp).setName("Venus")
			.setColor(138, 67, 18)
			.setRadius(6051.8)
			.setRotationAxis(177.36)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(-243.0185)))) )
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(108208000)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(224.701)))) );
	planets.push_back(temp);
	
	// Earth
	temp = new Planet;
	planets.push_back(temp);
	earth = temp;
	
	// Moon
	
	// Mars
	
	// Jupiter
	
	// Saturn
	
	// Uranus
	
	// Neptune
	
	
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
