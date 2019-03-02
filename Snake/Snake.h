#pragma once
#include <deque>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include<iostream>
#include"BFS.h"
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

using namespace std;

class Snake;

class Map //��ͼ��Ϣ����
{
public:
	
	void Init_map();//��ͼ��ʼ��
	void draw_map(int _x=3,int _y=3);//��ͼ����
	bool is_gameover();//������ʾ
	
};
class Food//ʳ��
{
private:
	COORD _food;
public:
	void rand_food(deque<COORD> & coord);//���ʳ��
	COORD GetFoodCoordinate()//����ʳ������
	{
		return _food;
	}
};
class Snake //�ߵ�������ƶ�
{
private:
	COORD head;//ͷ
	int dir;//����
	int cmps = 4;
	
	BFS AISnake;
	int direction[4][2] = { { 0,1 },{ 0,-1 },{ 1,0 },{ -1,0 } };
	bool map[21][21];
public:
	int speed = 500;
	bool gamemode;//��Ϸģʽ
	deque<COORD> body;//˫�˶�����

	bool eat_food(Food &f);//��ʳ
	void dis_score(int &speed);//��ӡ�ٶȳ���
	void move_snake(deque<COORD> &_snake, Food &food);//�ƶ��ĺ���
	void hit_kb();//���ܼ���
	bool alive(COORD s);//�������
	void init_sanke(int x = 12, int y = 12);
	void game_mode();
	void AI_find_path(Food &f);
	COORD tran_c(COORD pre_c);//����ת��
	COORD retran_c(COORD _c);
};