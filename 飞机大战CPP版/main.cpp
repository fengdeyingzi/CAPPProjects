#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "src/base.h"
#include "src/graphics.h"
#include "src/android.h"
#include "src/exb.h"
typedef uintptr_t IMAGE;
// #include <graphics.h>
#include <time.h>
#pragma comment(lib, "MSIMG32.LIB")
#pragma region definitions
// HWND hWnd;
#define WIDTH 600
#define HEIGHT 900
#define MAX_PLAYER_BULLET 30
#define MAX_ENEMY_NUMBER 20
#define MAX_ENEMY_NUMBER_IN_SCREEN 5
#define ENEMY_1_HP 1
#define ENEMY_2_HP 4
#define ENEMY_3_HP 12
int MAX_BULLET_INTERVAL = 10;
#define MAX_ENEMY_GENERATE_INTERVAL 50
#define MAX_SUPPLEMENT_GENERATE_INTERVAL 600
#define MAX_BOMB_INTERVAL 40
#define MAX_PLAYER_IMAGE_SWAP_INTERVAL 5
#define MAX_PLAYER_ENHANCE_DURATION 250
#define MAX_PAUSE_INTERVAL 20
#define SUPPLEMENT_SPEED 4
#define EDGE 3
#pragma endregion definitions
#pragma region imageSize
#define PLAYER_WIDTH 102
#define PLAYER_HEIGHT 126
#define enemy_1_WIDTH 57
#define enemy_1_HEIGHT 43
#define enemy_2_WIDTH 69
#define enemy_2_HEIGHT 99
#define enemy_3_WIDTH 169
#define enemy_3_HEIGHT 253
#define BULLET_WIDTH 5
#define BULLET_HEIGHT 11
#define BOMB_WIDTH 60
#define BOMB_HEIGHT 107
#define BULLET_SUPPLY_WIDTH 58
#define BULLET_SUPPLY_HEIGHT 88
#define BOMB_IN_SLOT_WIDTH 63
#define BOMB_IN_SLOT_HEIGHT 57
#define PLAYER_LIFE_WIDTH 46
#define PLAYER_LIFE_HEIGT 57
#define	PAUSE_BUTTON_WIDTH 60
#define PAUSE_BUTTON_HEIGHT 45
#define RESUME_BUTTON_WIDTH 60
#define RESUME_BUTTON_HEIGHT 45
#pragma endregion imageSizes
#pragma region imageLists

IMAGE background;
IMAGE player_plane[3];
IMAGE enemy_plane[4];
IMAGE bullet_img[2];
IMAGE supplement_img[3];
IMAGE supplement_in_slot_img;
IMAGE player_life;
IMAGE dying_player[4];
IMAGE dying_enemies[4][6];
IMAGE controllers[2];
IMAGE selections[3];
#pragma endregion imageLists

#pragma region intervals
int bullet_interval = 0;
int	enemy_generate_interval = 0;
int supplement_generate_interval = 0;
int bomb_interval = 0;
int player_image_swap_interval = 0;
int pause_interval = MAX_PAUSE_INTERVAL;
#pragma endregion intervals
#pragma region auxNumbers
int current_enemy_number = 0;
int current_bomb_number = 1;
int score = 0;
int enhance = 0;
int is_pause = 0;
#pragma endregion auxNumbers
#pragma region typeDefinitions
typedef struct PLAYER
{
	int x = WIDTH / 2;
	int y = HEIGHT * 4 / 5;
	int health = 3;
	int speed = 7;
	bool is_enhanced = false;
	int enhance = 0;
} Player;
Player player;
typedef struct enemy
{
	int x = 0;
	int y = 0;
	int enemy_type = 0;
	bool is_dead = true;
	int speed = 0;
	int hp = 0;
	int width = 0;
	int height = 0;
	bool damage_done = false;
	IMAGE* enemy_img = NULL;
	int dying_phase = 0;
} Enemy;
enemy enemy_list[MAX_ENEMY_NUMBER];
typedef struct BULLET
{
	int x = 0;
	int y = 0;
	int speed = 13;
	bool is_dead = true;
	bool is_enhanced = false;
	int power = 0;
} Bullet;
Bullet bullet_list[MAX_PLAYER_BULLET];
typedef struct SUPPLEMENT
{
	int x = 0;
	int y = 0;
	int type = 0;
	int width = 0;
	int height = 0;
	IMAGE* supply_img = NULL;
	bool is_active = false;
} Supplement;
Supplement supplement;
#pragma endregion typeDefinitions
#pragma region functions
void game_start(void);
void create_bullet(void);
void update_bullets(void);
void detect_keys(void);
void generate_enemy(void);
void update_enemy(void);
void draw(void);
void init_game(void);
void intervals_update(void);
void damage(void);
void update_player_status(void);
void generate_supplement(void);
void use_bomb(void);
void update_supplement(void);
void show_bomb(void);
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
void show_player_life(void);
void show_score(void);
void end_game(void);
void restart(void);
void check_player_health(void);

