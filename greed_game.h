#ifndef __greed_game_h_
#define __greed_game_h_

#define MAP_ROW 20
#define MAP_COL 40
//#define UP 'w'
//#define DOWN 's'
//#define LEFT 'a'
//#define RIGHT 'd'

void init_map(void);	//初始化地图
void update_food(void); //加载食物
void rand_food(void);	//正确的随机食物
void move_snake(void);  //移动蛇
int is_alive(void);		//判断蛇的存活
void get_speed(void);	//设置游戏难度，获得不同的速度
void gotoxy(int x, int y);



struct Food
{
	int x;
	int y;
}food;

struct Snake
{
	int x[MAP_ROW * MAP_COL];	//蛇身每个点的x坐标
	int y[MAP_ROW * MAP_COL];	//蛇身每个点的y坐标
	int len;					//蛇的长度
	int speed;					//蛇移动的速度
	char ch;					//控制方向的输入
	int grow;
}snake;



#endif