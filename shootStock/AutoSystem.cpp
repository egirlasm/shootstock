// AutoSystem.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "AutoSystem.h"
#include "afxdialogex.h"


// CAutoSystem dialog

IMPLEMENT_DYNAMIC(CAutoSystem, CDialogEx)

CAutoSystem::CAutoSystem(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAutoSystem::IDD, pParent)
{

}

CAutoSystem::~CAutoSystem()
{
}

void CAutoSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CAutoSystem, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_START, &CAutoSystem::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CAutoSystem::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// CAutoSystem message handlers


BOOL CAutoSystem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	InitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CAutoSystem::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)   
		return TRUE;
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)   
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CAutoSystem::InitList(void)
{
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_DOUBLEBUFFER );
	m_ListCtrl.ModifyStyle(0,LVS_SINGLESEL); 
	m_ListCtrl.SetGridLines();
	m_ListCtrl.InsertColumn(0,L"#",0,50);
	m_ListCtrl.InsertColumn(1,L"코드",0,50);
	m_ListCtrl.InsertColumn(2,L"종목명",0,80);
	m_ListCtrl.InsertColumn(3,L"현재가",0,70);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_ListCtrl.InsertColumn(4,L"등락률",0,80);
	m_ListCtrl.InsertColumn(5,L"거래량",0,80);
	m_ListCtrl.InsertColumn(6,L"시가",0,80);
	m_ListCtrl.InsertColumn(7,L"고가",0,80);
	m_ListCtrl.InsertColumn(8,L"저가",0,80);
	m_ListCtrl.InsertColumn(9,L"종가",0,80);
	m_ListCtrl.InsertColumn(10,L"매수호가",0,80);
	m_ListCtrl.InsertColumn(11,L"매도호가",0,80);
}


void CAutoSystem::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	((CWnd*)GetDlgItem((IDC_BUTTON_START)))->EnableWindow(FALSE);
	((CWnd*)GetDlgItem((IDC_BUTTON_STOP)))->EnableWindow(TRUE);
}


void CAutoSystem::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	((CWnd*)GetDlgItem((IDC_BUTTON_START)))->EnableWindow(TRUE);
	((CWnd*)GetDlgItem((IDC_BUTTON_STOP)))->EnableWindow(FALSE);
}
