/***************************************************************************//**
 * @author Daniel Andrus
 *
 * @Date	11/7/2014
 *
 * @file File containing the implementation of the Solar System class.
 *
 * @brief creates the Solar System, implementation of solar system class
*******************************************************************************/
/*******************************************************************************
 *                 DECLARATIONS, INCLUDES, AND NAMESPACES
*******************************************************************************/
#include "SolarSystem.h"

/*******************************************************************************
 *                          FUNCTION DEFINITIONS
*******************************************************************************/
/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Constuctor, Initializes the SolarSystem
 *
*******************************************************************************/
SolarSystem::SolarSystem()
{
	time = 0;
	subject = NULL;
	currentPlanet = 0;
	min_zoom = 100;
	speed = 1;
	drag = false;
	help = false;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Destructor, DeathStar effect on all Planets
 *
*******************************************************************************/
SolarSystem::~SolarSystem()
{
	for (Planet* planet : planets)
	{
		delete planet;
	}
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: Sets up Planets and calls glut init functions and camera
 *		functions
 *
 * @param[in] int argc - number of aurguments form commandline
 * @param[in] char *argv[] - array of augments from commandline
 *
 * @returns 0 - no problems
*******************************************************************************/
int SolarSystem::run(int argc, char *argv[])
{
	Planet* sun;
	Planet* earth;
	Planet* temp;
	
	manager.init(argc, argv);

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
			.setColor(29, 85, 112)
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
	manager.registerClickable(this);
	manager.drawObject(this);
	
	// Initialize camera
	manager.getCamera().setSubject(0,0,0).setRotationEasing(0.125)
			.setZoomEasing(0.125).setMovementEasing(1)
			.setPitch(45).setYaw(315).setDistance(1000);
	setCameraSubject(0);
	
	//add entries to our menu
	glutAddMenuEntry("0 - Sun",'0');
	glutAddMenuEntry("1 - Mercury", '1');
	glutAddMenuEntry("2 - Venus", '2');
	glutAddMenuEntry("3 - Earth", '3');
	glutAddMenuEntry("4 - Moon", '4');
	glutAddMenuEntry("5 - Mars", '5');
	glutAddMenuEntry("6 - Jupiter", '6');
	glutAddMenuEntry("7 - Saturn", '7');
	glutAddMenuEntry("8 - Uranus", '8');
	glutAddMenuEntry("9 - Neptune", '9');
	glutAddMenuEntry("H - Help", 'h');

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	// Enter main loop
	manager.run();
	return 0;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: changes what planet camera is viewing
 *
 * @param[in] int i - itterator though planet vector
*******************************************************************************/
void SolarSystem::setCameraSubject(int i)
{
	if (i < (int) planets.size())
	{
		subject = planets[i];
		manager.getCamera().setMinimumDistance(
			subject->getRadius() * PLANET_ZOOM_MIN)
			.setDistance(subject->getRadius() * 4);
	}
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: changes what planet camera is viewing
 *
 * @param[in] unsigned char key - key that was pressed
 * @param[in] int x - x coordinate of mouse when keyboard pressed
 * @param[in] int y - y coordinate of mouse when keyboard pressed
*******************************************************************************/
void SolarSystem::keyDown(unsigned char key, int x, int y)
{
	if (help)
	{
		if (key == 'h' || key == 'H')
		{
			help = false;
			return;
		}
	}
	else
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
			for (Planet* planet : planets)
				planet->cycleDrawMode();
			break;

		case 91:		// '['
		case 123:		// '{'
			if (speed > 1)
			{
				speed /= 2;
			}
			else if (speed <= -1)
			{
				if (speed > -1073741824)
				{
					speed *= 2;
				}
			}
			else
			{
				speed--;
			}
			break;

		case 93:		// ']'
		case 124:		// '}'
			if (speed >= 1)
			{
				if (speed < 1073741824)
				{
					speed *= 2;
				}
			}
			else if (speed < -1)
			{
				speed /= 2;
			}
			else
			{
				speed++;
			}
			break;

		case 32:		//space
			speed = 1;
			break;

		case 90:		// 'Z'
		case 122:		// 'z'
			GlutManager::getInstance()->
				getCamera().setSubject(0,0,0).setRotationEasing(0.125)
					.setZoomEasing(0.125).setMovementEasing(1)
					.setPitch(45).setYaw(315).setDistance(1000);
			setCameraSubject(0);
			break;
		
		case 'h':
		case 'H':
			help = true;
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

		default:
			break;
		}
	}
}

 /***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: handles what happens when key is released, currently
 *			unused
 *
 * @param[in] unsigned char key - key that was pressed
 * @param[in] int x - x coordinate of mouse when keyboard pressed
 * @param[in] int y - y coordinate of mouse when keyboard pressed
*******************************************************************************/
void SolarSystem::keyUp(unsigned char key, int x, int y) {}

 /*************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description:handles what happens when Special key is pressed, currently
 *			unused
 *
 * @param[in] unsigned char key - key that was pressed
 * @param[in] int x - x coordinate of mouse when keyboard pressed
 * @param[in] int y - y coordinate of mouse when keyboard pressed
******************************************************************************/
void SolarSystem::keySpecialDown(unsigned char key, int x, int y) {}

 /*************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: handles what happens when Special key is released,
 *			currently unused
 *
 * @param[in] unsigned char key - key that was pressed
 * @param[in] int x - x coordinate of mouse when keyboard pressed
 * @param[in] int y - y coordinate of mouse when keyboard pressed
******************************************************************************/
void SolarSystem::keySpecialUp(unsigned char key, int x, int y) {}

 /*************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: handles what happens when mouse button is pressed
 *
 * @param[in] int button - button pressed
******************************************************************************/
void SolarSystem::onMouseDown(int button)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		drag = true;
		manager.getCamera().setRotationEasing(1);
	}
}

 /*************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: handles what happens when mouse button is released
 *
 * @param[in] int button - button pressed
******************************************************************************/
void SolarSystem::onMouseUp(int button)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		drag = false;
		manager.getCamera().setRotationEasing(0.125);
	}
}

 /*************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: when mouse is over an object - unused
******************************************************************************/
void SolarSystem::onMouseEnter() {}

