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
int speed=500;//�ٶ�

//������λ��
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x; c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//������λ��
void gotocoord(COORD c)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ������

class Map{
public:

	void Init_map()//��ͼ��ʼ��
	{
		SetConsoleTitleA("�ҵ�̰����");//����
		COORD dSiz = { 80, 25 };
		SetConsoleScreenBufferSize(handle, dSiz);//���ô��ڻ�������С
		CONSOLE_CURSOR_INFO ptr = { 1, FALSE };//���ù���С�����ع��
		SetConsoleCursorInfo(handle, &ptr);
		system("color 0f");//���û�����ɫ
		srand((unsigned int)time(0));
	}
	void draw_map()//��ͼ����
	{
		
		system("cls");//����

		//��߿�
		for (int i = 0; i < 23; i++)
		{
			cout << endl << " ��";
		}
		//�ϱ߿�
		gotoxy(3, 1);
		for (int i = 0; i < 21; i++)
		{
			cout << "��";
		}
		//�±߿�
		gotoxy(3, 23);
		for (int i = 0; i < 21; i++)
		{
			cout << "��";
		}
		//�ұ߿�
		for (SHORT i = 1; i <= 23; i++)
		{
			gotoxy(45, i);
			cout << "��";
		}
	}
	void map_info(int _x=3, int _y=3)
	{
		SetConsoleTextAttribute(handle, 0xA);//�����ı���ɫ
		gotoxy(_x + 47, _y + 0);
		cout << "����Ϸ˵����";
		gotoxy(_x + 51, _y + 2);
		cout << "�Զ�����";
		gotoxy(_x + 51, _y + 3);
		cout << "��β������0";
		gotoxy(_x + 47, _y + 5);
		cout << "������˵����";
		gotoxy(_x + 51, _y + 7);
		cout << "�����ƶ����� A";
		gotoxy(_x + 51, _y + 8);
		cout << "�����ƶ����� D";
		gotoxy(_x + 51, _y + 9);
		cout << "�����ƶ����� S";
		gotoxy(_x + 51, _y + 10);
		cout << "�����ƶ����� W";
		gotoxy(_x + 51, _y + 11);
		cout << "���Ƽ��٣�+";
		gotoxy(_x + 51, _y + 12);
		cout << "��ͣ��Ϸ���ո�";
		gotoxy(_x + 51, _y + 13);
		cout << "������Ϸ�������";
		gotoxy(_x + 47, 22);
		cout << "By:     kailvn";
		gotoxy(_x + 53, 23);
		cout << "version 1.7";
	}
	void is_gameover()
	{

		gotoxy(17, 11);
		SetConsoleTextAttribute(handle, 0x0f);
		cout << "����ˮƽ...";
		gotoxy(17, 12);
		cout << "����������ȥѧϰ��!";
		SetConsoleTextAttribute(handle, 0x0f);

	}
	bool restart()
	{
		gotoxy(17, 14);
		SetConsoleTextAttribute(handle, 0x0a);
		cout << "Y ѧϰ��Ҫ/N ������� !";
		char ch = _getch();
		if (ch == 'Y' || ch == 'y')return false;
		return true;
	}
};
class Food {

public:
    COORD _food;
	void rand_food(deque<COORD> & coord)//���ʳ��
	{
		_food.X = 2*rand() % (20) + 3;
		_food.Y = rand() % (20) + 2;
		unsigned int i;
		//ʳ��������ߵ�λ����,��������
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
		cout << "��";
	}
	COORD GetFoodCoordinate()//����ʳ������
	{
		return _food;
	}
};

class snake {
public:
	deque<COORD> body;//˫�˶�����
	COORD head;//ͷ
	int dir;//����
	int cmps = 2;
	snake()//���캯������ʼ��
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
			cout << "��";
		}

	}
		
	bool eat_food(Food &f)//��ʳ
	{   
		COORD _f=f.GetFoodCoordinate();
		if (_f.X == body.back().X && _f.Y == body.back().Y)
		{
			return true;
		}
		else return false;
	}
	void dis_speed(int &speed)//��ӡ�ٶȳ���
	{
		int _x = 3, _y = 5;
		
		gotoxy(_x + 47, _y + 13);
		cout<< "�� �ƶ��ٶȣ� ";
		cout << 100-speed/10+1 ;
		gotoxy(_x + 47, _y + 14);
		cout << "�� ��ǰ���֣� ";
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
	void move_snake(deque<COORD> &_snake)//�ƶ��ĺ���
	{

		hit_kb();//���հ���

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
			ch = _getch();	//ʹ�� getch ������ȡ�������� 
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
	bool alive(COORD s)//�������
	{
		//�߽�
		if (s.Y <= 1 || (s.Y >= 23) || (s.X <= 2) || s.X >= 45)
		{
			return true;
		}
		//��ɱ
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
			if (s.eat_food(f))//�й��ߵ�����
			{
				f.rand_food(s.body);
			}
			else
			{
				gotocoord(s.body.front());
				s.body.pop_front();//ȥβ��
				cout << ' ';
			}
			if (s.alive(s.body.back()))
			{
				a.is_gameover();
				break;
			}
			SetConsoleTextAttribute(handle, 0xB);
			gotocoord(s.body.back());
			cout << "��";

			SetConsoleTextAttribute(handle, 0xB);
			s.dis_speed(speed);

			Sleep(speed);
		}
		if (!a.restart())break;
		speed=500;
	}
}
		

	