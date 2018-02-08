#pragma once
#include "afxcmn.h"
#include "../ReportCtrl/ReportCtrl.h"
#include "afxwin.h"

// CBuyList dialog

class CBuyList : public CDialogEx
{
	DECLARE_DYNAMIC(CBuyList)

public:
	CBuyList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CBuyList();
	CMapStringToString		m_mapJongCode;		// 리얼등록 종목
// Dialog Data
	enum { IDD = IDD_BUY_LIST };
	CString							m_strScrNo;
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	void SendJongSearch(int nCodeCount = 0, CString strCodeList = L"", int nAddType = 0);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CReportCtrl m_ListBox;
	void InitList(void);
	void OnUpdateListData(CStringArray &arrData, CString strRealType = L"");
	void GetDataSearch(void);

	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonDel();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonRefresh();
	CComboBox m_SearchComboList;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOrder1();
	afx_msg void OnBnClickedOrder2();
	afx_msg void OnBnClickedOrder3();
	void OnBnClickedButtonAdd(CString t_strCode);
	afx_msg void OnBnClickedButtonSellall();
	afx_msg void OnBnClickedButtonTest();
	afx_msg void OnHdnItemclickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
};
