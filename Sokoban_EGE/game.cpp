#include"founction.h"

void game_face(int level, int step_num, int restep_num);
void pause();
void lastlevel();
void passlevel(int step_num);


int gameloop(int level)
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
	
	//变量申明

	int x, y;//x 纵坐标, y 横坐标
	int wide;//地图居中偏移宽度
	int high;//地图居中偏移高度
	int count;//计数器
	char option;//游戏过程中读取键盘信息
	int scenes;//当前场景
	int isEnd;//结束判断变量
	int reValue;//返回值，主界面场景

				//定义游戏地图
	char map[50][50] = { 0 };

	//申明两数组，记录终点坐标
	int aim_x[50] = { 0 }, aim_y[50] = { 0 }, xnum, ynum;

	int restep_num;//记录剩余撤销次数
	int step_num;//记录本局总步数
	int isUndo;//记录是否撤销过
	int lastStep_num;//记录上一次推箱子前所走的步数
	int box_x, box_y;//记录上一次推箱子前箱的坐标
	int box_nx, box_ny;//记录上一次推箱子后箱的坐标
	int last_x, last_y;//记录上一次推箱子前角色的坐标

					   //游戏初始化

					   //初始化变量
	count = 0;
	wide = 0;
	step_num = 0;
	restep_num = 3;
	option = NULL;
	xnum = ynum = 0;
	isUndo = 0;
	scenes = 0;
	reValue = 0;
	isEnd = 0;

	//定义音乐对象
	MUSIC mus;
	mus.OpenFile("resources\\music\\Boxmove.wav"); // 打开文件

	//读取地图
	LoadMap(level,map);

	//计算地图宽度
	wide = strlen(map[0]);

	//初始化起始位置
	for (int i = 0; i < 20; i++) {
		for (int t = 0; map[i][t] != '\0'; t++)
			if (map[i][t] == '@') {
				x = i;
				y = t;
				i = 99;
				break;
			}
	}

	//寻找终点坐标
	for (int i = 2; i < 20; i++) {
		for (int t = 2; map[i][t] != '\0'; t++) {
			if (map[i][t] == 'X' || map[i][t] == 'Q') {
				aim_x[xnum] = i;
				aim_y[ynum] = t;
				xnum++;
				ynum++;
			}
			if (map[i][1] == '|') {
				high = i;
				i = 99;
				break;
			}
		}
	}

	//计算地图居中偏移量
	high = (13 - high) / 2;
	wide = (16 - strlen(map[0])) / 2;

	//游戏主循环
	for (; is_run(); delay_fps(60)) {

		//每运行一帧，计数器增加1，每计数到60清零
		if (count > 60)
			count = 0;
		count+=2;
		
		//界面打印
		switch (scenes) {
		case 0:
			//游戏界面
			game_face(level, step_num,restep_num);

			for (int i = 1; i <= 17; i++)
			{
				for (int t = 0; t < strlen(map[0]); t++)
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
						if (option == 'd' )
						{
							if (count > 30 )
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManRIGHT1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManRIGHT2);
						}
						else if (option == 'a' )
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManLEFT1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManLEFT2);
						}
						else if (option == 'w')
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManUP1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManUP2);
						}
						else
						{
							if (count > 30)
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManDOWN1);
							else
								putimage(50 + t * 40 + wide * 40, 20 + i * 40 + high * 40, pimg_ManDOWN2);
						}
				}
				if (map[i][1] == '|')
					break;
			}
			break;
		case 1:
			//暂停界面
			pause();
			break;
		case 2:
			//过关界面
			if(level==maps_num-1)
				lastlevel();
			else
				passlevel(step_num);
			break;
		default:
			break;
		}

		if (kbhit()) {
			//按键输入
			option = getch();//获取按键输入
			option = tolower(option);//如果输入是字母则变为小写

									 //事件判定
			switch (scenes) {
			case 0:
				if (option == 's') {//向下移动
									//当前方是空地或者空目的地时可以移动上去
					if (map[x + 1][y] == ' ' || map[x + 1][y] == 'X') {
						map[x][y] = ' ';//将角色当前位置更新为空地（如果该位置应该为目的地我们将在后续代码进行处理）
						x++;//更新角色位置
						map[x][y] = '@';//将新的位置更新为角色
						step_num++;//移动步数加1
					}
					//如果前方是箱子且箱子相同方向的下一位置不为墙或者箱子时，可以将当前箱子推动上去
					else if ((map[x + 1][y] == 'O' || map[x + 1][y] == 'Q') && map[x + 2][y] != 'O' && map[x + 2][y] != 'Q' && map[x + 2][y] != '#') {
						map[x][y] = ' ';

						//记录推动箱子前角色的坐标
						last_x = x;
						last_y = y;

						x++;

						//记录推动箱子前箱子的坐标
						box_nx = x;
						box_ny = y;

						map[x][y] = '@';
						map[x + 1][y] = 'O';//在角色移动方向的下一位上更新为箱子（如果该位置为目的地，则箱子显示形态我们将在后续代码进行处理）
						isUndo = 1;//将撤销判断变量设置为1（true）表示当前箱子位置为推动后的位置，允许撤销

								   //记录最后一次被推动箱子的坐标
						box_x = x + 1;
						box_y = y;

						lastStep_num = step_num;//记录上一次推箱子前所走的步数
						step_num++;

						mus.Play(0);//播放推动箱子的音频
					}
				}
				else if (option == 'w') {//向上移动
					if (map[x - 1][y] == ' ' || map[x - 1][y] == 'X') {
						map[x][y] = ' ';
						x--;
						map[x][y] = '@';
						step_num++;
					}
					else if ((map[x - 1][y] == 'O' || map[x - 1][y] == 'Q') && map[x - 2][y] != 'O' && map[x - 2][y] != 'Q' && map[x - 2][y] != '#') {
						map[x][y] = ' ';

						//记录推动箱子前角色的坐标
						last_x = x;
						last_y = y;

						x--;

						//记录推动箱子前箱子的坐标
						box_nx = x;
						box_ny = y;

						map[x][y] = '@';
						map[x - 1][y] = 'O';//在角色移动方向的下一位上更新为箱子（如果该位置为目的地，则箱子显示形态我们将在后续代码进行处理）
						isUndo = 1;//将撤销判断变量设置为1（true）表示当前箱子位置为推动后的位置，允许撤销

								   //记录最后一次被推动箱子的坐标
						box_x = x - 1;
						box_y = y;

						lastStep_num = step_num;//记录上一次推箱子前所走的步数
						step_num++;

						mus.Play(0);//播放推动箱子的音频
					}
				}
				else if (option == 'a') {//向左移动
					if (map[x][y - 1] == ' ' || map[x][y - 1] == 'X') {
						map[x][y] = ' ';
						y--;
						map[x][y] = '@';
						step_num++;
					}
					else if ((map[x][y - 1] == 'O' || map[x][y - 1] == 'Q') && map[x][y - 2] != 'O' && map[x][y - 2] != 'Q' && map[x][y - 2] != '#') {
						map[x][y] = ' ';

						//记录推动箱子前角色的坐标
						last_x = x;
						last_y = y;

						y--;

						//记录推动箱子前箱子的坐标
						box_nx = x;
						box_ny = y;

						map[x][y] = '@';
						map[x][y - 1] = 'O';//在角色移动方向的下一位上更新为箱子（如果该位置为目的地，则箱子显示形态我们将在后续代码进行处理）
						isUndo = 1;//将撤销判断变量设置为1（true）表示当前箱子位置为推动后的位置，允许撤销

								   //记录最后一次被推动箱子的坐标
						box_x = x;
						box_y = y - 1;

						lastStep_num = step_num;//记录上一次推箱子前所走的步数
						step_num++;

						mus.Play(0);//播放推动箱子的音频
					}
					break;
				}
				else if (option == 'd') {//向右移动
					if (map[x][y + 1] == ' ' || map[x][y + 1] == 'X') {
						map[x][y] = ' ';
						y++;
						map[x][y] = '@';
						step_num++;
					}
					else if ((map[x][y + 1] == 'O' || map[x][y + 1] == 'Q') && map[x][y + 2] != 'O' && map[x][y + 2] != 'Q'&&map[x][y + 2] != '#') {
						map[x][y] = ' ';

						//记录推动箱子前角色的坐标
						last_x = x;
						last_y = y;

						y++;

						//记录推动箱子前箱子的坐标
						box_nx = x;
						box_ny = y;

						map[x][y] = '@';
						map[x][y + 1] = 'O';//在角色移动方向的下一位上更新为箱子（如果该位置为目的地，则箱子显示形态我们将在后续代码进行处理）
						isUndo = 1;//将撤销判断变量设置为1（true）表示当前箱子位置为推动后的位置，允许撤销

								   //记录最后一次被推动箱子的坐标
						box_x = x;
						box_y = y + 1;

						lastStep_num = step_num;//记录上一次推箱子前所走的步数
						step_num++;

						mus.Play(0);//播放推动箱子的音频
					}
				}
				else if (option == 'u') {
					//撤销一步
					if (isUndo && restep_num > 0) {

						map[x][y] = ' ';//将角色当前位置更新为空地（如果该位置应该为目的地我们将在后续代码进行处理）
										//将角色位置更新为之前存储的位置
						x = last_x;
						y = last_y;
						map[x][y] = '@';//将角色还原的新位置更新为@

										//同理更新箱子的位置
						map[box_x][box_y] = ' ';
						map[box_nx][box_ny] = 'O';

						step_num = lastStep_num;//还原之前所走的步数

						isUndo = 0;//将撤销判断变量设置为0（false）表示当前箱子位置为撤销后的位置，禁止再次撤销
						restep_num--;//剩余可撤销次数减1
					}
				}
				else if (option == 'q') {//重置本局游戏
					reValue = 4;
					isEnd = 1;
				}
				else if (option == 27) {//打开暂停菜单
					scenes = 1;
				}
				break;
			case 1:
				if (option == 'r' || option == 27) {//继续游戏
					scenes = 0;
				}
				else if (option == 'x') {//进入到关卡选择界面，但中途推出关卡选择的话不会继续当前游戏，会回到主菜单
					reValue = 2;
					isEnd = 1;
				}
				else if (option == 'q') {
					reValue = 4;
					isEnd = 1;
				}
				else if (option == 'n' && level != maps_num - 1) {//如果当前不是最后一关，则进入下一关
					reValue = 5;
					isEnd = 1;
				}
				else if (option == 'm') {//返回主菜单
					reValue = 1;
					isEnd = 1;
				}
				break;
			case 2:
				if (option == 'x') {
					reValue = 2;
					isEnd = 1;
				}
				else if (option == 'q') {
					reValue = 4;
					isEnd = 1;
				}
				else if (option == 'n'&&level != maps_num - 1) {
					reValue = 5;
					isEnd = 1;
				}
				else if (option == 'm') {
					reValue = 1;
					isEnd = 1;
				}
				break;
			default:
				break;
			}
		}

		//逻辑更新

		//还原终点标记,处理之前没有处理的问题,该环节一点要在通关条件判定之前进行才能正确判断是否过关
		for (int i = 0; aim_x[i] != 0; i++) {//依次检查终点坐标
			if (map[aim_x[i]][aim_y[i]] == ' ')//如果为' '则更新为'X'
				map[aim_x[i]][aim_y[i]] = 'X';
			if (map[aim_x[i]][aim_y[i]] == 'O')//如果为'O'则更新为'Q'
				map[aim_x[i]][aim_y[i]] = 'Q';
		}

		//通关条件判定
		int count = 0;//记录当前有多少个箱子到达终点坐标
		for (int i = 0; aim_x[i] != 0; i++) {//依次检查终点坐标
			if (map[aim_x[i]][aim_y[i]] == 'Q')//如果该位置为箱子
				count++;//计数器加1
		}
		if (count == xnum) {//如果count等于终点坐标数目，则表示通关
			scenes = 2;
		}

		if (isEnd)
			break;
	}

	mus.Close(); // 关闭音频文件

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
	return reValue;
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

	sprintf(str, "剩余撤销次数：%d", restep_num);
	outtextxy(780, 300, str);

	outtextxy(780, 350, "重玩本关(Q)");
	outtextxy(780, 400, "撤销(U)");
	outtextxy(780, 450, "暂停(ESC)");
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
	outtextxy(700, 300, "主菜单(M)");
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
