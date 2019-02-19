#include <iostream>
#include <stdlib.h>
#include <string>
#include <deque>
#include <ctime>
#include <conio.h>
#include <Windows.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


using namespace std;
class Map;
class snake;
class Food;
int speed=500;//速度

//到坐标位置
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x; c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//到坐标位置
void gotocoord(COORD c)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取输出句柄

class Map{
public:

	void Init_map()//地图初始化
	{
		SetConsoleTitleA("我的贪吃蛇");//标题
		COORD dSiz = { 80, 25 };
		SetConsoleScreenBufferSize(handle, dSiz);//设置窗口缓冲区大小
		CONSOLE_CURSOR_INFO ptr = { 1, FALSE };//设置光标大小，隐藏光标
		SetConsoleCursorInfo(handle, &ptr);
		system("color 0f");//设置画布颜色
		srand((unsigned int)time(0));
	}
	void draw_map()//地图绘制
	{
		
		system("cls");//清屏

		//左边框
		for (int i = 0; i < 23; i++)
		{
			cout << endl << " ●";
		}
		//上边框
		gotoxy(3, 1);
		for (int i = 0; i < 21; i++)
		{
			cout << "●";
		}
		//下边框
		gotoxy(3, 23);
		for (int i = 0; i < 21; i++)
		{
			cout << "●";
		}
		//右边框
		for (SHORT i = 1; i <= 23; i++)
		{
			gotoxy(45, i);
			cout << "●";
		}
	}
	void map_info(int _x=3, int _y=3)
	{
		SetConsoleTextAttribute(handle, 0xA);//设置文本颜色
		gotoxy(_x + 47, _y + 0);
		cout << "■游戏说明：";
		gotoxy(_x + 51, _y + 2);
		cout << "自动加速";
		gotoxy(_x + 51, _y + 3);
		cout << "断尾求生：0";
		gotoxy(_x + 47, _y + 5);
		cout << "■操作说明：";
		gotoxy(_x + 51, _y + 7);
		cout << "向左移动：← A";
		gotoxy(_x + 51, _y + 8);
		cout << "向右移动：→ D";
		gotoxy(_x + 51, _y + 9);
		cout << "向下移动：↓ S";
		gotoxy(_x + 51, _y + 10);
		cout << "向上移动：↑ W";
		gotoxy(_x + 51, _y + 11);
		cout << "控制加速：+";
		gotoxy(_x + 51, _y + 12);
		cout << "暂停游戏：空格";
		gotoxy(_x + 51, _y + 13);
		cout << "继续游戏：任意键";
		gotoxy(_x + 47, 22);
		cout << "By:     kailvn";
		gotoxy(_x + 53, 23);
		cout << "version 1.7";
	}
	void is_gameover()
	{

		gotoxy(17, 11);
		SetConsoleTextAttribute(handle, 0x0f);
		cout << "您这水平...";
		gotoxy(17, 12);
		cout << "建议您还是去学习吧!";
		SetConsoleTextAttribute(handle, 0x0f);

	}
	bool restart()
	{
		gotoxy(17, 14);
		SetConsoleTextAttribute(handle, 0x0a);
		cout << "Y 学习重要/N 信你个鬼 !";
		char ch = _getch();
		if (ch == 'Y' || ch == 'y')return false;
		return true;
	}
};
class Food {

public:
    COORD _food;
	void rand_food(deque<COORD> & coord)//随机食物
	{
		_food.X = 2*rand() % (20) + 3;
		_food.Y = rand() % (20) + 2;
		unsigned int i;
		//食物出现在蛇的位置上,重新生成
		for (i = 0; i < coord.size(); i++)
		{
			
			if (coord[i].X == _food.X && coord[i].Y == _food.Y)
			{
				_food.X = 2*rand() % (20) + 3;
				_food.Y = rand() % (20) + 2;
				i = 0;
			}
		}
		gotoxy(_food.X,_food.Y);
		SetConsoleTextAttribute(handle, 0x0C);
		cout << "◆";
	}
	COORD GetFoodCoordinate()//返回食物坐标
	{
		return _food;
	}
};

