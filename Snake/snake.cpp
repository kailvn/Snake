#include"Snake.h"
using namespace std;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ������

void gotocoord(int x, int y)//������λ��
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
	SetConsoleTitleA("�ҵ�̰����");//����
	COORD dSiz = { 80, 25 };
	SetConsoleScreenBufferSize(handle, dSiz);//���ô��ڻ�������С
	CONSOLE_CURSOR_INFO ptr = { 1, FALSE };//���ù���С�����ع��
	SetConsoleCursorInfo(handle, &ptr);
	//system("color 0f");//���û�����ɫ
	srand((unsigned int)time(0));

}
void Map::draw_map(int _x,int _y)
{
	SetConsoleTextAttribute(handle, 0x0f);//�����ı���ɫ
	system("cls");//����
	//��߿�
	for (int i = 0; i < 23; i++)
	{
		cout << endl << " ��";
	}
	//�ϱ߿�
	gotocoord(3, 1);
	for (int i = 0; i < 21; i++)
	{
		cout << "��";
	}
	//�±߿�
	gotocoord(3, 23);
	for (int i = 0; i < 21; i++)
	{
		cout << "��";
	}
	//�ұ߿�
	for (SHORT i = 1; i <= 23; i++)
	{
		gotocoord(45, i);
		cout << "��";
	}
	SetConsoleTextAttribute(handle, 0x0a);//�����ı���ɫ
	gotocoord(_x + 47, _y + 0);
	cout << "����Ϸ˵����";
	gotocoord(_x + 51, _y + 2);
	cout << "�Զ�����";
	gotocoord(_x + 51, _y + 3);
	cout << "��β������0";
	gotocoord(_x + 47, _y + 5);
	cout << "������˵����";
	gotocoord(_x + 51, _y + 7);
	cout << "�����ƶ����� A";
	gotocoord(_x + 51, _y + 8);
	cout << "�����ƶ����� D";
	gotocoord(_x + 51, _y + 9);
	cout << "�����ƶ����� S";
	gotocoord(_x + 51, _y + 10);
	cout << "�����ƶ����� W";
	gotocoord(_x + 51, _y + 11);
	cout << "���Ƽ��٣�+";
	gotocoord(_x + 51, _y + 12);
	cout << "��ͣ��Ϸ���ո�";
	gotocoord(_x + 51, _y + 13);
	cout << "������Ϸ�������";
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
	cout << "ѡ����Ϸģʽ";
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
	cout << "����ˮƽ...";
	gotocoord(17, 12);
	cout << "����������ȥѧϰ��!";
	SetConsoleTextAttribute(handle, 0x0f);
	gotocoord(18, 8);
	SetConsoleTextAttribute(handle, 0x0a);
	cout << "Y ѧϰ��Ҫ/N ������� !";
	char ch = _getch();
	if (ch == 'Y' || ch == 'y')return false;
	return true;
}
void Snake::dis_score(int &speed)
{
	int _x = 3, _y = 5;
	gotocoord(_x + 47, _y + 13);
	cout << "�� �ƶ��ٶȣ� ";
	cout << 100 - speed / 10 + 1;
	gotocoord(_x + 47, _y + 14);
	cout << "�� ��ǰ���ȣ� ";
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
		ch = _getch();	//ʹ�� getch ������ȡ�������� 
		switch (ch)
		{
		case 'w':
		case 'W':
		case '8':
			if (this->dir == DOWN)//thisָ��ı�������dir
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
	//�߽�
	if (s.Y < 2 || (s.Y >22) || (s.X <3) || s.X >43)
	{
		return true;
	}
	//��ɱ
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
	
	if (eat_food(food))//�й��ߵ�����
	{
		food.rand_food(body);
	}
	else
	{
		gotocoord(body.front());
		body.pop_front();//ȥβ��
		cout << ' ';
	}
	SetConsoleTextAttribute(handle, 0xB);
	gotocoord(body.back());
	cout << "��";

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
		cout << "��";
	}
}
void Food::rand_food(deque<COORD> & coord)
{
	_food.X = 2 * rand() % (20) + 3;
	_food.Y = rand() % (20) + 2;
	unsigned int i;
	//ʳ��������ߵ�λ����,��������
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
	cout << "��";
}
void Snake::AI_find_path(Food &f)
{
	static int not_found = 1;
	static int cot = 0;
	COORD head, temp;
	COORD fpoint = f.GetFoodCoordinate();

	for (unsigned int i = 0; i < body.size(); i++)
	{
		map[(body[i].X-3)/2][body[i].Y-2] = true; //�ߵ�����Ҳ���ϰ�
	}
	COORD begin_point, end_point;

	begin_point = tran_c(body.back());//תΪС��ͼ
	end_point = tran_c(fpoint);//תΪС��ͼ

	AISnake.GetPath(begin_point, end_point);//С��ͼ

	
	if (!AISnake.paths_queue.empty())
	{
		head = retran_c(AISnake.paths_queue.front());//תΪ���ͼ
		AISnake.paths_queue.pop();
	}
	else
	{

		for (int i = 0; i < 4; i++)
		{
			int break_num = rand() % 4;
			temp = body.back();
			temp.X = temp.X + 2 * direction[i][0];
			temp.Y = temp.Y + direction[i][1];

			if (alive(temp))  //·����ͨ������
			{
				continue;
			}
			head = temp;
			if (break_num == i)
				break;
		}
	}



	//body.push_back(head);
	//if (eat_food(f))//�й��ߵ�����
	//{
	//	f.rand_food(body);
	//}
	//else
	//{
	//	gotocoord(body.front());
	//	body.pop_front();//ȥβ��
	//	cout << ' ';
	//}
	//SetConsoleTextAttribute(handle, 0xB);
	//gotocoord(body.back());
	//cout << "��";

	//SetConsoleTextAttribute(handle, 0xB);
	//dis_score(speed);

}
COORD Snake::tran_c(COORD pre_c)
{   
	COORD _c;
	_c.X = (pre_c.X - 3) / 2;
	_c.Y = pre_c.Y - 2;
	return _c;
}
COORD Snake::retran_c(COORD _c)
{
	COORD pre_c;
	pre_c.X = 2 * _c.X + 3;
	pre_c.Y = _c.Y + 2;
	return pre_c;
}