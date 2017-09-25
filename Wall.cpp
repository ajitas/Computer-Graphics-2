#include "Wall.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>
#include <FL/math.h>
#include <vector>



// Normalize a 3d vector.
static void
Normalize_3(float v[3])
{
    double  l = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    if ( l == 0.0 )
	return;

    v[0] /= (float)l;
    v[1] /= (float)l;
    v[2] /= (float)l;
}

// Destructor
Wall::~Wall(void)
{
    if ( initialized )
    {
	glDeleteLists(wall_list, 1);
	glDeleteTextures(1, &texture_obj);
    }
}

// Initializer. Would return false if anything could go wrong.
bool
Wall::Initialize(void)
{
	ubyte   *image_data;
    int	    image_height, image_width;

    if ( ! ( image_data = (ubyte*)tga_load("brick.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Couldn't load brick.tga\n");
	return false;
    }

	glGenTextures(1, &texture_obj);
    glBindTexture(GL_TEXTURE_2D, texture_obj);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width, image_height, 
		      GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

	wall_list = glGenLists(1);
    glNewList(wall_list, GL_COMPILE);

	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glBindTexture(GL_TEXTURE_2D, texture_obj);
   
    glBegin(GL_QUADS);

	glNormal3f(1.0f, 0.0f, 0.0f);//back wall
	glColor3f(1.0f, 1.0, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-50.0f, 50.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-50.0f, 50.0f, 10.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-50.0f, -50.0f, 10.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-50.0f, -50.0f, 0.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);//left wall
	glColor3f(1.0f, 1.0, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-50.0f, -50.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-50.0f, -50.0f, 10.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(50.0f, -50.0f, 10.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(50.0f, -50.0f, 0.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);//right wall
	glColor3f(1.0f, 1.0, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(50.0f, 50.0f, 0.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(50.0f, 50.0f, 10.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-50.0f, 50.0f, 10.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-50.0f, 50.0f, 0.0f);

    glEnd();
	glDisable(GL_TEXTURE_2D);
    glEndList();


    initialized = true;
    return true;
}

// Draw
void
Wall::Draw(void)
{
	if ( ! initialized )
	return;

	glPushMatrix();
	glCallList(ticket_list);
	glEnable(GL_CULL_FACE);
	glCallList(wall_list);
	glPopMatrix();


}




