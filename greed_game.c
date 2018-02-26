#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

#include"greed_game.h"



void init_map(void)
{
	//初始化蛇头的位置
	snake.x[0] = MAP_ROW / 2;
	snake.y[0] = MAP_COL / 2;
	//初始化蛇的长度为3
	gotoxy(snake.x[0], snake.y[0]);
	printf("@");
	snake.len = 3;
	snake.speed = 500;
	snake.ch = 'w';
	snake.grow = 0;
	for (int k = 1; k < snake.len; k++)
	{
		snake.x[k] = snake.x[k - 1] + 1;
		snake.y[k] = snake.y[k - 1];
		gotoxy(snake.x[k], snake.y[k]);
		printf("@");
	}

	//随机获取第一个食物的位置
	rand_food();
	gotoxy(food.x, food.y);
	printf("$");

	//打印围墙
	for (int j = 0; j < MAP_COL; j++)
	{
		gotoxy(0, j);
		printf("#");
		gotoxy(MAP_ROW - 1, j);
		printf("#");
	}
	for (int i = 1; i < MAP_ROW - 1; i++)
	{
		gotoxy(i, 0);
		printf("#");
		gotoxy(i, MAP_COL - 1);
		printf("#");
	}
}

void rand_food(void)
{
	while (1)
	{
		srand((unsigned int)time(NULL));
		food.x = rand() % (MAP_ROW - 2) + 1;
		food.y = rand() % (MAP_COL - 2) + 1;
		int count = 0;
		for (int i = 0; i < snake.len; i++)
		{
			if (food.x != snake.x[i] || food.y != snake.y[i])
			{
				count++;
				if (count == snake.len - 1)
					break;
			}
			else
			{
				break;
			}
		}
		if (count == snake.len - 1)
			break;
	}
}
void update_food(void)
{
	if (snake.x[0] == food.x && snake.y[0] == food.y)
	{
		rand_food();
		gotoxy(food.x, food.y);
		printf("$");

		snake.len++;
		snake.grow = 1;
	}
}

void move_snake(void)
{
	if (kbhit()) //
		snake.ch = getch();
	if (snake.grow == 0)
	{
		gotoxy(snake.x[snake.len - 1], snake.y[snake.len - 1]);
		printf(" ");
	}
	for (int k = snake.len - 1; k > 0; k--)
	{
		snake.x[k] = snake.x[k - 1];
		snake.y[k] = snake.y[k - 1];
	}

	switch (snake.ch)
	{
	case 'w':
		snake.x[0]--;
		break;
	case 's':
		snake.x[0]++;
		break;
	case 'a':
		snake.y[0]--;
		break;
	case 'd':
		snake.y[0]++;
		break;
	default:
		break;
	}

	gotoxy(snake.x[0], snake.y[0]);
	printf("@");
	snake.grow = 0;
	gotoxy(MAP_ROW, 0);
}

int is_alive(void)
{
	if (snake.x[0] == 0 || snake.x[0] == MAP_ROW - 1 || snake.y[0] == 0 || snake.y[0] == MAP_COL - 1)
		return 0;

	for (int k = 1; k < snake.len; k++)
	{
		if (snake.x[0] == snake.x[k] && snake.y[0] == snake.y[k])
			return 0;
	}

	return 1;
}

void get_speed(void)
{
	if (snake.len <= 6)
		snake.speed = 500;
	else if (snake.len <= 12)
		snake.speed = 400;
	else if (snake.len <= 16)
		snake.speed = 100;
	else if (snake.len <= 40)
		snake.speed = 200;
	else
		snake.speed = 300;
}

void gotoxy(int x, int y)
{
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = y;
	cor.Y = x;
	SetConsoleCursorPosition(hout, cor);
}