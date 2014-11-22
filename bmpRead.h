/*
	***** bmpRead.cc *****

Code to read in a BMP image file.

CSC433/533 Computer Graphics - Fall 2014

Author: John M. Weiss, Ph.D.
Written March 23, 2006.

Ref: based on code from RgbImage.cc (Buss, 3-D Computer Graphics, 2003).
*/

#ifndef __BMPREAD__H__
#define __BMPREAD__H__

// Windoze hacks (JMW 121026)
#if defined(_WIN32)
#  ifndef APIENTRY
#    define APIENTRY
#  endif
#  ifndef WINGDIAPI
#    define WINGDIAPI
#  endif
#endif

#define _CRT_SECURE_NO_WARNINGS

#include <GL/gl.h>
#include <stdio.h>

bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr );
static short readShort( FILE* infile );
static int readLong( FILE* infile );
static void skipChars( FILE* infile, int numChars );
static inline int GetNumBytesPerRow( int NumCols );

#endif