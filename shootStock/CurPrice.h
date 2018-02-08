#pragma once


// CCurPrice dialog

class CCurPrice : public CDialogEx
{
	DECLARE_DYNAMIC(CCurPrice)

public:
	CCurPrice(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCurPrice();

// Dialog Data
	enum { IDD = IDD_CUR_PRICE };
	CMapStringToString		m_mapJongCode;		// 리얼등록 종목
	// Dialog Data
	
	CString							m_strScrNo;
	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
