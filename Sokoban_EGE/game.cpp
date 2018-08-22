#include"founction.h"

void game_face(int level, int step_num, int restep_num);
void pause();
void lastlevel();
void passlevel(int step_num);


char gameloop(int level)
{
	mciSendString(TEXT("open Boxmove.wav alias Boxmove"), NULL, 0, NULL);

	PIMAGE pimg_wall = newimage();
	PIMAGE pimg_land = newimage();
	PIMAGE pimg_BoxYellow = newimage();
	PIMAGE pimg_BoxRed = newimage();
	PIMAGE pimg_aim = newimage();
	PIMAGE pimg_ManUP1 = newimage();
	PIMAGE pimg_ManUP2 = newimage();
	PIMAGE pimg_ManDOWN1 = newimage();
	PIMAGE pimg_ManDOWN2 = newimage();
	PIMAGE pimg_ManRIGHT1 = newimage();
	PIMAGE pimg_ManRIGHT2 = newimage();
	PIMAGE pimg_ManLEFT1 = newimage();
	PIMAGE pimg_ManLEFT2 = newimage();
	PIMAGE pimg_black = newimage();

	getimage(pimg_wall, "resources\\image\\wall.jpg", 0, 0);
	getimage(pimg_land, "resources\\image\\land.jpg", 0, 0);
	getimage(pimg_BoxYellow, "resources\\image\\BoxYellow.jpg", 0, 0);
	getimage(pimg_BoxRed, "resources\\image\\BoxRed.jpg", 0, 0);
	getimage(pimg_aim, "resources\\image\\aim.jpg", 0, 0);
	getimage(pimg_ManUP1, "resources\\image\\ManUP1.jpg", 0, 0);
	getimage(pimg_ManUP2, "resources\\image\\ManUP2.jpg", 0, 0);
	getimage(pimg_ManDOWN1, "resources\\image\\ManDOWN1.jpg", 0, 0);
	getimage(pimg_ManDOWN2, "resources\\image\\ManDOWN2.jpg", 0, 0);
	getimage(pimg_ManRIGHT1, "resources\\image\\ManRIGHT1.jpg", 0, 0);
	getimage(pimg_ManRIGHT2, "resources\\image\\ManRIGHT2.jpg", 0, 0);
	getimage(pimg_ManLEFT1, "resources\\image\\ManLEFT1.jpg", 0, 0);
	getimage(pimg_ManLEFT2, "resources\\image\\ManLEFT2.jpg", 0, 0);
	getimage(pimg_black, "resources\\image\\black.jpg", 0, 0);
	
	//定义及初始化地图
	char map[50][50];
	LoadMap(level, map);
	
	//变量申明
	//i,t 循环计数器, x 纵坐标, y 横坐标, pass 通关判断条件
	//restep_num 记录每局撤销次数,step_num 记录本局总步数,wide 地图宽度
	int i, t, x, y, pass, restep_num, step_num, wide, high, count;
	//(ch 游戏过程中读取键盘信息, option暂停过程中读取键盘信息及游戏结束返还值,last_step 记录上一步数据)
	char ch, option, last_step;
	//申明两数组，记录终点坐标
	int X_num[50] = { 0 }, Y_num[50] = { 0 }, xnum, ynum;
	//lstep 记录是否撤销过,x_box 记录上一次推箱子前箱的纵坐标子,y_box 记录上一次推箱子前箱的横坐标子, rerestep_num 记录上一次推箱子前所走的步数
	int lstep, x_box, y_box, rerestep_num;

	//初始化变量
	high = wide = step_num = restep_num = pass = 0;
	ch = option = last_step = NULL;
	xnum = ynum = 0;
	lstep = count = 0;

	//初始化起始位置
	for (i = 0; i < 20; i++)
	{
		for (t = 0; map[i][t] != '\0'; t++)
			if (map[i][t] == '@')
			{
				x = i;
				y = t;
				i = 99;
				break;
			}
	}

	//寻找终点坐标
	for (i = 2; i < 20; i++)
	{
		for (t = 2; map[i][t] != '\0'; t++)
		{
			if (map[i][t] == 'X' || map[i][t] == 'Q')
			{
				X_num[xnum] = i;
				Y_num[ynum] = t;
				xnum++;
				ynum++;
			}
			if (map[i][1] == '|')
			{
				i = 99;
				break;
			}
		}
	}
	//计算地图高度
	for (high = 0; high < 20; high++)
		if (map[high][0] != '|')
			break;
	high = (13 - high) / 2;

	//计算地图宽度
	wide = (16 - strlen(map[0])) / 2;

	//打印地图
	game_face(level, step_num, restep_num);
	for (i = 1; i <= 17; i++)
	{
		for (t = 0; t < strlen(map[0]); t++)
		{
			if (map[i][t] == '|' || map[i][t] == '=')
				putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_black);
			if (map[i][t] == ' ')
				putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_land);
			if (map[i][t] == 'O')
				putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_BoxYellow);
			if (map[i][t] == 'Q')
				putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_BoxRed);
			if (map[i][t] == '#')
				putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_wall);
			if (map[i][t] == 'X')
				putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_aim);
			if (map[i][t] == '@')
				if (ch == 'd' || ch == 'D')
				{
					if (count % 5 > 0)
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManRIGHT1);
					else
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManRIGHT2);
				}
				else if (ch == 'a' || ch == 'A')
				{
					if (count % 5 > 0)
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManLEFT1);
					else
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManLEFT2);
				}
				else if (ch == 'w' || ch == 'W')
				{
					if (count % 5 > 0)
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManUP1);
					else
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManUP2);
				}
				else
				{
					if (count % 5 > 0)
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManDOWN1);
					else
						putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManDOWN2);
				}
		}
		if (map[i][1] == '|')
			break;
	}


	//游戏主程序
	for (; is_run(); delay_fps(60))
	{
		fflush(stdin);
		Sleep(100);
		// todo: 逻辑更新
		if (kbhit())
		{
			ch = getch();
			ch = tolower(ch);

			switch (ch)
			{
				//向下移动
			case 's':
				if (map[x + 1][y] == ' ' || map[x + 1][y] == 'X')
				{
					map[x][y] = ' ';
					x++;
					map[x][y] = '@';
					step_num++;
				}
				else if ((map[x + 1][y] == 'O' || map[x + 1][y] == 'Q') && map[x + 2][y] != 'O' && map[x + 2][y] != 'Q' && map[x + 2][y] != '#')
				{
					map[x][y] = ' ';
					x++;
					map[x][y] = '@';
					map[x + 1][y] = 'O';
					lstep = 1;
					x_box = x;
					y_box = y;
					rerestep_num = step_num;
					step_num++;
					last_step = ch;//存储上一步信息

					mciSendString(TEXT("seek Boxmove to 0"), NULL, 0, NULL);
					mciSendString(TEXT("play Boxmove"), NULL, 0, NULL);
				}
				break;
				//向上移动
			case 'w':
				if (map[x - 1][y] == ' ' || map[x - 1][y] == 'X')
				{
					map[x][y] = ' ';
					x--;
					map[x][y] = '@';
					step_num++;
				}
				else if ((map[x - 1][y] == 'O' || map[x - 1][y] == 'Q') && map[x - 2][y] != 'O' && map[x - 2][y] != 'Q' && map[x - 2][y] != '#')
				{
					map[x][y] = ' ';
					x--;
					map[x][y] = '@';
					map[x - 1][y] = 'O';
					lstep = 1;
					x_box = x;
					y_box = y;
					rerestep_num = step_num;
					step_num++;
					last_step = ch;//存储上一步信息

					mciSendString(TEXT("seek Boxmove to 0"), NULL, 0, NULL);
					mciSendString(TEXT("play Boxmove"), NULL, 0, NULL);
				}
				break;
				//向左移动
			case 'a':
				if (map[x][y - 1] == ' ' || map[x][y - 1] == 'X')
				{
					map[x][y] = ' ';
					y--;
					map[x][y] = '@';
					step_num++;
				}
				else if ((map[x][y - 1] == 'O' || map[x][y - 1] == 'Q') && map[x][y - 2] != 'O' && map[x][y - 2] != 'Q' && map[x][y - 2] != '#')
				{
					map[x][y] = ' ';
					y--;
					map[x][y] = '@';
					map[x][y - 1] = 'O';
					lstep = 1;
					x_box = x;
					y_box = y;
					rerestep_num = step_num;
					step_num++;
					last_step = ch;//存储上一步信息

					mciSendString(TEXT("seek Boxmove to 0"), NULL, 0, NULL);
					mciSendString(TEXT("play Boxmove"), NULL, 0, NULL);
				}
				break;
				//向右移动
			case 'd':
				if (map[x][y + 1] == ' ' || map[x][y + 1] == 'X')
				{
					map[x][y] = ' ';
					y++;
					map[x][y] = '@';
					step_num++;
				}
				else if ((map[x][y + 1] == 'O' || map[x][y + 1] == 'Q') && map[x][y + 2] != 'O' && map[x][y + 2] != 'Q'&&map[x][y + 2] != '#')
				{
					map[x][y] = ' ';
					y++;
					map[x][y] = '@';
					map[x][y + 1] = 'O';
					lstep = 1;
					x_box = x;
					y_box = y;
					rerestep_num = step_num;
					step_num++;
					last_step = ch;//存储上一步信息

					mciSendString(TEXT("seek Boxmove to 0"), NULL, 0, NULL);
					mciSendString(TEXT("play Boxmove"), NULL, 0, NULL);
				}
				break;

			case 27://暂停界面
				pause();
				while (ch != 'r')
				{
					ch = getch();
					if (ch == 'x' || ch == 'q' || ch == 'n' || ch == 'm' || ch == 'X' || ch == 'Q' || ch == 'N' || ch == 'M')
					{
						option = ch;
						ch = 27;
						break;
					}
				}
				break;

			case 'q'://重玩
				option = ch;
				break;
			}
		}

		//撤销一步
		if (lstep == 1 && ch == 'b'&&restep_num < 3)
		{
			switch (last_step)
			{
				//返还向下移动
			case 's':
				map[x][y] = ' ';
				map[x_box + 1][y_box] = ' ';
				map[x_box][y_box] = 'O';
				x_box--;
				x = x_box;
				y = y_box;
				map[x][y] = '@';
				step_num = rerestep_num;
				restep_num++;
				lstep = 0;
				break;
				//返还向上移动
			case 'w':
				map[x][y] = ' ';
				map[x_box - 1][y_box] = ' ';
				map[x_box][y_box] = 'O';
				x_box++;
				x = x_box;
				y = y_box;
				map[x][y] = '@';
				step_num = rerestep_num;
				restep_num++;
				lstep = 0;
				break;
				//返还向左移动
			case 'a':
				map[x][y] = ' ';
				map[x_box][y_box - 1] = ' ';
				map[x_box][y_box] = 'O';
				y_box++;
				x = x_box;
				y = y_box;
				map[x][y] = '@';
				step_num = rerestep_num;
				restep_num++;
				lstep = 0;
				break;
				//返还向右移动
			case 'd':
				map[x][y] = ' ';
				map[x_box][y_box + 1] = ' ';
				map[x_box][y_box] = 'O';
				y_box--;
				x = x_box;
				y = y_box;
				map[x][y] = '@';
				step_num = rerestep_num;
				restep_num++;
				lstep = 0;
				break;
			}
		}

		//if (lstep = 1)
		//	last_step = ch;//存储上一步信息

		//还原终点标记
		for (i = 0; X_num[i] != 0; i++)
		{
			if (map[X_num[i]][Y_num[i]] == ' ')
				map[X_num[i]][Y_num[i]] = 'X';
			if (map[X_num[i]][Y_num[i]] == 'O')
				map[X_num[i]][Y_num[i]] = 'Q';
		}



		//中途退出或重玩
		if (ch == 27 || ch == 'q')
		{
			pass = 0;
			break;
		}

		count++;
		if (count == 99)
			count = 0;

		// todo: 图形更新
		// 清屏
		cleardevice();
		//打印地图
		game_face(level, step_num, restep_num);
		for (i = 1; i <= 17; i++)
		{
			for (t = 0; t < strlen(map[0]); t++)
			{
				if (map[i][t] == '|' || map[i][t] == '=')
					putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_black);
				if (map[i][t] == ' ')
					putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_land);
				if (map[i][t] == 'O')
					putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_BoxYellow);
				if (map[i][t] == 'Q')
					putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_BoxRed);
				if (map[i][t] == '#')
					putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_wall);
				if (map[i][t] == 'X')
					putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_aim);
				if (map[i][t] == '@')
					if (ch == 'd' || ch == 'D')
					{
						if (count % 5 > 0)
							putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManRIGHT1);
						else
							putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManRIGHT2);
					}
					else if (ch == 'a' || ch == 'A')
					{
						if (count % 5 > 0)
							putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManLEFT1);
						else
							putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManLEFT2);
					}
					else if (ch == 'w' || ch == 'W')
					{
						if (count % 5 > 0)
							putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManUP1);
						else
							putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManUP2);
					}
					else
					{
						if (count % 5 > 0)
							putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManDOWN1);
						else
							putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManDOWN2);
					}
			}
			if (map[i][1] == '|')
				break;
		}

		//通关条件判定
		for (i = 0; X_num[i] != 0; i++)
		{
			if (map[X_num[i]][Y_num[i]] == 'Q')
				pass++;
		}
		if (pass == xnum)
		{
			pass = 1;
			ch = 27;
			Sleep(1000);
			break;
		}
		else
			pass = 0;
	}

	//判断能否继续下一关
	cleardevice();
	if (option != NULL)
	{
		if (option == 'n')
		{
			if (level == maps_num - 1)
			{
				lastlevel();
				option = 'p';
				Sleep(1500);
				system("cls");
			}
		}

		delimage(pimg_wall);
		delimage(pimg_land);
		delimage(pimg_BoxYellow);
		delimage(pimg_BoxRed);
		delimage(pimg_aim);
		delimage(pimg_ManUP1);
		delimage(pimg_ManUP2);
		delimage(pimg_ManDOWN1);
		delimage(pimg_ManDOWN2);
		delimage(pimg_ManRIGHT1);
		delimage(pimg_ManRIGHT2);
		delimage(pimg_ManLEFT1);
		delimage(pimg_ManLEFT2);
		delimage(pimg_black);
		return option;
	}

	//通关界面
	if (pass == 1)
	{
		passlevel(step_num);
	}
	while (pass == 1)
	{
		option = getch();
		if (option == 27)
			option = 'm';
		if (option == 'n' || option == 'N')
		{
			if (level == maps_num - 1)
			{
				lastlevel();
				option = 'p';
				Sleep(1500);
				cleardevice();
			}
		}
		if (option == 'x' || option == 'q' || option == 'n' || option == 'p' || option == 'm' || option == 'X' || option == 'Q' || option == 'N' || option == 'P' || option == 'M')
		{
			cleardevice();

			delimage(pimg_wall);
			delimage(pimg_land);
			delimage(pimg_BoxYellow);
			delimage(pimg_BoxRed);
			delimage(pimg_aim);
			delimage(pimg_ManUP1);
			delimage(pimg_ManUP2);
			delimage(pimg_ManDOWN1);
			delimage(pimg_ManDOWN2);
			delimage(pimg_ManRIGHT1);
			delimage(pimg_ManRIGHT2);
			delimage(pimg_ManLEFT1);
			delimage(pimg_ManLEFT2);
			delimage(pimg_black);
			return option;
		}
	}

	delimage(pimg_wall);
	delimage(pimg_land);
	delimage(pimg_BoxYellow);
	delimage(pimg_BoxRed);
	delimage(pimg_aim);
	delimage(pimg_ManUP1);
	delimage(pimg_ManUP2);
	delimage(pimg_ManDOWN1);
	delimage(pimg_ManDOWN2);
	delimage(pimg_ManRIGHT1);
	delimage(pimg_ManRIGHT2);
	delimage(pimg_ManLEFT1);
	delimage(pimg_ManLEFT2);
	delimage(pimg_black);
	return option;
}

