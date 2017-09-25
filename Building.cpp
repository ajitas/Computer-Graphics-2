#include "Building.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>
#include <FL/math.h>
#include <vector>


GLUquadricObj *IDquadric;
GLUquadricObj *Sphere;
GLUquadricObj *PartialDisk;
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
Building::~Building(void)
{
    if ( initialized )
    {
	glDeleteLists(building_list, 1);
	glDeleteLists(building_list1, 1);
	glDeleteLists(building_list2, 1);
	glDeleteLists(building_list3, 1);
	glDeleteTextures(1, &texture_obj);
	gluDeleteQuadric(IDquadric);
    }
}

// Initializer. Would return false if anything could go wrong.
bool
Building::Initialize(void)
{
	ubyte   *image_data;
    int	    image_height, image_width;

    if ( ! ( image_data = (ubyte*)tga_load("pic1.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Couldn't load pic1.tga\n");
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

	building_list = glGenLists(1);
    glNewList(building_list, GL_COMPILE);
    glColor3f(1.0f, 1.0, 1.0f);

	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glBindTexture(GL_TEXTURE_2D, texture_obj);


    glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);//top
	glVertex3f(5.0f, 5.0f, 15.0f);
	glVertex3f(-5.0f, 5.0f, 15.0f);
	glVertex3f(-5.0f, -5.0f, 15.0f);
	glVertex3f(5.0f, -5.0f, 15.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);//bottom
	glVertex3f(5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);//near
	glTexCoord2f(1.0, 0.0);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(5.0f, 5.0f, 15.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(5.0f, -5.0f, 15.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(5.0f, -5.0f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);//far
	glVertex3f(-5.0f, 5.0f, 15.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, -5.0f, 15.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);//left
	glVertex3f(5.0f, -5.0f, 0.0f);
	glVertex3f(5.0f, -5.0f, 15.0f);
	glVertex3f(-5.0f, -5.0f, 15.0f);
	glVertex3f(-5.0f, -5.0f, 0.0f);

    glEnd();
	glDisable(GL_TEXTURE_2D);
    glEndList();

	if ( ! ( image_data = (ubyte*)tga_load("pic2.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Couldn't load pic2.tga\n");
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

	building_list1 = glGenLists(1);
    glNewList(building_list1, GL_COMPILE);
    glColor3f(1.0f, 1.0, 1.0f);

	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glBindTexture(GL_TEXTURE_2D, texture_obj);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);//right
	glTexCoord2f(1.0, 1.0);
	glVertex3f(5.0f, 5.0f, 15.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-5.0f, 5.0f, 15.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
    glEndList();


	    if ( ! ( image_data = (ubyte*)tga_load("pic3.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Couldn't load pic3.tga\n");
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

	building_list2 = glGenLists(1);
    glNewList(building_list2, GL_COMPILE);
    glColor3f(1.0f, 1.0, 1.0f);

	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glBindTexture(GL_TEXTURE_2D, texture_obj);


    glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);//top
	glVertex3f(5.0f, 5.0f, 15.0f);
	glVertex3f(-5.0f, 5.0f, 15.0f);
	glVertex3f(-5.0f, -5.0f, 15.0f);
	glVertex3f(5.0f, -5.0f, 15.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);//bottom
	glVertex3f(5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);//near
	glTexCoord2f(1.0, 0.0);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(5.0f, 5.0f, 15.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(5.0f, -5.0f, 15.0f);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(5.0f, -5.0f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);//far
	glVertex3f(-5.0f, 5.0f, 15.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(-5.0f, -5.0f, 0.0f);
	glVertex3f(-5.0f, -5.0f, 15.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);//right
	glVertex3f(5.0f, 5.0f, 15.0f);
	glVertex3f(5.0f, 5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 0.0f);
	glVertex3f(-5.0f, 5.0f, 15.0f);

    glEnd();
	glDisable(GL_TEXTURE_2D);
    glEndList();

	if ( ! ( image_data = (ubyte*)tga_load("pic4.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Couldn't load pic4.tga\n");
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

	building_list3 = glGenLists(1);
    glNewList(building_list3, GL_COMPILE);
    glColor3f(1.0f, 1.0, 1.0f);

	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glBindTexture(GL_TEXTURE_2D, texture_obj);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);//left
	glTexCoord2f(0.0, 0.0);
	glVertex3f(5.0f, -5.0f, 0.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(5.0f, -5.0f, 15.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-5.0f, -5.0f, 15.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-5.0f, -5.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
    glEndList();

    initialized = true;
    return true;
}

// Draw
void
Building::Draw(void)
{
	if ( ! initialized )
	return;

	glPushMatrix();
	glTranslatef(-40, -40, 0);
	glCallList(building_list);
	glCallList(building_list1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-40, 40, 0);
	glCallList(building_list2);
	glCallList(building_list3);
	glPopMatrix();

	ubyte   *image_data;
    int	    image_height, image_width;

	IDquadric=gluNewQuadric();
	gluQuadricNormals(IDquadric, GLU_SMOOTH);
	//gluQuadricTexture(IDquadric, GL_TRUE);
	glPushMatrix();
	glColor3f(0.13f, 0.54, 0.130f);
	gluCylinder(IDquadric,5.0f,0.0f,10.0f,32,32);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

		if ( ! ( image_data = (ubyte*)tga_load("grass1.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Couldn't load grass1.tga\n");
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
	
	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glBindTexture(GL_TEXTURE_2D, texture_obj);
	Sphere = gluNewQuadric();
	gluQuadricNormals(Sphere,GLU_SMOOTH);
	gluQuadricTexture(Sphere, GL_TRUE);
	glPushMatrix();
	glTranslatef(15.0,-40.0,3.0);
	gluSphere(Sphere,3.0f,32,32);
	//glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	Sphere = gluNewQuadric();
	gluQuadricNormals(Sphere,GLU_SMOOTH);
	gluQuadricTexture(Sphere, GL_TRUE);
	glPushMatrix();
	glTranslatef(15.0,40.0,3.0);
	gluSphere(Sphere,3.0f,32,32);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	/*if ( ! ( image_data = (ubyte*)tga_load("grass.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
	fprintf(stderr, "Couldn't load grass.tga\n");
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
	
	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
	glBindTexture(GL_TEXTURE_2D, texture_obj);

	PartialDisk =gluNewQuadric();
	gluQuadricNormals(PartialDisk,GLU_SMOOTH);
	gluQuadricTexture(PartialDisk, GL_TRUE);
	glPushMatrix();
	glColor3f(1.0f, 1.0, 1.0f);
	glRotatef(270,0,1.0,0);
	glRotatef(180,1.0,0,0.0);
	glTranslatef(0.0,0.0,50.0);
	gluPartialDisk(PartialDisk,20.0f,22.0,32,10,0,180);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();*/


	glPushMatrix();//tree1
	glColor3f(0.54f, 0.35, 0.0f);
	glTranslatef(8,40,0);
	gluCylinder(IDquadric,0.6f,0.6f,5.0f,32,32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.13f, 0.54, 0.130f);
	glTranslatef(8,40,4);
	gluCylinder(IDquadric,2.0f,0.0f,9.0f,32,32);
	glPopMatrix();

	glPushMatrix();//tree2
	glColor3f(0.54f, 0.35, 0.0f);
	glTranslatef(8,-40,0);
	gluCylinder(IDquadric,0.6f,0.6f,5.0f,32,32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.13f, 0.54, 0.130f);
	glTranslatef(8,-40,4);
	gluCylinder(IDquadric,2.0f,0.0f,9.0f,32,32);
	glPopMatrix();

	glPushMatrix();//tree3
	glColor3f(0.54f, 0.35, 0.0f);
	glTranslatef(22,40,0);
	gluCylinder(IDquadric,0.6f,0.6f,5.0f,32,32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.13f, 0.54, 0.130f);
	glTranslatef(22,40,4);
	gluCylinder(IDquadric,2.0f,0.0f,9.0f,32,32);
	glPopMatrix();

	glPushMatrix();//tree4
	glColor3f(0.54f, 0.35, 0.0f);
	glTranslatef(22,-40,0);
	gluCylinder(IDquadric,0.6f,0.6f,5.0f,32,32);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.13f, 0.54, 0.130f);
	glTranslatef(22,-40,4);
	gluCylinder(IDquadric,2.0f,0.0f,9.0f,32,32);
	glPopMatrix();

}




