#pragma once
#include <GL/glut.h>
enum CHESSNAME
{
	CN_EMPTY = 0, //0
	CN_CAOCAO,   //1
	CN_ZHANGFEI,//2
	CN_ZHAOYUN,//3
	CN_MACHAO,//4
	CN_GUANYU,//5
	CN_HUANGZHONG,//6
	CN_BIN,//7
	CN_YONG,//8
	CN_ZU,//9
	CN_DIN,//10
};
enum CELLSTATE
{
	CS_EMPTY = 0,     //0
	CS_TOPLEFT,//曹操左上角部分  //1
	CS_TOPRIGHT,     //2
	CS_BOTTOMLEFT,     //3
	CS_BOTTOMRIGHT,     //4
	CS_TOP,//将士竖着摆放时，将士上半部分     //5
	CS_BOTTOM,     //6
	CS_LEFT,//将士横着摆放时，将士左半部分     //7
	CS_RIGHT,     //8
	CS_BIN,//小将，就占一个格子     //9
};
//比翼横空
static int nameConfig1[5][4] =
{
	{7,0,8,6},
	{9,0,10,6},
	{3,3,4,4},
	{2,2,1,1},
	{5,5,1,1}
};
static int stateConfig1[5][4] =
{
	{9,0,9,6},
	{9,0,9,5},
	{7,8,7,8},
	{7,8,3,4},
	{7,8,1,2}
};
//三军联防
static int nameConfig2[5][4] =
{
	{7,0,0,8},
	{9,3,3,10},
	{5,5,2,2},
	{1,1,4,6},
	{1,1,4,6}
};
static int stateConfig2[5][4] =
{
	{9,0,0,9},
	{9,7,8,9},
	{7,8,7,8},
	{3,4,6,6},
	{1,2,5,5}
};
//重重包围
static int nameConfig3[5][4] =
{
	{7,0,0,8},
	{4,2,2,6},
	{4,5,5,6},
	{3,1,1,9},
	{3,1,1,10}
};
static int stateConfig3[5][4] =
{
	{9,0,0,9},
	{6,7,8,6},
	{5,7,8,5},
	{6,3,4,9},
	{5,1,2,9}
};
//调兵遣将
static int nameConfig4[5][4] =
{
	{0,6,6,0},
	{3,3,4,4},
	{5,5,2,2},
	{1,1,7,8},
	{1,1,9,10}
};
static int stateConfig4[5][4] =
{
	{0,7,8,0},
	{7,8,7,8},
	{7,8,7,8},
	{3,4,9,9},
	{1,2,9,9}
};
//水泄不通
static int nameConfig5[5][4] =
{
	{7,0,0,8},
	{3,3,4,4},
	{5,5,2,2},
	{9,1,1,6},
	{10,1,1,6}
};
static int stateConfig5[5][4] =
{
	{9,0,0,9},
	{7,8,7,8},
	{7,8,7,8},
	{9,3,4,6},
	{9,1,2,5}
};

class cell
{
public:
	cell();
	virtual ~cell();
public:
	void Setpos(GLfloat x, GLfloat y);
	void Setchessname(GLint name);
	void Setcellstate(GLint state);
	int Getchessname();
	int Getcellstate();
	bool DrawChess(GLuint* texture);
	bool CopyCell(cell tcell);
	bool clear();
private:
	GLfloat pos_x;
	GLfloat pos_y;
	GLint cellstate;
	GLint chessname;
	GLuint texid;

};

