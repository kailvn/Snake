#include"Snake.h"
#include"BFS.h"
int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);//获取输出句柄
	SetConsoleTitleA("我的贪吃蛇");//标题
	COORD dSiz = { 80, 25 };
	SetConsoleScreenBufferSize(handle, dSiz);//设置窗口缓冲区大小
	CONSOLE_CURSOR_INFO ptr = { 1, FALSE };//设置光标大小，隐藏光标
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
				cout << "你**竟然通关了？！";
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