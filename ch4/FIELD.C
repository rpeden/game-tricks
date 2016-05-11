#include <stdio.h>
#include <graph.h>
#include <math.h>

#define NUM_ASTEROIDS 10
#define ERASE 0
#define DRAW  1

#define X_COMP 0
#define Y_COMP 1
#define N_COMP 2

//vertex
typedef struct vertex_typ
{
    float p[3];   //single point with normalizing vector    
}

//matrix
typedef struct matrix_typ 
{
    float elem[3][3];
} matrix, *matrix_ptr;

//game object
typedef struct object_typ
{
    int num_vertices;
    int color;
    float x0,y0; //position of the object
    float x_velocity;
    float y_velocity;
    matrix scale;
    matrix rotation;
    vertex vertices[16];
} object, *object_ptr;

//globals

object asteroids[NUM_ASTEROIDS];

//////////////////////////////////////////

void Delay(int t)
{
    //eat some cycles
    float x = 1;
    
    while(t-- > 0) 
        x = cos(x);
}

void Make_Identity(matrix_ptr i)
{
    //make the given matrix into an identity matrix
    i->elem[0][0] = i->elem[1][1] = i->elem[2][2] = 1;
    i->elem[0][1] = i->elem[1][0] = i->elem[1][2] = 0;
    i->elem[2][0] = i->elem[0][2] = i->elem[2][1] = 0;
}

void Clear_Matrix

