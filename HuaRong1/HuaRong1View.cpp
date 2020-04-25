
// HuaRong1View.cpp: CHuaRong1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "HuaRong1.h"
#endif

#include "HuaRong1Doc.h"
#include "HuaRong1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHuaRong1View

IMPLEMENT_DYNCREATE(CHuaRong1View, CView)

BEGIN_MESSAGE_MAP(CHuaRong1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHuaRong1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CHuaRong1View 构造/析构

CHuaRong1View::CHuaRong1View() noexcept
{
	// TODO: 在此处添加构造代码
	nID = 1;
}

CHuaRong1View::~CHuaRong1View()
{
}

BOOL CHuaRong1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CHuaRong1View 绘图

void CHuaRong1View::OnDraw(CDC* pDC)
{
	CHuaRong1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	Display();
	if (cells[0][1].Getchessname() == CN_CAOCAO && cells[0][2].Getchessname() == CN_CAOCAO & cells[1][1].Getchessname() == CN_CAOCAO & cells[1][2].Getchessname() == CN_CAOCAO)
	{
		cells[0][1].Setchessname(CS_EMPTY);
		cells[0][2].Setchessname(CS_EMPTY);
		cells[1][1].Setchessname(CS_EMPTY);
		cells[1][2].Setchessname(CS_EMPTY);
		MessageBox(_T("胜利成功！"));
	}
}


// CHuaRong1View 打印


void CHuaRong1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHuaRong1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CHuaRong1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CHuaRong1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CHuaRong1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHuaRong1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHuaRong1View 诊断

#ifdef _DEBUG
void CHuaRong1View::AssertValid() const
{
	CView::AssertValid();
}

void CHuaRong1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHuaRong1Doc* CHuaRong1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHuaRong1Doc)));
	return (CHuaRong1Doc*)m_pDocument;
}
#endif //_DEBUG


// CHuaRong1View 消息处理程序


bool CHuaRong1View::movecell(MOVEDIRETION mdirection, int i, int j)
{
	// TODO: 在此处添加实现代码.
	switch (mdirection)
	{
	case MD_LEFT:
		cells[i][j - 1].CopyCell(cells[i][j]);
		break;
	case MD_RIGHT:
		cells[i][j + 1].CopyCell(cells[i][j]);
		break;
	case MD_BOTTOM:
		cells[i - 1][j].CopyCell(cells[i][j]);
		break;
	case MD_TOP:
		cells[i + 1][j].CopyCell(cells[i][j]);
		break;
	}
	cells[i][j].clear();
	return true;
}


bool CHuaRong1View::IsEmpty(int i, int j)
{
	// TODO: 在此处添加实现代码.
	if (i < 0 || j < 0 || i>4 || j>4)
		return false;
	if (cells[i][j].Getchessname() == CN_EMPTY)
	{
		return true;
	}
	else
		return false;
}