/*************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: when mouse leaves an object - unused
******************************************************************************/
void SolarSystem::onMouseLeave() {}

/*************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: zooms out when wheel is spun "up"
******************************************************************************/
void SolarSystem::onMouseScrollUp()
{
	// Zoom in
	manager.getCamera().setDistance(
		manager.getCamera().getDistance() * 0.75);
}

/*************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: zooms in when wheel is spun "down"
******************************************************************************/
void SolarSystem::onMouseScrollDown()
{
	// Zoom out
	manager.getCamera().setDistance(
		manager.getCamera().getDistance() * 1.33333333333);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: moves camera based on mouse drags
 *
 * @param[in] int x - x coordinate of mouse before drag
 * @param[in] int y - y coordinate of mouse before drag
 * @param[in] int x - x coordinate of mouse after drag
 * @param[in] int y - y coordinate of mouse after drag
*******************************************************************************/
void SolarSystem::onMouseMove(int x, int y, int lx, int ly)
{
	if (drag)
	{
		manager.getCamera().setPitch(
			manager.getCamera().getPitch() + (y - ly) / 4.0);
		manager.getCamera().setYaw(
			manager.getCamera().getYaw() + ((lx - x) / 4.0));
	}
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: checks if coords are valid
 *
 * @param[in] double x - x coordinate of mouse
 * @param[in] double y - y coordinate of mouse
 *
 * @return true - in solar system
 * @return false - not in solar system
*******************************************************************************/
bool SolarSystem::containsPoint(double x, double y) const
{
	return true;
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: handles solar system movement based on a time
*******************************************************************************/
void SolarSystem::step()
{
	time += speed;
	update(time);
}

/***************************************************************************//**
 * @author Daniel Andrus, Johnny Ackerman
 * 
 * @par Description: updates time value for all planets
*******************************************************************************/
void SolarSystem::update(long long time)
{
	if (help) return;
	
	for (Planet* planet : planets)
	{
		planet->update(time);
	}
	if (subject != NULL)
	{
		long double x, y, z;
		subject->getPosition(time, x, y, z);
		manager.getCamera().setSubject(x, y, z);
	}
}

/***************************************************************************//**
 * @author Daniel Andrus
 * 
 * @par Description: Draws the current simulation speed or the help box
*******************************************************************************/
void SolarSystem::draw()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	
	string txt;
	if (help)
	{
	
		glColor3ub(0,0,0);
		glRecti(0, 0, 540, 540);
		
		
		txt =
		"Welcome to the Solar System. Sol for short.\n"
		"There are many fun ways to soar through space.\n\n"
		
		"To orbit around a planet, use the WASD keys.\n"
		"You can also use the mouse. Simply left-click on the screen\n"
		"and drag the view around.\n\n"
		
		"To zoom in, use the + key. To zoom out, use the - key. You\n"
		"can also use the scroll wheel on your mouse.\n\n"
		
		"Press TAB to cycle through the display modes: textured,\n"
		"smooth shading, flat shading, and wireframe.\n\n"
		
		"Use the Q and E keys to cycle through the planets, or 0-9 to\n"
		"jump directly to a planet.\n\n"
		
		"Finally, press [ to decrease speed, ] to increase speed, and\n"
		"SPACE to reset speed to real time.\n\n"
		
		"Press H to close.\n\n"
		
		"Oh, and press T for a special surprise!";
	
	}
	else
	{
	
		txt = to_string(speed) + "x";

	}
	
	glColor3ub(255, 255, 255);
	glRasterPos2i(10, 24);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18,
					(const unsigned char *) txt.c_str() );
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

