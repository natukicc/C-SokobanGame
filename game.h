#ifndef GAME_H_INCLUDED
//防止头文件被重复引用
#define GAME_H_INCLUDED

/*游戏相关 - 地图参数*/
#define MAP_HEIGHT 20
#define MAP_WIDTH 20
#define MAP_EMPTY 0
#define MAP_BLOCK 1
#define MAP_PLAYER 2
#define MAP_EXIT 3
#define MAP_BOX 4
/*游戏相关 - 移动参数*/
#define MOVE_W 0
#define MOVE_A 1
#define MOVE_S 2
#define MOVE_D 3
/*游戏相关 - 状态参数*/
#define GAME_ING 0
#define GAME_FAILED 1
#define GAME_SUCCEED 2

/*输出相关 - 信息输出位置*/
#define OUTPUT_PLAYER MAP_HEIGHT
#define OUTPUT_BOX MAP_HEIGHT+1
#define OUTPUT_STEPS MAP_HEIGHT+2
#define OUTPUT_GAMESTAT MAP_HEIGHT+3

/*游戏相关 - 全局变量*/
int g_map[MAP_HEIGHT][MAP_WIDTH];
COORD g_player;
COORD g_box;
COORD g_exit;
int g_steps;
int g_stat;

/*游戏相关 - 函数声明*/
int initRandMap(int map[MAP_HEIGHT][MAP_WIDTH]);
void outPutRandMap(int map[MAP_HEIGHT][MAP_WIDTH]);
void playerMove(int map[MAP_HEIGHT][MAP_WIDTH],int move);
int isBoxMovable(int y, int x, int map[MAP_HEIGHT][MAP_WIDTH]);
void updateObjectCoord(int y,int x,int object);

/*输出相关 - 函数声明*/
void outputObjectCoord();
void outputPlayerSteps();
void outputGameStat(int stat);

/*初始化随机地图*/
int initRandMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	int i,x,y;
	int blockNum,blockCnt;
	//清空地图
	for(y=0;y<MAP_HEIGHT;y++)
	{
		for(x=0;x<MAP_WIDTH;x++)
		{
			map[y][x]=MAP_EMPTY;
		}
	}
	//生成边界
	for(y=0;y<MAP_HEIGHT;y++)
	{
		for(x=0;x<MAP_WIDTH;x++)
		{
			if(y==0 || x==0 || y==MAP_HEIGHT-1 || x==MAP_WIDTH-1)
			{
				map[y][x]=MAP_BLOCK;
			}
		}
	}
	//随机设置障碍物
	srand((unsigned)time(0));
	blockNum = mathRand(40,(MAP_WIDTH-10)*(MAP_HEIGHT-10));
	for(i=0;i<blockNum;i++)
	{
		x = rand()%(MAP_WIDTH-2)+1;
		y = rand()%(MAP_HEIGHT-2)+1;
		if(map[y][x]==MAP_EMPTY)
		{
			map[y][x] = MAP_BLOCK;
			blockCnt++;
		}
	}
	//放置人物
	g_player.Y = 2;
	g_player.X = 2;
	map[g_player.Y][g_player.X] = MAP_PLAYER;
	//放置出口
	g_exit.Y = mathRand(2,MAP_HEIGHT-2);
	g_exit.X = MAP_WIDTH-1;
	map[g_exit.Y][g_exit.X] = MAP_EXIT;
	//放置箱子
	g_box.Y = mathRand(2,MAP_HEIGHT-2);
	g_box.X = mathRand(2,MAP_WIDTH-2);
	map[g_box.Y][g_box.X] = MAP_BOX;
	return blockCnt;
}

/*输出地图*/
void outPutRandMap(int map[MAP_HEIGHT][MAP_WIDTH])
{
	int x,y;
	for(y=0;y<MAP_HEIGHT;y++)
	{
		for(x=0;x<MAP_WIDTH;x++)
		{
			switch(map[y][x])
			{
				case MAP_EMPTY:
					printf("  ");
					break;
				case MAP_BLOCK:
					printf("%c%c",0xa8,0x80);
					break;
				case MAP_PLAYER:
					printf("%c ",1);
					break;
				case MAP_EXIT:
					printf("  ");
					break;
				case MAP_BOX:
					printf("# ");
					break;
			}
		}
		printf("\n");
	}
}

