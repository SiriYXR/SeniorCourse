# Senior Course
成都大学 信工学院 学长课堂 C/C++方向  18级大一上学期

## 简介
&emsp;&emsp;本项目为成都大学信工学院学长课堂`C/C++方向`18级大一上学期课程同步教学资料,随课程进行，一些后续的相关学习资料也会持续更新到项目文件中，方便同学们下载使用。<br>

&emsp;&emsp;该课程将会以使用C语言开发一个控制台版推箱子游戏为主线，围绕该主线讲解使用到的C语言相关语法知识，以及一些拓展内容。带领大家从零基础学习C语言语法、开发软件使用、程序项目设计开发。后期还会教授大家学习使用一个图形库，开发界面色彩丰富，更为酷炫的程序软件。

&emsp;&emsp;本项目除第三方库配套教学代码以外，均采用规范编写格式编写，配套详细而丰富的中文注释，极大降低同学们的编程学习难度。<br>

## 使用说明
&emsp;&emsp;本项目程序采用`VS2017`和相应版本`EGE图形库`开发，项目相关资源库文件均包含在项目文件夹中，同时项目属性以相对路径进行配置，以保证同学们下载解压就能正常运行。所以建议同学们下载相同版本的开发软件进行使用，以免发生版本不兼容的问题。<br>

