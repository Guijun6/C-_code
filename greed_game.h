#ifndef __greed_game_h_
#define __greed_game_h_

#define MAP_ROW 20
#define MAP_COL 40
//#define UP 'w'
//#define DOWN 's'
//#define LEFT 'a'
//#define RIGHT 'd'

void init_map(void);	//��ʼ����ͼ
void update_food(void); //����ʳ��
void rand_food(void);	//��ȷ�����ʳ��
void move_snake(void);  //�ƶ���
int is_alive(void);		//�ж��ߵĴ��
void get_speed(void);	//������Ϸ�Ѷȣ���ò�ͬ���ٶ�
void gotoxy(int x, int y);



struct Food
{
	int x;
	int y;
}food;

struct Snake
{
	int x[MAP_ROW * MAP_COL];	//����ÿ�����x����
	int y[MAP_ROW * MAP_COL];	//����ÿ�����y����
	int len;					//�ߵĳ���
	int speed;					//���ƶ����ٶ�
	char ch;					//���Ʒ��������
	int grow;
}snake;



#endif