void CHuaRong1View::ResetChessState(int index)
{
	// TODO: 在此处添加实现代码.
	int i = (index - 1) / 4;
	int j = index - 4 * i - 1;
	int t = 0;
	if (cells[i][j].Getcellstate() == 0 && moveable == false)
	{
		return;
	}
	//求棋子左下角的索引
	if (cells[i][j].Getchessname() != CN_EMPTY)
	{
		if (cells[i][j].Getchessname() == CN_CAOCAO)
		{
			i = (cells[i][j].Getcellstate() == CS_BOTTOMLEFT || cells[i][j].Getcellstate() == CS_BOTTOMRIGHT) ? i : i - 1;
			j = (cells[i][j].Getcellstate() == CS_TOPLEFT || cells[i][j].Getcellstate() == CS_BOTTOMLEFT) ? j : j - 1;

		}
		else if (cells[i][j].Getchessname() == CN_BIN)
		{
			i = i;
			j = j;
		}
		else
		{
			i = (cells[i][j].Getcellstate() == CS_TOP) ? i - 1 : i;
			j = (cells[i][j].Getcellstate() == CS_RIGHT) ? j - 1 : j;
		}
		i_index = i;
		j_index = j;
		mchessname = (CHESSNAME)cells[i][j].Getchessname();
		moveable = true;
	}
	//确定棋子移动方向
	else
	{
		switch (mchessname)
		{
		case CN_CAOCAO:
			if (IsEmpty(i_index, j_index - 1) && IsEmpty(i_index + 1, j_index - 1) && (i == i_index && j == j_index - 1 || i == i_index + 1 && j == j_index - 1))
			{
				movecell(MD_LEFT, i_index, j_index);
				movecell(MD_LEFT, i_index + 1, j_index);
				movecell(MD_LEFT, i_index, j_index + 1);
				movecell(MD_LEFT, i_index + 1, j_index + 1);

			}
			if (IsEmpty(i_index - 1, j_index) && IsEmpty(i_index - 1, j_index + 1) && (i == i_index - 1 && j == j_index || i == i_index - 1 && j == j_index + 1))
			{
				movecell(MD_BOTTOM, i_index, j_index);
				movecell(MD_BOTTOM, i_index, j_index + 1);
				movecell(MD_BOTTOM, i_index + 1, j_index);
				movecell(MD_BOTTOM, i_index + 1, j_index + 1);
			}
			if (IsEmpty(i_index, j_index + 2) && IsEmpty(i_index + 1, j_index + 2) && (i == i_index && j == j_index + 2 || i == i_index + 1 && j == j_index + 2))
			{
				movecell(MD_RIGHT, i_index, j_index + 1);
				movecell(MD_RIGHT, i_index + 1, j_index + 1);
				movecell(MD_RIGHT, i_index, j_index);
				movecell(MD_RIGHT, i_index + 1, j_index);
			}
			if (IsEmpty(i_index + 2, j_index) && IsEmpty(i_index + 2, j_index + 1) && (i == i_index + 2 && j == j_index || i == i_index + 2 && j == j_index + 1))
			{
				movecell(MD_TOP, i_index + 1, j_index);
				movecell(MD_TOP, i_index + 1, j_index + 1);
				movecell(MD_TOP, i_index, j_index);
				movecell(MD_TOP, i_index, j_index + 1);
			}
			break;
		case CN_ZHANGFEI:
		case CN_ZHAOYUN:
		case CN_MACHAO:
		case CN_GUANYU:
		case CN_HUANGZHONG:
			//如果棋子横放
			if (cells[i_index][j_index].Getcellstate() == CS_LEFT)
			{
				if (IsEmpty(i_index, j_index - 1) && (i == i_index && j == j_index - 1))
				{
					movecell(MD_LEFT, i_index, j_index);
					movecell(MD_LEFT, i_index, j_index + 1);
				}
				if (IsEmpty(i_index - 1, j_index) && IsEmpty(i_index - 1, j_index + 1) && (i == i_index - 1 && j == j_index || i == i_index - 1 && j == j_index + 1))
				{
					movecell(MD_BOTTOM, i_index, j_index);
					movecell(MD_BOTTOM, i_index, j_index + 1);
				}
				if (IsEmpty(i_index, j_index + 2) && (i == i_index && j == j_index + 2))
				{
					movecell(MD_RIGHT, i_index, j_index + 1);
					movecell(MD_RIGHT, i_index, j_index);
				}
				//direction[t++]=MD_RIGHT;
				if (IsEmpty(i_index + 1, j_index) && IsEmpty(i_index + 1, j_index + 1) && (i == i_index + 1 && j == j_index || i == i_index + 1 && j == j_index + 1))
				{
					movecell(MD_TOP, i_index, j_index + 1);
					movecell(MD_TOP, i_index, j_index);
				}
			}
			//如果棋子竖放
			else
			{
				if (IsEmpty(i_index, j_index - 1) && IsEmpty(i_index + 1, j_index - 1) && (i == i_index && j == j_index - 1 || i == i_index + 1 && j == j_index - 1))
				{
					movecell(MD_LEFT, i_index, j_index);
					movecell(MD_LEFT, i_index + 1, j_index);
				}
				if (IsEmpty(i_index - 1, j_index) && (i == i_index - 1 && j == j_index))
				{
					movecell(MD_BOTTOM, i_index, j_index);
					movecell(MD_BOTTOM, i_index + 1, j_index);
				}
				if (IsEmpty(i_index, j_index + 1) && IsEmpty(i_index + 1, j_index + 1) && (i == i_index && j == j_index + 1 || i == i_index + 1 && j == j_index + 1))
				{
					movecell(MD_RIGHT, i_index + 1, j_index);
					movecell(MD_RIGHT, i_index, j_index);
				}
				if (IsEmpty(i_index + 2, j_index) && (i == i_index + 2 && j == j_index))
				{
					movecell(MD_TOP, i_index + 1, j_index);
					movecell(MD_TOP, i_index, j_index);
				}
			}
			break;
		case CN_BIN:
		case CN_YONG:
		case CN_ZU:
		case CN_DIN:
			if (IsEmpty(i_index, j_index - 1) && (i == i_index && j == j_index - 1))
				movecell(MD_LEFT, i_index, j_index);
			if (IsEmpty(i_index - 1, j_index) && (i == i_index - 1 && j == j_index))
				movecell(MD_BOTTOM, i_index, j_index);
			if (IsEmpty(i_index, j_index + 1) && (i == i_index && j == j_index + 1))
				movecell(MD_RIGHT, i_index, j_index);
			if (IsEmpty(i_index + 1, j_index) && (i == i_index + 1 && j == j_index))
				movecell(MD_TOP, i_index, j_index);
			break;
		}
		moveable = false;
		DrawBoard(GL_RENDER);
	}
}


void CHuaRong1View::DrawBoard(unsigned int mode)
{
	// TODO: 在此处添加实现代码.
	int nameNum = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (mode = GL_SELECT)
			{
				glLoadName(++nameNum);
			}
			cells[i][j].DrawChess(texture);
		}
	}
	glFlush();

}


void CHuaRong1View::readchessdata(int nameConfig[5][4], int stateConfig[5][4])
{
	// TODO: 在此处添加实现代码.
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cells[i][j].Setpos(j * 1 - 2.0, i * 1 - 2.5);
			cells[i][j].Setchessname(CHESSNAME(nameConfig[i][j]));
			cells[i][j].Setcellstate(CELLSTATE(stateConfig[i][j]));

		}
	}
}


bool CHuaRong1View::Loadtexfile(char* filename, int texid)
{
	// TODO: 在此处添加实现代码.
	AUX_RGBImageRec* pImage = NULL;
	pImage = auxDIBImageLoad(filename);//载入位图
	if (pImage == NULL)
		return false;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texid);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pImage->sizeX, pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);//二维纹理定义函数：glTexImage2D 宽高要求2n 
	//纹理控制	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//设置纹理在s方向上的纹理环绕方式
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// 线形滤波
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// 线形滤波
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	free(pImage);
	return true;
}


