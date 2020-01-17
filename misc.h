#ifndef MISC_H_INCLUDED
//防止头文件被重复引用
#define MISC_H_INCLUDED

HANDLE g_misc_handle;

/*其他功能 - 函数声明*/
int mathRand(int min,int max);
void gotoXY(int y,int x);

/*取范围随机数*/
int mathRand(int min,int max)
{
	return rand()%(max-min+1)+min;
}

/*光标定位*/
void gotoXY(int y,int x)
{
    COORD coord;
	coord.Y = y;
    coord.X = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
#endif