void player_die(void);
void enemy_die(void);
void show_pause_button(void);
int isRun = 0;
int32 timer;
#pragma endregion functions

void logoc(int32 data){
    if (!isRun) {
			// closegraph(); // 关闭图形窗口
			app_exit(); // 退出程序
		}
		draw();
		check_player_health();
		generate_enemy();
		generate_supplement();
		update_bullets();
		damage();
		update_enemy();
		damage();
		update_supplement();
		detect_keys();
		create_bullet();
		update_player_status();
		intervals_update();
}

#pragma region funcDefinitions

void loadimage(IMAGE* img, const char* path){
    *img = readBitmapFromAssets((char*)(path+2));
}

void init_game(void)
{
	//初始化随机数和画布
	srand((unsigned int)time(NULL));
	// initgraph(WIDTH, HEIGHT);
	// setbkmode(TRANSPARENT);
	// settextstyle(30, 0, _T("Comic Sans MS"));	//设置字体
	// settextcolor(0x1E1E1E);
	//装载图像
	loadimage(&background, ("./images/background1.png")); //装载游戏背景
	loadimage(&player_plane[0], ("./images/me1.png"));	//装载玩家飞机图像
	loadimage(&player_plane[1], ("./images/me2.png"));
	loadimage(&dying_player[3], ("./images/me_destroy_1.png"));
	loadimage(&dying_player[2], ("./images/me_destroy_2.png"));
	loadimage(&dying_player[1], ("./images/me_destroy_3.png"));
	loadimage(&dying_player[0], ("./images/me_destroy_4.png"));
	loadimage(&enemy_plane[1], ("./images/enemy1.png"));	//装载敌机图像
	loadimage(&dying_enemies[1][3], ("./images/enemy1_down1.png"));
	loadimage(&dying_enemies[1][2], ("./images/enemy1_down2.png"));
	loadimage(&dying_enemies[1][1], ("./images/enemy1_down3.png"));
	loadimage(&dying_enemies[1][0], ("./images/enemy1_down4.png"));
	loadimage(&enemy_plane[2], ("./images/enemy2.png"));
	loadimage(&dying_enemies[2][3], ("./images/enemy2_down1.png"));
	loadimage(&dying_enemies[2][2], ("./images/enemy2_down2.png"));
	loadimage(&dying_enemies[2][1], ("./images/enemy2_down3.png"));
	loadimage(&dying_enemies[2][0], ("./images/enemy2_down4.png"));
	loadimage(&enemy_plane[3], ("./images/enemy3_n1.png"));
	loadimage(&dying_enemies[3][4], ("./images/enemy3_down1.png"));
	loadimage(&dying_enemies[3][3], ("./images/enemy3_down2.png"));
	loadimage(&dying_enemies[3][2], ("./images/enemy3_down3.png"));
	loadimage(&dying_enemies[3][1], ("./images/enemy3_down4.png"));
	loadimage(&dying_enemies[3][0], ("./images/enemy3_down5.png"));
	loadimage(&bullet_img[0], ("./images/bullet1.png"));		//装载子弹图像
	loadimage(&bullet_img[1], ("./images/bullet2.png"));
	loadimage(&supplement_img[0], ("./images/bullet_supply.png"));		//装载道具图像
	loadimage(&supplement_img[1], ("./images/bomb_supply.png"));
	loadimage(&supplement_in_slot_img, ("./images/bomb.png"));		//装载状态栏图像
	loadimage(&player_life, ("./images/life.png"));
	loadimage(&controllers[0], ("./images/pause_nor.png"));
	loadimage(&controllers[1], ("./images/resume_nor.png"));
	loadimage(&selections[0], ("./image/select.png"));
}
#ifdef __cplusplus
extern "C" {
    int pause(void);
}
#endif
void detect_keys(void)
{
	if (pause_interval >= MAX_PAUSE_INTERVAL)
	{
		pause_interval = MAX_PAUSE_INTERVAL;
		pause();
	}
    if(getKeyPressed(_UP) == 0){

    // }
	// if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
	// {
		if (player.y - player.speed < PLAYER_HEIGHT / 2)
		{
			player.y = PLAYER_HEIGHT / 2;
		}
		else
		{
			player.y -= player.speed;
		}
	}
    if(getKeyPressed(_DOWN) == 0){
    // }
	// if (GetAsyncKeyState('S') & 32768 || GetAsyncKeyState(VK_DOWN) & 32768)
	// {
		if (player.y + player.speed > HEIGHT - PLAYER_HEIGHT / 2)
		{
			player.y = HEIGHT - PLAYER_HEIGHT / 2;
		}
		else
		{
			player.y += player.speed;
		}
	}
    if(getKeyPressed(_LEFT) == 0){
    // }
	// if (GetAsyncKeyState('A') & 32768 || GetAsyncKeyState(VK_LEFT) & 32768)
	// {
		if (player.x - player.speed < 0)
		{
			player.x = WIDTH + player.x - player.speed;
		}
		else
		{
			player.x -= player.speed;
		}
	}
    if(getKeyPressed(_RIGHT) == 0){
    // }
	// if (GetAsyncKeyState('D') & 32768 || GetAsyncKeyState(VK_RIGHT) & 32768)
	// {
		if (player.x + player.speed > WIDTH)
		{
			player.x = player.x + player.speed - WIDTH;
		}
		else
		{
			player.x += player.speed;
		}
	}
    if(getKeyPressed(_SELECT) == 0){

    // }
	// if ((GetAsyncKeyState(' ') & 32768))
	// {
		use_bomb();
	}
}
void game_start(void)
{
}
void create_bullet(void)
{
	if (bullet_interval < MAX_BULLET_INTERVAL)
	{
		return;
	}
	for (int i = 0; i < MAX_PLAYER_BULLET; i++)
	{
		if (bullet_list[i].is_dead == true)
		{
			bullet_list[i].x = player.x;
			bullet_list[i].y = player.y - 11;
			bullet_list[i].is_dead = false;
			if (player.is_enhanced == true)
			{
				bullet_list[i].is_enhanced = true;
				bullet_list[i].power = 2;
			}
			else
			{
				bullet_list[i].is_enhanced = false;
				bullet_list[i].power = 1;
			}
			break;
		}
	}
	bullet_interval = 0;
}

