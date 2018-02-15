#pragma once
#include "afxcmn.h"
#include "../ReportCtrl/ReportCtrl.h"

// CDailyReport dialog

class CDailyReport : public CDialogEx
{
	DECLARE_DYNAMIC(CDailyReport)

public:
	CDailyReport(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDailyReport();

// Dialog Data
	enum { IDD = IDD_DIALOG_DAILY };
	CString							m_strScrNo;
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CReportCtrl m_RepotCtrl;
	void InitList(void);
	void SendSearch(void);
	afx_msg void OnBnClickedButtonMore();
	CString m_LastSearchedDate;
};
