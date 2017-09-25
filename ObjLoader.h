//#include <SDL/SDL.h>
#include <windows.h>
#include <GL/glu.h>
#include <Fl/gl.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <gl/gl.h>
#ifndef OBJLOADER_H
#define OBJLOADER_H
 
//This struct contain 3 floats and a constructor, it's used for vertexes and normal vectors
struct coordinate{
        float x,y,z;
        coordinate(float a,float b,float c);
};
 
//This structure is store every property of a face
struct face{
        int facenum;    //the number of the face (it's start from 1 not 0, so if you use it as an index, subtract 1 from it), it's used for the normal vectors
        bool four;              //if true, than it's a quad else it's a triangle
        int faces[4];   //indexes for every vertex, which makes the face (it's start from 1 not 0, so if you use it as an index, subtract 1 from it)
                                       
        face(int facen,int f1,int f2,int f3);        //constuctor for triangle
        face(int facen,int f1,int f2,int f3,int f4);  //-"- for quad
};
 
//the main class for the object loader
class objloader{
        std::vector<std::string*> coord;        //every line of code from the obj file
        std::vector<coordinate*> vertex;        //all vertexes
        std::vector<face*> faces;                                       //all faces
        std::vector<coordinate*> normals;       //all normal vectors
        std::vector<unsigned int> lists;        //the id for all lists (so we can delete the lists after use it)
        bool isnormals;    //obvious
        void clean(); //free all of the used memory

       
        public:
        objloader();   
        ~objloader();   //free the textures and lists
        void load(const char* filename); //the main model load function

};
 
#endif