void update_bullets(void)
{
	for (int i = 0; i < MAX_PLAYER_BULLET; i++)
	{
		bullet_list[i].y -= bullet_list[i].speed;
		if (bullet_list[i].y < 0)
		{
			bullet_list[i].is_dead = true;
		}

	}
}
void generate_enemy(void)
{
	if (enemy_generate_interval < MAX_ENEMY_GENERATE_INTERVAL || current_enemy_number >= MAX_ENEMY_NUMBER_IN_SCREEN)
	{
		return;
	}
	int flag = rand() % 5;
	if (!(flag <= 1))
	{
		return;
	}
	int type = rand() % 11;
	for (int i = 0; i < MAX_ENEMY_NUMBER; i++)
	{
		if (enemy_list[i].is_dead == true && enemy_list[i].dying_phase == 0)
		{
			switch (type)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				enemy_list[i].x = rand() % (WIDTH - 2 * enemy_1_WIDTH) + enemy_1_WIDTH;
				enemy_list[i].y = (0 - enemy_1_HEIGHT / 2);
				enemy_list[i].speed = rand() % 3 + 4;
				enemy_list[i].is_dead = false;
				enemy_list[i].hp = ENEMY_1_HP;
				enemy_list[i].width = enemy_1_WIDTH;
				enemy_list[i].height = enemy_1_HEIGHT;
				enemy_list[i].enemy_img = (&enemy_plane[1]);
				enemy_list[i].damage_done = false;
				enemy_list[i].enemy_type = 1;
				enemy_generate_interval = 0;
				break;

			case 7:
			case 8:
			case 9:		enemy_list[i].x = rand() % (WIDTH - 2 * enemy_2_WIDTH) + enemy_2_WIDTH;
				enemy_list[i].y = (0 - enemy_2_HEIGHT / 2);
				enemy_list[i].speed = rand() % 2 + 3;
				enemy_list[i].is_dead = false;
				enemy_list[i].hp = ENEMY_2_HP;
				enemy_list[i].width = enemy_2_WIDTH;
				enemy_list[i].height = enemy_2_HEIGHT;
				enemy_list[i].enemy_img = (&enemy_plane[2]);
				enemy_list[i].damage_done = false;
				enemy_list[i].enemy_type = 2;
				enemy_generate_interval = 0;
				break;

			case 10:		enemy_list[i].x = rand() % (WIDTH - 2 * enemy_3_WIDTH) + enemy_3_WIDTH;
				enemy_list[i].y = (0 - enemy_3_HEIGHT / 2);
				enemy_list[i].speed = 2;
				enemy_list[i].is_dead = false;
				enemy_list[i].hp = ENEMY_3_HP;
				enemy_list[i].width = enemy_3_WIDTH;
				enemy_list[i].height = enemy_3_HEIGHT;
				enemy_list[i].enemy_img = (&enemy_plane[3]);
				enemy_list[i].damage_done = false;
				enemy_list[i].enemy_type = 3;
				enemy_generate_interval = 0;
				break;
			}
			current_enemy_number++;
			break;
		}
	}
	if (current_enemy_number <= 2)
	{
		enemy_generate_interval += 30;
	}
}
void update_enemy(void)
{
	for (int i = 0; i < MAX_ENEMY_NUMBER; i++)
	{
		if (enemy_list[i].is_dead == true)
		{
			continue;
		}
		else
		{
			enemy_list[i].y += enemy_list[i].speed;
		}
		if (enemy_list[i].y > HEIGHT)
		{
			enemy_list[i].is_dead = true;
			enemy_list[i].damage_done = true;
			player.health -= 1;
			current_enemy_number--;
		}
	}
}

