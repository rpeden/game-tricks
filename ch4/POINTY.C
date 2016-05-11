#include <stdio.h>
#include <graph.h>

void main(void)
{
    int x, y, color, index;
    
    _setvideomode(_VRES16COLOR);
    
    //draw 10,000 points
    for(index = 0; index < 10000; index++)
    {
        x = rand() % 640;
        y = rand() % 480;
        color = rand() % 16;
        _setcolor(color);
        _setpixel(x,y);
    }
    
    while(!kbhit()) {}
    
    _setvideomode(_DEFAULTMODE);
}
