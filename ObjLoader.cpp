#include "ObjLoader.h"
#include "libtarga.h"
#include <windows.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <Fl/gl.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Gl_Window.h>
#include <gl/gl.h>
#include <string.h>
        //nothing to explain here
        coordinate::coordinate(float a,float b,float c)
        {
                x=a;
                y=b;
                z=c;
        }
        //nothing to explain here
        face::face(int facen,int f1,int f2,int f3){
                facenum=facen;
                faces[0]=f1;
                faces[1]=f2;
                faces[2]=f3;
                four=false;
        }
        //nothing to explain here
        face::face(int facen,int f1,int f2,int f3,int f4){
                facenum=facen;
                faces[0]=f1;
                faces[1]=f2;
                faces[2]=f3;
                faces[3]=f4;
                four=true;
        }
       
       
 
void objloader::load(const char* filename)
{
        std::ifstream in(filename);     //open the model file
        if(!in.is_open())
        {
                std::cout << "Not opened" << std::endl; //if it's not opened then error message, and return with -1
               
        }
        char buf[2000];  //temp buffer
        int curmat=0;   //the current (default) material is 0, it's used, when we read the faces
        while(!in.eof())
        {
                in.getline(buf,256);    //while we are not in the end of the file, read everything as a string to the coord vector
                coord.push_back(new std::string(buf));
        }
        for(int i=0;i<coord.size();i++) //and then go through all line and decide what kind of line it is
        {
                if((*coord[i])[0]=='#') //if it's a comment
                        continue;       //we don't have to do anything with it
                else if((*coord[i])[0]=='v' && (*coord[i])[1]==' ')     //if a vertex
                {
                        float tmpx,tmpy,tmpz;
                        sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);       //read the 3 floats, which makes up the vertex
                        vertex.push_back(new coordinate(tmpx,tmpy,tmpz));       //and put it in the vertex vector
                }
				else if((*coord[i])[0]=='v' && (*coord[i])[1]=='n')    //if it's a normal vector
                {
                        float tmpx,tmpy,tmpz;
                        sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
                        normals.push_back(new coordinate(tmpx,tmpy,tmpz));      //basically do the same
                        isnormals=true;
                }
				else if((*coord[i])[0]=='f')   //if it's a face
                {
                        int a,b,c,d,e;
                        if(count(coord[i]->begin(),coord[i]->end(),' ')==4)     //if this is a quad
                        {
                                if(coord[i]->find("//")!=std::string::npos)     //if it's contain a normal vector, but not contain texture coorinate
                                {
                                        sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);      //read in this form
                                        faces.push_back(new face(b,a,c,d,e));    //and put to the faces, we don't care about the texture coorinate in this case
                                                                                                                                                                                                                                                                //and if there is no material, it doesn't matter, what is curmat
                                }
								else
								{
                                        //else we don't have normal vectors nor texture coorinate
                                        sscanf(coord[i]->c_str(),"f %d %d %d %d",&a,&b,&c,&d);
                                        faces.push_back(new face(-1,a,b,c,d));          
                                }
                        }
						else
						{  //if it's a triangle
                                                        //do the same, except we use one less vertex/texture coorinate/face number
                                        if(coord[i]->find("//")!=std::string::npos)
                                        {
                                                sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
                                                faces.push_back(new face(b,a,c,d));
                                        }
										else
										{
                                                sscanf(coord[i]->c_str(),"f %d %d %d",&a,&b,&c);
                                                faces.push_back(new face(-1,a,b,c));                                      
                                        }
                        }
				}
		}


        //draw
        GLuint num;
        num=glGenLists(1);      //I generate a unique identifier for the list
        glNewList(num,GL_COMPILE);
		glColor3f(0.421f, 0.48, 0.542f);

        for(int i=0;i<faces.size();i++) //go throught all faces
        {
				if(faces[i]->four)      //if quad
                {
                        glBegin(GL_QUADS);
                                if(isnormals)   //if there are normals
                                        glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);    //use them
                                glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
                        glEnd();
                }
				else
				{
						 glBegin(GL_TRIANGLES);
                                if(isnormals)   //if there are normals
                                        glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
								glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
                        glEnd();
					
                }
        }
        glEndList();
        clean();

	
		glPushMatrix();
		glScalef(5,5,5);
		//glRotatef(90, 1.0f, 0.0f, 0.0f);
		glTranslatef(-11,0,0.5);
		glCallList(num); 
		glPopMatrix();
		
		

		

       
}
 
void objloader::clean()
{
        //delete all the dynamically allocated memory
        for(int i=0;i<coord.size();i++)
                delete coord[i];
        for(int i=0;i<faces.size();i++)
                delete faces[i];
        for(int i=0;i<normals.size();i++)
                delete normals[i];
        for(int i=0;i<vertex.size();i++)
                delete vertex[i];
     
        //and all elements from the vector
        coord.clear();
        faces.clear();
        normals.clear();
        vertex.clear();

}
 
objloader::~objloader()
{
      
        for(std::vector<unsigned int>::const_iterator it=lists.begin();it!=lists.end();it++)
        {
                glDeleteLists(*it,1);
        }
}
 

 
objloader::objloader()
{
        //at default we set all booleans to false, so we don't use anything
        isnormals=false;
		
}

