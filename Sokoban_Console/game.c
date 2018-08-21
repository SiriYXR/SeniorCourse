#include"function.h"

char game(int level)
{
	//变量申明
	//i,t 循环计数器, x 纵坐标, y 横坐标, pass 通关判断条件
	//restep_num 记录每局撤销次数,step_num 记录本局总步数,wide 地图宽度
	int i,t, x, y, pass,restep_num,step_num,wide;
	//(ch 游戏过程中读取键盘信息, option暂停过程中读取键盘信息及游戏结束返还值,last_step 记录上一步数据)
	char ch, option,last_step;
	//申明两数组，记录终点坐标
	int X_num[50] = { 0 }, Y_num[50] = { 0 },xnum,ynum;
	//lstep 记录是否撤销过,x_box 记录上一次推箱子前箱的纵坐标子,y_box 记录上一次推箱子前箱的横坐标子, rerestep_num 记录上一次推箱子前所走的步数
	int lstep,x_box,y_box, rerestep_num;
	int map_high;


	//定义及初始化地图
	char map[50][50] = { 0 };
	LoadMap(level, &map_high, map);

	//初始化变量
	wide=step_num = restep_num= pass = 0;
	ch = option =last_step= NULL;
	xnum = ynum = 0;
	lstep = 0;

	//初始化起始位置
	for ( i = 0;i<20; i++)
	{ 
		for (t = 0;map [i][t] != '\0'; t++)
			if (map [i][t] == '@')
			{
				x = i;
				y = t;
				i = 99;
				break;
			}
	}
	
	//寻找终点坐标
	for (i = 2; i<20; i++)
	{
		for (t = 2; map [i][t] != '\0'; t++)
		{
			if (map [i][t] == 'X'|| map [i][t] == 'Q')
			{
				X_num[xnum] = i;
				Y_num[ynum] = t;
				xnum++;
				ynum++;
			}
			if (i==map_high)
			{
				i = 99;
				break;
			}
		}
	}

	//计算地图宽度
	wide = strlen(map [0]);

	//打印地图
	system("cls");
	printf("\n\n\n\n\t\t\t\t\t\t         第%d关",level+1);
	printf("\n\n");
	for (i = 0; i <= 17; i++)
	{
		for ( t = 0; t <(120-wide)/2; t++)
			printf(" ");
		puts(map[i]);
	}
	printf("\t\t\t\t\t\t步数：%d  剩余撤销次数：%d", step_num, 3 - restep_num);
	printf("\n\n\t\t\t\t\t      重玩本关(Q) 撤销(B) 菜单(ESC)");

	//游戏主程序
	while (1)
	{
		ch = getch();
		ch= tolower(ch);
		
		switch (ch)
		{
		//向下移动
		case 's':
			if (map [x + 1][y] == ' ' || map [x + 1][y] == 'X')
			{
				map [x][y] = ' ';
				x++;
				map [x][y] = '@';
				step_num++;
			}
			else if ((map [x + 1][y] == 'O' || map [x + 1][y] == 'Q') && map [x + 2][y] != 'O' && map [x + 2][y] != 'Q' && map [x + 2][y] != '#')
			{
				map [x][y] = ' ';
				x++;
				map [x][y] = '@';
				map [x + 1][y] = 'O';
				lstep = 1;
				x_box = x;
				y_box = y;
				rerestep_num = step_num;
				step_num++;
				last_step = ch;//存储上一步信息
			}
			break;
		//向上移动
		case 'w':
			if (map [x - 1][y] == ' ' || map [x - 1][y] == 'X')
			{
				map [x][y] = ' ';
				x--;
				map [x][y] = '@';
				step_num++;
			}
			else if ((map [x - 1][y] == 'O' || map [x - 1][y] == 'Q') && map [x - 2][y] != 'O' && map [x - 2][y] != 'Q' && map [x - 2][y] != '#')
			{
				map [x][y] = ' ';
				x--;
				map [x][y] = '@';
				map [x - 1][y] = 'O';
				lstep = 1;
				x_box = x;
				y_box = y;
				rerestep_num = step_num;
				step_num++;
				last_step = ch;//存储上一步信息
			}
			break;
		//向左移动
		case 'a':
			if (map [x][y - 1] == ' ' || map [x][y - 1] == 'X')
			{
				map [x][y] = ' ';
				y--;
				map [x][y] = '@';
				step_num++;
			}
			else if ((map [x][y - 1] == 'O' || map [x][y - 1] == 'Q') && map [x][y - 2] != 'O' && map [x][y - 2] != 'Q' && map [x][y - 2] != '#')
			{
				map [x][y] = ' ';
				y--;
				map [x][y] = '@';
				map [x][y - 1] = 'O';
				lstep = 1;
				x_box = x;
				y_box = y;
				rerestep_num = step_num;
				step_num++;
				last_step = ch;//存储上一步信息
			}
			break;
		//向右移动
		case 'd':
			if (map [x][y + 1] == ' ' || map [x][y + 1] == 'X')
			{
				map [x][y] = ' ';
				y++;
				map [x][y] = '@';
				step_num++;
			}
			else if ((map [x][y + 1] == 'O' || map [x][y + 1] == 'Q') && map [x][y + 2] != 'O' && map [x][y + 2] != 'Q'&&map [x][y + 2] != '#')
			{
				map [x][y] = ' ';
				y++;
				map [x][y] = '@';
				map [x][y + 1] = 'O';
				lstep = 1;
				x_box = x;
				y_box = y;
				rerestep_num = step_num;
				step_num++;
				last_step = ch;//存储上一步信息
			}
			break;

		case 27://暂停界面
			system("cls");
			printf("\n\n\n\n\n\t\t\t\t\t\t        继续(R)\n");
			printf("\n\n\t\t\t\t         选关(X)  重玩(Q)  下一关(N)  主菜单(M)  \n");
			printf("\n\n\n\t\t\t\t\t\t      操作说明");
			printf("\n\n\t\t\t\t\t        W:上  S:下  A:左  D:右");
			printf("\n\n\t\t\t\t\t         @:人  O:箱子  X:终点 ");
			while (ch != 'r')
			{
				ch = getch();
				if (ch == 'x' || ch == 'q' || ch == 'n' || ch == 'm'||ch == 'X' || ch == 'Q' || ch == 'N' || ch == 'M')
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

		//撤销一步
		if (lstep == 1 && ch == 'b'&&restep_num<3)
		{
			switch (last_step)
			{
			//返还向下移动
			case 's':
				map [x][y] = ' ';
				map [x_box+1][y_box] = ' ';
				map [x_box][y_box] = 'O';
				x_box--;
				x = x_box;
				y = y_box;
				map [x][y] = '@';
				step_num=rerestep_num;
				restep_num++;
				lstep = 0;
				break;
			//返还向上移动
			case 'w':
				map [x][y] = ' ';
				map [x_box -1][y_box] = ' ';
				map [x_box][y_box] = 'O';
				x_box++;
				x = x_box;
				y = y_box;
				map [x][y] = '@';
				step_num = rerestep_num;
				restep_num++;
				lstep = 0;
				break;
				//返还向左移动
			case 'a':
				map [x][y] = ' ';
				map [x_box][y_box-1] = ' ';
				map [x_box][y_box] = 'O';
				y_box++;
				x = x_box;
				y = y_box;
				map [x][y] = '@';
				step_num = rerestep_num;
				restep_num++;
				lstep = 0;
				break;
				//返还向右移动
			case 'd':
				map [x][y] = ' ';
				map [x_box][y_box + 1] = ' ';
				map [x_box][y_box] = 'O';
				y_box--;
				x = x_box;
				y = y_box;
				map [x][y] = '@';
				step_num = rerestep_num;
				restep_num++;
				lstep = 0;
				break;
			}
		}

		//if (lstep = 1)
		//	last_step = ch;//存储上一步信息

		//还原终点标记
		for ( i = 0;X_num[i]!=0; i++)
		{
			if (map [X_num[i]][Y_num[i]] == ' ')
				map [X_num[i]][Y_num[i]] = 'X';
			if (map [X_num[i]][Y_num[i]] == 'O')
				map [X_num[i]][Y_num[i]] ='Q';
		}

		//打印地图
		if (option != 'q')
		{
			system("cls");
			printf("\n\n\n\n\t\t\t\t\t\t         第%d关", level + 1);
			printf("\n\n");
			for (i = 0; i <= 17; i++)
			{
				for (t = 0; t <(120 - wide) / 2; t++)
					printf(" ");
				puts(map [i]);
			}
			printf("\t\t\t\t\t\t步数：%d  剩余撤销次数：%d", step_num, 3 - restep_num);
			printf("\n\n\t\t\t\t\t      重玩本关(Q) 撤销(B) 菜单(ESC)");
		}

		//通关条件判定
		for (i = 0; X_num[i] != 0; i++)
		{
			if (map [X_num[i]][Y_num[i]] == 'Q')
				pass++;
		}
		if (pass == xnum)
		{
			pass = 1;
			ch = 27;
			break;
		}
		else
			pass = 0;

		//中途退出或重玩
		if (ch == 27||ch=='q')
		{
			pass = 0;
			break;
		}
	}

	//判断能否继续下一关
	system("cls");
	if (option != NULL)
	{
		if (option == 'n')
		{
			if (level == maps_num - 1)
			{
				system("cls");
				printf(" \n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t这已经是最后一关了！");
				option = 'p';
				Sleep(1500);
				system("cls");
			}
		}
		return option;
	}

	//通关界面
	if (pass == 1)
	{
		printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t  过关!");
		printf("\n\n\t\t\t\t\t\t    本关总计步数：%d", step_num);
		printf("\n\n\t\t\t\t\t  选关(X)  重玩(Q)  下一关(N)  主菜单(M)  \n");
	}
	while (pass == 1)
	{
		option= getch();
		if (option == 'm'|| option == 'M')
			option = 'm';
		if (option == 'n'|| option == 'N')
		{
			if (level == maps_num - 1)
			{
				system("cls");
				printf(" \n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t这已经是最后一关了！");
				option = 'p';
				Sleep(1500);
				system("cls");
			}
		}
		if (option == 'x' || option == 'q'  || option == 'n' || option == 'p' || option == 'm' || option == 'X' || option == 'Q' || option == 'N' || option == 'P' || option == 'M')
		{
			system("cls");
			return option;
		}
	}
	return option;
}

void init() {
	//该段代码功能是隐藏光标，调用了win32编程接口，不需要掌握
	{
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取窗口句柄
		CONSOLE_CURSOR_INFO cci;//实列化一个控制台光标信息类
		GetConsoleCursorInfo(hOut, &cci);//获取光标信息
		cci.bVisible = FALSE;//隐藏光标
		SetConsoleCursorInfo(hOut, &cci);//设置光标信息
	}

	system("title 推箱子1.0");//设定窗口名称
	system("mode con cols=120 lines=30");//设定窗口大小
}

void mainloop() {
	int level, level_option, i;
	char option;

	//初始化关卡，操作指令
	level = 0;
	option = 'M';

	//主界面
	char main_interface[50][50] = {
		"\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t 推箱子",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    开始(S)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   退出(ESC)   |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|",
	};

	char menu2[50][50] = {
		"\n\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t 推箱子",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    开始(S)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   退出(ESC)   |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|",
	};



	//开始消息循环
	while(1)//条件永远为真，无限循环
	{
		system("cls");
		for (i = 0; i<11; i++)//打印主界面
			puts(main_interface[i]);

		while (1)
		{
			option = getch();
			if (option == 's' || option == 'S' || option == 27)
				break;
		}
		while (1)
		{
			if (option == 's' || option == 'S')//打印主菜单2
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\n");
				printf("\t\t\t\t\t\t\t 推箱子\n");
				printf("\t\t\t\t\t\t   |===============|\n");
				printf("\t\t\t\t\t\t   |               |\n");
				printf("\t\t\t\t\t\t   |   从头开始(A) |\n");
				printf("\t\t\t\t\t\t   |               |\n");
				printf("\t\t\t\t\t\t   |    选关(X)    |\n");
				printf("\t\t\t\t\t\t   |               |\n");
				printf("\t\t\t\t\t\t   |    返回(R)    |\n");
				printf("\t\t\t\t\t\t   |               |\n");
				printf("\t\t\t\t\t\t   |===============|");
				while (1)
				{
					option = getch();
					if (option == 'a' || option == 'A' || option == 'x' || option == 'X' || option == 'r' || option == 'R')
						break;
				}
			}
			if (option == 'n' || option == 'N')//进入下一关
			{
				system("cls");
				level++;
				option = game(level);//进入游戏
			}
			if (option == 'q' || option == 'Q')//重玩本关
			{
				system("cls");
				option = game(level);//进入游戏
			}
			if (option == 'a' || option == 'A')//从头开始
			{
				system("cls");
				level = 0;
				option = game(level);//进入游戏
			}
			if (option == 'x' || option == 'X')//选关
			{
				while (1)
				{
					system("cls");
					printf("\n\n\n\n\n\n\n\n\n\n\n");
					printf("\t\t\t\t\t\t");
					printf("请输入关卡(1-%d):", maps_num);
					scanf("%d", &level_option);
					if (level_option > 0 && level_option < maps_num + 1)//限定关卡选择范围
					{
						level = level_option - 1;
						option = 'q';
						break;
					}
				}
			}
			if (option == 'p' || option == 'P')//通关重置数据
			{
				option = 'm';
				level = 0;
				break;
			}
			if (option == 'm' || option == 'M' || option == 'r' || option == 'R')//主菜单1选择
			{
				break;
			}
			if (option == 27)//退出程序
				break;
		}
	}
}

void LoadMap(int level,int *map_high, char(*map)[50])
{
	char buffer[256];
	FILE *fp;
	sprintf(buffer, "data\\Map\\%d.txt", level + 1);
	fp = fopen(buffer, "r");
	for (int i = 0;; i++)
	{
		fgets(map[i], 256, fp);
		map[i][strlen(map[i])-1] = '\0';
		if (map[i][1] == '|')
		{
			map[i][1] = '=';
			map_high = i;
			break;
		}
	}
	fclose(fp);
}
