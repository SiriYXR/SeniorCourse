#include "tests.h"

#include <iostream>

using namespace std;

int main() {

	int key = 0;

	while (true) {
		system("cls");
		cout << "\t\t\t\t\t\t\t示例列表" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "编号\t名称\t\t\t\t\t\t\t\t说明" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "绘图入门" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1\t第一个图形窗口程序\t\t\t\t\t第一个图形窗口程序，学会建立窗口界面" << endl;
		cout << "2\t第一个画图程序\t\t\t\t\t\t学会绘画简单的图形，以及基本概念介绍说明" << endl;
		cout << "3\t色彩的计算\t\t\t\t\t\t学会使用指定绘图颜色，以及更多的画图函数" << endl;
		cout << "4\t颜色填充\t\t\t\t\t\t使用填充颜色，画实心图案" << endl;
		cout << "5\t图形边界和填充\t\t\t\t\t\t分别设置图形边界颜色和填充颜色来绘图" << endl;
		cout << "6\t屏幕背景色\t\t\t\t\t\t设置屏幕的背景色" << endl;
		cout << "7\t文字绘制与文字相关设置" << endl;
		cout << "8\t图形视口裁剪" << endl;
		cout << "9\t使用PIMAGE——抓图，绘画到PIMAGE，PIMAGE到屏幕\t\tPIMAGE的基本使用方法" << endl;
		cout << "10\t使用PIMAGE——图片缩放" << endl;
		cout << "11\t使用PIMAGE——透明，半透明" << endl;
		cout << "12\t用户交互——键盘1" << endl;
		cout << "13\t用户交互——键盘2" << endl;
		cout << "14\t用户交互——鼠标1" << endl;
		cout << "15\t用户交互——鼠标2" << endl;
		cout << "16\t用户交互——字符串数据输入" << endl;
		cout << "17\t更多的文字对齐方式设置" << endl;
		cout << "18\t更多的颜色表示办法(HSV/HSL)" << endl;
		cout << "19\t高级：绘画渐变色/彩虹" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "图形动画入门" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "20\t基础动画一：规范框架\t\t\t\t\t第一个图形动画规范框架示例" << endl;
		cout << "21\t基础动画二：简单平移动画\t\t\t\t简单平移示例" << endl;
		cout << "22\t基础动画三，更丰富的变化与帧率\t\t\t\t平移碰撞加帧率显示示例" << endl;
		cout << "23\t基础动画四，半透明淡入淡出\t\t\t\t透明半透明控制显示示例" << endl;
		cout << "24\t基础动画五，对象封装，使代码更有条理\t\t\t对象封装示例" << endl;
		cout << "25\t基础动画六，利用对象封装，显示多个对象\t\t\t对象封装应用示例" << endl;
		cout << "26\t基础动画七，使用非整数参数，随机色彩，使你的动画更自然\t对象封装复杂应用示例" << endl;
		cout << "27\t基础动画八，使用C++封装你的对象\t\t\t\tC++对象封装示例" << endl;
		cout << "28\t基础动画九，使用场景，更灵活地控制动画\t\t\t场景控制示例" << endl;
		cout << "29\t基础动画十，场景管理下的输入输出控制\t\t\t事实上已经是简单的游戏示例" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "99\t退出" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "请输入要执行示例的编号:" ;

		cin >> key;
		switch (key)
		{
		case 1:
			test1::test();
			break;
		case 2:
			test2::test();
			break;
		case 3:
			test3::test();
			break;
		case 4:
			test4::test();
			break;
		case 5:
			test5::test();
			break;
		case 6:
			test6::test();
			break;
		case 7:
			test7::test();
			break;
		case 8:
			test8::test();
			break;
		case 9:
			test9::test();
			break;
		case 10:
			test10::test();
			break;
		case 11:
			test11::test();
			break;
		case 12:
			test12::test();
			break;
		case 13:
			test13::test();
			break;
		case 14:
			test14::test();
			break;
		case 15:
			test15::test();
			break;
		case 16:
			test16::test();
			break;
		case 17:
			test17::test();
			break;
		case 18:
			test18::test();
			break;
		case 19:
			test19::test();
			break;
		case 20:
			test20::test();
			break;
		case 21:
			test21::test();
			break;
		case 22:
			test22::test();
			break;
		case 23:
			test23::test();
			break;
		case 24:
			test24::test();
			break;
		case 25:
			test25::test();
			break;
		case 26:
			test26::test();
			break;
		case 27:
			test27::test();
			break;
		case 28:
			test28::test();
			break;
		case 29:
			test29::test();
			break;
		case 99:
			return 0;
			break;
		default:
			break;
		}

	}

	return 0;
}