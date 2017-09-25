#ifndef _WALL_H_
#define _WALL_H_

#include <Fl/gl.h>
#include "libtarga.h"
#include <stdio.h>

class Wall {
private:
	GLubyte wall_list;
	GLubyte ticket_list;
	GLuint texture_obj;
	bool initialized;
	
public:
    // Constructor
	Wall(void) { initialized = false;};
	 // Destructor
    ~Wall(void);

	 bool    Initialize(void);
	 void    Draw(void);
};
#endif