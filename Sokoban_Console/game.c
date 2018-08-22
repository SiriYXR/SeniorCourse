#include"function.h"

void init() {

	//该段代码功能是隐藏光标，调用了win32编程接口，不需要掌握
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//获取窗口句柄
	CONSOLE_CURSOR_INFO cci;//实列化一个控制台光标信息类
	GetConsoleCursorInfo(hOut, &cci);//获取光标信息
	cci.bVisible = FALSE;//隐藏光标
	SetConsoleCursorInfo(hOut, &cci);//设置光标信息

	system("title 推箱子1.0");//设定窗口名称
	system("mode con cols=120 lines=30");//设定窗口大小
}

void mainloop() {
	int level;//当前关卡
	int level_option;//选择的关卡
	int scenes;//场景
	char option;//操作指令
	int isEnd;//是否结束

	//初始化参数
	level = 0;//初始化当前关卡为第一关（从0算起，范围为0-maps_num）
	level_option = 1;//初始化选择关卡为第一关（从1算起）
	scenes = 0;//初始化场景为主界面
	isEnd = 0;//初始化结束判断变量为0（false）

	//绘制界面
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

	//主菜单2
	char menu2[50][50] = {
		"\n\n\n\n\n\n\n\n",
		"\t\t\t\t\t\t\t 推箱子\n",
		"\t\t\t\t\t\t   |===============|",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |   从头开始(A) |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    选关(X)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |    返回(R)    |",
		"\t\t\t\t\t\t   |               |",
		"\t\t\t\t\t\t   |===============|"
	};


	//开始消息循环
	while (1) {//条件永远为真，无限循环

		//界面打印
		system("cls");//清空屏幕
		switch (scenes) {
		case 0:
			//打印主界面
			for (int i = 0; i < 11; i++)
				puts(main_interface[i]);
			break;
		case 1:
			//打印主菜单2
			for (int i = 0; i < 11; i++)
				puts(menu2[i]);
			break;
		case 2:
			//打印关卡选择界面
			printf("\n\n\n\n\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t\t");
			printf("请选择关卡(1-%d):%d", maps_num, level_option);
			break;
		default:
			break;
		}

		//按键输入
		if (scenes < 3) {
			option = getch();//获取键盘输入
			option = tolower(option);//如果输入是字母则变为小写
		}

		//事件判定
		switch (scenes) {
		case 0://主界面事件判定
			if (option == 's')//如果输入为's',则进入主菜单2
				scenes = 1;
			else if (option == 27) {//如果输入为esc（27），则退出游戏
				isEnd = 1;
			}
			break;
		case 1://主菜单2事件判定
			if (option == 'r' || option == 27)//返回上级菜单
				scenes = 0;
			else if (option == 'a') {//从第一关开始游戏
				scenes = 3;
			}
			else if (option == 'x') {//进入关卡选择界面
				scenes = 2;
			}
			break;
		case 2://关卡选择界面事件判定
			   //如果level_option大于1则减小1，如果level_option小于maps_num则增加1，加入该判断以防止越界
			if ((option == 'a') && level_option > 1)
				level_option--;
			else if ((option == 'd') && level_option < maps_num)
				level_option++;
			else if ((option == 13 || option == 32)) {//如果输入为空格（32）或回车（13）则进入选择的关卡
				level = level_option - 1;//将当前关卡更新为选择的关卡，其对应关系为 level = level_option - 1
				scenes = 4;
			}
			else if (option == 27)
				scenes = 1;
			break;
		case 3://从头开始
			level = 0;
			scenes = gameloop(level);//进入游戏
			break;
		case 4://开始当前关卡
			scenes = gameloop(level);
			break;
		case 5://进入下一关
			level++;
			scenes = 4;
			break;
		case 6://通关重置数据
			scenes = 0;
			level = 0;
			break;
		default:
			break;
		}

		if (isEnd)//如果结束判断变量为1（true）则跳出循环，即退出游戏
			break;
	}
}

