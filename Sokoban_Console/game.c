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
	int level, level_option,scenes;
	char option;
	int isEnd;

	//初始化参数
	level = 0;
	level_option = 1;
	scenes = 0;
	isEnd = 0;

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
	while (1){//条件永远为真，无限循环

		//界面打印
		system("cls");//清空屏幕
		switch (scenes){
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

		//获取按键输入
		if (scenes < 3) {
			option = getch();
			option = tolower(option);//如果输入是字母则变为小写
		}

		//事件判定
		switch (scenes){
		case 0://主界面事件判定
			if (option == 's')
				scenes = 1;
			else if (option == 27) {
				isEnd = 1;
			}
			break;
		case 1://主菜单2事件判定
			if (option == 'r'|| option == 27)//返回上级菜单
				scenes = 0;
			else if (option == 'a') {
				scenes = 3;
			}
			else if (option == 'x') {
				scenes = 2;
			}
			break;
		case 2://关卡选择界面事件判定
			if ((option == 'a') && level_option > 1)
				level_option--;
			else if ((option == 'd') && level_option < maps_num)
				level_option++;
			else if ((option == 30 || option == 32)) {
				level = level_option - 1;
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

		if (isEnd)
			break;
	}
}

int gameloop(int level)
{
	//变量申明
	//i,t 循环计数器, x 纵坐标, y 横坐标
	//restep_num 记录每局撤销次数,step_num 记录本局总步数,wide 地图宽度
	int x, y,restep_num, step_num, wide;
	//(ch 游戏过程中读取键盘信息,last_step 记录上一步数据)
	char option, last_step;
	//申明两数组，记录终点坐标
	int X_num[50] = { 0 }, Y_num[50] = { 0 }, xnum, ynum;
	//lstep 记录是否撤销过,x_box 记录上一次推箱子前箱的纵坐标子,y_box 记录上一次推箱子前箱的横坐标子, rerestep_num 记录上一次推箱子前所走的步数
	int lstep, x_box, y_box, rerestep_num;
	int map_high;
	int scenes;
	int reValue;
	int isEnd;

	//游戏初始化
	//定义及初始化地图
	char map[50][50] = { 0 };
	LoadMap(level, &map_high, map);

	//初始化变量
	wide = step_num = restep_num = 0;
	option=last_step = NULL;
	xnum = ynum = 0;
	lstep = 0;
	scenes = 0;
	reValue = 0;
	isEnd = 0;

	//初始化起始位置
	for (int i = 0; i < 20; i++){
		for (int t = 0; map[i][t] != '\0'; t++)
			if (map[i][t] == '@'){
				x = i;
				y = t;
				i = 99;
				break;
			}
	}

	//寻找终点坐标
	for (int i = 2; i < 20; i++){
		for (int t = 2; map[i][t] != '\0'; t++){
			if (map[i][t] == 'X' || map[i][t] == 'Q'){
				X_num[xnum] = i;
				Y_num[ynum] = t;
				xnum++;
				ynum++;
			}
			if (i == map_high){
				i = 99;
				break;
			}
		}
	}

	//计算地图宽度
	wide = strlen(map[0]);

	//游戏主循环
	while (1) {

		//界面打印
		system("cls");//清空屏幕
		switch (scenes){
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
			printf("\t\t\t\t\t\t步数：%d  剩余撤销次数：%d", step_num, 3 - restep_num);
			printf("\n\n\t\t\t\t\t      重玩本关(Q) 撤销(B) 菜单(ESC)");
			break;
		case 1:
			//暂停界面
			printf("\n\n\n\n\n\t\t\t\t\t\t        继续(R)\n");
			printf("\n\n\t\t\t\t         选关(X)  重玩(Q)  下一关(N)  主菜单(M)  \n");
			printf("\n\n\n\t\t\t\t\t\t      操作说明");
			printf("\n\n\t\t\t\t\t        W:上  S:下  A:左  D:右");
			printf("\n\n\t\t\t\t\t         @:人  O:箱子  X:终点 ");
			break;
		case 2:
			//过关界面
			if (level == maps_num - 1)
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

		//获取按键输入
		option = getch();
		option = tolower(option);//如果输入是字母则变为小写

		//事件判定
		switch (scenes){
		case 0:
			if (option =='s'){//向下移动
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
					last_step = option;//存储上一步信息
				}
			}
			else if (option == 'w') {//向上移动
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
					last_step = option;//存储上一步信息
				}
			}
			else if (option == 'a') {//向左移动
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
					last_step = option;//存储上一步信息
				}
				break;
			}
			else if (option == 'd') {//向右移动
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
					last_step = option;//存储上一步信息
				}
			}
			else if (option == 'b') {
				//撤销一步
				if (lstep == 1 && restep_num < 3){
					switch (last_step){
					case 's'://返还向下移动
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
					case 'w'://返还向上移动
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
					case 'a'://返还向左移动
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
					case 'd'://返还向右移动
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
			}
			else if (option == 'q') {
				reValue = 4;
				isEnd = 1;
			}
			else if (option == 27) {
				scenes = 1;
			}
			break;
		case 1:
			if (option == 'r'||option==27) {
				scenes = 0;
			}
			else if (option == 'x') {
				reValue = 2;
				isEnd = 1;
			}
			else if (option == 'q') {
				reValue = 4;
				isEnd = 1;
			}
			else if (option == 'n') {
				reValue = 5;
				isEnd = 1;
			}
			else if (option == 'm') {
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

		//还原终点标记
		for (int i = 0; X_num[i] != 0; i++)
		{
			if (map[X_num[i]][Y_num[i]] == ' ')
				map[X_num[i]][Y_num[i]] = 'X';
			if (map[X_num[i]][Y_num[i]] == 'O')
				map[X_num[i]][Y_num[i]] = 'Q';
		}

		//通关条件判定
		int count=0;
		for (int i = 0; X_num[i] != 0; i++){
			if (map[X_num[i]][Y_num[i]] == 'Q')
				count++;
		}
		if (count == xnum){
			scenes = 2;
		}

		if (isEnd)
			break;
	}

	return reValue;
}

void LoadMap(int level, int *map_high, char(*map)[50])
{
	char buffer[256];
	FILE *fp;
	sprintf(buffer, "data\\Map\\%d.txt", level + 1);
	fp = fopen(buffer, "r");
	for (int i = 0;; i++)
	{
		fgets(map[i], 256, fp);
		map[i][strlen(map[i]) - 1] = '\0';
		if (map[i][1] == '|')
		{
			map[i][1] = '=';
			map_high = i;
			break;
		}
	}
	fclose(fp);
}