void damage(void) //判断子弹与敌人的碰撞
{
	for (int i = 0; i < MAX_ENEMY_NUMBER; i++)
	{
		if (enemy_list[i].is_dead == true)
		{
			continue;
		}
		for (int j = 0; j < MAX_PLAYER_BULLET; j++)
		{
			if (bullet_list[j].is_dead == true)
			{
				continue;
			}
			if ((bullet_list[j].x + BULLET_WIDTH / 2 + EDGE >= enemy_list[i].x - enemy_list[i].width / 2) &&
				(bullet_list[j].x - BULLET_WIDTH / 2 - EDGE <= enemy_list[i].x + enemy_list[i].width / 2) &&
				(bullet_list[j].y + BULLET_HEIGHT / 2 >= enemy_list[i].y - enemy_list[i].height / 2) &&
				(bullet_list[j].y - BULLET_HEIGHT / 2 <= enemy_list[i].y + enemy_list[i].height / 2))
			{
				bullet_list[j].is_dead = true;
				enemy_list[i].hp -= bullet_list[j].power;
				if (enemy_list[i].hp <= 0)
				{
					enemy_list[i].is_dead = true;
					enemy_list[i].damage_done = true;
					current_enemy_number--;
					switch (enemy_list[i].enemy_type)
					{
					case 1:		enemy_list[i].dying_phase = 39;
						score += 1;
						break;

					case 2:		enemy_list[i].dying_phase = 39;
						score += 5;
						break;

					case 3:		enemy_list[i].dying_phase = 49;
						score += 10;
						break;

					}
				}
			}

		}
	}
}

void update_player_status(void)
{
	for (int i = 0; i < MAX_ENEMY_NUMBER; i++)
	{
		if (enemy_list[i].is_dead == true)
		{
			continue;
		}
		else
		{
			if (enemy_list[i].damage_done == false)
			{
				if ((player.x + PLAYER_WIDTH / 4 >= enemy_list[i].x - enemy_list[i].width / 2) &&
					(player.x - PLAYER_WIDTH / 4 <= enemy_list[i].x + enemy_list[i].width / 2) &&
					(player.y + PLAYER_HEIGHT / 4 >= enemy_list[i].y - enemy_list[i].height / 2) &&
					(player.y - PLAYER_HEIGHT / 4 <= enemy_list[i].y + enemy_list[i].height / 2))
				{
					player.health -= 1;
					enemy_list[i].damage_done = true;
					enemy_list[i].is_dead = true;
					current_enemy_number--;
					switch (enemy_list[i].enemy_type)
					{
					case 1:		enemy_list[i].dying_phase = 39;
						score += 1;
						break;

					case 2:		enemy_list[i].dying_phase = 39;
						score += 5;
						break;

					case 3:		enemy_list[i].dying_phase = 49;
						score += 10;
						break;

					}

				}
			}
		}
	}


	//判断玩家子弹增强的状态
	if (player.enhance > 0)		//若持续时间大于0则减少
	{
		player.enhance--;
	}
	if (player.enhance == 0)
	{
		player.is_enhanced = false;
		MAX_BULLET_INTERVAL = 10;
	}

	if (supplement.is_active == true)
	{
		if ((player.x + PLAYER_WIDTH / 4 >= supplement.x - supplement.width / 2) &&
			(player.x - PLAYER_WIDTH / 4 <= supplement.x + supplement.width / 2) &&
			(player.y + PLAYER_HEIGHT / 4 >= supplement.y - supplement.height / 2) &&
			(player.y - PLAYER_HEIGHT / 4 <= supplement.y + supplement.height / 2))
		{
			supplement.is_active = false;
			if (supplement.type == 1)
			{
				if (current_bomb_number < 3)
				{
					current_bomb_number += 1;
				}
			}
			if (supplement.type == 0)
			{
				player.is_enhanced = true;
				MAX_BULLET_INTERVAL = 7;
				player.enhance = MAX_PLAYER_ENHANCE_DURATION;
			}
		}
	}
}