void game_face(int level, int step_num, int restep_num)
{
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(750, 0, 755, 700);

	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(48, 0, "楷体");
	setbkmode(TRANSPARENT);
	char str[20];
	sprintf(str, "第%d关", level + 1);
	outtextxy(800, 100, str);
	setfont(24, 0, "楷体");
	sprintf(str, "步数：%d", step_num);
	outtextxy(780, 250, str);

	sprintf(str, "剩余撤销次数：%d", 3 - restep_num);
	outtextxy(780, 300, str);

	outtextxy(780, 350, "重玩本关(Q)");
	outtextxy(780, 400, "撤销(B)");
	outtextxy(780, 450, "菜单(M)");
}

void pause()
{
	cleardevice();

	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(48, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(400, 200, "继续(R)");

	setfont(40, 0, "楷体");
	outtextxy(140, 300, "选关(X)");
	outtextxy(320, 300, "重玩(Q)");
	outtextxy(480, 300, "下一关(N)");
	outtextxy(700, 300, "菜单(M)");
}

void lastlevel()
{
	cleardevice();

	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(48, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(280, 250, "这已经是最后一关了！");
}

void passlevel(int step_num)
{
	cleardevice();

	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));
	setfont(60, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(420, 150, "过关！");

	setfont(40, 0, "楷体");
	char str[20];
	sprintf(str, "本关总计步数:%d", step_num);
	outtextxy(350, 250, str);

	setfont(40, 0, "楷体");
	outtextxy(140, 350, "选关(X)");
	outtextxy(320, 350, "重玩(Q)");
	outtextxy(480, 350, "下一关(N)");
	outtextxy(700, 350, "菜单(M)");
}

void LoadMap(int level,char (*map)[50])
{
	char buffer[256];
	FILE *fp;
	sprintf(buffer, "resources/map/%d.txt", level+1);
	fp = fopen(buffer,"r");
	for(int i=0;;i++)
	{
		fgets(map[i], 256, fp);
		if (map[i][1] == '|')
			break;
	}
	fclose(fp);
}
