#include "SolarSystem.h"

SolarSystem::SolarSystem()
{
	time = 0;
	subject = NULL;
	currentPlanet = 0;
}

SolarSystem::~SolarSystem()
{
	for (Planet* planet : planets)
	{
		delete planet;
	}
}

int SolarSystem::run(int argc, char *argv[])
{
	Planet* sun;
	Planet* earth;
	Planet* temp;
	
	// Sun
	temp = new Star;
	(*temp).setName("Sun")
			.setColor(254, 250, 152)
			.setRadius(696342)
			.setTexture("textures/sun.bmp", 512, 256)
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
			.setTexture("textures/mercury.bmp", 512, 256)
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
			.setTexture("textures/venus.bmp", 512, 256)
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
			.setTexture("textures/earth.bmp", 512, 256)
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
			.setTexture("textures/moon.bmp", 512, 256)
			.setRotationAxis(6.687)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(27.321582)))) )
			.setRightAscension(0) // unknown
			.setOrbitTarget(earth)
			.setOrbitInitial(0)
			.setOrbitRadius(384399)
			//.setOrbitRadius(149598261)	// TESTING
			.setOrbitPeriod( FPS*(6 + 60*(43 + 60*(7 + 24*(27)))) );
	planets.push_back(temp);
	
	// Mars
	temp = new Planet;
	(*temp).setName("Mars")
			.setColor(193, 92, 40)
			.setRadius(3389.5)
			.setTexture("textures/mars.bmp", 512, 256)
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
			.setTexture("textures/jupiter.bmp", 512, 256)
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
			.setTexture("textures/saturn.bmp", 512, 256)
			.setRotationAxis(26.73)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(0 + 60*(34 + 60*(10))) )
			.setRightAscension(83.537)
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(1433449370)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(10759.22)))) );
	planets.push_back(temp);
	earth = temp;	// Yeah, I know, but lazy.
	
	// Uranus
	temp = new Planet;
	(*temp).setName("Uranus")
			.setColor(140, 170, 183)
			.setRadius(25362)
			.setTexture("textures/uranus.bmp", 512, 256)
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
			.setTexture("textures/neptune.bmp", 512, 256)
			.setRotationAxis(28.32)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(36 + 60*(6 + 60*(16))) )
			.setRightAscension(299.3)
			.setOrbitTarget(sun)
			.setOrbitInitial(0)
			.setOrbitRadius(4498542600)
			.setOrbitPeriod( FPS*(0 + 60*(0 + 60*(0 + 24*(60190.03)))) );
	planets.push_back(temp);

	// Saturn's rings
	temp = new Ring;
	(*temp).setName("")
			.setColor(217, 176, 145)
			.setRadius(136775)
			.setTexture("textures/saturnrings.bmp", 512, 256)
			.setRotationAxis(26.73)
			.setRotationInitial(0)
			.setRotationPeriod( FPS*(0 + 60*(34 + 60*(10))) )
			.setRightAscension(83.537)
			.setOrbitRadius(92000)
			.setOrbitTarget(earth);
	planets.push_back(temp);
	
	
	// Register planets with glut manager
	for (Planet* planet : planets)
		manager.drawObject(planet);
	manager.registerStepable(this);
	manager.registerPressable(this);
	
	manager.getCamera().setSubject(0,0,0).setRotationEasing(0.125)
			.setZoomEasing(0.125).setMovementEasing(1)
			.setPitch(45).setYaw(315).setDistance(1000);
	
	return manager.run(argc, argv);
}

void SolarSystem::setCameraSubject(int i)
{
	if (i < (int) planets.size())
		subject = planets[i];
}

void SolarSystem::keyDown(unsigned char key, int x, int y)
{
	Planet* Placeholder;
	static int counter = 0;
	if (key != GLUT_LEFT_BUTTON)
	{
		switch ( key )
		{
			case 27:		// Escape
				exit( 0 );
				break;

			case 61:		// "="
			case 43:		// "+"
				GlutManager::getInstance()->
					getCamera().setDistance( GlutManager::getInstance()->
					getCamera().getDistance() * .75 );
				break;

			case 95:		// "_"
			case 45:		// "-"
				GlutManager::getInstance()->
					getCamera().setDistance( GlutManager::getInstance()->
					getCamera().getDistance() * 1.333333333 );
				break;

			case 87:		// "W"
			case 119:		// "w"
				GlutManager::getInstance()->
					getCamera().setPitch( GlutManager::getInstance()->
					getCamera().getPitch() + 15 );
				break;

			case 83:		// "S"
			case 115:		// "s"
				GlutManager::getInstance()->
					getCamera().setPitch( GlutManager::getInstance()->
					getCamera().getPitch() - 15 );
				break;

			case 65:		// "A"
			case 97:		// "a"
				GlutManager::getInstance()->
					getCamera().setYaw( GlutManager::getInstance()->
					getCamera().getYaw() + 20 );
				break;

			case 68:		// "D"
			case 100:		// "d"
				GlutManager::getInstance()->
					getCamera().setYaw( GlutManager::getInstance()->
					getCamera().getYaw() - 20 );
				break;

			case 81:		// "Q"
			case 113:		// "q"
				currentPlanet = currentPlanet-1;
				if( currentPlanet == -1 ) currentPlanet = 9 ;
				setCameraSubject( (currentPlanet) % 10 );
				break;

			case 69:		// "E"
			case 101:		// "e"
				currentPlanet = currentPlanet+1;
				setCameraSubject( (currentPlanet) % 10 );
				break;

			case 9:			// Tab
				Placeholder = subject;
				counter = (counter+1) % 3;
				if( counter == 0 ) 
				{ for( int j = 0; j < 10; j++ )
					{
						subject = planets[j];
						subject -> setTextureOn( true );
						subject -> setWireON( false );
					}
				}
				if( counter == 1 ) 
				{ for( int j = 0; j < 10; j++ )
					{
						subject = planets[j];
						subject -> setTextureOn( false );
						subject -> setWireON( false );
					}
				}
				if( counter == 2 ) 
				{ for( int j = 0; j < 10; j++ )
					{
						subject = planets[j];
						subject -> setTextureOn( false );
						subject -> setWireON( true );
					}
				}
				subject = Placeholder;
				break;

			case 32:		// space
				//resets view
				GlutManager::getInstance()->
					getCamera().setSubject(0,0,0).setRotationEasing(0.125)
						.setZoomEasing(0.125).setMovementEasing(1)
						.setPitch(45).setYaw(315).setDistance(1000);
				setCameraSubject(0);
				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				setCameraSubject(key - '0');
				currentPlanet = key - '0';
				break;

			default:		// Everything else, forward to game manager
				/*current_program::function( key ); */
				break;
		}
	}
}

void SolarSystem::keyUp(unsigned char key, int x, int y) {}

void SolarSystem::keySpecialDown(unsigned char key, int x, int y) {}

void SolarSystem::keySpecialUp(unsigned char key, int x, int y) {}

void SolarSystem::step()
{
	// time += 1;	// 1 to 1 ratio
	time += (FPS * 60 * 60);// * 24);
	update(time);
}

void SolarSystem::update(long long time)
{
	for (Planet* planet : planets)
	{
		planet->update(time);
	}
	if (subject != NULL)
	{
		long double x, y, z;
		subject->getPosition(time, x, y, z);
		GlutManager::getInstance()->getCamera().setSubject(x, y, z);
	}
}
