#include "pch.h"
#include "cell.h"

cell::cell()
{

}

cell::~cell()
{

}
bool cell::CopyCell(cell tcell)
{
	chessname = tcell.Getchessname();
	cellstate = tcell.Getcellstate();
	tcell.clear();
	return true;
}

bool cell::clear()
{
	chessname = CN_EMPTY;
	cellstate = CS_EMPTY;
	return true;
}

void cell::Setpos(GLfloat x, GLfloat y)
{
	pos_x = x;
	pos_y = y;
}

void cell::Setchessname(GLint name)
{
	chessname = name;
}

void cell::Setcellstate(GLint state)
{
	cellstate = state;
}

int cell::Getchessname()
{
	return chessname;
}

int cell::Getcellstate()
{
	return cellstate;
}

bool cell::DrawChess(GLuint* texture)
{
	glPushMatrix();//将当前变换矩阵(单位阵)压入堆栈
	glTranslatef(pos_x, pos_y, 0.0);//平移矩阵

	switch (chessname)
	{
	case CN_CAOCAO:
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		break;
	case CN_ZHANGFEI:
		switch (cellstate)
		{
		case CS_LEFT:
		case CS_RIGHT:
			glBindTexture(GL_TEXTURE_2D, texture[6]);
			break;
		case CS_BOTTOM:
		case CS_TOP:
			glBindTexture(GL_TEXTURE_2D, texture[7]);
			break;
		}
		break;
	case CN_ZHAOYUN:
		switch (cellstate)
		{
		case CS_LEFT:
		case CS_RIGHT:
			glBindTexture(GL_TEXTURE_2D, texture[8]);
			break;
		case CS_BOTTOM:
		case CS_TOP:
			glBindTexture(GL_TEXTURE_2D, texture[9]);
			break;
		}
		break;
	case CN_MACHAO:
		switch (cellstate)
		{
		case CS_LEFT:
		case CS_RIGHT:
			glBindTexture(GL_TEXTURE_2D, texture[4]);
			break;
		case CS_BOTTOM:
		case CS_TOP:
			glBindTexture(GL_TEXTURE_2D, texture[5]);
			break;
		}
		break;
	case CN_GUANYU:
		switch (cellstate)
		{
		case CS_LEFT:
		case CS_RIGHT:
			glBindTexture(GL_TEXTURE_2D, texture[1]);
			break;
		case CS_BOTTOM:
		case CS_TOP:
			glBindTexture(GL_TEXTURE_2D, texture[1]);
			break;
		}
		break;

	case CN_HUANGZHONG:
		switch (cellstate)
		{
		case CS_LEFT:
		case CS_RIGHT:
			glBindTexture(GL_TEXTURE_2D, texture[2]);
			break;
		case CS_BOTTOM:
		case CS_TOP:
			glBindTexture(GL_TEXTURE_2D, texture[3]);
			break;
		}
		break;
	case CN_BIN:
	case CN_YONG:
	case CN_ZU:
	case CN_DIN:
		glBindTexture(GL_TEXTURE_2D, texture[10]);
		break;
	case CN_EMPTY:
		glBindTexture(GL_TEXTURE_2D, texture[12]);
		break;


	}
	glBegin(GL_QUADS);
	switch (cellstate)
	{
	case CS_TOPLEFT:
		glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(0.5f, 0.5f); glVertex3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 1.0, 0.0);
		break;
	case CS_TOPRIGHT:
		glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.5f); glVertex3f(1.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0, 1.0, 0.0);
		break;
	case CS_BOTTOMLEFT:
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(0.5f, 0.0f); glVertex3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.5f, 0.5f); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0, 1.0, 0.0);
		break;
	case CS_BOTTOMRIGHT:
		glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.5f); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0, 1.0, 0.0);
		break;
	case CS_LEFT:
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(0.5f, 0.0f); glVertex3f(1.0, 0.0, 0.0);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 1.0, 0.0);
		break;
	case CS_RIGHT:
		glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.5f, 1.0f); glVertex3f(0.0, 1.0, 0.0);
		break;
	case CS_TOP:
		glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.5f); glVertex3f(1.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 1.0, 0.0);
		break;
	case CS_BOTTOM:
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.5f); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0, 1.0, 0.0);
		break;
	case CS_BIN:
	case CS_EMPTY:
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, 0.0, 0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, 0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 1.0, 0.0);
		break;

	}

	glEnd();
	glPopMatrix();
	return true;
}
