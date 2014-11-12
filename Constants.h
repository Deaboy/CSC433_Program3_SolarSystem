//
//  constants.h
//  CSC433_Program3_SolarSystem
//
//  Created by Daniel Andrus on 2014-11-11.
//  Copyright (c) 2014 Daniel Andrus. All rights reserved.
//

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define FPS		60			// Frames per second
#define MSPF	1000/FPS	// Milliseconds per frame

#ifndef M_PI
#define M_PI	3.14159265358979323846  /* pi */
#endif

#ifndef DEGTORAD
#define DEGTORAD(x) x*M_PI/180.0
#endif

#ifndef RADTODEG
#define RADTODEG(x) x*180.0/M_PI
#endif

#endif
