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
} vertex, *vertex_ptr;

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
void Clear_Matrix(matrix_ptr m)
{
    m->elem[0][0] = m->elem[1][1] = m->elem[2][2] = 0;
    m->elem[0][1] = m->elem[1][0] = m->elem[1][2] = 0;
    m->elem[2][0] = m->elem[0][2] = m->elem[2][1] = 0;
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

//creates the asteroid field
void Create_Field(void)
{
    int index;
    float angle, c, s, scale;
    
    for(index = 0; index < NUM_ASTEROIDS; index++)
    {
        asteroids[index].num_vertices = 6;
        asteroids[index].color = 1 + (rand() % 13);
        
        asteroids[index].x0    = 41 + (rand() % 599);
        asteroids[index].y0    = 41 + (rand() % 439);
        asteroids[index].x_velocity = -10 + (rand() % 20);
        asteroids[index].y_velocity = -10 + (rand() % 20);

        //clear and set up rotation matrix 
        Make_Identity((matrix_ptr)&asteroids[index].rotation);
        
        angle = (float)(-50 + (float)(rand() % 100)) / 100;
        c = cos(angle);
        s = sin(angle);
        
        asteroids[index].rotation.elem[0][0] = c;
        asteroids[index].rotation.elem[0][1] = -s;
        asteroids[index].rotation.elem[1][0] = s;
        asteroids[index].rotation.elem[1][1] = c;
        
        //clear and set up scaling matrix
        Make_Identity((matrix_ptr)&asteroids[index].scale);

		scale = (float)(rand() % 30) / 10;
        asteroids[index].scale.elem[0][0] = scale;
        asteroids[index].scale.elem[1][1] = scale;
        
        asteroids[index].vertices[0].p[X_COMP] = 4.0;
        asteroids[index].vertices[0].p[Y_COMP] = 3.5;
        asteroids[index].vertices[0].p[N_COMP] = 1;
        
        asteroids[index].vertices[1].p[X_COMP] = 8.5;
        asteroids[index].vertices[1].p[Y_COMP] = -3.0;
        asteroids[index].vertices[1].p[N_COMP] = 1;
        
        asteroids[index].vertices[2].p[X_COMP] = 6;
        asteroids[index].vertices[2].p[Y_COMP] = -5;
        asteroids[index].vertices[2].p[N_COMP] = 1;
        
        asteroids[index].vertices[3].p[X_COMP] = 2;
        asteroids[index].vertices[3].p[Y_COMP] = -3;
        asteroids[index].vertices[3].p[N_COMP] = 1;
        
        asteroids[index].vertices[4].p[X_COMP] = -4;
        asteroids[index].vertices[4].p[Y_COMP] = -6;
        asteroids[index].vertices[4].p[N_COMP] = 1;
        
        asteroids[index].vertices[5].p[X_COMP] = -3.5;
        asteroids[index].vertices[5].p[Y_COMP] = 5.5;
        asteroids[index].vertices[5].p[N_COMP] = 1;
        
        //scale asteroid to proper size
        Scale_Object_Mat((object_ptr)&asteroids[index]);
    }
}

//draws or erases asteroids
void Draw_Asteroids(int erase)
{
    int index, vertex;
    float x0, y0;
    
    for(index = 0; index < NUM_ASTEROIDS; index++)
    {      
        object_ptr ast = &asteroids[index];
        
        if(erase == ERASE)
        {
            _setcolor(0);
        }
        else 
        {
            _setcolor(ast->color);
        }
        
        x0 = ast->x0;
        y0 = ast->y0;
        
        //move to first vertex
        _moveto((int)(x0 + ast->vertices[0].p[X_COMP]),
                (int)(y0 + ast->vertices[0].p[Y_COMP]));
                
		//draw the asteroid
        for(vertex = 1; vertex < asteroids[index].num_vertices; vertex++)
        {
            _lineto((int)(x0 + ast->vertices[vertex].p[X_COMP]),
                    (int)(y0 + ast->vertices[vertex].p[Y_COMP]));
        }

        //draw line back to first vertex
        _lineto((int)(x0 + ast->vertices[0].p[X_COMP]),
                (int)(y0 + ast->vertices[0].p[Y_COMP]));
    }
}

//move the asteroids
void Translate_Asteroids(void)
{
    int index;
    
    for(index = 0; index < NUM_ASTEROIDS; index++)
    {
        object_ptr ast = &asteroids[index];
        ast->x0 += ast->x_velocity;
        ast->y0 += ast->y_velocity;
        
        //check for collision
        if(ast->x0 > 600 || ast->x0 < 40)
        {
            ast->x_velocity = -ast->x_velocity;
            ast->x0 += ast->x_velocity;
        }
        
        if(ast->y0 > 440 || ast->y0 < 40)
        {
            ast->y_velocity = -ast->y_velocity;
            ast->y0 += ast->y_velocity;
        }
    }    
}

void Rotate_Asteroids(void)
{
    int index;
    
    for(index = 0; index < NUM_ASTEROIDS; index++)
    {
        Rotate_Object_Mat(&asteroids[index]);
    }
}

void main(void) 
{
    //srand(time(NULL));
	_setvideomode(_VRES16COLOR);
	Create_Field();
	Draw_Asteroids(DRAW);	
    
    while( !kbhit() ) {
        Draw_Asteroids(ERASE);
        
        Rotate_Asteroids();
        
        Translate_Asteroids();
        
		Draw_Asteroids(DRAW);

        Delay(500);
    }
    
    _setvideomode(_DEFAULTMODE);
}
