#include <stdio.h>
#include <graph.h>

void main(void)
{
	_setvideomode(_VRES16COLOR);

	_setcolor(1);
	_moveto(100,100);
	_lineto(120,120);
	_lineto(150,200);
	_lineto(80,190);
	_lineto(80,60);
	_lineto(100,100);

	while(!kbhit()) {}

	_setvideomode(_DEFAULTMODE);
}