void intervals_update(void)
{
	if (bullet_interval > 10000)
	{
		bullet_interval = MAX_BULLET_INTERVAL;
	}
	bullet_interval++;

	if (enemy_generate_interval > 10000)
	{
		enemy_generate_interval = MAX_ENEMY_GENERATE_INTERVAL;
	}
	enemy_generate_interval++;

	supplement_generate_interval++;

	bomb_interval++;
	if (bomb_interval > MAX_BOMB_INTERVAL)
	{
		bomb_interval = MAX_BOMB_INTERVAL;
	}

	player_image_swap_interval++;
	pause_interval++;
}

void draw(void)
{
	// cleardevice();
    cls(0,0,0);
	// putimage(0, 0, &background);
    drawBitmap(background, 0, 0);

	//画出己方飞机
	if (player_image_swap_interval >= 0 && player_image_swap_interval < MAX_PLAYER_IMAGE_SWAP_INTERVAL)
	{

		transparentimage(NULL, player.x - PLAYER_WIDTH / 2, player.y - PLAYER_HEIGHT / 2, &player_plane[0]);
	}
	if (player_image_swap_interval == MAX_PLAYER_IMAGE_SWAP_INTERVAL)
	{
		transparentimage(NULL, player.x - PLAYER_WIDTH / 2, player.y - PLAYER_HEIGHT / 2, &player_plane[1]);
		player_image_swap_interval = (0 - MAX_PLAYER_IMAGE_SWAP_INTERVAL);
	}
	if (player_image_swap_interval < 0)
	{

		transparentimage(NULL, player.x - PLAYER_WIDTH / 2, player.y - PLAYER_HEIGHT / 2, &player_plane[1]);
	}



	//画出子弹

	for (int i = 0; i < MAX_PLAYER_BULLET; i++)
	{
		if (bullet_list[i].is_dead == true)
		{
			continue;
		}
		if (bullet_list[i].is_enhanced == true)
		{
			transparentimage(NULL, bullet_list[i].x - BULLET_WIDTH / 2, bullet_list[i].y, &bullet_img[1]);
		}
		if (bullet_list[i].is_enhanced == false)
		{
			transparentimage(NULL, bullet_list[i].x - BULLET_WIDTH / 2, bullet_list[i].y, &bullet_img[0]);
		}
		//else
		//{
		//	transparentimage(NULL, bullet_list[i].x - BULLET_WIDTH / 2, bullet_list[i].y, &bullet_img);
		//}
	}

	//画出敌机

	for (int i = 0; i < MAX_ENEMY_NUMBER; i++)
	{
		if (enemy_list[i].is_dead == true)
		{
			continue;
		}
		else
		{
			transparentimage(NULL, enemy_list[i].x - enemy_list[i].width / 2, enemy_list[i].y - enemy_list[i].height / 2, enemy_list[i].enemy_img);
		}
	}
	//挂了的敌机
	enemy_die();


	//画出道具
	if (supplement.is_active == true)
	{
		transparentimage(NULL, supplement.x - supplement.width / 2, supplement.y - supplement.height / 2, supplement.supply_img);
	}

	//道具栏
	show_bomb();
	//生命值
	show_player_life();
	//暂停按钮
	show_pause_button();

	//显示分数
	show_score();
	transparentimage(NULL, WIDTH / 2, HEIGHT / 2, &selections[0]);
    ref(0, 0, SCRW, SCRH);
	// FlushBatchDraw();
}


