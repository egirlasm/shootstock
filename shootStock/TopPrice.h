#pragma once
#include "afxcmn.h"

#include "../ReportCtrl/ReportCtrl.h"
#include "afxdtctl.h"
// CTopPrice dialog


class TopData{
public:
	CString strCode;
	CString strOpen;
	CString strHigh;
	CString strLow;
	CString strClose;
	CString strRate;
	CString strVol;
	CString strBuyerPersonal;
	CString strBuyerOrganizational;
	CString strBuyerForeigner;
};

class CTopPrice : public CDialogEx
{
	DECLARE_DYNAMIC(CTopPrice)

public:
	CTopPrice(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTopPrice();

// Dialog Data
	enum { IDD = IDD_TOP_PRICE };
	CMapStringToString		m_mapJongCode;		// 리얼등록 종목
	CString							m_strScrNo;
	TopData	* m_ArrTopdata;
	int		  m_ArrCount;
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CReportCtrl m_TopList;
	void InitList(void);
	void SendSearch(void);
	void OnUpdateListData(CStringArray &arrData, CString strRealType = L"");
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPopmenuAdd();
	CDateTimeCtrl m_DateCtrl;
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonNext();
	void BackupToSqlite(void);
	afx_msg void OnBnClickedButtonSave();
	string m_szPath;
	CString m_curDate;
	afx_msg void OnBnClickedButtonInfo();
	int m_normalQueryIndex;
	afx_msg void OnBnClickedButtonChart();
};
