#include"founction.h"

void mainloop()
{

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

	//开始消息循环
	while (is_run()) {//只要窗口没有关闭，无限循环

			   //界面打印
		switch (scenes) {
		case 0:
			//打印主界面
			main_interface1();
			break;
		case 1:
			//打印主菜单2
			main_interface2();
			break;
		case 2:
			selectLevel(level_option);
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

void main_interface1()
{
	PIMAGE pimg_logo = newimage();
	getimage(pimg_logo, "resources\\image\\logo.jpg", 0, 0);

	//清屏
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	setbkmode(TRANSPARENT);
	putimage(280, 50, pimg_logo);
	setfont(48, 0, "楷体");
	outtextxy(400, 300, "开始(S)");
	outtextxy(380, 400, "退出(ESC)");

	delimage(pimg_logo);
}

void main_interface2()
{
	PIMAGE pimg_logo = newimage();
	getimage(pimg_logo, "resources\\image\\logo.jpg", 0, 0);
	//清屏
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
	setfont(80, 0, "楷体");

	//要使用特殊格式化字符请用outtextrect
	//设置文字背景填充方式为透明，默认为OPAQUE不透明
	setbkmode(TRANSPARENT);
	putimage(280, 50, pimg_logo);

	setfont(48, 0, "楷体");
	outtextxy(360, 300, "从头开始(A)");
	outtextxy(400, 350, "选关(X)");
	outtextxy(400, 400, "返回(R)");

	delimage(pimg_logo);
}

void selectLevel(int level)
{
	//清屏
	cleardevice();

	setcolor(EGERGB(0x40, 0xE0, 0xD0));
	setfillcolor(WHITE);
	bar(0, 595, 1000, 600);
	bar(0, 0, 5, 600);
	bar(995, 0, 1000, 600);

	//文字背景色（注意setbkcolor函数也会同时改变文字背景色）
	setfontbkcolor(EGERGB(0x80, 0x00, 0x80));

	//设置字体，第一个参数是字体的高度（像素），第二个参数是字体的宽度，第二个参数如果为0，就使用默认比例值
	//如果高度为12，即相当于小五号字，或者9磅字，实际的换算就自己完成吧
	setfont(48, 0, "楷体");

	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
	//要使用特殊格式化字符请用outtextrect
	//设置文字背景填充方式为透明，默认为OPAQUE不透明
	setbkmode(TRANSPARENT);
	outtextxy(340, 200, "按A，D键选关");
	char str[20];
	sprintf(str, "关卡:%d", level);
	outtextxy(400, 300, str);
	outtextxy(400, 400, "返回(ESC)");
}