void generate_supplement(void)
{
	if (supplement_generate_interval < MAX_SUPPLEMENT_GENERATE_INTERVAL)
	{
		return;
	}
	if (supplement_generate_interval == 1.3 * MAX_SUPPLEMENT_GENERATE_INTERVAL)
	{
		supplement.is_active = true;
		switch (rand() % 2)
		{
		case 0:		supplement.type = 0;
			supplement.width = BULLET_SUPPLY_WIDTH;
			supplement.height = BULLET_SUPPLY_HEIGHT;
			supplement.type = 0;
			supplement.supply_img = (&supplement_img[0]);
			break;

		case 1:		supplement.width = BOMB_HEIGHT;
			supplement.height = BOMB_HEIGHT;
			supplement.type = 1;
			supplement.supply_img = (&supplement_img[1]);
			break;
		}

		supplement.x = rand() % (WIDTH - 2 * supplement.width) + supplement.width;
		supplement.y = 0 - supplement.height / 2;
		supplement_generate_interval = 0;
	}
	else
	{
		if ((rand() % 101) <= 1)
		{
			supplement.is_active = true;
			switch (rand() % 2)
			{
			case 0:		supplement.type = 0;
				supplement.width = BULLET_SUPPLY_WIDTH;
				supplement.height = BULLET_SUPPLY_HEIGHT;
				supplement.type = 0;
				supplement.supply_img = (&supplement_img[0]);
				break;

			case 1:		supplement.width = BOMB_HEIGHT;
				supplement.height = BOMB_HEIGHT;
				supplement.supply_img = (&supplement_img[1]);
				supplement.type = 1;
				break;
			}

			supplement.x = rand() % (WIDTH - 2 * supplement.width) + supplement.width;
			supplement.y = 0 - supplement.height / 2;
			supplement_generate_interval = 0;
		}
	}
}

void use_bomb(void)
{
	if (current_bomb_number > 0)
	{
		if (bomb_interval < MAX_BOMB_INTERVAL)
		{
			return;
		}

		bomb_interval = 0;
		for (int i = 0; i < MAX_ENEMY_NUMBER; i++)
		{
			if (enemy_list[i].is_dead == true)
			{
				continue;
			}
			enemy_list[i].hp = 0;
			enemy_list[i].is_dead = true;
			enemy_list[i].damage_done = true;
			current_enemy_number--;
			switch (enemy_list[i].enemy_type)
			{
			case 1:		enemy_list[i].dying_phase = 39;
				score += 1;
				break;

			case 2:		enemy_list[i].dying_phase = 39;
				score += 5;
				break;

			case 3:		enemy_list[i].dying_phase = 49;
				score += 10;
				break;

			}

		}
		current_bomb_number--;
	}
}

void update_supplement(void)
{
	if (supplement.is_active == true)
	{
		supplement.y += SUPPLEMENT_SPEED;
	}
	if (supplement.y >= HEIGHT)
	{
		supplement.is_active = false;
	}
}



void show_bomb(void)
{
	int x = 20, y = 20;
	for (int i = 1; i <= current_bomb_number; i++)
	{
		transparentimage(NULL, x, y, &supplement_in_slot_img);
		x += BOMB_IN_SLOT_WIDTH + 10;
	}
}

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
	// HDC dstDC = GetImageHDC(dstimg);
	// HDC srcDC = GetImageHDC(srcimg);
	// int w = srcimg->getwidth();
	// int h = srcimg->getheight();

	// // 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	// BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
    drawBitmap(*srcimg, x, y);
}

void show_player_life(void)
{
	int x = WIDTH - PLAYER_LIFE_WIDTH - 20, y = 20;
	for (int i = 1; i <= player.health; i++)
	{
		transparentimage(NULL, x, y, &player_life);
		x -= PLAYER_LIFE_WIDTH + 10;
	}
}

void show_pause_button(void)
{
	if (is_pause == 0)
	{
		transparentimage(NULL, WIDTH - 10 - PAUSE_BUTTON_WIDTH, HEIGHT - 10 - PAUSE_BUTTON_HEIGHT, &controllers[0]);
	}
	if (is_pause == 1)
	{
		transparentimage(NULL, WIDTH - 10 - RESUME_BUTTON_WIDTH, HEIGHT - 10 - RESUME_BUTTON_HEIGHT, &controllers[1]);
	}
}

void show_score(void)
{
	char str[20];
	sprintf(str, "Score: %d", score);
	// outtextxy(20, HEIGHT - 40, str);
    dtext(str, 20, HEIGHT - 40, 20, 20, 20, 0, 1);
}

void end_game(void)
{
	int click;
	char str[50];
	sprintf(str, "本局分数: %d\n是否再来一局？", score);
	// click = MessageBoxW(hWnd, str, L"游戏结束", MB_RETRYCANCEL | MB_ICONHAND);
	// if (click == IDRETRY)
	// {
		restart();
	// }
	// if (click == IDCANCEL)
	// {
	// 	exit(0);
	// }
}

