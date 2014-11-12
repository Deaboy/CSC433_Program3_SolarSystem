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
			.setRotationPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(25.05)))) )
			.setRightAscension(286.13)
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
			.setRightAscension(281.01)
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
			.setRightAscension(272.76)
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(108208000)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(224.701)))) );
	planets.push_back(temp);
	
	// Earth
	temp = new Planet;
	(*temp).setName("Earth")
			.setColor(49, 79, 43)
			.setRadius(6371.0)
			.setRotationAxis(((21.4119/60) + 26)/60 + 23)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(4.1 + 60*(56 + 60*(23))) )
			.setRightAscension(90)
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(149598261)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(365.256363004)))) );
	planets.push_back(temp);
	earth = temp;
	
	// Moon
	temp = new Planet;
	(*temp).setName("Moon")
			.setColor(191, 191, 191)
			.setRadius(1737.1)
			.setRotationAxis(6.687)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(27.321582)))) )
			.setRightAscension(0) // unknown
			.setOrbitTarget(earth)
			.setOrbitInitial(0)
			.setOrbitRadius(384399)
			.setOrbitPeriod( FPS*(6 + 60*(43 + 60*(7 + 24*(27)))) );
	planets.push_back(temp);
	
	// Mars
	temp = new Planet;
	(*temp).setName("Mars")
			.setColor(193, 92, 40)
			.setRadius(3389.5)
			.setRotationAxis(25.19)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(22 + 60*(37 + 60*(24))) )
			.setRightAscension(317.68143)
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(227939100)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(686.971)))) );
	planets.push_back(temp);
	
	// Jupiter
	temp = new Planet;
	(*temp).setName("Jupiter")
			.setColor(225, 186, 138)
			.setRadius(69911)
			.setRotationAxis(3.13)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(30 + 60*(55 + 60*(9))) )
			.setRightAscension(268.057)
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(778547200)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(4332.59)))) );
	planets.push_back(temp);
	
	// Saturn
	temp = new Planet;
	(*temp).setName("Saturn")
			.setColor(207, 166, 135)
			.setRadius(58232)
			.setRotationAxis(26.73)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(0 + 60*(34 + 60*(10))) )
			.setRightAscension(83.537)
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(1433449370)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(10759.22)))) );
	planets.push_back(temp);
	
	// Uranus
	temp = new Planet;
	(*temp).setName("Uranus")
			.setColor(140, 170, 183)
			.setRadius(25362)
			.setRotationAxis(97.77)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(24 + 60*(14 + 60*(17))) )
			.setRightAscension(257.311)
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(2870671400)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(30687.15)))) );
	planets.push_back(temp);
	
	// Neptune
	temp = new Planet;
	(*temp).setName("Neptune")
			.setColor(66, 106, 139)
			.setRadius(24622)
			.setRotationAxis(28.32)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(36 + 60*(6 + 60*(16))) )
			.setRightAscension(299.3)
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(4498542600)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(60190.03)))) );
	planets.push_back(temp);
	
	
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
