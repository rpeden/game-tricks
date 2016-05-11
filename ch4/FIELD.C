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

//make the given matrix into an identity matrix
void Make_Identity(matrix_ptr i)
{
    
    i->elem[0][0] = i->elem[1][1] = i->elem[2][2] = 1;
    i->elem[0][1] = i->elem[1][0] = i->elem[1][2] = 0;
    i->elem[2][0] = i->elem[0][2] = i->elem[2][1] = 0;
}

//zero out the given matrix
void Clear_Matrix
{
    i->elem[0][0] = i->elem[1][1] = i->elem[2][2] = 0;
    i->elem[0][1] = i->elem[1][0] = i->elem[1][2] = 0;
    i->elem[2][0] = i->elem[0][2] = i->elem[2][1] = 0;
}

//multiply 1x3 matrix by 3x3 matrix
void Mat_Mul(vertex_ptr v, matrix_ptr m)
{
    float x_new, y_new;
    
    x_new = v->p[0] * m->elem[0][0] + v->p[1] * m->elem[1][0] + m->elem[2][0];
    y_new = v->p[0] * m->elem[0][1] + v->p[1] * m->elem[1][1] + m->elem[2][1];
    
    v->p[X_COMP] = x_new;
    v->p[Y_COMP] = y_new;
}

//multiply each point in object by its scaling matrix
void Scale_Object_Mat(object_ptr obj)
{
    int index;
    
    for(index = 0; index < obj->num_vertices; index++)
    {
        Mat_Mul((vertex_ptr)&obj->vertices[index], (matrix_ptr)&obj->scale);
    }
}

//multiply each point in object by its rotation matrix
void Rotate_Object_Mat(object_ptr obj)
{
    int index;
    
    for(index = 0; index < obj->num_vertices; index++)
    {
        Mat_Mul((vertex_ptr)&obj->vertices[index], (matrix_ptr)&obj->rotation);
    }
}