int gameloop(int level)
{
	//变量申明

	int x, y;//x 纵坐标, y 横坐标
	int wide;//地图宽度
	int high;//地图高度
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
	wide = 0;
	step_num = 0;
	restep_num = 3;
	option = NULL;
	xnum = ynum = 0;
	isUndo = 0;
	scenes = 0;
	reValue = 0;
	isEnd = 0;

	//读取地图
	LoadMap(level, &high, map);

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
			if (i == high) {
				i = 99;
				break;
			}
		}
	}

	//游戏主循环
	while (1) {

		//界面打印
		system("cls");//清空屏幕
		switch (scenes) {
		case 0:
			//游戏界面
			printf("\n\n\n\n\t\t\t\t\t\t         第%d关", level + 1);
			printf("\n\n");
			for (int i = 0; i <= 17; i++)
			{
				for (int t = 0; t < (120 - wide) / 2; t++)
					printf(" ");
				puts(map[i]);
			}
			printf("\t\t\t\t\t\t步数：%d  剩余撤销次数：%d", step_num, restep_num);
			printf("\n\n\t\t\t\t\t      重玩本关(Q) 撤销(U) 菜单(ESC)");
			break;
		case 1:
			//暂停界面
			printf("\n\n\n\n\n\t\t\t\t\t\t        继续(R)\n");
			if (level == maps_num - 1)//如果当前关卡为最后一关，则不显示"下一关(N)"
				printf("\n\n\t\t\t\t         选关(X)  重玩(Q)  主菜单(M)  \n");
			else
				printf("\n\n\t\t\t\t         选关(X)  重玩(Q)  下一关(N)  主菜单(M)  \n");
			printf("\n\n\n\t\t\t\t\t\t      操作说明");
			printf("\n\n\t\t\t\t\t        W:上  S:下  A:左  D:右");
			printf("\n\n\t\t\t\t\t         @:人  O:箱子  X:终点 ");
			break;
		case 2:
			//过关界面
			if (level == maps_num - 1)//如果当前关卡为最后一关
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t这已经是最后一关了！");
			else
				printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t  过关!");
			printf("\n\n\t\t\t\t\t\t    本关总计步数：%d", step_num);
			if (level == maps_num - 1)
				printf("\n\n\t\t\t\t\t  选关(X)  重玩(Q)  主菜单(M)  \n");
			else
				printf("\n\n\t\t\t\t\t  选关(X)  重玩(Q)  下一关(N)  主菜单(M)  \n");
			break;
		default:
			break;
		}

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
				}
			}
			else if (option == 'u') {
				//撤销一步
				if (isUndo && restep_num >0) {

					map[x][y] = ' ';//将角色当前位置更新为空地（如果该位置应该为目的地我们将在后续代码进行处理）
					//将角色位置更新为之前存储的位置
					x = last_x;
					y = last_y;
					map[x][y] = '@';//将角色还原的新位置更新为@

					//同理更新箱子的位置
					map[box_x][box_y] = ' ';
					map[box_nx][box_ny] = 'O';

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

	return reValue;//返回reValue
}

void LoadMap(int level, int *map_high, char(*map)[50]) {
	char buffer[256];//字符串缓冲区，用于存放关卡文件路径
	FILE *fp;//用于打开关卡文件的文件指针
	sprintf(buffer, "data\\Map\\%d.txt", level + 1);//通过sprintf函数格式化文件路径为我们要读取的文件
	fp = fopen(buffer, "r");//以只读的形式打开文件
	for (int i = 0;; i++) {//循环读取文件内容，直到达到退出条件
		fgets(map[i], 256, fp);//读取一行字符串
		map[i][strlen(map[i]) - 1] = '\0';//在字符串末尾手动加上结束符'\0'
		if (map[i][1] == '|') {//当字符串第二位出现'|'时表示该行为最后一行，文件读取结束
			map[i][1] = '=';//将该位字符设置为'='
			map_high = i;//记录当前i值为地图的高度
			break;//跳出循环
		}
	}
	fclose(fp);//关闭文件指针
}
