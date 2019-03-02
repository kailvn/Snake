#pragma once
#include <deque>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include<iostream>
//#include"BFS.h"
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

using namespace std;

class Snake;

class Map //地图信息绘制
{
public:
	
	void Init_map();//地图初始化
	void draw_map(int _x=3,int _y=3);//地图绘制
	bool is_gameover();//结束提示
	
};
class Food//食物
{
private:
	COORD _food;
public:
	void rand_food(deque<COORD> & coord);//随机食物
	COORD GetFoodCoordinate()//返回食物坐标
	{
		return _food;
	}
};
class Snake //蛇的主体和移动
{
private:
	COORD head;//头
	int dir;//方向
	int cmps = 4;
	
	/*BFS AISnake;
	int direction[4][2] = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };
	bool map[21][21];*/
public:
	int speed = 500;
	bool gamemode;//游戏模式
	deque<COORD> body;//双端队列型

	bool eat_food(Food &f);//进食
	void dis_score(int &speed);//打印速度长度
	void move_snake(deque<COORD> &_snake, Food &food);//移动的函数
	void hit_kb();//接受键盘
	bool alive(COORD s);//检测死亡
	void init_sanke(int x = 13, int y = 12);
	void game_mode();
	/*void AI_find_path(Food &f);
	COORD tran_c(COORD pre_c);//坐标转换
	COORD retran_c(COORD _c);*/
};
