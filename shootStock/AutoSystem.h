#pragma once
#include "afxcmn.h"
#include "../ReportCtrl/ReportCtrl.h"

// CAutoSystem dialog

class CAutoSystem : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoSystem)

public:
	CAutoSystem(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAutoSystem();

// Dialog Data
	enum { IDD = IDD_AUTO_SYSTEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void InitList(void);
	CReportCtrl m_ListCtrl;
	CString							m_strScrNo;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};