void restart(void)
{
	player.x = WIDTH / 2;
	player.y = HEIGHT * 4 / 5;
	player.enhance = 0;
	player.health = 3;
	player.is_enhanced = false;

	for (int i = 0; i < MAX_ENEMY_NUMBER; i++)
	{
		enemy_list[i].x = 0;
		enemy_list[i].y = 0;
		enemy_list[i].enemy_type = 0;
		enemy_list[i].is_dead = true;
		enemy_list[i].speed = 0;
		enemy_list[i].hp = 0;
		enemy_list[i].width = 0;
		enemy_list[i].height = 0;
		enemy_list[i].damage_done = false;
		enemy_list[i].enemy_img = NULL;
		enemy_list[i].dying_phase = 0;
	}

	for (int i = 0; i < MAX_PLAYER_BULLET; i++)
	{
		bullet_list[i].x = 0;
		bullet_list[i].y = 0;
		bullet_list[i].speed = 13;
		bullet_list[i].is_dead = true;
		bullet_list[i].is_enhanced = false;
		bullet_list[i].power = 0;
	}

	supplement.x = 0;
	supplement.y = 0;
	supplement.type = 0;
	supplement.width = 0;
	supplement.height = 0;
	supplement.supply_img = NULL;
	supplement.is_active = false;

	bullet_interval = 0;
	enemy_generate_interval = 0;
	supplement_generate_interval = 0;
	bomb_interval = 0;
	player_image_swap_interval = 0;

	current_enemy_number = 0;
	current_bomb_number = 1;
	score = 0;
	enhance = 0;
}

void check_player_health(void)
{
	if (player.health <= 0)
	{
		player_die();
		end_game();
	}
}

void player_die(void)
{
	// for (int timer = 159; timer > 0; timer--)
	// {
		// cleardevice();

		// putimage(0, 0, &background);
        drawBitmap(background, 0, 0);


		//画出敌机

		for (int i = 0; i < MAX_ENEMY_NUMBER; i++)
		{
			if (enemy_list[i].is_dead == true)
			{
				continue;
			}
			else
			{
				transparentimage(NULL, enemy_list[i].x - enemy_list[i].width / 2, enemy_list[i].y - enemy_list[i].height / 2, enemy_list[i].enemy_img);
			}
		}

		transparentimage(NULL, player.x - PLAYER_WIDTH / 2, player.y - PLAYER_HEIGHT / 2, &dying_player[timer / 40]);

		show_score();
        ref(0, 0, SCRW, SCRH);
		// FlushBatchDraw();

		// Sleep(10);
	// }
}

