#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <Fl/gl.h>
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

class Building {
private:
	GLubyte building_list;
	GLubyte building_list1;
	GLubyte building_list2;
	GLubyte building_list3;
	GLuint texture_obj;
	bool initialized;
	//GLUquadricObj *quadObj;
	
public:
    // Constructor
	Building(void) { initialized = false;};
	 // Destructor
    ~Building(void);

	 bool    Initialize(void);
	 void    Draw(void);
};
#endif