#ifndef _PRESSABLE_H_
#define _PRESSABLE_H_

class Pressable
{
public:
	virtual void keyDown(unsigned char key, int x, int y) = 0;
	virtual void keyUp(unsigned char key, int x, int y) = 0;
	virtual void keySpecialDown(unsigned char key, int x, int y) = 0;
	virtual void keySpecialUp(unsigned char key, int x, int y) = 0;
};

#endif