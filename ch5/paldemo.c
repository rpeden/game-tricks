#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <bios.h>
#include <fcntl.h>
#include <memory.h>
#include <math.h>
#include <string.h>

#define VGA256              0x13
#define TEXT_MODE           0x03
#define PALETTE_MASK        0x3c6
#define PALETTE_REGISTER    0x3c8
#define PALETTE_DATA        0x3c9

#define SCREEN_WIDTH        (unsigned int)320
#define SCREEN_HEIGHT       (unsigned int)200