void CHuaRong1View::init()
{
	// TODO: 在此处添加实现代码.
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(13, texture);	//申请纹理空间
	Loadtexfile("picture/曹操.bmp", texture[0]);
	Loadtexfile("picture/关羽1.bmp", texture[1]);
	Loadtexfile("picture/黄忠1.bmp", texture[2]);
	Loadtexfile("picture/黄忠2.bmp", texture[3]);
	Loadtexfile("picture/马超1.bmp", texture[4]);
	Loadtexfile("picture/马超2.bmp", texture[5]);
	Loadtexfile("picture/张飞1.bmp", texture[6]);
	Loadtexfile("picture/张飞2.bmp", texture[7]);
	Loadtexfile("picture/赵云1.bmp", texture[8]);
	Loadtexfile("picture/赵云2.bmp", texture[9]);
	Loadtexfile("picture/兵.bmp", texture[10]);
	Loadtexfile("picture/背景纹理.bmp", texture[11]);
	Loadtexfile("picture/空格纹理.bmp", texture[12]);
	S[0].mark = 1;
	S[0].Run();
	S[1].mark = 2;
	S[1].Run();
	S[2].mark = 3;
	S[2].Run();
	S[3].mark = 4;
	S[3].Run();
	memset(&chess, 0, sizeof(chess));
	readchessdata(nameConfig1, stateConfig1);
	SetTimer(0, 100, NULL);
}


void CHuaRong1View::Display()
{
	// TODO: 在此处添加实现代码.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, texture[11]);
	glTranslatef(0.0, 0.0, -0.1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(3.0, 3.0, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-3.0, 3.0, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-3.0, -3.0, 0.0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(3.0, -3.0, 0.0);
	glEnd();
	glTranslatef(0.0, 0.0, 0.1);
	DrawBoard(GL_RENDER);
	SwapBuffers(wglGetCurrentDC());
}


void CHuaRong1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CView::OnSize(nType, cx, cy);
	W = cx;
	H = cy;
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//视场调节	
	gluPerspective(60.0, (GLfloat)cx / (GLfloat)cy, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);

}


BOOL CHuaRong1View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CView::OnEraseBkgnd(pDC);
}


void CHuaRong1View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	CView::OnDestroy();

	// TODO: Add your message handler code here
	if (wglGetCurrentContext() != NULL)
	{
		wglMakeCurrent(m_hDC->GetSafeHdc(), NULL);
	}
	if (m_hRC != NULL)
	{
		wglDeleteContext(m_hRC);
	}
	if (m_hDC)
		delete m_hDC;
}


void CHuaRong1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	GLuint SelectBuffer[BUFSIZE] = { 0 };
	GLint hits = 0;
	GLint viewport[4] = { 0 };
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(BUFSIZE, SelectBuffer);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(0);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	GLfloat fAspect = (float)W / (float)H;
	gluPickMatrix(point.x, viewport[3] - point.y, 5.0, 5.0, viewport);
	gluPerspective(60.0, fAspect, 1.0, 500.0);
	DrawBoard(GL_SELECT);
	SwapBuffers(wglGetCurrentDC());
	/*glutSwapBuffers();*/
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	hits = glRenderMode(GL_RENDER);//渲染模式。对基元进行栅格化，生成像素片段，然后将其写入帧缓冲区
	GLuint* ptr = SelectBuffer;
	for (int i = 0; i < hits; i++)
	{
		int names = *ptr;
		/*cout<<"本次点击得到的名字数量："<<names<<endl;*/
		ptr++;
		ptr += 2;
		for (int j = 0; j < names; j++) {
			//cout<<"name"<<j+1<<": "<<*ptr<<endl;		
			ResetChessState(*ptr);
			ptr++;
		}
	}
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}

int CHuaRong1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	m_hDC = new CClientDC(this);
	//初始化像素格式及选取合适的格式来创建RC
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR) ,  // pfd结构的大小
			1 ,  // 版本号
			PFD_DRAW_TO_WINDOW | // 支持在窗口中绘图
			PFD_SUPPORT_OPENGL | // 支持OpenGL 
			PFD_DOUBLEBUFFER | // 双缓存模式
			PFD_STEREO |  //支持立体模式
			PFD_TYPE_RGBA ,  // RGBA 颜色模式
			24 ,  // 24 位颜色深度
			0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  // 忽略颜色位
			0 ,  // 没有非透明度缓存
			0 ,  // 忽略移位位
			0 ,  // 无累加缓存
			0 ,  0 ,  0 ,  0 ,  // 忽略累加位
			32 ,  // 32 位深度缓存
			0 ,  // 无模板缓存
			0 ,  // 无辅助缓存
			PFD_MAIN_PLANE ,  // 主层
			0 ,  // 保留
			0 ,  0 ,  0 // 忽略层, 可见性和损毁掩模
	};
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_hDC->GetSafeHdc(), &pfd);
	if (pixelformat == 0)
	{
		MessageBox(_T("选择像素格式失败!"), _T("设置像素格式"), MB_ICONERROR);
		return FALSE;
	}
	//设置指定象素格式
	if (::SetPixelFormat(m_hDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox(_T("选择像素格式失败!"), _T("设置像素格式"), MB_ICONERROR);
		return FALSE;
	}

	//初始化OpenGL，创建渲染描述表
	m_hRC = ::wglCreateContext(m_hDC->GetSafeHdc());
	//设置当前的RC，以后的画图操作都画在m_pDC指向的DC上
	::wglMakeCurrent(m_hDC->GetSafeHdc(), m_hRC); //当前化渲染描述表
	GetClientRect(&m_oldRect);  //获取客户区大小
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);  //启动深度测试
	glMatrixMode(GL_MODELVIEW); //启动模型矩阵
	glLoadIdentity();   //初始化矩阵
	init();
	return 0;
}

