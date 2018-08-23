# SeniorCourse
成都大学 信工学院 学长课堂 18级上学期

## 简介
&emsp;&emsp;本项目为成都大学信工学院学长课堂18级上学期课程同步教学资料,本项目程序采用`VS2017`和相应版本`EGE图形库`开发，项目相关资源库文件均包含在项目文件夹中，同时项目属性以相对路径进行配置，以保证同学们下载解压就能正常运行。所以建议同学们下载相同版本的开发软件进行使用，以免发生版本不兼容的问题。随课程进行，一些后续的相关学习资料也会持续更新到项目文件中，方便同学们下载使用。<br>
&emsp;&emsp;本项目除第三方配套教学代码以外，均采用规范编写格式编写，配套详细而丰富的中文注释，极大降低同学们的编程学习难度。<br>
## 项目结构介绍
项目结构如下：<br>
* SeniorCourse
* EGEBase
* Sokoban_Console
* Sokoban_EGE
* library
* doc
### SeniorCourse
&emsp;&emsp;该项目工程为上课教学代码编写演示所用，其下将会保存上课时所写的一些代码草稿。
### EGEBase
&emsp;&emsp;该项目工程为EGE的基础教学代码，来自EGE官方教程，其中包含了29个练习示例和14个demo程序供同学参考学习。课堂上会选讲一些该项目中的重要内容，主要还是需要同学们下来利用课余时间自行学习。

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/tree/master/doc/img/egebase/1.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/tree/master/doc/img/egebase/2.png"/>
</div>

### Sokoban_Console
&emsp;&emsp;本项目修改自[Sokoban1.1](https://github.com/SiriYXR/Sokoban1.1),是一个纯C语言的Win32控制台推箱子游戏，实现了关卡选择，行动撤回等功能。<br>
&emsp;&emsp;由于原项目为我大一上学期时编写，因当时编程经验不足导致代码冗余，没有注释不易理解，算法不够优化等问题。所以现今现版本在尽量保留原有程序C语言风格的基础上做如下修改：
1. 重构程序消息循环架构
2. 优化算法，删除冗余代码
3. 修改变量命名，使其更具语义化
4. 添加详细注释

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_console/1.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_console/2.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_console/3.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_console/4.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_console/5.png"/>
</div>

### Sokoban_EGE
&emsp;&emsp;本项目修改自[Sokoban2.1](https://github.com/SiriYXR/Sokoban2.1)

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_ege/1.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_ege/2.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_ege/3.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_ege/4.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/sokoban_ege/5.png"/>
</div>

### library
&emsp;&emsp;该文件夹中为适配于`VS2017`的`EGE图形库`文件，同时还包含了EGE官方的HTML教学资料和帮助文档以及示例程序源码，是非常重要的学习资料，其中帮助文档为全中文，特别适合新手程序员阅读学习，在今后的编程学习之路上会经常使用一些第三方的库，而其配套文档往往非常复杂且是英文编写，所以学会阅读帮助文档也是变成学习的一个重要技能。<br>
&emsp;&emsp;教程文件位置在`library/ege/man`文件夹下，打开`index.htm`文件即可在浏览器中以网页形式浏览:<br>

<div align=center>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/ege/ege_index.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/ege/ege_test.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/ege/ege_help.png"/>
  <img src="https://github.com/SiriYXR/SeniorCourse/blob/master/doc/img/ege/ege_help2.png"/>
</div>

&emsp;&emsp;**需要注意的是，由于本项目仅配有`VS2017`版本的`EGE图形库`，所以使用`VS2015`,`VS2010`甚至更低版本或者其他品牌IDE的同学需要到[EGE官网](http://xege.org/)去自行下载配置相应版本的EGE图形库。**
### doc
&emsp;&emsp;该文件夹下存储的README所用的图片资源。
