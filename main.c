#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "misc.h"
#include "game.h"

/*按键参数*/
#define KEY_ESC 27

/*函数声明*/
void bindKeyDown();
void uniOutputGameInfo();

int main()
{
	system("cls");
	//游戏初始化
	g_steps=0;
	g_stat=GAME_ING;
	//开始游戏
	do{
		initRandMap(g_map);
	}while(!isBoxMovable(g_box.Y,g_box.X,g_map));
	outPutRandMap(g_map);
	uniOutputGameInfo();
	bindKeyDown();
	return 0;
}
/*监听键盘事件*/
void bindKeyDown()
{
	char ch;
	ch = getch();
	while(ch!=KEY_ESC)
	{
		if('a'<=ch && ch<='z')
		{
			ch-=32;
		}
		if(g_stat==GAME_ING)
		{
			switch(ch)
			{
				case 'W':
					playerMove(g_map,MOVE_W);
					break;
				case 'S':
					playerMove(g_map,MOVE_S);
					break;
				case 'A':
					playerMove(g_map,MOVE_A);
					break;
				case 'D':
					playerMove(g_map,MOVE_D);
					break;
			}
		}
		//显示游戏状态
		uniOutputGameInfo();
		ch = getch();
	}
	main();
}
/*游戏信息统一显示*/
void uniOutputGameInfo()
{
	outputObjectCoord();
	outputPlayerSteps();
	outputGameStat(g_stat);
}