// CLeftView.cpp: 实现文件
//

#include "pch.h"
#include "HuaRong1.h"
#include "CLeftView.h"
#include "HuaRong1Doc.h"

// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CFormView)

CLeftView::CLeftView()
	: CFormView(IDD_DIALOG1)
{

}

CLeftView::~CLeftView()
{
}

void CLeftView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_by1);
	DDX_Control(pDX, IDC_STATIC2, m_by2);
	DDX_Control(pDX, IDC_STATIC3, m_sj1);
	DDX_Control(pDX, IDC_STATIC4, m_sj2);
	DDX_Control(pDX, IDC_STATIC5, m_cc1);
	DDX_Control(pDX, IDC_STATIC6, m_cc2);
	DDX_Control(pDX, IDC_STATIC7, m_db1);
	DDX_Control(pDX, IDC_STATIC8, m_db2);
	DDX_Control(pDX, IDC_STATIC9, m_by11);
	DDX_Control(pDX, IDC_STATIC10, m_by22);
	DDX_Control(pDX, IDC_STATIC11, m_sj11);
	DDX_Control(pDX, IDC_STATIC12, m_sj22);
	DDX_Control(pDX, IDC_STATIC13, m_cc11);
	DDX_Control(pDX, IDC_STATIC14, m_cc22);
	DDX_Control(pDX, IDC_STATIC15, m_db11);
	DDX_Control(pDX, IDC_STATIC16, m_db22);
}

BEGIN_MESSAGE_MAP(CLeftView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CLeftView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLeftView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLeftView::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CLeftView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CLeftView::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CLeftView::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CLeftView::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CLeftView::OnBnClickedButton8)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON9, &CLeftView::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CLeftView::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CLeftView::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CLeftView::OnBnClickedButton12)
END_MESSAGE_MAP()


// CLeftView 诊断

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView 消息处理程序


void CLeftView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();

	pDoc->Num = 1;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();

	pDoc->Num = 2;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();

	pDoc->Num = 3;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();

	pDoc->Num = 4;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();

	pDoc->Num = 5;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();

	pDoc->Num = 6;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();

	pDoc->Num = 7;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();

	pDoc->Num = 8;
	pDoc->UpdateAllViews(this);
}

void CLeftView::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();
	pDoc->Num = 13;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();
	pDoc->Num = 14;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();
	pDoc->Num = 15;
	pDoc->UpdateAllViews(this);
}


void CLeftView::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();
	pDoc->Num = 16;
	pDoc->UpdateAllViews(this);
}

void CLeftView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();
	pDoc->total = 0;
	pDoc->UpdateAllViews(this);
	SetTimer(0, 100, NULL);
}


void CLeftView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString str;
	CString str1;
	if (nIDEvent == 0) {
		CHuaRong1Doc* pDoc = (CHuaRong1Doc*)CFormView::GetDocument();
		switch (pDoc -> Num) {
		case 0:
			str.Format(_T("%s"),"");
			m_by1.SetWindowText(str);
			m_by11.SetWindowText(str);
			m_by2.SetWindowText(str);
			m_by22.SetWindowText(str);
			m_sj1.SetWindowText(str);
			m_sj11.SetWindowText(str);
			m_sj2.SetWindowText(str);
			m_sj22.SetWindowText(str);
			m_cc1.SetWindowText(str);
			m_cc11.SetWindowText(str);
			m_cc2.SetWindowText(str);
			m_cc22.SetWindowText(str);
			m_db1.SetWindowText(str);
			m_db11.SetWindowText(str);
			m_db2.SetWindowText(str);
			m_db22.SetWindowText(str);
		case 9:
			if (pDoc->total != 0) {
				str.Format(_T("共：%d 步"), pDoc->total);
				m_by1.SetWindowText(str);

				str1.Format(_T("第：%d 步"), pDoc->signal);
				m_by2.SetWindowText(str1);
			}

			break;
		case 10:
			if (pDoc->total != 0) {
				str.Format(_T("共：%d 步"), pDoc->total);
				m_sj1.SetWindowText(str);

				str1.Format(_T("第：%d 步"), pDoc->signal);
				m_sj2.SetWindowText(str1);
			}

			break;
		case 11:
			if (pDoc->total != 0) {
				str.Format(_T("共：%d 步"), pDoc->total);
				m_cc1.SetWindowText(str);
				str1.Format(_T("第：%d 步"), pDoc->signal);
				m_cc2.SetWindowText(str1);
			}
			break;
		case 12:
			if (pDoc->total != 0) {
				str.Format(_T("共：%d 步"), pDoc->total);
				m_db1.SetWindowText(str);

				str1.Format(_T("第：%d 步"), pDoc->signal);
				m_db2.SetWindowText(str1);
			}
			break;
		case 13:
			if (pDoc->total != 0 && pDoc->flag == 1) {
				str.Format(_T("共：%d 步"), pDoc->total);
				m_by11.SetWindowText(str);

				str1.Format(_T("第：%d 步"), pDoc->signal);
				m_by22.SetWindowText(str1);
			}

			break;
		case 14:
			if (pDoc->total != 0 && pDoc->flag == 2) {
				str.Format(_T("共：%d 步"), pDoc->total);
				m_sj11.SetWindowText(str);

				str1.Format(_T("第：%d 步"), pDoc->signal);
				m_sj22.SetWindowText(str1);
			}

			break;
		case 15:
			if (pDoc->total != 0 && pDoc->flag == 3) {
				str.Format(_T("共：%d 步"), pDoc->total);
				m_cc11.SetWindowText(str);
				str1.Format(_T("第：%d 步"), pDoc->signal);
				m_cc22.SetWindowText(str1);
			}
			break;
		case 16:
			if (pDoc->total != 0 && pDoc->flag == 4) {
				str.Format(_T("共：%d 步"), pDoc->total);
				m_db11.SetWindowText(str);

				str1.Format(_T("第：%d 步"), pDoc->signal);
				m_db22.SetWindowText(str1);
			}
			break;
		}
	}
	CFormView::OnTimer(nIDEvent);
}