int CHuaRong1View::first(int a[], int num)
{
	// TODO: 在此处添加实现代码.
	int b = 0;
	for (int i = 0; i < 20; i++) {
		if (a[i] == num) b = 1;
	}
	return b;
}


void CHuaRong1View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int n;
	int i;
	char a[20];
	int c[20];
	for (i = 0; i < 20; i++) {
		c[i] = 0;
	}
	int m = 1;
	int nameConfig[5][4];
	int stateConfig[5][4];
	static int C = 0;
	static int flag = 0;
	static int flag1 = 1;
	CRect rect;

	GetClientRect(&rect);
	CDC* pDC = GetDC();

	string str ;
	CString cstr;
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CView::GetDocument();

	switch (nIDEvent) {
	case 0:
		switch (pDoc->Num) {
		case 1:
			if (flag == 0) {
				flag1 = 1;
				readchessdata(nameConfig1, stateConfig1);
				Invalidate();
				pDoc->Num = 0;
			}
			break;
		case 2:
			if (flag == 0)
			{
				flag1 = 2;
				readchessdata(nameConfig3, stateConfig3);
				Invalidate();
				pDoc->Num = 0;
			}

			break;
		case 3:
			if (flag == 0)
			{
				flag1 = 3;
				readchessdata(nameConfig4, stateConfig4);
				Invalidate();
				pDoc->Num = 0;
			}

			break;
		case 4:
			if (flag == 0)
			{
				flag1 = 4;
				readchessdata(nameConfig5, stateConfig5);
				Invalidate();
				pDoc->Num = 0;
			}

			break;
		case 5:
			if (flag == 0) {
				SetTimer(1, 700, NULL);
				pDoc->Num = 21;
			}
			break;
		case 6:
			if (flag == 0) {
				SetTimer(2, 700, NULL);
				pDoc->Num = 21;
			}
			break;
		case 7:
			if (flag == 0) {
				SetTimer(3, 700, NULL);
				pDoc->Num = 21;
			}
			break;
		case 8:
			if (flag == 0) {
				SetTimer(4, 700, NULL);
				pDoc->Num = 21;
			}
			break;
		case 13:
			if (flag == 0 && flag1 == 1) {
				pDoc->flag = 1;
				Name1ToNum(cells);
				S[4].mark = 1;
				S[4].Run1(chess);
				SetTimer(5, 700, NULL);
				pDoc->Num = 21;
			}
			break;
		case 14:
			if (flag == 0 && flag1 == 2) {
				pDoc->flag = 2;
				Name2ToNum(cells);
				S[5].mark = 2;
				S[5].Run1(chess);
				SetTimer(6, 700, NULL);
				pDoc->Num = 21;
			}
			break;
		case 15:
			if (flag == 0 && flag1 == 3) {
				pDoc->flag = 3;
				Name3ToNum(cells);
				S[6].mark = 3;
				S[6].Run1(chess);
				SetTimer(7, 700, NULL);
				pDoc->Num = 21;
			}
			break;
		case 16:
			if (flag == 0 && flag1 == 4) {
				pDoc->flag = 4;
				Name4ToNum(cells);
				S[7].mark = 4;
				S[7].Run1(chess);
				SetTimer(8, 700, NULL);
				pDoc->Num = 21;
			}
			break;
		}
		break;

	case 1:
		if (flag == 0 || flag == 1) {
			flag = 1;
			memcpy(a, S[0].answer[C], sizeof(S[0].answer[C]));   //起始状态
			for (i = 0; i < 20; i++) {
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) nameConfig[4 - d][b] = 0;
				if (a[i] == 1) nameConfig[4 - d][b] = 9;
				if (a[i] == 2) nameConfig[4 - d][b] = 7;
				if (a[i] == 3) nameConfig[4 - d][b] = 10;
				if (a[i] == 4) nameConfig[4 - d][b] = 8;
				if (a[i] == 5) nameConfig[4 - d][b] = 4;
				if (a[i] == 6) nameConfig[4 - d][b] = 5;
				if (a[i] == 7) nameConfig[4 - d][b] = 2;
				if (a[i] == 8) nameConfig[4 - d][b] = 3;
				if (a[i] == 9) nameConfig[4 - d][b] = 6;
				if (a[i] == 10) nameConfig[4 - d][b] = 1;
			}

			for (i = 0; i < 20; i++) {//stateConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) stateConfig[4 - d][b] = 0;
				if (a[i] == 1 || a[i] == 2 || a[i] == 3 || a[i] == 4)
					stateConfig[4 - d][b] = 9;

				if (a[i] == 5 && first(c, 5) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 5;
				}
				else if (a[i] == 5 && first(c, 5) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 6 && first(c, 6) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 6;
				}
				else if (a[i] == 6 && first(c, 6) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 7 && first(c, 7) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 7;
				}
				else if (a[i] == 7 && first(c, 7) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 8 && first(c, 8) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 8;
				}
				else if (a[i] == 8 && first(c, 8) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 9 && first(c, 9) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 9;
				}
				else if (a[i] == 9 && first(c, 9) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 10)
				{
					stateConfig[4 - d][b] = m;
					m++;
				}

			}
			pDoc->total = S[0].count;
			pDoc->signal = C;
			pDoc->Num = 9;
			readchessdata(nameConfig, stateConfig);
			Invalidate();
			if (C == S[0].count) {
				C = 0;
				pDoc->Num = 0;
				pDoc->total = 0;
				pDoc->signal = 0;
				pDoc->UpdateAllViews(this);
				flag = 0;
				KillTimer(1);
			}
			else {
				C++;
			}
		}
		break;
	case 2:
		if (flag == 0 || flag == 2) {
			flag = 2;
			memcpy(a, S[1].answer[C], sizeof(S[1].answer[C]));   //起始状态
			for (i = 0; i < 20; i++) {//nameConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) nameConfig[4 - d][b] = 0;
				if (a[i] == 1) nameConfig[4 - d][b] = 7;
				if (a[i] == 2) nameConfig[4 - d][b] = 8;
				if (a[i] == 3) nameConfig[4 - d][b] = 10;
				if (a[i] == 4) nameConfig[4 - d][b] = 9;
				if (a[i] == 5) nameConfig[4 - d][b] = 2;
				if (a[i] == 6) nameConfig[4 - d][b] = 5;
				if (a[i] == 7) nameConfig[4 - d][b] = 3;
				if (a[i] == 8) nameConfig[4 - d][b] = 4;
				if (a[i] == 9) nameConfig[4 - d][b] = 6;
				if (a[i] == 10) nameConfig[4 - d][b] = 1;
			}

			for (i = 0; i < 20; i++) {//stateConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) stateConfig[4 - d][b] = 0;
				if (a[i] == 1 || a[i] == 2 || a[i] == 3 || a[i] == 4)
					stateConfig[4 - d][b] = 9;

				if (a[i] == 5 && first(c, 5) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 5;
				}
				else if (a[i] == 5 && first(c, 5) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 6 && first(c, 6) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 6;
				}
				else if (a[i] == 6 && first(c, 6) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 7 && first(c, 7) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 7;
				}
				else if (a[i] == 7 && first(c, 7) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 8 && first(c, 8) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 8;
				}
				else if (a[i] == 8 && first(c, 8) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 9 && first(c, 9) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 9;
				}
				else if (a[i] == 9 && first(c, 9) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 10)
				{
					stateConfig[4 - d][b] = m;
					m++;
				}

			}

			pDoc->total = S[1].count;
			pDoc->signal = C;
			pDoc->Num = 10;
			readchessdata(nameConfig, stateConfig);
			Invalidate();
			if (C == S[1].count) {
				C = 0;
				pDoc->total = 0;
				pDoc->signal = 0;
				pDoc->Num = 0;
				pDoc->UpdateAllViews(this);
				flag = 0;
				KillTimer(2);
			}
			else {
				C++;
			}
		}
		break;
	case 3:
		if (flag == 0 || flag == 3) {
			flag = 3;
			memcpy(a, S[2].answer[C], sizeof(S[2].answer[C]));   //起始状态
			for (i = 0; i < 20; i++) {//nameConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) nameConfig[4 - d][b] = 0;
				if (a[i] == 1) nameConfig[4 - d][b] = 7;
				if (a[i] == 2) nameConfig[4 - d][b] = 8;
				if (a[i] == 3) nameConfig[4 - d][b] = 9;
				if (a[i] == 4) nameConfig[4 - d][b] = 10;
				if (a[i] == 5) nameConfig[4 - d][b] = 5;
				if (a[i] == 6) nameConfig[4 - d][b] = 2;
				if (a[i] == 7) nameConfig[4 - d][b] = 3;
				if (a[i] == 8) nameConfig[4 - d][b] = 4;
				if (a[i] == 9) nameConfig[4 - d][b] = 6;
				if (a[i] == 10) nameConfig[4 - d][b] = 1;
			}

			for (i = 0; i < 20; i++) {//stateConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) stateConfig[4 - d][b] = 0;
				if (a[i] == 1 || a[i] == 2 || a[i] == 3 || a[i] == 4)
					stateConfig[4 - d][b] = 9;

				if (a[i] == 5 && first(c, 5) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 5;
				}
				else if (a[i] == 5 && first(c, 5) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 6 && first(c, 6) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 6;
				}
				else if (a[i] == 6 && first(c, 6) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 7 && first(c, 7) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 7;
				}
				else if (a[i] == 7 && first(c, 7) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 8 && first(c, 8) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 8;
				}
				else if (a[i] == 8 && first(c, 8) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 9 && first(c, 9) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 9;
				}
				else if (a[i] == 9 && first(c, 9) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 10)
				{
					stateConfig[4 - d][b] = m;
					m++;
				}

			}

			pDoc->total = S[2].count;
			pDoc->signal = C;
			pDoc->Num = 11;
			readchessdata(nameConfig, stateConfig);
			Invalidate();
			if (C == S[2].count) {
				C = 0;
				pDoc->Num = 0;
				pDoc->total = 0;
				pDoc->signal = 0;
				pDoc->UpdateAllViews(this);
				flag = 0;
				KillTimer(3);
			}
			else {
				C++;
			}
		}
		break;
	case 4:
		if (flag == 0 || flag == 4) {
			flag = 4;
			memcpy(a, S[3].answer[C], sizeof(S[3].answer[C]));   //起始状态
			for (i = 0; i < 20; i++) {//nameConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) nameConfig[4 - d][b] = 0;
				if (a[i] == 1) nameConfig[4 - d][b] = 7;
				if (a[i] == 2) nameConfig[4 - d][b] = 8;
				if (a[i] == 3) nameConfig[4 - d][b] = 10;
				if (a[i] == 4) nameConfig[4 - d][b] = 9;
				if (a[i] == 5) nameConfig[4 - d][b] = 3;
				if (a[i] == 6) nameConfig[4 - d][b] = 4;
				if (a[i] == 7) nameConfig[4 - d][b] = 5;
				if (a[i] == 8) nameConfig[4 - d][b] = 2;
				if (a[i] == 9) nameConfig[4 - d][b] = 6;
				if (a[i] == 10) nameConfig[4 - d][b] = 1;
			}

			for (i = 0; i < 20; i++) {//stateConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) stateConfig[4 - d][b] = 0;
				if (a[i] == 1 || a[i] == 2 || a[i] == 3 || a[i] == 4)
					stateConfig[4 - d][b] = 9;

				if (a[i] == 5 && first(c, 5) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 5;
				}
				else if (a[i] == 5 && first(c, 5) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 6 && first(c, 6) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 6;
				}
				else if (a[i] == 6 && first(c, 6) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 7 && first(c, 7) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 7;
				}
				else if (a[i] == 7 && first(c, 7) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 8 && first(c, 8) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 8;
				}
				else if (a[i] == 8 && first(c, 8) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 9 && first(c, 9) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 9;
				}
				else if (a[i] == 9 && first(c, 9) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 10)
				{
					stateConfig[4 - d][b] = m;
					m++;
				}

			}

			pDoc->total = S[3].count;
			pDoc->signal = C;
			pDoc->Num = 12;
			readchessdata(nameConfig, stateConfig);
			Invalidate();
			if (C == S[3].count) {
				C = 0;
				pDoc->Num = 0;
				pDoc->total = 0;
				pDoc->signal = 0;
				pDoc->UpdateAllViews(this);
				flag = 0;
				KillTimer(4);
			}
			else {
				C++;
			}
		}
		break;
	case 5:
		if (flag == 0 || flag == 5) {
			flag = 5;
			memcpy(a, S[4].answer[C], sizeof(S[4].answer[C]));   //起始状态
			for (i = 0; i < 20; i++) {
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) nameConfig[4 - d][b] = 0;
				if (a[i] == 1) nameConfig[4 - d][b] = 9;
				if (a[i] == 2) nameConfig[4 - d][b] = 7;
				if (a[i] == 3) nameConfig[4 - d][b] = 10;
				if (a[i] == 4) nameConfig[4 - d][b] = 8;
				if (a[i] == 5) nameConfig[4 - d][b] = 4;
				if (a[i] == 6) nameConfig[4 - d][b] = 5;
				if (a[i] == 7) nameConfig[4 - d][b] = 2;
				if (a[i] == 8) nameConfig[4 - d][b] = 3;
				if (a[i] == 9) nameConfig[4 - d][b] = 6;
				if (a[i] == 10) nameConfig[4 - d][b] = 1;
			}

			for (i = 0; i < 20; i++) {//stateConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) stateConfig[4 - d][b] = 0;
				if (a[i] == 1 || a[i] == 2 || a[i] == 3 || a[i] == 4)
					stateConfig[4 - d][b] = 9;

				if (a[i] == 5 && first(c, 5) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 5;
				}
				else if (a[i] == 5 && first(c, 5) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 6 && first(c, 6) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 6;
				}
				else if (a[i] == 6 && first(c, 6) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 7 && first(c, 7) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 7;
				}
				else if (a[i] == 7 && first(c, 7) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 8 && first(c, 8) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 8;
				}
				else if (a[i] == 8 && first(c, 8) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 9 && first(c, 9) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 9;
				}
				else if (a[i] == 9 && first(c, 9) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 10)
				{
					stateConfig[4 - d][b] = m;
					m++;
				}

			}
			pDoc->total = S[4].count;
			pDoc->signal = C;
			pDoc->Num = 13;
			readchessdata(nameConfig, stateConfig);
			Invalidate();
			if (C == S[4].count) {
				C = 0;
				pDoc->Num = 0;
				pDoc->total = 0;
				pDoc->signal = 0;
				pDoc->UpdateAllViews(this);
				flag = 0;
				KillTimer(5);
			}
			else {
				C++;
			}
		}
		break;
	case 6:
		if (flag == 0 || flag == 6) {
			flag = 6;
			memcpy(a, S[5].answer[C], sizeof(S[5].answer[C]));   //起始状态
			for (i = 0; i < 20; i++) {//nameConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) nameConfig[4 - d][b] = 0;
				if (a[i] == 1) nameConfig[4 - d][b] = 7;
				if (a[i] == 2) nameConfig[4 - d][b] = 8;
				if (a[i] == 3) nameConfig[4 - d][b] = 10;
				if (a[i] == 4) nameConfig[4 - d][b] = 9;
				if (a[i] == 5) nameConfig[4 - d][b] = 2;
				if (a[i] == 6) nameConfig[4 - d][b] = 5;
				if (a[i] == 7) nameConfig[4 - d][b] = 3;
				if (a[i] == 8) nameConfig[4 - d][b] = 4;
				if (a[i] == 9) nameConfig[4 - d][b] = 6;
				if (a[i] == 10) nameConfig[4 - d][b] = 1;
			}

			for (i = 0; i < 20; i++) {//stateConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) stateConfig[4 - d][b] = 0;
				if (a[i] == 1 || a[i] == 2 || a[i] == 3 || a[i] == 4)
					stateConfig[4 - d][b] = 9;

				if (a[i] == 5 && first(c, 5) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 5;
				}
				else if (a[i] == 5 && first(c, 5) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 6 && first(c, 6) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 6;
				}
				else if (a[i] == 6 && first(c, 6) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 7 && first(c, 7) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 7;
				}
				else if (a[i] == 7 && first(c, 7) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 8 && first(c, 8) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 8;
				}
				else if (a[i] == 8 && first(c, 8) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 9 && first(c, 9) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 9;
				}
				else if (a[i] == 9 && first(c, 9) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 10)
				{
					stateConfig[4 - d][b] = m;
					m++;
				}

			}

			pDoc->total = S[1].count;
			pDoc->signal = C;
			pDoc->Num = 14;
			readchessdata(nameConfig, stateConfig);
			Invalidate();
			if (C == S[5].count) {
				C = 0;
				pDoc->total = 0;
				pDoc->signal = 0;
				pDoc->Num = 0;
				pDoc->UpdateAllViews(this);
				flag = 0;
				KillTimer(6);
			}
			else {
				C++;
			}
		}
		break;
	case 7:
		if (flag == 0 || flag == 7) {
			flag = 7;
			memcpy(a, S[6].answer[C], sizeof(S[6].answer[C]));   //起始状态
			for (i = 0; i < 20; i++) {//nameConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) nameConfig[4 - d][b] = 0;
				if (a[i] == 1) nameConfig[4 - d][b] = 7;
				if (a[i] == 2) nameConfig[4 - d][b] = 8;
				if (a[i] == 3) nameConfig[4 - d][b] = 9;
				if (a[i] == 4) nameConfig[4 - d][b] = 10;
				if (a[i] == 5) nameConfig[4 - d][b] = 5;
				if (a[i] == 6) nameConfig[4 - d][b] = 2;
				if (a[i] == 7) nameConfig[4 - d][b] = 3;
				if (a[i] == 8) nameConfig[4 - d][b] = 4;
				if (a[i] == 9) nameConfig[4 - d][b] = 6;
				if (a[i] == 10) nameConfig[4 - d][b] = 1;
			}

			for (i = 0; i < 20; i++) {//stateConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) stateConfig[4 - d][b] = 0;
				if (a[i] == 1 || a[i] == 2 || a[i] == 3 || a[i] == 4)
					stateConfig[4 - d][b] = 9;

				if (a[i] == 5 && first(c, 5) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 5;
				}
				else if (a[i] == 5 && first(c, 5) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 6 && first(c, 6) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 6;
				}
				else if (a[i] == 6 && first(c, 6) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 7 && first(c, 7) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 7;
				}
				else if (a[i] == 7 && first(c, 7) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 8 && first(c, 8) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 8;
				}
				else if (a[i] == 8 && first(c, 8) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 9 && first(c, 9) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 9;
				}
				else if (a[i] == 9 && first(c, 9) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 10)
				{
					stateConfig[4 - d][b] = m;
					m++;
				}

			}

			pDoc->total = S[6].count;
			pDoc->signal = C;
			pDoc->Num = 15;
			readchessdata(nameConfig, stateConfig);
			Invalidate();
			if (C == S[6].count) {
				C = 0;
				pDoc->Num = 0;
				pDoc->total = 0;
				pDoc->signal = 0;
				pDoc->UpdateAllViews(this);
				flag = 0;
				KillTimer(7);
			}
			else {
				C++;
			}
		}
		break;
	case 8:
		if (flag == 0 || flag == 8) {
			flag = 8;
			memcpy(a, S[7].answer[C], sizeof(S[7].answer[C]));   //起始状态
			for (i = 0; i < 20; i++) {//nameConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) nameConfig[4 - d][b] = 0;
				if (a[i] == 1) nameConfig[4 - d][b] = 7;
				if (a[i] == 2) nameConfig[4 - d][b] = 8;
				if (a[i] == 3) nameConfig[4 - d][b] = 10;
				if (a[i] == 4) nameConfig[4 - d][b] = 9;
				if (a[i] == 5) nameConfig[4 - d][b] = 3;
				if (a[i] == 6) nameConfig[4 - d][b] = 4;
				if (a[i] == 7) nameConfig[4 - d][b] = 5;
				if (a[i] == 8) nameConfig[4 - d][b] = 2;
				if (a[i] == 9) nameConfig[4 - d][b] = 6;
				if (a[i] == 10) nameConfig[4 - d][b] = 1;
			}

			for (i = 0; i < 20; i++) {//stateConfig
				int d = i / 4;
				int b = i % 4;
				if (a[i] == 0) stateConfig[4 - d][b] = 0;
				if (a[i] == 1 || a[i] == 2 || a[i] == 3 || a[i] == 4)
					stateConfig[4 - d][b] = 9;

				if (a[i] == 5 && first(c, 5) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 5;
				}
				else if (a[i] == 5 && first(c, 5) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 6 && first(c, 6) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 6;
				}
				else if (a[i] == 6 && first(c, 6) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 7 && first(c, 7) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 7;
				}
				else if (a[i] == 7 && first(c, 7) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 8 && first(c, 8) == 0) {
					stateConfig[4 - d][b] = 7;
					c[i] = 8;
				}
				else if (a[i] == 8 && first(c, 8) == 1) {
					stateConfig[4 - d][b] = 8;
				}

				if (a[i] == 9 && first(c, 9) == 0) {
					stateConfig[4 - d][b] = 5;
					c[i] = 9;
				}
				else if (a[i] == 9 && first(c, 9) == 1) {
					stateConfig[4 - d][b] = 6;
				}

				if (a[i] == 10)
				{
					stateConfig[4 - d][b] = m;
					m++;
				}

			}

			pDoc->total = S[7].count;
			pDoc->signal = C;
			pDoc->Num = 16;
			readchessdata(nameConfig, stateConfig);
			Invalidate();
			if (C == S[7].count) {
				C = 0;
				pDoc->Num = 0;
				pDoc->total = 0;
				pDoc->signal = 0;
				pDoc->UpdateAllViews(this);
				flag = 0;
				KillTimer(8);
			}
			else {
				C++;
			}
		}
		break;
	}

	CView::OnTimer(nIDEvent);
}

