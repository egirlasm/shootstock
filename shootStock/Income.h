#pragma once
#include "afxcmn.h"
#include "../ReportCtrl/ReportCtrl.h"

// CIncome dialog

class CIncome : public CDialogEx
{
	DECLARE_DYNAMIC(CIncome)

public:
	CIncome(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIncome();
	CString							m_strScrNo;
// Dialog Data
	enum { IDD = IDD_DIALOG_INCOME };
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CReportCtrl m_IncomeList;
	void GetDailyIncome(void);
	
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