### IDE下载安装
&emsp;&emsp;[最新版 Visual Studio 微软官网下载链接](https://visualstudio.microsoft.com/zh-hans/?rr=https%3A%2F%2Fdeveloper.microsoft.com%2Fzh-cn%2Fwindows)<br>

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/Instructions/IDEdownload.png"/>
</div>

&emsp;&emsp;下载时请选择`Visual Studio IDE Community(社区版)`,该版本是微软针对于个人或小型开发团队发布的一个免费`IDE(集成开发环境)`编程软件,凭借其强大的调试功能，堪称C++最强开发软件!!!

&emsp;&emsp;[Visual Studio 安装教程文件链接](https://github.com/SiriYXR/SeniorCourse/blob/master/doc/%E5%8F%82%E8%80%83%E8%B5%84%E6%96%99/%E7%8E%AF%E5%A2%83%E9%85%8D%E7%BD%AE/Microsoft%20Visual%20Studio%E5%BF%AB%E9%80%9F%E5%85%A5%E9%97%A8v2.0.docx)`(该文件包含VS2013,VS2015，VS2017安装教程)`<br>

&emsp;&emsp;**Visual Studio安装程序为在线安装，所以安装过程中请保持网络稳定。仅安装编程学习必要的C++组件需要大约8个G,虽然可以选择安装路径，但是大部分核心组件默认必须安装在C盘，所以为了方便后期软件管理，建议使用默认安装路径，将整个程序安装在C盘，安装前请保证C盘空间足够。**<br>

&emsp;&emsp;**`由于后期编程学习还要安装配置大量环境、软件，将会占用大量C盘空间，所以在系统分盘的时候建议C盘保留至少100G，一旦C盘空间分离出去除非使用第三方分盘软件或者重装系统格式化硬盘否则将无法将空闲分区重新分配给C盘！！！`**<br>


### 项目下载
<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/Instructions/download.png"/>
</div>

### 项目使用
<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/Instructions/open.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/Instructions/running.png"/>
</div>

### 其他
&emsp;&emsp;该`github`账号下上传了我从学习编程以来到现在所写的各种大大小小的项目，也欢迎大家下载参考学习，以后还有有更多的项目代码上传到该账号中。感兴趣的同学可以在我的主页`"Follow"`我，成为我的`"Followers"`。(/≧▽≦)/~┴┴<br>

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/Instructions/follow.png"/>
</div>

## 项目结构介绍

### 项目结构如下：<br>
* [doc](#doc)
* [SeniorCourse](#seniorcourse)
* [EGEBase](#egebase)
* [Sokoban_Console](#sokoban_console)
* [Sokoban_EGE](#sokoban_ege)
* [library](#library)

---
### doc
&emsp;&emsp;该文件夹下存储的上课使用的教学课件，提供给同学们课下学习的资料文件以及README所用的图片资源。<br>

#### 目录结构：
* README
* 教学课件
* 参考资料
  * [语法](https://github.com/SiriYXR/SeniorCourse/tree/master/doc/%E5%8F%82%E8%80%83%E8%B5%84%E6%96%99/%E8%AF%AD%E6%B3%95)
  * [算法](https://github.com/SiriYXR/SeniorCourse/tree/master/doc/%E5%8F%82%E8%80%83%E8%B5%84%E6%96%99/%E7%AE%97%E6%B3%95)
  * [数据结构](https://github.com/SiriYXR/SeniorCourse/tree/master/doc/%E5%8F%82%E8%80%83%E8%B5%84%E6%96%99/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84)
  * [其他](https://github.com/SiriYXR/SeniorCourse/tree/master/doc/%E5%8F%82%E8%80%83%E8%B5%84%E6%96%99/%E5%85%B6%E4%BB%96)
  * [环境配置](https://github.com/SiriYXR/SeniorCourse/tree/master/doc/%E5%8F%82%E8%80%83%E8%B5%84%E6%96%99/%E7%8E%AF%E5%A2%83%E9%85%8D%E7%BD%AE)
  * [帮助文档](https://github.com/SiriYXR/SeniorCourse/tree/master/doc/%E5%8F%82%E8%80%83%E8%B5%84%E6%96%99/%E5%B8%AE%E5%8A%A9%E6%96%87%E6%A1%A3)

### SeniorCourse
&emsp;&emsp;该项目工程为上课教学代码编写演示所用，其下将会保存上课时所写的一些代码草稿。

### EGEBase
&emsp;&emsp;该项目工程为EGE的基础教学代码，来自EGE官方教程，其中包含了29个练习示例和14个demo程序供同学参考学习。课堂上会选讲一些该项目中的重要内容，主要还是需要同学们下来利用课余时间自行学习。

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/egebase/1.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/egebase/2.png"/>
</div>

---
### Sokoban_Console
&emsp;&emsp;本项目修改自[Sokoban1.1](https://github.com/SiriYXR/Sokoban1.1),是一个纯C语言的Win32控制台推箱子游戏，实现了关卡选择，行动撤回等功能。<br>

&emsp;&emsp;由于原项目为我大一上学期时编写，因当时编程经验不足导致代码冗余，没有注释不易理解，算法不够优化等问题。所以现今现版本在尽量保留原有程序C语言风格的基础上做如下修改：
1. 重构程序消息循环架构
2. 优化算法，删除冗余代码
3. 修改变量命名，使其更具语义化
4. 添加详细注释

代码文件：<br>

|文件名|说明|
|:---|:---|
|[function.h](https://github.com/SiriYXR/SeniorCourse/blob/master/Sokoban_Console/function.h)|函数前置声明，全局变量声明|
|[main.c](https://github.com/SiriYXR/SeniorCourse/blob/master/Sokoban_Console/main.c)|定义程序入口main()函数|
|[game.c](https://github.com/SiriYXR/SeniorCourse/blob/master/Sokoban_Console/game.c)|定义游戏循环，文件读取等函数|

资源文件：<br>

|文件/文件夹名|说明|
|:---|:---|
|[data/Map](https://github.com/SiriYXR/SeniorCourse/tree/master/Sokoban_Console/data/Map)|存储游戏的地图文件|

<br>

简要流程框图：<br>

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_console/%E6%8E%A8%E7%AE%B1%E5%AD%90%E6%B5%81%E7%A8%8B%E5%9B%BE.png"/>
</div>

运行效果图：<br>

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_console/1.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_console/2.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_console/3.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_console/4.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_console/5.png"/>
</div>

---
### Sokoban_EGE
&emsp;&emsp;本项目修改自[Sokoban2.1](https://github.com/SiriYXR/Sokoban2.1)，采用新版Sokoban_Console算法架构，通过ege图形库实现图形界面显示，游戏音效等功能。

代码文件：<br>

|文件名|说明|
|:---|:---|
|[function.h](https://github.com/SiriYXR/SeniorCourse/blob/master/Sokoban_EGE/founction.h)|函数前置声明，全局变量声明|
|[main.cpp](https://github.com/SiriYXR/SeniorCourse/blob/master/Sokoban_EGE/main.cpp)|定义程序入口main()函数|
|[mainloop.cpp](https://github.com/SiriYXR/SeniorCourse/blob/master/Sokoban_EGE/mainloop.cpp)|实现消息循环，菜单界面等函数|
|[game.cpp](https://github.com/SiriYXR/SeniorCourse/blob/master/Sokoban_EGE/game.cpp)|定义游戏循环，菜单界面，文件读取等函数|

资源文件：<br>

|文件/文件夹名|说明|
|:---|:---|
|[resources/map](https://github.com/SiriYXR/SeniorCourse/tree/master/Sokoban_EGE/resources/map)|地图文件|
|[resources/image](https://github.com/SiriYXR/SeniorCourse/tree/master/Sokoban_EGE/resources/image)|贴图纹理文件|
|[resources/music](https://github.com/SiriYXR/SeniorCourse/tree/master/Sokoban_EGE/resources/music)|音频文件|

<br>

运行效果图：<br>

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_ege/1.jpg"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_ege/2.jpg"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_ege/3.jpg"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_ege/4.jpg"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/sokoban_ege/5.jpg"/>
</div>

---
### library
&emsp;&emsp;该文件夹中为适配于`VS2017`的`EGE图形库`文件，同时还包含了EGE官方的HTML教学资料和帮助文档以及示例程序源码，是非常重要的学习资料，其中帮助文档为全中文，特别适合新手程序员阅读学习，在今后的编程学习之路上会经常使用一些第三方的库，而其配套文档往往非常复杂且是英文编写，所以学会阅读帮助文档也是变成学习的一个重要技能。<br>

&emsp;&emsp;教程文件位置在`library/ege/man`文件夹下，打开`index.htm`文件即可在浏览器中以网页形式浏览:<br>

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/README/ege/ege_index.png"/>
</div>

&emsp;&emsp;**需要注意的是，由于本项目仅配有`VS2017`版本的`EGE图形库`，所以使用`VS2015`,`VS2010`甚至更低版本或者其他品牌IDE的同学需要到[EGE官网](http://xege.org/)去自行下载配置相应版本的EGE图形库。**

