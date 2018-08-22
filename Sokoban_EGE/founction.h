#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<ege.h>
#include <graphics.h>

#include <mmsystem.h>
#include<string>
#pragma comment(lib,"winmm.lib")

#define maps_num 35

void mainloop();
char gameloop(int level);
void main_interface1();
void main_interface2();
void endmovie();
void selectLevel(int level);
void LoadMap(int level, char(*map)[50]);
