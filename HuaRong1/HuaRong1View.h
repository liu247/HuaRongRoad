
// HuaRong1View.h: CHuaRong1View 类的接口
//

#pragma once
#include <gl/glut.h>
#include <gl/GLAUX.h>
#pragma comment(lib, "legacy_stdio_definitions.lib")
#pragma comment(lib,"glaux.lib")
#include "cell.h"
#include "Search.h"
#include "HuaRong1Doc.h"
#include<string>
using namespace std;
#define  BUFSIZE 512
enum MOVEDIRETION {
	MD_LEFT,
	MD_BOTTOM,
	MD_RIGHT,
	MD_TOP,
};

class CHuaRong1View : public CView
{
protected: // 仅从序列化创建
	CHuaRong1View() noexcept;
	DECLARE_DYNCREATE(CHuaRong1View)

// 特性
public:
	CHuaRong1Doc* GetDocument() const;

// 操作
public:
	CDC* m_hDC;
	HGLRC m_hRC;
	CRect m_oldRect;
	GLfloat W, H;
	GLuint	texture[13];
	cell cells[5][4];
	GLboolean moveable;
	int i_index;
	int j_index;
	int ii_index;
	int jj_index;
	CHESSNAME mchessname;
public:
	int nID;
	Search S[8];
	char chess[5][4];
	bool movecell(MOVEDIRETION mdirection, int i, int j);
	bool IsEmpty(int i, int j);
	void ResetChessState(int index);
	void DrawBoard(unsigned int mode);
	void readchessdata(int nameConfig[5][4], int stateConfig[5][4]);
	bool Loadtexfile(char* filename, int texid);
	void init();
	void Display();
	void Name1ToNum(cell cell[5][4]);
	void Name2ToNum(cell cell[5][4]);
	void Name3ToNum(cell cell[5][4]);
	void Name4ToNum(cell cell[5][4]);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CHuaRong1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int first(int a[], int num);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // HuaRong1View.cpp 中的调试版本
inline CHuaRong1Doc* CHuaRong1View::GetDocument() const
   { return reinterpret_cast<CHuaRong1Doc*>(m_pDocument); }
#endif