/*人物移动*/
void playerMove(int map[MAP_HEIGHT][MAP_WIDTH],int move)
{
	switch(move)
	{
		case MOVE_W:
			if(map[g_player.Y-1][g_player.X]==MAP_BLOCK)
			{
				return;
			}
			else if(map[g_player.Y-1][g_player.X]==MAP_EMPTY)
			{
				//人物擦除
				gotoXY(g_player.Y, 2+g_player.X*2-1);
				printf("\b ");
				map[g_player.Y][g_player.X]=MAP_EMPTY;
				//人物上移
				gotoXY(g_player.Y-1, 2+g_player.X*2-1);
				printf("\b%c",1);
				map[g_player.Y-1][g_player.X]=MAP_PLAYER;
				//人物坐标更新
				updateObjectCoord(g_player.Y-1, g_player.X, MAP_PLAYER);
			}
			else if(map[g_player.Y-1][g_player.X]==MAP_BOX)
			{
				//判断箱子不能移动
				if(map[g_player.Y-2][g_player.X]==MAP_BLOCK)
				{
					return;
				}
				//箱子能够移动
				//人物擦除
				gotoXY(g_player.Y, 2+g_player.X*2-1);
				printf("\b ");
				map[g_player.Y][g_player.X]=MAP_EMPTY;
				//人物上移
				gotoXY(g_player.Y-1, 2+g_player.X*2-1);
				printf("\b%c",1);
				map[g_player.Y-1][g_player.X]=MAP_PLAYER;
				//人物坐标更新
				updateObjectCoord(g_player.Y-1, g_player.X, MAP_PLAYER);
				//箱子上移
				gotoXY(g_player.Y-1, 2+g_player.X*2-1);
				printf("\b#");
				map[g_player.Y-1][g_player.X]=MAP_BOX;
				//箱子坐标更新
				updateObjectCoord(g_player.Y-1, g_player.X, MAP_BOX);
			}
		break;
		case MOVE_S:
			if(map[g_player.Y+1][g_player.X]==MAP_BLOCK)
			{
				return;
			}
			else if(map[g_player.Y+1][g_player.X]==MAP_EMPTY)
			{
				//人物擦除
				gotoXY(g_player.Y, 2+g_player.X*2-1);
				printf("\b ");
				map[g_player.Y][g_player.X]=MAP_EMPTY;
				//人物下移
				gotoXY(g_player.Y+1, 2+g_player.X*2-1);
				printf("\b%c",1);
				map[g_player.Y+1][g_player.X]=MAP_PLAYER;
				//人物坐标更新
				updateObjectCoord(g_player.Y+1, g_player.X, MAP_PLAYER);
			}
			else if(map[g_player.Y+1][g_player.X]==MAP_BOX)
			{
				//判断箱子不能移动
				if(map[g_player.Y+2][g_player.X]==MAP_BLOCK)
				{
					return;
				}
				//箱子能够移动
				//人物擦除
				gotoXY(g_player.Y, 2+g_player.X*2-1);
				printf("\b ");
				map[g_player.Y][g_player.X]=MAP_EMPTY;
				//人物下移
				gotoXY(g_player.Y+1, 2+g_player.X*2-1);
				printf("\b%c",1);
				map[g_player.Y+1][g_player.X]=MAP_PLAYER;
				//人物坐标更新
				updateObjectCoord(g_player.Y+1, g_player.X, MAP_PLAYER);
				//箱子下移
				gotoXY(g_player.Y+1, 2+g_player.X*2-1);
				printf("\b#");
				map[g_player.Y+1][g_player.X]=MAP_BOX;
				//箱子坐标更新
				updateObjectCoord(g_player.Y+1, g_player.X, MAP_BOX);
			}
		break;
		case MOVE_A:
			if(map[g_player.Y][g_player.X-1]==MAP_BLOCK)
			{
				return;
			}
			else if(map[g_player.Y][g_player.X-1]==MAP_EMPTY)
			{
				//人物擦除
				gotoXY(g_player.Y, 2+g_player.X*2-1);
				printf("\b ");
				map[g_player.Y][g_player.X]=MAP_EMPTY;
				//人物左移
				gotoXY(g_player.Y, 2+(g_player.X-1)*2-1);
				printf("\b%c",1);
				map[g_player.Y][g_player.X-1]=MAP_PLAYER;
				//人物坐标更新
				updateObjectCoord(g_player.Y, g_player.X-1, MAP_PLAYER);
			}
			else if(map[g_player.Y][g_player.X-1]==MAP_BOX)
			{
				//判断箱子不能移动
				if(map[g_player.Y][g_player.X-2]==MAP_BLOCK)
				{
					return;
				}
				//箱子能够移动
				//人物擦除
				gotoXY(g_player.Y, 2+g_player.X*2-1);
				printf("\b ");
				map[g_player.Y][g_player.X]=MAP_EMPTY;
				//人物左移
				gotoXY(g_player.Y, 2+(g_player.X-1)*2-1);
				printf("\b%c",1);
				map[g_player.Y][g_player.X-1]=MAP_PLAYER;
				//人物坐标更新
				updateObjectCoord(g_player.Y, g_player.X-1, MAP_PLAYER);
				//箱子左移
				gotoXY(g_player.Y, 2+(g_player.X-1)*2-1);
				printf("\b#");
				map[g_player.Y][g_player.X-1]=MAP_BOX;
				//箱子坐标更新
				updateObjectCoord(g_player.Y, g_player.X-1, MAP_BOX);
			}
		break;
		case MOVE_D:
			if(map[g_player.Y][g_player.X+1]==MAP_BLOCK)
			{
				return;
			}
			else if(map[g_player.Y][g_player.X+1]==MAP_EMPTY)
			{
				//人物擦除
				gotoXY(g_player.Y, 2+g_player.X*2-1);
				printf("\b ");
				map[g_player.Y][g_player.X]=MAP_EMPTY;
				//人物右移
				gotoXY(g_player.Y, 2+(g_player.X+1)*2-1);
				printf("\b%c",1);
				map[g_player.Y][g_player.X+1]=MAP_PLAYER;
				//人物坐标更新
				updateObjectCoord(g_player.Y, g_player.X+1, MAP_PLAYER);
			}
			else if(map[g_player.Y][g_player.X+1]==MAP_BOX)
			{
				//判断箱子不能移动
				if(map[g_player.Y][g_player.X+2]==MAP_BLOCK)
				{
					return;
				}
				//箱子能够移动
				//人物擦除
				gotoXY(g_player.Y, 2+g_player.X*2-1);
				printf("\b ");
				map[g_player.Y][g_player.X]=MAP_EMPTY;
				//人物右移
				gotoXY(g_player.Y, 2+(g_player.X+1)*2-1);
				printf("\b%c",1);
				map[g_player.Y][g_player.X+1]=MAP_PLAYER;
				//人物坐标更新
				updateObjectCoord(g_player.Y, g_player.X+1, MAP_PLAYER);
				//箱子右移
				gotoXY(g_player.Y, 2+(g_player.X+1)*2-1);
				printf("\b#");
				map[g_player.Y][g_player.X+1]=MAP_BOX;
				//箱子坐标更新
				updateObjectCoord(g_player.Y, g_player.X+1, MAP_BOX);
			}
		break;
	}
	g_steps++;
	//判断箱子是否到达终点
	if(g_box.X==g_exit.X && g_box.Y==g_exit.Y)
	{
		g_stat = GAME_SUCCEED;
		return;
	}
	//判断箱子是否进入死角
	if(!isBoxMovable(g_box.Y,g_box.X,g_map))
	{
		g_stat = GAME_FAILED;
		return;
	}
}