void CHuaRong1View::Name1ToNum(cell cells[5][4]) {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			switch (cells[i][j].Getchessname()) {
			case CN_EMPTY:
				chess[4 - i][j] = 0;
				break;
			case CN_CAOCAO:
				chess[4 - i][j] = 10;
				break;
			case CN_ZHANGFEI:
				chess[4 - i][j] = 7;
				break;
			case CN_ZHAOYUN:
				chess[4 - i][j] = 8;
				break;
			case CN_MACHAO:
				chess[4 - i][j] = 5;
				break;
			case CN_GUANYU:
				chess[4 - i][j] = 6;
				break;
			case CN_HUANGZHONG:
				chess[4 - i][j] = 9;
				break;
			case CN_BIN:
				chess[4 - i][j] = 2;
				break;
			case CN_YONG:
				chess[4 - i][j] = 4;
				break;
			case CN_ZU:
				chess[4 - i][j] = 1;
				break;
			case CN_DIN:
				chess[4 - i][j] = 3;
				break;

			}
		}
	}
}

void CHuaRong1View::Name2ToNum(cell cells[5][4]) {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			switch (cells[i][j].Getchessname()) {
			case CN_EMPTY:
				chess[4 - i][j] = 0;
				break;
			case CN_CAOCAO:
				chess[4 - i][j] = 10;
				break;
			case CN_ZHANGFEI:
				chess[4 - i][j] = 5;
				break;
			case CN_ZHAOYUN:
				chess[4 - i][j] = 7;
				break;
			case CN_MACHAO:
				chess[4 - i][j] = 8;
				break;
			case CN_GUANYU:
				chess[4 - i][j] = 6;
				break;
			case CN_HUANGZHONG:
				chess[4 - i][j] = 9;
				break;
			case CN_BIN:
				chess[4 - i][j] = 1;
				break;
			case CN_YONG:
				chess[4 - i][j] = 2;
				break;
			case CN_ZU:
				chess[4 - i][j] = 4;
				break;
			case CN_DIN:
				chess[4 - i][j] = 3;
				break;

			}
		}
	}
}

