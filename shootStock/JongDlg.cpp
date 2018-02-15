// JongDlg.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "JongDlg.h"
#include "afxdialogex.h"


// CJongDlg dialog

IMPLEMENT_DYNAMIC(CJongDlg, CDialogEx)

CJongDlg::CJongDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJongDlg::IDD, pParent)
	, strMarket(_T(""))
{

}

CJongDlg::~CJongDlg()
{
}

void CJongDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_TreeList);
	DDX_Text(pDX, IDC_EDIT1, strMarket);
}


BEGIN_MESSAGE_MAP(CJongDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CJongDlg::OnEnChangeEdit)
END_MESSAGE_MAP()


// CJongDlg message handlers


BOOL CJongDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->ShowWindow(SW_SHOW);
	// TODO:  Add extra initialization here
	CStringArray arr;
	
	CString strMarketList =  theApp.m_khOpenApi.GetCodeListByMarket(L"0");
	
	HTREEITEM top =  m_TreeList.InsertItem(L"거래소",TVI_ROOT,TVI_LAST);

	CString tmp = _T("");
	int count = 0;

	while(true){

		if(AfxExtractSubString(tmp, strMarketList, count++,';')){
			//TRACE(_T("%s\n"), tmp);
			CString tmpName =  theApp.m_khOpenApi.GetMasterCodeName(tmp);
			m_MarketList.SetAt(tmp,tmpName);
			HTREEITEM cur = m_TreeList.InsertItem(tmpName,top,TVI_LAST);
			m_TreeList.SetItemData(cur,(DWORD_PTR)tmp.GetBuffer());
		}
		else
		{
			break;
		}
	}

	strMarketList =  theApp.m_khOpenApi.GetCodeListByMarket(L"10");
	HTREEITEM top2 =  m_TreeList.InsertItem(L"코스닥",TVI_ROOT,TVI_LAST);
	count = 0;
	while(true){

		if(AfxExtractSubString(tmp, strMarketList, count++,';')){
			//TRACE(_T("%s\n"), tmp);
			CString tmpName =  theApp.m_khOpenApi.GetMasterCodeName(tmp);
			m_MarketList.SetAt(tmp,tmpName);
			HTREEITEM cur =m_TreeList.InsertItem(tmpName,top2,TVI_LAST);
			m_TreeList.SetItemData(cur,(DWORD_PTR)tmp.GetBuffer());
			//m_TreeList.SetItemData(tmp);
		}
		else
		{
			break;
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CJongDlg::OnEnChangeEdit()
{
	UpdateData(TRUE);
	CString strValue ;
	if(m_MarketList.Lookup(strMarket,strValue)){
		AfxMessageBox(strValue);
	}
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
