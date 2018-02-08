
// shootStockDlg.cpp : ±¸Çö ÆÄÀÏ
//

#include "stdafx.h"
#include "shootStock.h"
#include "shootStockDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>
#include <iterator>
#include <locale>
#include <string>
#include <sstream>

#define  COMMISSION	0.00015
#define  COMMISSION1	0.0015
#define  COMMISSION2	0.003
// {Á¶È¸ Å°,		¸®¾ó Å°,	Çà, ¿­, Å¸ÀÔ,			»ö º¯°æ, Á¤·Ä, ¾Õ ¹®ÀÚ, µÞ ¹®ÀÚ}
const stGRID lstFID[] = 
{
	
	{L"Á¾¸ñÄÚµå",	L"9001",	-1,	0,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
	{L"½Å¿ë±¸ºÐ",	L"917",		-1,	1,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
	{L"Á¾¸ñ¸í",		L"302",		-1,	2,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
	{L"ÇöÀç°¡",		L"10",		-1,	3,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"º¸À¯¼ö·®",	L"930",		-1,	4,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"Æò°¡±Ý¾×",	L"-1",		-1,	5,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"Æò°¡¼ÕÀÍ",	L"-1",		-1,	6,		DT_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"¼öÀÍ·ü",		L"-1",		-1,	7,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L"%"},
	{L"¸ÅÀÔ±Ý¾×",	L"932",		-1,	8,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
	{L"ÇöÀç°¡",		L"10",		-1,	9,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(°è»ê¿ëÀ¸·Î ¼û±è)
	{L"º¸À¯¼ö·®",	L"930",		-1,	10,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(°è»ê¿ëÀ¸·Î ¼û±è)
	{L"¸ÅÀÔ±Ý¾×",	L"932",		-1,	11,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(°è»ê¿ëÀ¸·Î ¼û±è)
	{L"Æò°¡±Ý¾×",	L"-1",		-1,	12,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(°è»ê¿ëÀ¸·Î ¼û±è)
};


// {Á¶È¸ Å°,		¸®¾ó Å°,	Çà, ¿­, Å¸ÀÔ,			»ö º¯°æ, Á¤·Ä, ¾Õ ¹®ÀÚ, µÞ ¹®ÀÚ}
const stGRID lstOPT10001[] = 
{
	{L"Á¾¸ñÄÚµå",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"Á¾¸ñ¸í",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// ÇöÀç°¡ ±×¸®µå
	{L"ÇöÀç°¡",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"´ëºñ±âÈ£",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"ÀüÀÏ´ëºñ",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"µî¶ôÀ²",		L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"°Å·¡·®",		L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"°Å·¡´ëºñ",	L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	/////////////////////////////////////
	// ÁÖ½Ä±âº»Á¤º¸ ±×¸®µå 1Çà
	{L"250ÃÖ°í",		L"-1",	0,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"250ÃÖ°í°¡´ëºñÀ²",L"-1",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"250ÃÖ°í°¡ÀÏ",	L"-1",	0,	3,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"¾×¸é°¡",		L"-1",	0,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" ¿ø"}, 
	{L"½Ã°¡ÃÑ¾×",	L"-1",	0,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" ¾ï"}, 
	{L"EPS",			L"-1",	0,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// ÁÖ½Ä±âº»Á¤º¸ ±×¸®µå 2Çà
	{L"250ÃÖÀú",		L"-1",	1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"250ÃÖÀú°¡´ëºñÀ²",L"-1",	1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"250ÃÖÀú°¡ÀÏ",	L"-1",	1,	3,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"ÀÚº»±Ý",		L"-1",	1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" ¾ï"}, 
	{L"´ë¿ë°¡",		L"-1",	1,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"PER",			L"-1",	1,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// ÁÖ½Ä±âº»Á¤º¸ ±×¸®µå 3Çà
	{L"¿ÜÀÎ¼ÒÁø·ü",	L"-1",	2,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"%"}, 
	{L"»óÀåÁÖ½Ä",	L"-1",	2,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" Ãµ"}, 
	{L"½Å¿ëºñÀ²",	L"-1",	2,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"%"}, 
	{L"°á»ê¿ù",		L"-1",	2,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"¿ù"}, 
	/////////////////////////////////////
	// ÁÖ½Ä±âº»Á¤º¸ ±×¸®µå 4Çà
	{L"¿¬ÁßÃÖ°í",	L"-1",	3,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"BPS",			L"-1",	3,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L""}, 
	/////////////////////////////////////
	// ÁÖ½Ä±âº»Á¤º¸ ±×¸®µå 5Çà
	{L"¿¬ÁßÃÖÀú",	L"-1",	4,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"PBR",			L"-1",	4,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L""}, 
};


// {Á¶È¸ Å°,		¸®¾ó Å°,	Çà, ¿­, Å¸ÀÔ,			»ö º¯°æ, Á¤·Ä, ¾Õ ¹®ÀÚ, µÞ ¹®ÀÚ}
const stGRID lstOPT10012[] = 
{
	{L"ÁÖ¹®¼ö·®",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"ÁÖ¹®°¡°Ý",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// ÇöÀç°¡ ±×¸®µå
	{L"¹ÌÃ¼°á¼ö·®",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"ÁÖ¹®±¸ºÐ",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"ÁÖ¹®»óÅÂ",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"µî¶ôÀ²",		L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"°Å·¡·®",		L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"°Å·¡´ëºñ",	L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	/////////////////////////////////////
	// ÁÖ½Ä±âº»Á¤º¸ ±×¸®µå 1Çà

};

// {Á¶È¸ Å°,		¸®¾ó Å°,	Çà, ¿­, Å¸ÀÔ,			»ö º¯°æ, Á¤·Ä, ¾Õ ¹®ÀÚ, µÞ ¹®ÀÚ}
const stGRID lstOPW00013[] = 
{
	{L"±ÝÀÏÀç»ç¿ë°¡´É±Ý¾×",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"Çö±Ý±Ý¾×",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// ÇöÀç°¡ ±×¸®µå
	{L"Çö±ÝÁõ°Å±Ý",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"»ç¿ë°¡´ÉÇö±Ý",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"¹Ì¼ö±Ý",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// ÁÖ½Ä±âº»Á¤º¸ ±×¸®µå 1Çà

};



class MoneyOutputter
{
public:
  MoneyOutputter(const char* const locale_name = "US") : 
      loc(locale_name), 
      output(std::use_facet<std::money_put<char> >(loc)),
      iterator(os)
  {

    os.imbue(loc);
    os.setf(std::ios_base::showbase);
  }

  std::string as_string(double value)
  {
    os.str("");  // clear string
    output.put(iterator, false, os, ' ', value * 100.0);
    return os.str();
  }

private:
  std::locale loc;
  const std::money_put<char>& output;
  std::ostringstream os;
  std::ostreambuf_iterator<char, std::char_traits<char> > iterator;
};

// ÀÀ¿ë ÇÁ·Î±×·¥ Á¤º¸¿¡ »ç¿ëµÇ´Â CAboutDlg ´ëÈ­ »óÀÚÀÔ´Ï´Ù.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ´ëÈ­ »óÀÚ µ¥ÀÌÅÍÀÔ´Ï´Ù.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Áö¿øÀÔ´Ï´Ù.

// ±¸ÇöÀÔ´Ï´Ù.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

//*******************************************************************/
// BEGIN_EVENTSINK_MAP
//*******************************************************************/
BEGIN_EVENTSINK_MAP(CshootStockDlg, CDialogEx)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 1, OnReceiveTrDataKhopenapictrl,	VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 2, OnReceiveRealDataKhopenapictrl,	VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 3, OnReceiveMsgKhopenapictrl,		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR )
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 4, OnReceiveChejanData,				VTS_BSTR VTS_I4 VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 5, OnEventConnect,					VTS_I4)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 7, OnReceiveRealCondition,			VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 8, OnReceiveTrCondition,			VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_I2)
	ON_EVENT(CshootStockDlg, IDC_KHOPENAPICTRL, 9, OnReceiveConditionVer,			VTS_I4 VTS_BSTR)
END_EVENTSINK_MAP()
// CshootStockDlg ´ëÈ­ »óÀÚ




CshootStockDlg::CshootStockDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CshootStockDlg::IDD, pParent)
	, m_staticCode(_T("Á¾¸ñÄÚµå"))
	, m_staticName(_T("Á¾¸ñ¸í"))
	, m_staticPrice(_T("ÇöÀç°¡"))
	, m_boardJongmokCode(_T(""))
{
	m_nRet = 0;
	m_nScrN0 = 0;
	m_nCount				= 0;
	m_bNextFlag			= FALSE;
	m_AccNo = L"";
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CshootStockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOPENAPICTRL, theApp.m_khOpenApi);
	DDX_Control(pDX, IDC_LIST1, m_logList);
	DDX_Control(pDX, IDC_TAB1, m_TabControl);
	DDX_Control(pDX, IDC_DEAL_LIST, m_dealList);
	DDX_Text(pDX, IDC_STATIC_CODE, m_staticCode);
	DDX_Text(pDX, IDC_STATIC_NAME, m_staticName);
	DDX_Text(pDX, IDC_STATIC_PRICE, m_staticPrice);
}

BEGIN_MESSAGE_MAP(CshootStockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_UPDATESTATUSBAR, &CshootStockDlg::OnUpdatestatusbar)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CshootStockDlg::OnSelchangeTab)

	ON_COMMAND(ID_LIST_SEARCH, &CshootStockDlg::OnListSearch)
END_MESSAGE_MAP()


// CshootStockDlg ¸Þ½ÃÁö Ã³¸®±â

BOOL CshootStockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ½Ã½ºÅÛ ¸Þ´º¿¡ "Á¤º¸..." ¸Þ´º Ç×¸ñÀ» Ãß°¡ÇÕ´Ï´Ù.

	// IDM_ABOUTBOX´Â ½Ã½ºÅÛ ¸í·É ¹üÀ§¿¡ ÀÖ¾î¾ß ÇÕ´Ï´Ù.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ÀÌ ´ëÈ­ »óÀÚÀÇ ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù. ÀÀ¿ë ÇÁ·Î±×·¥ÀÇ ÁÖ Ã¢ÀÌ ´ëÈ­ »óÀÚ°¡ ¾Æ´Ò °æ¿ì¿¡´Â
	//  ÇÁ·¹ÀÓ¿öÅ©°¡ ÀÌ ÀÛ¾÷À» ÀÚµ¿À¸·Î ¼öÇàÇÕ´Ï´Ù.
	SetIcon(m_hIcon, TRUE);			// Å« ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù.
	SetIcon(m_hIcon, FALSE);		// ÀÛÀº ¾ÆÀÌÄÜÀ» ¼³Á¤ÇÕ´Ï´Ù.

	// TODO: ¿©±â¿¡ Ãß°¡ ÃÊ±âÈ­ ÀÛ¾÷À» Ãß°¡ÇÕ´Ï´Ù.
	InitStatusBar();
	InitlogList();
	InitTabControl();
	InitDealList();
	theApp.m_khOpenApi.CommConnect();
	return TRUE;  // Æ÷Ä¿½º¸¦ ÄÁÆ®·Ñ¿¡ ¼³Á¤ÇÏÁö ¾ÊÀ¸¸é TRUE¸¦ ¹ÝÈ¯ÇÕ´Ï´Ù.
}

void CshootStockDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ´ëÈ­ »óÀÚ¿¡ ÃÖ¼ÒÈ­ ´ÜÃß¸¦ Ãß°¡ÇÒ °æ¿ì ¾ÆÀÌÄÜÀ» ±×¸®·Á¸é
//  ¾Æ·¡ ÄÚµå°¡ ÇÊ¿äÇÕ´Ï´Ù. ¹®¼­/ºä ¸ðµ¨À» »ç¿ëÇÏ´Â MFC ÀÀ¿ë ÇÁ·Î±×·¥ÀÇ °æ¿ì¿¡´Â
//  ÇÁ·¹ÀÓ¿öÅ©¿¡¼­ ÀÌ ÀÛ¾÷À» ÀÚµ¿À¸·Î ¼öÇàÇÕ´Ï´Ù.

void CshootStockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ±×¸®±â¸¦ À§ÇÑ µð¹ÙÀÌ½º ÄÁÅØ½ºÆ®ÀÔ´Ï´Ù.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Å¬¶óÀÌ¾ðÆ® »ç°¢Çü¿¡¼­ ¾ÆÀÌÄÜÀ» °¡¿îµ¥¿¡ ¸ÂÃä´Ï´Ù.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ¾ÆÀÌÄÜÀ» ±×¸³´Ï´Ù.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// »ç¿ëÀÚ°¡ ÃÖ¼ÒÈ­µÈ Ã¢À» ²ô´Â µ¿¾È¿¡ Ä¿¼­°¡ Ç¥½ÃµÇµµ·Ï ½Ã½ºÅÛ¿¡¼­
//  ÀÌ ÇÔ¼ö¸¦ È£ÃâÇÕ´Ï´Ù.
HCURSOR CshootStockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CshootStockDlg::MainOnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg){
	CString strRQName = sRQName;

	//Áõ°Å±Ý¼¼ºÎ³»¿ªÁ¶È¸¿äÃ»
	if (strRQName == _T("Áõ°Å±Ý¼¼ºÎ³»¿ªÁ¶È¸¿äÃ»"))		// ÁÖ½Ä±âº»Á¤º¸ ¼³Á¤
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt =  sizeof(lstOPW00013) / sizeof(*lstOPW00013);		// ÀüÃ¼Å©±â / ¿ø¼ÒÅ©±â = ¿ø¼Ò°³¼ö

		strRQName = _T("Áõ°Å±Ý¼¼ºÎ³»¿ªÁ¶È¸");
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"±ÝÀÏÀç»ç¿ë°¡´É±Ý¾×" );	strData.Trim();
		TraceOutputW(strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"Çö±Ý±Ý¾×" );	strData.Trim();
		TraceOutputW(strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"±ÝÀÏÀç»ç¿ë´ë»ó±Ý¾×" );	strData.Trim();
		TraceOutputW(strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"±ÝÀÏÀç»ç¿ë»ç¿ë±Ý¾×" );	strData.Trim();
		TraceOutputW(strData);
		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,L"Çö±ÝÁõ°Å±Ý" );	strData.Trim();
		TraceOutputW(strData);
		if(!strData.IsEmpty()){
			theApp.g_MyMoney = _wtoi(strData);
			if(!theApp.g_MyMoney) return;
			MoneyOutputter outputter;
			string strMoney  = outputter.as_string(stod(strData.GetBuffer()));
			USES_CONVERSION;
			strData =  A2W(strMoney.c_str());
			strData = L"´ë»ó±Ý¾×: "+ strData;
			SendMessage(WM_UPDATESTATUSBAR,1,(LPARAM)strData.GetBuffer());
		}
		//arrData.RemoveAll();
		//for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		//{
		//
		//	strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,lstOPW00013[i].strKey );	strData.Trim();
		//	TraceOutputW(strData);
		//	if(!strData.IsEmpty()){
		//		TraceOutputW(strData);
		//	}
		//	arrData.Add(strData);
		//}
	}
	if (strRQName == _T("¿¹¼ö±Ý»ó¼¼ÇöÈ²¿äÃ»"))		// ÁÖ½Ä±âº»Á¤º¸ ¼³Á¤
	{
		CString strData;

		strRQName = _T("¿¹¼ö±Ý»ó¼¼ÇöÈ²¿äÃ»");

		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"¿¹¼ö±Ý");	strData.Trim();

		theApp.g_MyMoney = _wtoi(strData);
		if(!theApp.g_MyMoney) return;
		MoneyOutputter outputter;
		string strMoney  = outputter.as_string(stod(strData.GetBuffer()));
		USES_CONVERSION;
		strData =  A2W(strMoney.c_str());
		strData = L"¿¹¼ö±Ý: "+ strData;
		SendMessage(WM_UPDATESTATUSBAR,1,(LPARAM)strData.GetBuffer());

		//SetDlgItemInt(IDC_EDIT1,atoi(strData));


		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"d+1ÃßÁ¤¿¹¼ö±Ý");	strData.Trim();
		//SetDlgItemInt(IDC_EDIT2,atoi(strData));



		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"d+2ÃßÁ¤¿¹¼ö±Ý");	strData.Trim();
		//SetDlgItemInt(IDC_EDIT3,atoi(strData));



		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"d+1Ãâ±Ý°¡´É±Ý¾×");	strData.Trim();
		//SetDlgItemInt(IDC_EDIT4,atoi(strData));


		strMoney  = outputter.as_string(stod(strData.GetBuffer()));

		strData =  A2W(strMoney.c_str());
		strData = L"d+1Ãâ±Ý°¡´É: "+strData;
		SendMessage(WM_UPDATESTATUSBAR,2,(LPARAM)strData.GetBuffer());

		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"d+2Ãâ±Ý°¡´É±Ý¾×");	strData.Trim();


		strMoney  = outputter.as_string(stod(strData.GetBuffer()));

		strData =  A2W(strMoney.c_str());
		strData = L"d+2Ãâ±Ý°¡´É: "+strData;
		SendMessage(WM_UPDATESTATUSBAR,3,(LPARAM)strData.GetBuffer());
		//SetDlgItemInt(IDC_EDIT5,atoi(strData));
		//SetDataJongInfoGrid(arrData);
	}


	CString strPrevNext(sPrevNext);

	if (strRQName == _T("°èÁÂ¼öÀÍ·ü"))			// °èÁÂ¼öÀÍ·ü
	{
		m_bNextFlag = FALSE;
		CString strData;
		int nFieldCnt = sizeof(lstFID) / sizeof(*lstFID);		// ÀüÃ¼Å©±â / ¿ø¼ÒÅ©±â = ¿ø¼Ò°³¼ö

		strRQName = _T("°èÁÂ¼öÀÍ·ü");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);	//µ¥ÀÌÅÍ °Ç¼ö
		m_nCount += nCnt;	//µ¥ÀÌÅÍ °Ç¼ö¿¡ ±×¸®µå Çì´õ Ãß°¡
		//m_grdRate.SetRowCount(m_nCount);
		CString strIndex= L"";
		for (i = 0; i < nCnt; i++)
		{
			CString strCode;
			strIndex.Format(L"%d", i);

			int dwitem = 0;
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstFID[j].strKey);
				strData.Trim();
				if (j == 0)	//Á¾¸ñ¸í
				{
					strCode = strData;
					m_mapJongCode.SetAt(strCode, strIndex);

					//m_grdKwanSim.SetRowHeight(i, 20);		// ÇàÀÇ ³ôÀÌ ¼³Á¤
					//m_grdKwanSim.SetItemText(i, 0, strCode);
					int dwCount = m_dealList.GetItemCount();

					dwitem = m_dealList.InsertItem(dwCount,strCode,0);
				}
				else if (j == 1) //½Å¿ë±¸ºÐ
				{
					if (strData == _T("00"))
					{
						strData = _T("Çö±Ý");
					} 
					else if (strData == _T("03"))
					{
						strData = _T("À¶ÀÚ");
					}
					else if (strData == _T("99"))
					{
						strData = _T("À¶ÀÚÇÕ");
					}

					m_dealList.SetItemText(i,j, theApp.ConvDataFormat(lstFID[j].nDataType, strData, lstFID[j].strBeforeData,lstFID[j].strAfterData));
				}
				if (strData != "")
				{
					if(j == 4){
						m_OrderList.SetAt(strCode,strData);
					}

					m_dealList.SetItemText(i,j, theApp.ConvDataFormat(lstFID[j].nDataType, strData, lstFID[j].strBeforeData,lstFID[j].strAfterData));
					//m_grdRate.SetItemFormat(i + 1 + m_nNextRow, lstFID[j].nCol, lstFID[j].nAlign);
					//m_grdRate.SetItemText(i + 1 + m_nNextRow, j, theApp.ConvDataFormat(lstFID[j].nDataType, strData, lstFID[j].strBeforeData, lstFID[j].strAfterData));
				}
			}

			int nRow(0);
			//nRow = i + 1 + m_nNextRow;

			//Á¾¸ñº° ¼öÀÍ·ü °è»ê
			//SetRate(nRow, strCode);

			//CString strIndex;
			//strIndex.Format(_T("%d"), nRow);

			//Á¾¸ñÀ» Å°°ªÀ¸·Î ÇØ¼­ ·Î¿ì°ªÀ» °ü¸®ÇÑ´Ù.
			//m_mapJongCode.SetAt(strCode, strIndex);
		}

		//ÃÑ ¼öÀÍ·ü °è»ê
		//SetTotalRate();

		if (strPrevNext == "2")	//¿¬¼ÓÁ¶È¸
		{
			m_bNextFlag = TRUE;	//¿¬¼ÓÁ¶È¸¿©ºÎ
			//m_nCount = m_nCount - 1;	//±×¸®µå Çì´õRow¼ö/¸¦ »«´Ù.
			//m_nNextRow = m_nCount;	//¿¬¼ÓÁ¶È¸·Î ¸¶Áö¸· Row°ªÀ» ÀúÀå.

			//CString strAccNo;
			//m_EdtAcc.GetWindowText(strAccNo);	//ÀÔ·ÂÇÑ °èÁÂ¹øÈ£.

			//¿¬¼ÓÁ¶È¸¸¦ ÇÑ´Ù.
			theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);
			theApp.m_khOpenApi.CommRqData(L"°èÁÂ¼öÀÍ·ü", L"OPT10085", 2, m_strScrNo);
		}

		//¿¬¼ÓÁ¶È¸°¡ ¾Æ´Ò¶§¸¸ ½Ç½Ã°£ µî·ÏÀ» ÇÑ´Ù.
		if (!m_bNextFlag)
		{
			CString strRQName = _T("°ü½ÉÁ¾¸ñ"), strCodeList, strCode;
			long  nCodeCount(0);

			for (int nRow = 0; nRow < m_nCount; nRow++)
			{
				nCodeCount++;
				strCode = m_dealList.GetItemText(nRow, 0);
				strCode.Trim();
				strCode + ";";
				strCodeList += strCode ;
				//Á¾¸ñÄÚµå = Àü¹® Á¶È¸ÇÒ Á¾¸ñÄÚµå
				theApp.m_khOpenApi.SetInputValue(L"Á¾¸ñÄÚµå"	,  strCode);
				theApp.m_khOpenApi.CommRqData( L"ÁÖ½Ä±âº»Á¤º¸¿äÃ»",  L"OPT10001", 0, m_strScrNo); 
			}

			long lRet = theApp.m_khOpenApi.CommKwRqData(strCodeList, 0, nCodeCount, 0, strRQName, m_strScrNo);
			if (!lRet)
			{
				return;
			}

		}
	}

	if (strRQName == _T("ÁÖ½Ä±âº»Á¤º¸¿äÃ»"))			// °èÁÂ¼öÀÍ·ü//if (!lstrcmp(sRealType, L"ÁÖ½ÄÃ¼°á"))	// ÁÖ½ÄÃ¼°á
	{

		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10001) / sizeof(*lstOPT10001);		// ÀüÃ¼Å©±â / ¿ø¼ÒÅ©±â = ¿ø¼Ò°³¼ö

		strRQName = _T("ÁÖ½Ä±âº»Á¤º¸");




		arrData.RemoveAll();
		for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		{
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, lstOPT10001[nIdx].strKey);	strData.Trim();
			if(nIdx== 0){
				if(strData == m_boardJongmokCode){
					//strData = theApp.m_khOpenApi.GetCommRealData(strData, 10);	strData.Trim(); //ÇöÀç°¡
					
					m_staticCode = strData;
					
					m_staticName =   theApp.m_khOpenApi.GetMasterCodeName(strData);
					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"ÇöÀç°¡");	strData.Trim();
					m_staticPrice = strData;
					//TraceOutputW(strData);
					UpdateData(FALSE);
				}
			}
			arrData.Add(strData);
		}
		//SetDataJongInfoGrid(arrData);

		//m_grdRate.SetItemText(_ttoi(strIndex), i, theApp.ConvDataFormat(lstFID[i].nDataType, strData, lstFID[i].strBeforeData, lstFID[i].strAfterData));
		m_dealList.SetItemText(0, 3, arrData.GetAt(2));

		//Á¾¸ñº° ¼öÀÍ·ü °è»ê
		CString strCode = arrData.GetAt(0);

		CString strIndex;
		if (!m_mapJongCode.Lookup(strCode, strIndex))
		{
			return;
		}
		SetRate(_wtoi(strIndex), strCode);

		//ÃÑ ¼öÀÍ·ü °è»ê
		//SetTotalRate();
	}

	if (strRQName == _T("ÁÖ¹®Ã¼°á¿äÃ»"))			// °èÁÂ¼öÀÍ·ü//if (!lstrcmp(sRealType, L"ÁÖ½ÄÃ¼°á"))	// ÁÖ½ÄÃ¼°á
	{
		TraceOutputW(strRQName);
		CString strData;
		CStringArray arrData;
		int nFieldCnt = 60;// sizeof(lstOPT10012) / sizeof(*lstOPT10012);		// ÀüÃ¼Å©±â / ¿ø¼ÒÅ©±â = ¿ø¼Ò°³¼ö

		strRQName = _T("ÁÖ¹®Ã¼°á");
		arrData.RemoveAll();
		for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		{
			strData.Format(L"%d",nIdx);
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,strData );	strData.Trim();
			if(!strData.IsEmpty()){
				TraceOutputW(strData);
			}
			arrData.Add(strData);
		}
	}
	////end
}



