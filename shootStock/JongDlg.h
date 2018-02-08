#pragma once
#include "afxcmn.h"


// CJongDlg dialog

class CJongDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CJongDlg)

public:
	CJongDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CJongDlg();

// Dialog Data
	enum { IDD = IDD_JONG_LIST };
	CString							m_strScrNo;
	CMapStringToString m_MarketList;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_TreeList;
	CString strMarket;
	afx_msg void OnEnChangeEdit();
};