class snake {
public:
	deque<COORD> body;//双端队列型
	COORD head;//头
	int dir;//方向
	int cmps = 2;
	snake()//构造函数，初始化
	{
		head.X = 12;
		head.Y = 12;
		body.push_back(head);
		head.X++;
		body.push_back(head);
		
		for (unsigned int i = 0; i < body.size(); i++)
		{
			gotoxy(body[i].X, body[i].Y);
			SetConsoleTextAttribute(handle, 0x0B);
			cout << "■";
		}

	}
		
	bool eat_food(Food &f)//进食
	{   
		COORD _f=f.GetFoodCoordinate();
		if (_f.X == body.back().X && _f.Y == body.back().Y)
		{
			return true;
		}
		else return false;
	}
	void dis_speed(int &speed)//打印速度长度
	{
		int _x = 3, _y = 5;
		
		gotoxy(_x + 47, _y + 13);
		cout<< "◆ 移动速度： ";
		cout << 100-speed/10+1 ;
		gotoxy(_x + 47, _y + 14);
		cout << "◆ 当前积分： ";
		cout <<body.size();
		if (body.size() > cmps)
		{
			speed -= 14;
			cmps += 2;
		}
		/*if (body.size() > cmps/speed)
		{
			cmps -= 20;
			speed -= 5;
		}*/
	}
	void move_snake(deque<COORD> &_snake)//移动的函数
	{

		hit_kb();//接收按键

		head = body.back();

		switch (this->dir)
		{
		case UP:
			head.Y--;
			break;
		case DOWN:
			head.Y++;
			break;
		case LEFT:
			head.X-=2;
			break;
		case RIGHT:
			head.X+=2;
			break;

		default:
			head.Y++;
		}

		SetConsoleTextAttribute(handle, 0x0B);
		_snake.push_back(head);
		
	}
	void hit_kb()
	{
		char ch;

		if (_kbhit())				
		{
			ch = _getch();	//使用 getch 函数获取键盘输入 
			switch (ch)
			{
			case 'w':
			case 'W':
			case '8':
				if (this->dir == DOWN)
					break;
				this->dir = UP;
				break;
			case 's':
			case 'S':
			case '2':
				if (this->dir == UP)
					break;
				this->dir = DOWN;
				break;
			case 'a':
			case 'A':
			case '4':
				if (this->dir == RIGHT)
					break;
				this->dir = LEFT;
				break;
			case 'd':
			case 'D':
			case '6':
				if (this->dir == LEFT)
					break;
				this->dir = RIGHT;
				break;
			case '+':
				if (speed > 25)
				{
					speed -= 50;
				}
				break;
			case '-':
				if (speed < 100)
				{
					speed += 25;
				}
				break;
			case ' ':
				gotoxy(1, 24);
				SetConsoleTextAttribute(handle, 0x0);
				system("pause");
			case '0':
				if (this->body.size() <= 2)
					break;
				cout << ' ';
				this->body.pop_front();
				speed += 50;
				break;
			}
		
		}
	}
	bool alive(COORD s)//检测死亡
	{
		//边界
		if (s.Y <= 1 || (s.Y >= 23) || (s.X <= 2) || s.X >= 45)
		{
			return true;
		}
		//自杀
		for (unsigned int i = 0; i < body.size()-1; i++)
		{
			if (body.back().X == body.at(i).X && body.back().Y == body.at(i).Y)
			{
				return true;
			}
			
		}
		return false;
	}

};

int main()
{
	while (true) {
		Map a;
		a.Init_map();
		a.draw_map();
		a.map_info();
		snake s;
		Food f;
		f.rand_food(s.body);
		while (true)
		{
			s.move_snake(s.body);
			if (s.eat_food(f))//有关蛇的增长
			{
				f.rand_food(s.body);
			}
			else
			{
				gotocoord(s.body.front());
				s.body.pop_front();//去尾巴
				cout << ' ';
			}
			if (s.alive(s.body.back()))
			{
				a.is_gameover();
				break;
			}
			SetConsoleTextAttribute(handle, 0xB);
			gotocoord(s.body.back());
			cout << "■";

			SetConsoleTextAttribute(handle, 0xB);
			s.dis_speed(speed);

			Sleep(speed);
		}
		if (!a.restart())break;
		speed=500;
	}
}
		

	