void enemy_die(void)
{
	for (int i = 0; i < MAX_ENEMY_NUMBER; i++)
	{
		if (enemy_list[i].is_dead == false)
		{
			continue;
		}
		if (enemy_list[i].dying_phase > 0)
		{
			transparentimage(NULL, enemy_list[i].x - enemy_list[i].width / 2,
				enemy_list[i].y - enemy_list[i].height / 2,
				&dying_enemies[enemy_list[i].enemy_type][enemy_list[i].dying_phase / 10]);
			enemy_list[i].dying_phase -= 1;

		}
	}
}
#ifdef __cplusplus
extern "C"
{ // 因为cpp文件默认定义了该�?),则采用C语言方式进行编译
#endif

int init(void)
{
    isRun = 1;
    setscrsize(WIDTH, HEIGHT);
    timer = timercreate();
	init_game();
	// BeginBatchDraw();
	// hWnd = GetHWnd();
	// FreeConsole();
    timerstart(timer, 30, 1, logoc, 1);

	// EndBatchDraw();
	return 0;
}

int pause(void)
{
    if(getKeyPressed(_SELECT)){

    // }
	// if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	// {
		is_pause = 1;
		draw();
		// while (1)
		// {
		// 	if (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
		// 	{
		// 		break;
		// 	}
		// 	Sleep(10);
		// }
		// while (1)
		// {
		// 	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		// 	{
		// 		is_pause = 0;
		// 		pause_interval = 0;
		// 		break;
		// 	}
		// 	Sleep(10);
		// }
	}
    return 0;
}

#pragma endregion funcDefinitions






//event函数，接收消息事件
int event(int type, int p1, int p2)
{
    if(KY_UP == type)
    {
        switch(p1)
        {
        case _BACK:
            app_exit();
            break;
        case _MENU:
            break;
        }
    }

    return 0;
}



//应用恢复，程序变为可见时调用此函数
int resume()
{
    return 0;
}

//应用退出函数，在应用退出时可做一些内存释放操作
int exitApp()
{
    return 0;
}
#ifdef __cplusplus
}
#endif
/*

&#x60F3;&#x8BF4;&#x7684;&#x8BDD;&#xFF1A;
	&#x611F;&#x8C22;&#x4F60;&#x80FD;&#x770B;&#x5230;&#x8FD9;&#x91CC;&#xFF0C;&#x4E0D;&#x8FC7;&#x5C31;&#x5F53;&#x8FD9;&#x4E9B;&#x8BDD;&#x662F;&#x4E9B;&#x7262;&#x9A9A;&#x8BDD;&#x5427;&#x3002;
	&#x8FD9;&#x4E2A;&#x7A0B;&#x5E8F;&#x7531;&#x6211;&#x4E00;&#x4E2A;&#x4EBA;&#x5F00;&#x53D1;&#xFF0C;&#x7EC4;&#x91CC;&#x9762;&#x7684;&#x4EBA;&#x5BF9;&#x8FD9;&#x4E2A;&#x9879;&#x76EE;&#x7684;&#x8D21;&#x732E;&#x53EA;&#x6709;&#x8D34;&#x56FE;&#x548C;&#x90A3;&#x4E2A;&#x7C98;&#x8D34;&#x6587;&#x5B57;&#x7684;PPT&#x3002;
	&#x6211;&#x52A0;&#x5165;&#x4ED6;&#x4EEC;&#x7684;&#x961F;&#x4F0D;&#x7684;&#x65F6;&#x5019;&#xFF0C;&#x4ED6;&#x4EEC;&#x8FD8;&#x6CA1;&#x5F00;&#x59CB;&#x8BA8;&#x8BBA;&#x8FD9;&#x4E2A;&#x4F5C;&#x4E1A;&#x3002;
	&#x6211;&#x539F;&#x672C;&#x4EE5;&#x4E3A;&#x6211;&#x4EEC;&#x53EF;&#x4EE5;&#x4E24;&#x5929;&#x521B;&#x9020;&#x5947;&#x8FF9;&#xFF0C;&#x4F46;&#x662F;&#x4ED6;&#x4EEC;&#x5BF9;&#x8FD9;&#x4EF6;&#x4E8B;&#x4E00;&#x70B9;&#x90FD;&#x4E0D;&#x4E0A;&#x5FC3;&#x3002;
	&#x4E8E;&#x662F;&#x6211;&#x79C1;&#x81EA;&#x5305;&#x63FD;&#x4E86;&#x7F16;&#x5199;&#xFF0C;&#x5E76;&#x628A;&#x7B2C;&#x4E00;&#x7248;&#x53D1;&#x5230;&#x7FA4;&#x91CC;&#x3002;
	0&#x4E0B;&#x8F7D;&#xFF0C;&#x8FD8;&#x83AB;&#x540D;&#x6210;&#x4E86;&#x7EC4;&#x957F;&#x3002;
	&#x4F46;&#x662F;&#x6211;&#x8FD8;&#x662F;&#x5F97;&#x81EA;&#x5DF1;&#x52A0;&#x5165;&#x529F;&#x80FD;&#xFF0C;&#x8C01;&#x8BA9;&#x6211;&#x9009;&#x62E9;&#x4E86;&#x8FD9;&#x4E2A;&#x961F;&#x3002;
	&#x6211;&#x4E0D;&#x6E05;&#x695A;&#x4ED6;&#x4EEC;&#x5728;&#x7FA4;&#x91CC;&#x9762;&#x4E0D;&#x56DE;&#x590D;&#x6211;&#x7684;&#x65F6;&#x5019;&#x90FD;&#x5728;&#x5E72;&#x4EC0;&#x4E48;&#x3002;
	&#x662F;&#x5728;&#x590D;&#x4E60;&#x6570;&#x5B66;&#xFF1F;&#x8FD8;&#x662F;&#x5728;&#x6253;&#x6E38;&#x620F;&#x770B;&#x89C6;&#x9891;&#xFF1F;
	&#x6211;&#x4E0D;&#x6E05;&#x695A;&#xFF0C;&#x4F46;&#x662F;&#x6211;&#x4E0D;&#x80FD;&#x5728;&#x8FD9;&#x4E2A;&#x9879;&#x76EE;&#x4E0A;&#x62FF;&#x4E0D;&#x5230;&#x770B;&#x5F97;&#x8FC7;&#x53BB;&#x7684;&#x5206;&#x6570;&#x3002;
	&#x7EDD;&#x5BF9;&#x4E0D;&#x80FD;&#x3002;


*/