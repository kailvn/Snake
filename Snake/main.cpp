#include"Snake.h"
#include"BFS.h"
int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ������
	SetConsoleTitleA("�ҵ�̰����");//����
	COORD dSiz = { 80, 25 };
	SetConsoleScreenBufferSize(handle, dSiz);//���ô��ڻ�������С
	CONSOLE_CURSOR_INFO ptr = { 1, FALSE };//���ù���С�����ع��
	SetConsoleCursorInfo(handle, &ptr);
	srand((unsigned int)time(0));

	Map map;
	Snake snake;
	Food food;
	
	map.Init_map();
	snake.game_mode();
	map.draw_map();
	food.rand_food(snake.body);
	snake.init_sanke(13, 12);
	
	
	while (true)
	{
		if (snake.gamemode)
		{
			snake.move_snake(snake.body, food);
		}
		else {
			snake.AI_find_path(food);
		}
		if (snake.alive(snake.body.back()))
		{
			if (snake.body.size() == 440)
			{   
				cout << "��**��Ȼͨ���ˣ���";
			}
			else
			{
				map.is_gameover();
				break;
			}
		}
		Sleep(snake.speed);
	}
}