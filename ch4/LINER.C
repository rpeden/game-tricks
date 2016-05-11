#include <stdio.h>
#include <graph.h>

void main(void)
{
    int x1, y1, x2, y2, color, index;
    
    _setvideomode(_VRES16COLOR);
    
    //draw 10,000 points
    for(index = 0; index < 1000; index++)
    {
        x1 = rand() % 640;
        y1 = rand() % 480;
        x2 = rand() % 640;
        y2 = rand() % 480;
        
        color = rand() % 16;
        
        _setcolor(color);
        _moveto(x1,y1);
        _lineto(x2,y2);
    }
    
    while(!kbhit()) {}
    
    _setvideomode(_DEFAULTMODE);
}