/*更新人物或箱子坐标*/
void updateObjectCoord(int y,int x,int object)
{
	switch(object)
	{
		case MAP_PLAYER:
			g_player.Y = y;
			g_player.X = x;
			break;
		case MAP_BOX:
			g_box.Y = y;
			g_box.X = x;
			break;
	}
}

/*判断箱子可否移动*/
int isBoxMovable(int y, int x, int map[MAP_HEIGHT][MAP_WIDTH])
{
	if(map[y-1][x]==MAP_BLOCK && map[y][x+1]==MAP_BLOCK)
	{
		return 0;
	}
	else if(map[y][x+1]==MAP_BLOCK && map[y+1][x]==MAP_BLOCK)
	{
		return 0;
	}
	else if(map[y+1][x]==MAP_BLOCK && map[y][x-1]==MAP_BLOCK)
	{
		return 0;
	}
	else if(map[y][x-1]==MAP_BLOCK && map[y-1][x]==MAP_BLOCK)
	{
		return 0;
	}
	return 1;
}

/*输出 - 箱子及人物坐标*/
void outputObjectCoord()
{
	gotoXY(OUTPUT_PLAYER,0);
	printf("Coord Player: x=%d,y=%d",g_player.X,g_player.Y);
	gotoXY(OUTPUT_BOX,0);
	printf("Coord Box: x=%d,y=%d",g_box.X,g_box.Y);
}

/*输出 - 游戏步数信息*/
void outputPlayerSteps()
{
	gotoXY(OUTPUT_STEPS,0);
	printf("Player Steps: %d",g_steps);
}

/*输出 - 游戏状态*/
void outputGameStat(int stat)
{
	gotoXY(OUTPUT_GAMESTAT,0);
	printf("Game stat: ");
	switch(stat)
	{
		case GAME_ING:
			printf("Gaming.");
			break;
		case GAME_FAILED:
			printf("Game failed.");
			break;
		case GAME_SUCCEED:
			printf("Game succeed");
			break;
	}
}
#endif