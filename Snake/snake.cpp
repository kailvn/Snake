#include"Snake.h"
using namespace std;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取输出句柄

void gotocoord(int x, int y)//到坐标位置
{
	COORD c;
	c.X = x; c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void gotocoord(COORD c)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void Map::Init_map()
{
	SetConsoleTitleA("我的贪吃蛇");//标题
	COORD dSiz = { 80, 25 };
	SetConsoleScreenBufferSize(handle, dSiz);//设置窗口缓冲区大小
	CONSOLE_CURSOR_INFO ptr = { 1, FALSE };//设置光标大小，隐藏光标
	SetConsoleCursorInfo(handle, &ptr);
	//system("color 0f");//设置画布颜色
	srand((unsigned int)time(0));

}
void Map::draw_map(int _x,int _y)
{
	SetConsoleTextAttribute(handle, 0x0f);//设置文本颜色
	system("cls");//清屏
	//左边框
	for (int i = 0; i < 23; i++)
	{
		cout << endl << " ●";
	}
	//上边框
	gotocoord(3, 1);
	for (int i = 0; i < 21; i++)
	{
		cout << "●";
	}
	//下边框
	gotocoord(3, 23);
	for (int i = 0; i < 21; i++)
	{
		cout << "●";
	}
	//右边框
	for (SHORT i = 1; i <= 23; i++)
	{
		gotocoord(45, i);
		cout << "●";
	}
	SetConsoleTextAttribute(handle, 0x0a);//设置文本颜色
	gotocoord(_x + 47, _y + 0);
	cout << "■游戏说明：";
	gotocoord(_x + 51, _y + 2);
	cout << "自动加速";
	gotocoord(_x + 51, _y + 3);
	cout << "断尾求生：0";
	gotocoord(_x + 47, _y + 5);
	cout << "■操作说明：";
	gotocoord(_x + 51, _y + 7);
	cout << "向左移动：← A";
	gotocoord(_x + 51, _y + 8);
	cout << "向右移动：→ D";
	gotocoord(_x + 51, _y + 9);
	cout << "向下移动：↓ S";
	gotocoord(_x + 51, _y + 10);
	cout << "向上移动：↑ W";
	gotocoord(_x + 51, _y + 11);
	cout << "控制加速：+";
	gotocoord(_x + 51, _y + 12);
	cout << "暂停游戏：空格";
	gotocoord(_x + 51, _y + 13);
	cout << "继续游戏：任意键";
	gotocoord(_x + 47, 22);
	cout << "By:     kailvn";
	gotocoord(_x + 53, 23);
	cout << "version 3.0";
}
void Snake::game_mode()
{
	SetConsoleTextAttribute(handle, 0x6b);
	system("cls");
	gotocoord(50, 22);
	cout << "By:     kailvn";
	gotocoord(56, 23);
	cout << "version 3.0";
	gotocoord(23, 12);
	cout << "选择游戏模式";
	gotocoord(23, 13);
	cout << "1.easy      ";
	gotocoord(23, 14) ;
	cout << "2.normal    " ;
	gotocoord(23, 15);
	cout << "3.difficult ";
	gotocoord(23, 16);
	cout << "4.AI        ";
	
	
	char ch = _getch();
	switch (ch)
	{
	case '1':
		speed = 600;
		gamemode = true;
		break;
	case'2':
		speed = 500;
		gamemode = true;
		break;
	case'3':
		speed = 400;
		gamemode = true;
		break;
	case '4':
		speed = 800;
		gamemode = false;
		break;
	default:
		speed = 800;
		gamemode = true;
		break;
		
	}
}
bool Map::is_gameover()
{
	gotocoord(17, 11);
	SetConsoleTextAttribute(handle, 0x0f);
	cout << "您这水平...";
	gotocoord(17, 12);
	cout << "建议您还是去学习吧!";
	SetConsoleTextAttribute(handle, 0x0f);
	gotocoord(18, 8);
	SetConsoleTextAttribute(handle, 0x0a);
	cout << "Y 学习重要/N 信你个鬼 !";
	char ch = _getch();
	if (ch == 'Y' || ch == 'y')return false;
	return true;
}
void Snake::dis_score(int &speed)
{
	int _x = 3, _y = 5;
	gotocoord(_x + 47, _y + 13);
	cout << "◆ 移动速度： ";
	cout << 100 - speed / 10 + 1;
	gotocoord(_x + 47, _y + 14);
	cout << "◆ 当前长度： ";
	cout << body.size();
	if (speed > 50)
		if (body.size() > cmps)
		{
			speed -= 14;
			cmps += 2;
		}
}
bool Snake::eat_food(Food &f)
{
	COORD _f = f.GetFoodCoordinate();
	if (_f.X == body.back().X && _f.Y == body.back().Y)
	{
		return true;
	}
	else return false;
}
void Snake::hit_kb()
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
			if (this->dir == DOWN)//this指针改变蛇类中dir
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
			gotocoord(1, 24);
			SetConsoleTextAttribute(handle, 0x0);
			system("pause");
			break;
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
bool Snake::alive(COORD s)
{
	//边界
	if (s.Y < 2 || (s.Y >22) || (s.X <3) || s.X >43)
	{
		return true;
	}
	//自杀
	for (unsigned int i = 0; i < body.size() - 1; i++)
	{
		if (body.back().X == body.at(i).X && body.back().Y == body.at(i).Y)
		{
			return true;
		}

	}
	return false;
}
void Snake::move_snake(deque<COORD> &_snake, Food &food)
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
		head.X -= 2;
		break;
	case RIGHT:
		head.X += 2;
		break;

	default:
		head.Y++;
		break;
	}
	SetConsoleTextAttribute(handle, 0x0B);
	_snake.push_back(head);
	
	if (eat_food(food))//有关蛇的增长
	{
		food.rand_food(body);
	}
	else
	{
		gotocoord(body.front());
		body.pop_front();//去尾巴
		cout << ' ';
	}
	SetConsoleTextAttribute(handle, 0xB);
	gotocoord(body.back());
	cout << "■";

	SetConsoleTextAttribute(handle, 0xB);
	dis_score(speed);
}
void Snake::init_sanke(int x, int y)
{
	head.X = 13;
	head.Y = 12;
	body.push_back(head);
	head.Y++;
	body.push_back(head);

	for (unsigned int i = 0; i < body.size(); i++)
	{
		gotocoord(body[i].X, body[i].Y);
		SetConsoleTextAttribute(handle, 0x0B);
		cout << "■";
	}
}
void Food::rand_food(deque<COORD> & coord)
{
	_food.X = 2 * rand() % (20) + 3;
	_food.Y = rand() % (20) + 2;
	unsigned int i;
	//食物出现在蛇的位置上,重新生成
	for (i = 0; i < coord.size(); i++)
	{

		if (coord[i].X == _food.X && coord[i].Y == _food.Y)
		{
			_food.X = 2 * rand() % (20) + 3;
			_food.Y = rand() % (20) + 2;
			i = 0;
		}
	}
	gotocoord(_food.X, _food.Y);
	SetConsoleTextAttribute(handle, 0x0e);
	cout << "■";
}