void CHuaRong1View::Name3ToNum(cell cells[5][4]) {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			switch (cells[i][j].Getchessname()) {
			case CN_EMPTY:
				chess[4 - i][j] = 0;
				break;
			case CN_CAOCAO:
				chess[4 - i][j] = 10;
				break;
			case CN_ZHANGFEI:
				chess[4 - i][j] = 6;
				break;
			case CN_ZHAOYUN:
				chess[4 - i][j] = 7;
				break;
			case CN_MACHAO:
				chess[4 - i][j] = 8;
				break;
			case CN_GUANYU:
				chess[4 - i][j] = 5;
				break;
			case CN_HUANGZHONG:
				chess[4 - i][j] = 9;
				break;
			case CN_BIN:
				chess[4 - i][j] = 1;
				break;
			case CN_YONG:
				chess[4 - i][j] = 2;
				break;
			case CN_ZU:
				chess[4 - i][j] = 3;
				break;
			case CN_DIN:
				chess[4 - i][j] = 4;
				break;

			}
		}
	}
}

void CHuaRong1View::Name4ToNum(cell cells[5][4]) {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			switch (cells[i][j].Getchessname()) {
			case CN_EMPTY:
				chess[4 - i][j] = 0;
				break;
			case CN_CAOCAO:
				chess[4 - i][j] = 10;
				break;
			case CN_ZHANGFEI:
				chess[4 - i][j] = 8;
				break;
			case CN_ZHAOYUN:
				chess[4 - i][j] = 5;
				break;
			case CN_MACHAO:
				chess[4 - i][j] = 6;
				break;
			case CN_GUANYU:
				chess[4 - i][j] = 7;
				break;
			case CN_HUANGZHONG:
				chess[4 - i][j] = 9;
				break;
			case CN_BIN:
				chess[4 - i][j] = 1;
				break;
			case CN_YONG:
				chess[4 - i][j] = 2;
				break;
			case CN_ZU:
				chess[4 - i][j] = 4;
				break;
			case CN_DIN:
				chess[4 - i][j] = 3;
				break;

			}
		}
	}
}


