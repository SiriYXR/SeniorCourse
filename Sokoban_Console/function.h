#include<stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<string.h>

#define maps_num 35

void init();
void mainloop();
int gameloop(int level);
void LoadMap(int level, int *map_high, char(*map)[50]);