//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : Á¶È¸ ÀÀ´ä Ã³¸®
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (_wtoi(strScrType))
		{
		case 0:		// ¸ÞÀÎÃ¢
			{
				((CshootStockDlg *)pWnd)->MainOnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);
			}
			break;
		case 1:
			{
				
				((CBuyList *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 2:
			{

				((CCurPrice *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 3:
			{

				((CTopPrice *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 4:
			{

				((CDailyReport *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveMsgKhopenapictrl
//! Function      : Á¶È¸ ¿¡·¯ Ã³¸®
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveMsgKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sMsg)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CString strRQ = sRQName;
	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		CString strData;
		strData.Format(_T("[%s] [%s] ¿À·ù"), sRQName, sTrCode);

		CString strRQName = strRQ.Mid(4);
		switch (_wtoi(strScrType))
		{
		case 0:		// ÇöÀç°¡
			{
				//((CCurrentPriceDlg *)pWnd)->OnReceiveMsgKhopenapictrl(sScrNo, strRQName, sTrCode, sMsg);
				//pWnd->MessageBox(sMsg, strData, MB_ICONERROR | MB_OK);
				TraceOutputW(sMsg);
			}
			break;


		}
	}
}
//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : ½Ç½Ã°£ Ã³¸®
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::MainOnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	
	//Áõ°Å±Ý¼¼ºÎ³»¿ªÁ¶È¸¿äÃ»

	if (!lstrcmp(sRealType, L"ÁÖ½Ä½Ã¼¼"))		// ÁÖ½Ä½Ã¼¼
	{
		TraceOutputW(sRealType);
	}
	else if (!lstrcmp(sRealType, L"ÁÖ½ÄÃ¼°á"))	// ÁÖ½ÄÃ¼°á
	{



		CString strIndex, strData;


		if(sJongmokCode == m_boardJongmokCode){
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 10);	strData.Trim(); //ÇöÀç°¡
			m_staticPrice = strData;
			m_staticCode = sJongmokCode;
			m_staticName =   theApp.m_khOpenApi.GetMasterCodeName(sJongmokCode);
			//TraceOutputW(strData);
			UpdateData(FALSE);
		}

		if (!m_mapJongCode.Lookup(sJongmokCode, strIndex))
		{
			return;
		}



		CString strCode;

		int i, nFieldCnt = sizeof(lstFID) / sizeof(*lstFID);		// ÀüÃ¼Å©±â / ¿ø¼ÒÅ©±â = ¿ø¼Ò°³¼ö
		for (i = 0; i < nFieldCnt; i++)
		{
			if (_wtoi(lstFID[i].strRealKey) < 0)
			{
				continue;
			}

			//½Ç½Ã°£ µ¥ÀÌÅÍ¸¦ Ç×¸ñ¿¡ ¸Â°Ô °¡Á®¿Â´Ù.
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstFID[i].strRealKey));	strData.Trim();

			//Ç×¸ñ¿¡ ¸Â´Â µ¥ÀÌÅÍ°¡ ÀÖÀ»¶§¸¸ ±×¸®µå¿¡ Ç¥½ÃÇÑ´Ù.
			if (strData != "")
			{
				//m_grdRate.SetItemText(_ttoi(strIndex), i, theApp.ConvDataFormat(lstFID[i].nDataType, strData, lstFID[i].strBeforeData, lstFID[i].strAfterData));
				m_dealList.SetItemText(_ttoi(strIndex), i, theApp.ConvDataFormat(lstFID[i].nDataType, strData, lstFID[i].strBeforeData, lstFID[i].strAfterData));
			}
		}

		//Á¾¸ñº° ¼öÀÍ·ü °è»ê
		strCode = sJongmokCode;
		SetRate(_ttoi(strIndex), strCode);

		//ÃÑ ¼öÀÍ·ü °è»ê
		//SetTotalRate();
	}
}
//*******************************************************************/
//! Function Name : OnReceiveRealDataKhopenapictrl
//! Function      : ½Ç½Ã°£ Ã³¸®
//! Param         : LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (_wtoi(strScrType))
			{
			case 0:		// main window
				{
					//TraceOutputW(sRealType);
					this->MainOnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
					//this->onrecvrea
					
				}
				break;
			case 1:		// °ü½ÉÁ¾¸ñ
				{
					
					 ((CBuyList *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 2:		// ÇöÀç°¡
				{

					((CCurPrice *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 3:		// µî¶ô·ü
				{

					((CTopPrice *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 4:		// µî¶ô·ü
				{

					((CDailyReport *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			}
		}
	}

	// Àå¿î¿µ Á¤º¸ Ã³¸®
	if (!lstrcmp(sRealType, L"Àå½ÃÀÛ½Ã°£"))
	{
		int i;
		CString strData[3], strMsg;
		// 0: Àå¿î¿µ±¸ºÐ, 1:½Ã°£, 2:Àå½ÃÀÛ ¿¹»óÀÜ¿©½Ã°£
		for (i = 0; i < 3; i++)
		{
			strData[i] = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, i);	strData[i].Trim();
		}
		strMsg.Format(L"Àå¿î¿µ±¸ºÐ : %s\r\n½Ã°£ : %s\r\n¿¹»óÀÜ¿©½Ã°£ : %s", strData[0], strData[1], strData[2]);

		if (_wtoi(strData[2]) == 10)
		{
			ReplyMessage(S_OK);		// SendMessage Ç®¸²
			MessageBox(strMsg, L"Àå¿î¿µ Á¤º¸", MB_ICONINFORMATION | MB_OK);
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveChejanData
//! Function      : Ã¼°áÀÜ°í ½Ç½Ã°£ Ã³¸®
//! Param         : LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (_wtoi(strScrType))
			{
			case 0:		// ÇöÀç°¡
				{
					//((CCurrentPriceDlg *)pWnd)->OnReceiveChejanData(sGubun, nItemCnt, sFidList);

					CString strGuBun(sGubun), strAccNo, strAcc;

					strAccNo	= theApp.m_khOpenApi.GetChejanData(9201);	// Ã¼°áµÈ Á¾¸ñÀÇ °èÁÂ¹øÈ£
												// ÇöÀç °èÁÂ¹øÈ£
					TraceOutputW(strAccNo);
					
					CString orderNo =  theApp.m_khOpenApi.GetChejanData(9201); //9203 ÁÖ¹®¹øÈ£
					TraceOutputW(orderNo);

					CString orderStatus =  theApp.m_khOpenApi.GetChejanData(913); //913 ÁÖ¹®»óÅÂ
					TraceOutputW(orderStatus);
					//ÇöÀç ¼öÀÍ·ü Á¶È¸ÇÑ °èÁÂ¹øÈ£¿¡ ÀÖ´Â Ã¼°áµÈ Á¾¸ñ¸¸ ¹ÞÀ» ¼ö ÀÖ°Ô Ã³¸®.
					if (strAccNo == strAcc)
					{
						if (strGuBun == "4")
						{
							TraceOutputW(L"º¸À¯Á¾¸ñ ÀçÁ¶È¸");
							//OnBtnSearch(); //º¸À¯Á¾¸ñÀ» ÀçÁ¶È¸ÇÑ´Ù.
						}
					}

				}
				break;

			}
		}
	}
}

//*******************************************************************/
//! Function Name : OnReceiveRealCondition
//! Function      : Á¶°Ç°Ë»ö ½Ç½Ã°£ Á¾¸ñ »ðÀÔ/»èÁ¦
//! Param         : LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveRealCondition(LPCTSTR strCode, LPCTSTR strType, LPCTSTR strConditionName, LPCTSTR strConditionIndex)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CWnd *pWnd;
	CString strKey, strScrType;
	POSITION pos = m_mapScreenNum.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreenNum.GetNextAssoc(pos, strKey, strScrType);
		if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
		{
			switch (_wtoi(strScrType))
			{
			case 3:		// Á¶°Ç°Ë»ö
				{
					//((CRealAddDlg *)pWnd)->OnReceiveRealCondition(strCode, strType, strConditionName, strConditionIndex);
				}
				break;
			}
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveTrCondition
//! Function			: Á¶°Ç°Ë»ö Á¾¸ñÁ¶È¸ ÀÀ´ä
//! Param				: LPCTSTR sScrNo					- È­¸é¹øÈ£
//!						: LPCTSTR strCodeList			- Á¾¸ñ¸®½ºÆ®
//!						: LPCTSTR strConditionName	- Á¶°Ç¸í
//!						: int nIndex								- Á¶°Ç¸íÀÎµ¦½º
//!						: int nNext								- ¿¬¼ÓÁ¶È¸¿©ºÎ(2: ¿¬¼ÓÁ¶È¸, 0:¿¬¼ÓÁ¶È¸¾øÀ½)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveTrCondition(LPCTSTR sScrNo, LPCTSTR strCodeList, LPCTSTR strConditionName, int nIndex, int nNext)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (_wtoi(strScrType))
		{
		case 3:	//Á¶°Ç°Ë»ö
			{
				//((CRealAddDlg *)pWnd)->OnReceiveTrCondition(sScrNo, strCodeList, strConditionName, nIndex, nNext);
			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name	: OnReceiveConditionVer
//! Function			: »ç¿ëÀÚ Á¶°Ç½Ä ÀÀ´ä
//! Param				: BOOL bRet							- ¼º°ø(TRUE), ½ÇÆÐ(FALSE)
//!						: LPCTSTR sMsg					- ¸Þ¼¼Áö(reserved)
//! Return        : void
//! Create        : , 2015/04/20
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnReceiveConditionVer(long lRet, LPCTSTR sMsg)
{
	if (!this->GetSafeHwnd())
	{
		return;
	}

	if(lRet != 1)
	{// »ç¿ëÀÚ Á¶°Ç°Ë»ö½Ä ¼­¹ö¿äÃ»Áß ¿¡·¯°¡ ¹ß»ýÇÑ °æ¿ì...
		CString		strErr; strErr.Format(_T("%s [%d]"), sMsg, lRet);
		AfxMessageBox(strErr);
		return;
	}

	int nScrNo = GetNextScreenNum(3);
	CString strScrNo;
	strScrNo.Format(L"%04d", nScrNo);

	CString strScrType, strKey = strScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd *pWnd = NULL;
	if (m_mapScreen.Lookup(strKey, (void *&)pWnd) && pWnd)
	{
		switch (_wtoi(strScrType))
		{
		case 3:	//Á¶°Ç°Ë»ö
			{
				//((CRealAddDlg *)pWnd)->OnReceiveConditionVer(lRet, sMsg);
			}
			break;
		}
	}
}

//*******************************************************************/
//! Function Name : OnEventConnect
//! Function      : Á¢¼Ó Åëº¸ Ã³¸®
//! Param         : LONG nItemCnt
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CshootStockDlg::OnEventConnect(LONG nItemCnt)
{
	if (nItemCnt == 0)
	{
		// Á¢¼Ó Á¤»óÃ³¸®
		OutputDebugString(L"connect successs");

		
		SendMessage(WM_UPDATESTATUSBAR,0,(LPARAM)L"¿¬°á¼º°ø.");
		this->OnBtnGetAccData();
		m_buyList.GetDataSearch();
		//¼öÀÍ·ü°è»ê Á¶È¸ //8100875411

		//theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);
		//long lRet = theApp.m_khOpenApi.CommRqData(L"°èÁÂÆò°¡ÀÜ°í³»¿ª¿äÃ»", L"OPW00018", 0, m_strScrNo);
		//if (!theApp.IsError(lRet))
		//{
		//}

		//theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);
		// lRet = theApp.m_khOpenApi.CommRqData(L"°èÁÂ¼öÀÍ·ü", L"OPT10085", 0, m_strScrNo);
		//if (!theApp.IsError(lRet))
		//{
		//}
		//theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);
		//lRet = theApp.m_khOpenApi.CommRqData(L"ÁÖ¹®Ã¼°á¿äÃ»", L"OPT10012", 0, m_strScrNo);
		//if (!theApp.IsError(lRet))
		//{
		//}
	}
	else
	{
		// Á¢¼Ó ºñÁ¤»ó Ã³¸®
		EndDialog(IDCANCEL);
	}
}

//*******************************************************************/
//! Function Name : GetNextScreenNum
//! Function      : ´ÙÀ½ È­¸é ¹øÈ£ Ãëµæ
//! Param         : int nScreenType
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
BOOL CshootStockDlg::GetNextScreenNum(int nScreenType)
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	static int nRepeat = 0;
	m_nScrN0++;
	if (m_nScrN0 > 9999)
	{
		nRepeat++;
		m_nScrN0 = 1;
	}

	if (nRepeat > 1)
	{
		nRepeat = 0;
		AfxMessageBox(L"´õ ÀÌ»ó È­¸éÀ» ¿­¼ö ¾ø½À´Ï´Ù.´Ù¸¥ È­¸éÀ» ´Ý°í ½ÇÇà ÇØ ÁÖ¼¼¿ä~!");
		return FALSE;
	}

	CString strKey, strTemp;
	strKey.Format(L"%04d", m_nScrN0);
	if (m_mapScreenNum.Lookup(strKey, strTemp))
	{
		return GetNextScreenNum(nScreenType);
	}

	nRepeat = 0;
	strTemp.Format(L"%d", nScreenType);
	m_mapScreenNum.SetAt(strKey, strTemp);
	return TRUE;
}



afx_msg LRESULT CshootStockDlg::OnUpdatestatusbar(WPARAM wParam, LPARAM lParam)
{
	return m_StatusBar.SetPaneText(wParam,(LPCTSTR)lParam);
}


void CshootStockDlg::InitStatusBar(void)
{
	UINT m_IsCreated =  m_StatusBar.Create(this);


	UINT  Indicates[5]; 
	for (int i = 1; i<5;i++)
	{
		Indicates[i] = 50+i;
	}

	m_StatusBar.SetIndicators(Indicates,5);
	CRect rect;
	GetClientRect(&rect);
	UINT PaneWidth = rect.Width();

	m_StatusBar.SetPaneInfo(0,0,SBPS_NORMAL,PaneWidth * 10 / 100);
	m_StatusBar.SetPaneInfo(1,0,SBPS_NORMAL,PaneWidth * 21 / 100);
	m_StatusBar.SetPaneInfo(2,0,SBPS_NORMAL,PaneWidth * 21 / 100);
	m_StatusBar.SetPaneInfo(3,0,SBPS_NORMAL,PaneWidth * 21 / 100);
	m_StatusBar.SetPaneInfo(4,0,SBPS_NORMAL,PaneWidth * 27 / 100);

	m_StatusBar.SetPaneText(0,L" ¿¬°ÉÁß..");
	m_StatusBar.SetPaneText(1,L"¿¹¼ö±Ý: N/A");
	m_StatusBar.SetPaneText(2,L"d+1Ãâ±Ý°¡´É N/A");
	m_StatusBar.SetPaneText(3,L"d+2Ãâ±Ý°¡´É N/A");
	m_StatusBar.SetPaneText(4,L"ÇöÀç½Ã°£");
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
}


void CshootStockDlg::OnBtnGetAccData(void)
{

	m_AccNo = theApp.m_khOpenApi.GetLoginInfo(L"ACCLIST");
	m_AccNo.Replace(L";",L"");
	CString   strSafeKeyStatus = theApp.m_khOpenApi.GetLoginInfo(L"KEY_BSECGB" );

	//HWND pWnd = ::FindWindow(NULL,L"°èÁÂºñ¹Ð¹øÈ£ ÀÔ·Â (¹öÀü: 3.72)");
	CWnd *pWnd = FindWindowEx(this->m_hWnd,NULL,NULL,L"°èÁÂºñ¹Ð¹øÈ£ ÀÔ·Â (¹öÀü: 3.72)");
	//FindWindowEx(this)	::SetWindowPos (pWnd,NULL,0,0,0,0,SWP_SHOWWINDOW);
	CString strServerType =  theApp.m_khOpenApi.KOA_Functions(_T("GetServerGubun"), _T(""));
	if(strServerType == L"1"){//¸ðÀÇÅõÀÚ
		AfxMessageBox(L"ÇöÀç Á¢¼ÓÇÑ ¼­¹ö´Â ¸ðÀÇÅõÀÚ¼­¹öÀÔ´Ï´Ù,ºñ¹Ð¹øÈ£ ¾Æ¹«°Å³ª ÀÔ·ÂÇÏ¼Åµµ µË´Ï´Ù !",MB_ICONINFORMATION);
		theApp.m_khOpenApi.KOA_Functions(_T("ShowAccountWindow"), _T(""));
	}else{
		MessageBox(L"°æ°í!ÁÖÀÇ!À§Çè!",L"ÇöÀç Á¢¼ÓÇÑ ¼­¹ö´Â ¸®¾ó¼­¹öÀÔ´Ï´Ù,\nºñ¹Ð¹øÈ£ ¿À·ù½Ã °èÁÂ°¡ Á¤Áö µË´Ï´Ù\nÀ¯ÀÇÇØÁÖ½Ã±æ¹Ù¶ø´Ï´Ù !",MB_ICONWARNING);
		theApp.m_khOpenApi.KOA_Functions(_T("ShowAccountWindow"), _T(""));
	}
	
	


// 	¿©±â¼­ strAcctList´Â ';'·Î ºÐ¸®ÇÑ º¸À¯°èÁÂ ¸ñ·ÏÀÓ
// 		¿¹) "3040525910;567890;3040526010"

	if (!GetNextScreenNum(0))
	{
		return;
	}


	this->m_strScrNo.Format(_T("%04d"), m_nScrN0);


	m_mapScreen.SetAt(m_strScrNo, this);

	theApp.g_MyMoney = 100000;
	//CString strRQName = _T("Áõ°Å±Ý¼¼ºÎ³»¿ªÁ¶È¸¿äÃ»");
	//CString strTRCode = TR_OPW00013;
	////theApp.theApp.m_khOpenApi.SetInputValue("Á¾¸ñÄÚµå", "113810");
	////°èÁÂ¹øÈ£ = Àü¹® Á¶È¸ÇÒ º¸À¯°èÁÂ¹øÈ£  //51653280
	//theApp.m_khOpenApi.SetInputValue(_T("°èÁÂ¹øÈ£")	, m_AccNo);
	////theApp.theApp.m_khOpenApi.SetInputValue("°èÁÂ¹øÈ£"	,  "5165328010");
	////ºñ¹Ð¹øÈ£ = »ç¿ë¾ÈÇÔ(°ø¹é)
	//theApp.m_khOpenApi.SetInputValue(_T("ºñ¹Ð¹øÈ£")	,  _T(""));

	//long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	//CString		strErr;
	//if (!theApp.IsError(lRet))
	//{
	//	strErr.Format(_T("ÁÖ½Ä±âº»Á¤º¸¿äÃ» ¿¡·¯ [%s][%d]"), strTRCode, lRet);
	//	OutputDebugString(strErr);
	//};

	//CString strRQName = _T("¿¹¼ö±Ý»ó¼¼ÇöÈ²¿äÃ»");
	//CString strTRCode = TR_OPW00001;
	////theApp.theApp.m_khOpenApi.SetInputValue("Á¾¸ñÄÚµå", "113810");
	////°èÁÂ¹øÈ£ = Àü¹® Á¶È¸ÇÒ º¸À¯°èÁÂ¹øÈ£  //51653280
	//theApp.m_khOpenApi.SetInputValue(_T("°èÁÂ¹øÈ£")	, m_AccNo);
	////theApp.theApp.m_khOpenApi.SetInputValue("°èÁÂ¹øÈ£"	,  "5165328010");
	////ºñ¹Ð¹øÈ£ = »ç¿ë¾ÈÇÔ(°ø¹é)
	//theApp.m_khOpenApi.SetInputValue(_T("ºñ¹Ð¹øÈ£")	,  _T("2419"));

	////ºñ¹Ð¹øÈ£ÀÔ·Â¸ÅÃ¼±¸ºÐ = 00
	//theApp.m_khOpenApi.SetInputValue(_T("ºñ¹Ð¹øÈ£ÀÔ·Â¸ÅÃ¼±¸ºÐ")	,  _T("2419"));

	////Á¶È¸±¸ºÐ = 1:ÃßÁ¤Á¶È¸, 2:ÀÏ¹ÝÁ¶È¸
	//theApp.m_khOpenApi.SetInputValue(_T("Á¶È¸±¸ºÐ")	,  _T("2"));
	//long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	//CString		strErr;
	//if (!theApp.IsError(lRet))
	//{
	//	strErr.Format(_T("ÁÖ½Ä±âº»Á¤º¸¿äÃ» ¿¡·¯ [%s][%d]"), strTRCode, lRet);
	//	OutputDebugString(strErr);
	//};
}


void CshootStockDlg::InitlogList(void)
{
	CRect rect;
	m_logList.GetClientRect(&rect);//»ñÈ¡ÁÐ±íÊÓÍ¼¿Ø¼þµÄ¿í¶È

	int nWidth = rect.Width();

	m_logList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);
	m_logList.InsertColumn(0, _T("No"), LVCFMT_LEFT);
	m_logList.InsertColumn(1, _T("Time"), LVCFMT_LEFT);
	m_logList.InsertColumn(2, _T("Information"), LVCFMT_LEFT);

	//ÉèÖÃ¸÷ÁÐµÄ¿í¶È

	m_logList.GetClientRect(&rect);//»ñÈ¡ÁÐ±íÊÓÍ¼¿Ø¼þµÄ¿í¶È

	nWidth = rect.Width();
	m_logList.SetColumnWidth(0, nWidth * 7 / 100);//Ãû³ÆÕ¼25%
	m_logList.SetColumnWidth(1, nWidth * 15 / 100);//ÃÜÂëÕ¼13%
	m_logList.SetColumnWidth(2, nWidth * 78 / 100);//µØÖ·Õ¼25%


	m_logList.SetBkColor(RGB(0,0,0)); 
	m_logList.SetTextColor(RGB(0,255,102)); 
	m_logList.SetTextBkColor(RGB(0,0,0)); 
}
void CshootStockDlg::TraceOutputA(const char* fmt,...)
{
	string str = fmt;
	str += "\r\n";
	USES_CONVERSION;
	//m_RichEdit.SetSel(-1, -1);
	//m_RichEdit.ReplaceSel( (LPCTSTR)A2W(str.c_str()) );
	//m_RichEdit.PostMessage(WM_VSCROLL, SB_BOTTOM,0); 
	//InitRichEdit();
	// 

	//Èç¹û´óÓÚÌõÄ¿´óÓÚ1000Ôò¸Éµô
	//if(t_loglistControl.GetItemCount() > 1000 )
	//t_loglistControl.DeleteAllItems();

	CString time; //»ñÈ¡ÏµÍ³Ê±¼ä
	CTime tm; 

	tm = CTime::GetCurrentTime(); 

	time=tm.Format("%X"); 

	//OutputDebugString(time);
	//Ìí¼Ó
	CString l_index;

	int dwCount = m_logList.GetItemCount();

	l_index.Format(_T("%d"),dwCount+1);

	int dwitem = m_logList.InsertItem(dwCount,l_index,0);
	m_logList.SetItem(dwitem,1,1,time,0,0,0,0);
	m_logList.SetItem(dwitem,2,1,A2W(str.c_str()),0,0,0,0);
	m_logList.EnsureVisible(dwitem,TRUE);
}

void CshootStockDlg::TraceOutputW(const TCHAR* fmt,...)
{
	CString time; //»ñÈ¡ÏµÍ³Ê±¼ä
	CTime tm; 

	tm = CTime::GetCurrentTime(); 

	time=tm.Format("%X"); 

	//OutputDebugString(time);
	//Ìí¼Ó
	CString l_index;

	int dwCount = m_logList.GetItemCount();

	l_index.Format(_T("%d"),dwCount+1);

	int dwitem = m_logList.InsertItem(dwCount,l_index,0);
	m_logList.SetItem(dwitem,1,1,time,0,0,0,0);
	m_logList.SetItem(dwitem,2,1,fmt,0,0,0,0);
	m_logList.EnsureVisible(dwitem,TRUE);
}

void CshootStockDlg::InitTabControl(void)
{
	TCITEM   tm;   
	CImageList pImageList;


	pImageList.Create(16, 16, ILC_COLOR16|ILC_MASK,0,2);
	pImageList.SetBkColor(::GetSysColor(COLOR_BTNFACE));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	pImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	//this->m_hWnd = 0;

	m_TabControl.SetImageList(&pImageList);
	m_TabControl.InsertItem(0, _T("°ü½ÉÁ¾¸ñ"));
	m_TabControl.InsertItem(1, _T("ÇöÀç°¡"));
	m_TabControl.InsertItem(2, _T("ÀüÀÏµî¶ô·ü"));
	m_TabControl.InsertItem(3, _T("ÀÏÀÚº°½Ã¼¼"));
	pImageList.Detach();

	tm.mask = TCIF_IMAGE;   //   ¼ÓÉÏÕâ¾ä¾Í¿ÉÒÔÁË   
	for(int i=0; i<3; i++)   
	{   
		m_TabControl.GetItem(i,&tm);   
		tm.iImage=i;   
		m_TabControl.SetItem(i,&tm);   
	}


	if (!GetNextScreenNum(1))
	{
		return;
	}

	m_buyList.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_buyList.Create(IDD_BUY_LIST, &m_TabControl);
	
	m_mapScreen.SetAt(m_buyList.m_strScrNo, &m_buyList);


	if (!GetNextScreenNum(2))
	{
		return;
	}

	m_curPrice.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_curPrice.Create(IDD_CUR_PRICE,&m_TabControl);
	
	m_mapScreen.SetAt(m_curPrice.m_strScrNo, &m_curPrice);

	if (!GetNextScreenNum(3))
	{
		return;
	}


	m_topPrice.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_topPrice.Create(IDD_TOP_PRICE,&m_TabControl);

	m_mapScreen.SetAt(m_topPrice.m_strScrNo, &m_topPrice);
	//m_BenXOut.Create(IDD_DIALOG_OUT,&m_TabControl);


	if (!GetNextScreenNum(4))
	{
		return;
	}


	m_DailyReport.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_DailyReport.Create(IDD_DIALOG_DAILY,&m_TabControl);

	m_mapScreen.SetAt(m_DailyReport.m_strScrNo, &m_DailyReport);

	CRect r;
	m_TabControl.GetClientRect (&r);

	m_buyList.SetWindowPos (NULL,3,22,r.right -8 ,r.bottom-28,SWP_SHOWWINDOW);
	m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW);
	m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW);
	m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
}


void CshootStockDlg::OnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CRect r;
	m_TabControl.GetClientRect (&r);

	switch(m_TabControl.GetCurSel())
	{
	case 0:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28 ,SWP_SHOWWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		break;
	case 1:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		break;
	case 2:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SendSearch();
		//m_TabControl.SetCurSel(0);
		break;
	case 3:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_DailyReport.SendSearch();
		//m_TabControl.SetCurSel(0);
		break;
	}
	*pResult = 0;
}


//{L"Á¾¸ñÄÚµå",	L"9001",	-1,	0,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
//{L"½Å¿ë±¸ºÐ",	L"917",		-1,	1,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
//{L"Á¾¸ñ¸í",		L"302",		-1,	2,		DT_NONE,					FALSE,	DT_CENTER,	L"",	L""},
//{L"ÇöÀç°¡",		L"10",		-1,	3,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"º¸À¯¼ö·®",	L"930",		-1,	4,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"Æò°¡±Ý¾×",	L"-1",		-1,	5,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"Æò°¡¼ÕÀÍ",	L"-1",		-1,	6,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"¼öÀÍ·ü",		L"-1",		-1,	7,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L"%"},
//{L"¸ÅÀÔ±Ý¾×",	L"932",		-1,	8,		DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,		L"",	L""},
//{L"ÇöÀç°¡",		L"10",		-1,	9,		DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(°è»ê¿ëÀ¸·Î ¼û±è)
//{L"º¸À¯¼ö·®",	L"930",		-1,	10,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(°è»ê¿ëÀ¸·Î ¼û±è)
//{L"¸ÅÀÔ±Ý¾×",	L"932",		-1,	11,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(°è»ê¿ëÀ¸·Î ¼û±è)
//{L"Æò°¡±Ý¾×",	L"-1",		-1,	12,	DT_NONE,					FALSE,	DT_RIGHT,		L"",	L""},	//(°è»ê¿ëÀ¸·Î ¼û±è)
void CshootStockDlg::InitDealList(void)
{
	m_dealList.SetExtendedStyle(LVS_EX_FULLROWSELECT );
	m_dealList.ModifyStyle(0,LVS_SINGLESEL); 
	m_dealList.SetGridLines();
	m_dealList.InsertColumn(0,L"Á¾¸ñÄÚµå",0,70);
	m_dealList.InsertColumn(1,L"½Å¿ë±¸ºÐ",0,80);
	m_dealList.InsertColumn(2,L"Á¾¸ñ¸í",0,100);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_dealList.InsertColumn(3,L"ÇöÀç°¡",0,80);
	m_dealList.InsertColumn(4,L"º¸À¯¼ö·®",0,80);
	m_dealList.InsertColumn(5,L"Æò°¡±Ý¾×",0,80);
	m_dealList.InsertColumn(6,L"Æò°¡¼ÕÀÍ",0,80);
	m_dealList.InsertColumn(7,L"¼öÀÍ·ü",0,80);
	m_dealList.InsertColumn(8,L"¸ÅÀÔ±Ý¾×",0,100);
}
//*******************************************************************/
//! Function Name	: SetRate
//! Function			: Á¾¸ñº° ¼öÀÍ·ü °è»ê
//! Param				: 
//! Return				: void
//! Create				: , 2015/05/12
//! Comment			: 
//******************************************************************/
void CshootStockDlg::SetRate(int nRow, CString strCode)
{
	//ÁÖ½Ä Á¾¸ñ¿¡ ´ëÇÑ ¼öÀÍ·ü °è»êÀÌ¶ó ÁÖ½Ä¿Ü Á¾¸ñÀÇ ¼öÀÍ·üÀº ´Ù¸¦¼ö ÀÖÀ½À» ¾Ë·Áµå¸³´Ï´Ù.

	//ÇöÀç°¡
	CString strData, strTmp;
	strData = m_dealList.GetItemText(nRow, 3);
	strData.Replace(L",",L"");
	strTmp = strData.Left(1);
	if (strTmp == "-" || strTmp == "+")
	{
		strData = strData.Mid(1);
	}
	double nPrice = _ttof(strData);

	//¼ö·®
	double nQty = _ttof(m_dealList.GetItemText(nRow, 4));

	//¸ÅÀÔ±Ý¾×
	strTmp =  m_dealList.GetItemText(nRow, 8);
	strTmp.Replace(L",",L"");
	double nPurchase = _ttof(strTmp);

	int nCount(0);
	nCount = m_dealList.GetItemCount();

	//¸Å¼ö°¡°è»ê ¼ö¼ö·á = ¸ÅÀÔ±Ý¾× * ¸ÅÃ¼¼ö¼ö·á(0.015%) (10¿ø¹Ì¸¸ Àý»ç)
	m_BuyComm = nPurchase * COMMISSION;
	m_BuyComm = floor(m_BuyComm / 10) * 10;	//(10¿ø¹Ì¸¸ Àý»ç)

	//¸Åµµ°¡°è»ê ¼ö¼ö·á = ÇöÀç°¡ * ¼ö·® * ¸ÅÃ¼¼ö¼ö·á(0.015%) (10¿ø¹Ì¸¸ Àý»ç)
	m_SellComm = nPrice * nQty * COMMISSION;
	m_SellComm = floor(m_SellComm / 10) * 10;	//(10¿ø¹Ì¸¸ Àý»ç)

	//Á¦¼¼±Ý
	long lMarketType = theApp.m_khOpenApi.GetMarketType(strCode);
	if (lMarketType == 0) //°Å·¡¼Ò
	{
		//Á¦¼¼±Ý(°Å·¡¼Ò) = ÇöÀç°¡ * ¼ö·® * 0.15%(¿ø¹Ì¸¸ Àý»ç) * 2
		m_Tax = nPrice * nQty * COMMISSION1;
		m_Tax = floor(m_Tax) * 2;
	} 
	else if (lMarketType == 10)//ÄÚ½º´Ú
	{
		//Á¦¼¼±Ý(ÄÚ½º´Ú) = ÇöÀç°¡ * ¼ö·® * 0.3%(¿ø¹Ì¸¸ Àý»ç)
		m_Tax = floor(nPrice * nQty * COMMISSION2);
	}

	CString strTemp;

	//Á¾¸ñº° Æò°¡±Ý¾× = (ÇöÀç°¡ * ¼ö·®) - ¸Å¼ö°¡°è»ê ¼ö¼ö·á - ¸Åµµ°¡°è»ê ¼ö¼ö·á - Á¦¼¼±Ý °¡°è»ê
	m_Eval = (nPrice * nQty) - m_BuyComm - m_SellComm - m_Tax;
	strTemp.Format(_T("%0.lf"), m_Eval);
	
	m_dealList.SetItemText(nRow, 5,  theApp.ConvDataFormat(lstFID[5].nDataType, strTemp, lstFID[5].strBeforeData, lstFID[5].strAfterData));
	//m_dealList.SetItemText(nRow, 12,  theApp.ConvDataFormat(lstFID[12].nDataType, strTemp, lstFID[12].strBeforeData, lstFID[12].strAfterData));

	COLORREF tempC = RGB(0,0,255);
	//Á¾¸ñº° Æò°¡¼ÕÀÍ = Æò°¡±Ý¾× - ¸ÅÀÔ±Ý¾×
	m_Profit = m_Eval - nPurchase;
	strTemp.Format(_T("%0.lf"), m_Profit);

	if (strTemp.GetAt(0) == '+' )	// ºÎÈ£¿¡ µû¶ó »ö»óº¯°æ
	{
		tempC =  RGB(255,0,0);
	}
	else if (strTemp.GetAt(0) == '-')	// ºÎÈ£¿¡ µû¶ó »ö»óº¯°æ
	{
		tempC =  RGB(0,0,255);
	}
	else
	{
		tempC =  RGB(0,0,0);
	}

	m_dealList.SetItemText(nRow, 6,  theApp.ConvDataFormat(lstFID[6].nDataType, strTemp, lstFID[6].strBeforeData, lstFID[6].strAfterData));
	m_dealList.SetItemTextColor(nRow, 6,tempC);
	//Á¾¸ñº° ¼öÀÍ·ü = Æò°¡¼ÕÀÍ / ¸ÅÀÔ±Ý¾× * 100
	if (nPurchase == 0)
	{
		m_Rate = 0;
	}
	else
	{
		m_Rate = m_Profit / nPurchase * 100;
	}
	strTemp.Format(_T("%0.2lf"), m_Rate);

	
	if (strTemp.GetAt(0) == '+' )	// ºÎÈ£¿¡ µû¶ó »ö»óº¯°æ
	{
		tempC =  RGB(255,0,0);
	}
	else if (strTemp.GetAt(0) == '-')	// ºÎÈ£¿¡ µû¶ó »ö»óº¯°æ
	{
		tempC =  RGB(0,0,255);
	}
	else
	{
		tempC =  RGB(0,0,0);
	}
	m_dealList.SetItemText(nRow, 7,  theApp.ConvDataFormat(lstFID[7].nDataType, strTemp, lstFID[7].strBeforeData, lstFID[7].strAfterData));
	m_dealList.SetItemTextColor(nRow, 7,tempC);


}

//*******************************************************************/
//! Function Name	: SetRate
//! Function			: Á¾¸ñº° ¼öÀÍ·ü °è»ê
//! Param				: 
//! Return				: void
//! Create				: , 2015/05/12
//! Comment			: 
//******************************************************************/
void CshootStockDlg::SetTotalRate()
{
// 	int nCnt = m_grdRate.GetRowCount();	//±×¸®µå Row °¹¼ö ±¸ÇÏ±â
// 	double dTotalEval(0), dTotalPurchase(0), dTotalProfit, dTotalRate(0);
// 	CString strTotalEval, strTotalPurchase, strTotalProfit, strTotalRate;
// 
// 	for (int i = 1; i < nCnt; i++)
// 	{
// 		dTotalEval += _ttof(m_grdRate.GetItemText(i, 12));			// ÃÑ Æò°¡±Ý¾×
// 		dTotalPurchase += _ttof(m_grdRate.GetItemText(i, 11));	// ÃÑ ¸ÅÀÔ±Ý¾×
// 	}
// 
// 	strTotalEval.Format(_T("%0.lf"), dTotalEval);
// 	strTotalEval = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalEval);
// 	m_EdtTotalEval.SetWindowText(strTotalEval);
// 
// 	strTotalPurchase.Format(_T("%0.lf"), dTotalPurchase);
// 	strTotalPurchase = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalPurchase);
// 	m_EdtTotalPurchase.SetWindowText(strTotalPurchase);
// 
// 
// 	// ÃÑ Æò°¡¼ÕÀÍ
// 	dTotalProfit = dTotalEval - dTotalPurchase;
// 	strTotalProfit.Format(_T("%0.lf"), dTotalProfit);
// 	strTotalProfit = theApp.ConvDataFormat(DT_ZERO_NUMBER, strTotalProfit);
// 	m_EdtTotalProfit.SetWindowText(strTotalProfit);
// 
// 	// ÃÑ ¼öÀÍ·ü
// 	dTotalRate = dTotalProfit / dTotalPurchase * 100;
// 	strTotalRate.Format(_T("%0.2lf"), dTotalRate);
// 	strTotalRate = theApp.ConvDataFormat(DT_NONE, strTotalRate, "", "%");
// 	m_EdtTotalRate.SetWindowText(strTotalRate);
}



void CshootStockDlg::OnListSearch()
{
	// TODO: Add your command handler code here
	if (!GetNextScreenNum(1))
	{
		return;
	}

	CJongDlg *pJongDlg = new CJongDlg(this);
	pJongDlg->m_strScrNo.Format(L"%04d", m_nScrN0);
	pJongDlg->Create(IDD_JONG_LIST);

	m_mapScreen.SetAt(pJongDlg->m_strScrNo, pJongDlg);
}


BOOL CshootStockDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)   
		return TRUE;
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)   
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
