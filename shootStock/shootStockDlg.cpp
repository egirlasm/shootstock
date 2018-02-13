
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

// {Á¶È¸ Å°,		¸®¾ó Å°,	Çà, ¿­, Å¸ÀÔ,			»ö º¯°æ, Á¤·Ä, ¾Õ ¹®ÀÚ, µÞ ¹®ÀÚ}
const stGRID lstOPW00018[] = 
{
	{L"Á¾¸ñ¹øÈ£",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"Á¾¸ñ¸í",				L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"Æò°¡¼ÕÀÍ",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"¼öÀÍ·ü",				L"25",	0,	1,	DT_ZERO_NUMBER,		TRUE,	DT_CENTER,L"",L""}, 
	{L"¸ÅÀÔ°¡",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"º¸À¯¼ö·®",			L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"ÇöÀç°¡",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
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
	, m_sellPercentage(2)
	, m_FuckPercentage(0)
	, isRunning(false)
	//, m_boughtPrice(0)
	//, m_checkedCount(0)
	//, m_checkedCode(_T(""))
	//, m_boughtCount(0)
	, isManual(false)
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
	DDX_Control(pDX, IDC_CONCLUDE_LIST, m_ConcludeList);
}

BEGIN_MESSAGE_MAP(CshootStockDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_UPDATESTATUSBAR, &CshootStockDlg::OnUpdatestatusbar)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CshootStockDlg::OnSelchangeTab)

	ON_COMMAND(ID_LIST_SEARCH, &CshootStockDlg::OnListSearch)
END_MESSAGE_MAP()


IMPLEMENT_SERIAL(CSubject, CObject, VERSIONABLE_SCHEMA | 2)
void CSubject::Serialize(CArchive& ar){

}
void CSubject::AssertValid() const{

}
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
	InitConcludeList();
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
	if (strRQName == _T("½Ç½Ã°£¹ÌÃ¼°á¿äÃ»"))		// ÁÖ½Ä±âº»Á¤º¸ ¼³Á¤
	{
		m_ConcludeList.DeleteAllItems();
		CString strData;
		int nFieldCnt = 25;//sizeof(lstFID) / sizeof(*lstFID);		// ÀüÃ¼Å©±â / ¿ø¼ÒÅ©±â = ¿ø¼Ò°³¼ö

		strRQName = _T("½Ç½Ã°£¹ÌÃ¼°á");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);	//µ¥ÀÌÅÍ °Ç¼ö
		m_nCount = nCnt;	//µ¥ÀÌÅÍ °Ç¼ö¿¡ ±×¸®µå Çì´õ Ãß°¡
		CString strIndex= L"";
		for (i = 0; i < nCnt; i++)
		{

			strIndex.Format(L"%d", i);

			int dwitem = 0;
			int dwCount = m_ConcludeList.GetItemCount();




			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"ÁÖ¹®¹øÈ£");strData.Trim();
			CString tmpOrderNo = strData;

			dwitem = m_ConcludeList.InsertItem(dwCount,strData,0);
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"Á¾¸ñÄÚµå");strData.Trim();
			CString tmpCode = strData;
			m_ConcludeList.SetItemText(i,1,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"Á¾¸ñ¸í");strData.Trim();
			m_ConcludeList.SetItemText(i,2,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"ÁÖ¹®±¸ºÐ");strData.Trim();
			m_ConcludeList.SetItemText(i,3,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"ÁÖ¹®°¡°Ý");strData.Trim();
			m_ConcludeList.SetItemText(i,4,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"¹ÌÃ¼°á¼ö·®");strData.Trim();
			m_ConcludeList.SetItemText(i,5,_wtoi(strData) );

			// ÀÜ°í ¸®½ºÆ®¿¡ ³Ö¾î ÀÏ°ü¸Åµµ ÇÒ¶§ »¡¸® ÇÔ
			m_mapOrderNo.SetAt(tmpCode,tmpOrderNo);

			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"¸Å¸Å±¸ºÐ");strData.Trim();
			m_ConcludeList.SetItemText(i,6,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"ÇöÀç°¡");strData.Trim();
			m_ConcludeList.SetItemText(i,7,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"½Ã°£");strData.Trim();
			strData.Format(L"%s:%s:%s",strData.Mid(0,2),strData.Mid(2,2),strData.Mid(4,2));
			m_ConcludeList.SetItemText(i,8,strData );
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
	}

	if (strRQName == _T("°èÁÂÆò°¡ÀÜ°í³»¿ª¿äÃ»"))			// °èÁÂ¼öÀÍ·ü//if (!lstrcmp(sRealType, L"ÁÖ½ÄÃ¼°á"))	// ÁÖ½ÄÃ¼°á
	{
		//m_checkedSubject.RemoveAll();
		CString strData;
		int nFieldCnt = 22;//sizeof(lstFID) / sizeof(*lstFID);		// ÀüÃ¼Å©±â / ¿ø¼ÒÅ©±â = ¿ø¼Ò°³¼ö

		strRQName = _T("°èÁÂÆò°¡ÀÜ°í³»¿ª");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);	//µ¥ÀÌÅÍ °Ç¼ö
		m_nCount = nCnt;	//µ¥ÀÌÅÍ °Ç¼ö¿¡ ±×¸®µå Çì´õ Ãß°¡
		CString strIndex= L"";
		for (i = 0; i < nCnt; i++)
		{
			
			strIndex.Format(L"%d", i);

			int dwitem = 0;
	
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"Á¾¸ñ¹øÈ£");strData.Trim();
			m_mapJongCode.SetAt(strData.Mid(1,6), strIndex);

			CString tmpJomgmok = strData.Mid(1,6);
			//m_grdKwanSim.SetRowHeight(i, 20);		// ÇàÀÇ ³ôÀÌ ¼³Á¤
			//m_grdKwanSim.SetItemText(i, 0, strCode);
			int dwCount = m_dealList.GetItemCount();

			dwitem = m_dealList.InsertItem(dwCount,strData.Mid(1,6),0);
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"Á¾¸ñ¸í");strData.Trim();
			m_dealList.SetItemText(i,1,strData );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"Æò°¡¼ÕÀÍ");strData.Trim();
			m_dealList.SetItemText(i,2,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"¼öÀÍ·ü(%)");strData.Trim();
			m_dealList.SetItemText(i,3,_wtof(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"¸ÅÀÔ°¡");strData.Trim();
			m_dealList.SetItemText(i,4,_wtoi(strData) );

			int nBuyPrice = _wtoi(strData);

			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"º¸À¯¼ö·®");strData.Trim();
			m_dealList.SetItemText(i,5,_wtoi(strData) );

			// ÀÜ°í ¸®½ºÆ®¿¡ ³Ö¾î ÀÏ°ü¸Åµµ ÇÒ¶§ »¡¸® ÇÔ
			m_OrderList.SetAt(tmpJomgmok,strData);

			CSubject * subject = new CSubject(nBuyPrice);
			subject->set_count(_wtoi(strData));
			subject->set_status(false);
			
		/*	subject->set_price(nBuyPrice);*/

			/************************************************************************/
			/*                                                                            */
			/************************************************************************/
			isRunning = true; //ÇÁ·Î±×·¥ÀÌ ½ÃÀÛµÇ¸é  ÇöÀç °Å·¡ÁßÀÎ Á¾¸ñÀÌ ÀÖÀ¸¸é ¹Ù·Î ¼ÕÀý °¨½Ã ÀÛµ¿ 
			m_checkedSubject.SetAt(tmpJomgmok,subject);

			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"ÇöÀç°¡");strData.Trim();
			m_dealList.SetItemText(i,6,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"¼ö¼ö·áÇÕ");strData.Trim();
			m_dealList.SetItemText(i,7,_wtoi(strData) );
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, L"¼¼±Ý");strData.Trim();
			m_dealList.SetItemText(i,8,_wtoi(strData) );
		}

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
			//
			
		}

		long lRet = theApp.m_khOpenApi.CommKwRqData(strCodeList, 0, nCodeCount, 0, strRQName, m_strScrNo);
		if (!lRet)
		{
			return;
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
		case 5:
			{

				((CChartView *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

			}
			break;
		case 6:
			{

				((CIncome *)pWnd)->OnReceiveTrDataKhopenapictrl(sScrNo, sRQName, sTrcode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

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
	CString strRealType = sRealType;
	if (strRealType == _T("ÁÖ¹®Ã¼°á"))			// °ü½ÉÁ¾¸ñÁ¤º¸ ¼³Á¤
	{
		

	}
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



		if(isRunning){ //¼ÕÀý ÆÇ´Ü 
			CshootStockDlg* pMain =  (CshootStockDlg*)AfxGetApp()->GetMainWnd();
			CSubject *subject = new CSubject();
			if(pMain->m_checkedSubject.Lookup(sJongmokCode,(CObject*&)subject) && !subject->get_status()){
				
				strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 10);	strData.Trim(); //ÇöÀç°¡
				int nPrice = _wtoi(strData);
				if(nPrice < 0)
					nPrice = nPrice * -1;
				int nTmpBoughtPrice  = subject->get_price();
				if(nPrice < nTmpBoughtPrice){
					int nTemp = nTmpBoughtPrice - nPrice;
					double nPercentage = (double)nTemp / (double)nTmpBoughtPrice * 100;
					if(nPercentage > 1.5){ // 3%ÀÌ»óÀÌ¸é ¼ÕÀý
						
						CString strOrderNo;
						if (m_mapOrderNo.Lookup(sJongmokCode, strOrderNo))
						{
							CString strRQName = _T("ÁÖ½ÄÁÖ¹®"); //ÀÏ´Ü ¸Åµµ Ãë¼Ò
							LONG lRet = theApp.m_khOpenApi.SendOrder(strRQName,m_strScrNo,m_AccNo, 4, sJongmokCode,subject->get_count(), 0, L"00",strOrderNo);
							subject->set_status(true);
							m_checkedSubject.SetAt(sJongmokCode,subject);
							//pMain->m_checkedCode = L"";
						}

					}
				}
			}
			
		}

		if (!m_mapJongCode.Lookup(sJongmokCode, strIndex))
		{
			return;
		}



		CString strCode;

		//int i, nFieldCnt = sizeof(lstFID) / sizeof(*lstFID);		// ÀüÃ¼Å©±â / ¿ø¼ÒÅ©±â = ¿ø¼Ò°³¼ö
		//for (i = 0; i < nFieldCnt; i++)
		//{
		//	if (_wtoi(lstFID[i].strRealKey) < 0)
		//	{
		//		continue;
		//	}

			//½Ç½Ã°£ µ¥ÀÌÅÍ¸¦ Ç×¸ñ¿¡ ¸Â°Ô °¡Á®¿Â´Ù.
			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 10);	strData.Trim();

			//Ç×¸ñ¿¡ ¸Â´Â µ¥ÀÌÅÍ°¡ ÀÖÀ»¶§¸¸ ±×¸®µå¿¡ Ç¥½ÃÇÑ´Ù.
// 			if (strData != "")
// 			{
				//m_grdRate.SetItemText(_ttoi(strIndex), i, theApp.ConvDataFormat(lstFID[i].nDataType, strData, lstFID[i].strBeforeData, lstFID[i].strAfterData));
				//m_dealList.SetItemText(_ttoi(strIndex), 6, strData);

				COLORREF tempC = RGB(0,0,255);

				if (strData.GetAt(0) == '+' )	// ºÎÈ£¿¡ µû¶ó »ö»óº¯°æ
				{
					tempC =  RGB(255,0,0);
				}
				else if (strData.GetAt(0) == '-')	// ºÎÈ£¿¡ µû¶ó »ö»óº¯°æ
				{
					tempC =  RGB(0,0,255);
				}
				else
				{
					tempC =  RGB(0,0,0);
				}

				m_dealList.SetItemText(_ttoi(strIndex), 6,  theApp.ConvDataFormat(lstFID[5].nDataType, strData, lstFID[5].strBeforeData, lstFID[5].strAfterData));
				m_dealList.SetItemTextColor(_ttoi(strIndex), 6,tempC);

				CString strBuyPrice = m_dealList.GetItemText(_ttoi(strIndex),4);
				CString strBuyCount = m_dealList.GetItemText(_ttoi(strIndex),5);
				CString strfee = m_dealList.GetItemText(_ttoi(strIndex),7);
				CString strTax = m_dealList.GetItemText(_ttoi(strIndex),8);
				int nCount =  _wtoi(strBuyCount);
				int nNowPrice = _wtoi(strData);
				if( nNowPrice < 0) //if minus then convert to plus
					nNowPrice = nNowPrice * -1;
				int nTotalBought = _wtoi(strBuyPrice) *nCount;
				int nowTotalPrice = nNowPrice * nCount;

				int nProfit = nowTotalPrice - nTotalBought - _wtoi(strfee) - _wtoi(strTax);

				double nPercentageProfit = (double)nProfit / (double)nTotalBought* 100;
				CString strTemp;
				strTemp.Format(_T("%d"), nProfit);
				m_dealList.SetItemText(_ttoi(strIndex), 2,  theApp.ConvDataFormat(lstFID[6].nDataType, strTemp, lstFID[6].strBeforeData, lstFID[6].strAfterData));
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
				m_dealList.SetItemTextColor(_ttoi(strIndex), 2,tempC);
				strTemp.Format(_T("%0.2lf"), nPercentageProfit);
				m_dealList.SetItemText(_ttoi(strIndex),3,  theApp.ConvDataFormat(lstFID[7].nDataType, strTemp, lstFID[7].strBeforeData, lstFID[7].strAfterData));
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
				m_dealList.SetItemTextColor(_ttoi(strIndex), 3,tempC);
//			}
		//}

		//Á¾¸ñº° ¼öÀÍ·ü °è»ê
		//strCode = sJongmokCode;
		//SetRate(_ttoi(strIndex), strCode);

		//ÃÑ ¼öÀÍ·ü °è»ê
		//SetTotalRate();
	}


	if (strRealType == _T("Àå½ÃÀÛ½Ã°£"))			// °ü½ÉÁ¾¸ñÁ¤º¸ ¼³Á¤
	{
		//TraceOutputW(L"Àå½ÃÀÛ½Ã°£ ¸Þ¼¼Áö°¡ ¿Ô½À´Ï´Ù");
		CString fmt;
		CString strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 215);	strData.Trim(); //Àå¿î¿µ±¸ºÐ (0 Àå½ÃÀÛÀü,2 ÀåÁ¾·áÀü 3 Àå½ÃÀÛ 4 ,8 ÀåÁ¾·á 9 Àå¸¶°¨
		CString strRemainedTime = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 214);	strData.Trim(); //¿¹»óÀÜ¿©½Ã°£
		CString tradeTime = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, 20);	strData.Trim(); //Ã¼°á½Ã°£ (HHMMSS);
		
		CString szHour = strRemainedTime.Mid(0,2);
		CString szMinute = strRemainedTime.Mid(2,2);
		CString szSecond = strRemainedTime.Mid(4,2);

		CString szHour1 = tradeTime.Mid(0,2);
		CString szMinute1 = tradeTime.Mid(2,2);
		CString szSecond1 = tradeTime.Mid(4,2);
		
		int nType = _wtoi(strData);
		switch(nType){
		case 0:
			fmt.Format(L"ÇöÀç½Ã°£ %s:%s:%s Àå½ÃÀÛÀü %s ºÐ ³²¾Ò½À´Ï´Ù ",szHour1,szMinute1,szSecond1,szMinute);
			TraceOutputW(fmt);
			break;
		case 2:
			fmt.Format(L"ÇöÀç½Ã°£ %s:%s:%s ÀåÁ¾·áÀü %s ºÐ ³²¾Ò½À´Ï´Ù ",szHour1,szMinute1,szSecond1,szMinute);
			TraceOutputW(fmt);
			break;
		case 8:
			fmt.Format(L"ÇöÀç½Ã°£ %s:%s:%s Àå½ÃÀÛÀÌ µÇ¿´½À´Ï´Ù %s:%s:%s ºÐ ³²¾Ò½À´Ï´Ù ",szHour1,szMinute1,szSecond1,szHour,szMinute,szSecond);
			TraceOutputW(fmt);
			break;
		case 9:
			fmt.Format(L"ÇöÀç½Ã°£ %s:%s:%s Àå¸¶°¨ÀÌ µÇ¿´½À´Ï´Ù %s:%s:%s ºÐ ³²¾Ò½À´Ï´Ù ",szHour1,szMinute1,szSecond1,szHour,szMinute,szSecond);
			TraceOutputW(fmt);
			break;
		default:
			TraceOutputW(L"default Àå½ÃÀÛ½Ã°£ ¿À·ù  ");
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
			case 5:		// µî¶ô·ü
				{

					((CChartView *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
				}
				break;
			case 6:		// µî¶ô·ü
				{

					((CIncome *)pWnd)->OnReceiveRealDataKhopenapictrl(sJongmokCode, sRealType, sRealData);
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
void CshootStockDlg::MainOnReceiveChejanData(LPCTSTR sGubun, LONG nItemCnt, LPCTSTR sFidList){
	CString strGuBun(sGubun), strAccNo, strAcc;


	//OnReceiveChejanData(
	//	BSTR sGubun, // Ã¼°á±¸ºÐ Á¢¼ö¿Í Ã¼°á½Ã '0'°ª, ±¹³»ÁÖ½Ä ÀÜ°íÀü´ÞÀº '1'°ª, ÆÄ»ýÀÜ°í Àü´ÞÀº '4'
	//	LONG nItemCnt,
	//	BSTR sFIdList
	//	)

	//	ÁÖ¹®¿äÃ»ÈÄ ÁÖ¹®Á¢¼ö, Ã¼°áÅëº¸, ÀÜ°íÅëº¸¸¦ ¼ö½ÅÇÒ ¶§ ¸¶´Ù È£ÃâµÇ¸ç GetChejanData()ÇÔ¼ö¸¦ ÀÌ¿ëÇØ¼­ »ó¼¼ÇÑ Á¤º¸¸¦ ¾òÀ»¼ö ÀÖ½À´Ï´Ù.
	if(strGuBun == L"0"){//Ã¼°áÅëº¸
		strAccNo	= theApp.m_khOpenApi.GetChejanData(9201);	// Ã¼°áµÈ Á¾¸ñÀÇ °èÁÂ¹øÈ£
		CString orderNo =  theApp.m_khOpenApi.GetChejanData(9201); //9203 ÁÖ¹®¹øÈ£
		CString orderStatus =  theApp.m_khOpenApi.GetChejanData(913); //913 ÁÖ¹®»óÅÂ

		TraceOutputW(orderStatus);
		if(orderStatus == L"Á¢¼ö"){
			
			CString strData = theApp.m_khOpenApi.GetChejanData( 907);	strData.Trim(); //¸Åµµ¼ö±¸ºÐ 1 ¸Åµµ 2 ¸Å¼ö ÀÌ°Ç ¹øÈ£·Î
		
			strData = theApp.m_khOpenApi.GetChejanData( 905);	strData.Trim(); //¸Åµµ¼ö±¸ºÐ  ¸Åµµ  ¸Å¼ö ÀÌ°Ç ¹®ÀÚ·Î
			TraceOutputW(strData + L"Á¢¼ö µÇ¿´¾¹´Ï´Ù");
			//if(strData = _T("-¸Åµµ")){
			//	

			//	

			//	theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);

			//	//Ã¼°á±¸ºÐ = 0:Ã¼°á+¹ÌÃ¼°áÁ¶È¸, 1:¹ÌÃ¼°áÁ¶È¸, 2:Ã¼°áÁ¶È¸
			//	//SetInputValue("Ã¼°á±¸ºÐ"	,  "1");
			//	theApp.m_khOpenApi.SetInputValue(L"Ã¼°á±¸ºÐ", L"1");
			//	//¸Å¸Å±¸ºÐ = 0:ÀüÃ¼, 1:¸Åµµ, 2:¸Å¼ö
			//	//SetInputValue("¸Å¸Å±¸ºÐ"	,  "");
			//	theApp.m_khOpenApi.SetInputValue(L"¸Å¸Å±¸ºÐ", L"0");

			//	LONG lRet = theApp.m_khOpenApi.CommRqData(L"½Ç½Ã°£¹ÌÃ¼°á¿äÃ»", L"OPT10075", 0, m_strScrNo);
			//	if (!theApp.IsError(lRet))
			//	{
			//	}

			//}



			//ÁÖ¹®Á¢¼öÀÏ¼öµµ ÀÖ´Ù ÁÖ¹®Ãë¼ÒÀÏ¼öµµ ÀÖ°í
		}else if(orderStatus == L"È®ÀÎ"){
			//TraceOutputW(L"ÁÖ¹®Ãë¼Ò°¡ È®ÀÎ µÇ¿´¾¹´Ï´Ù");
			CString strData = theApp.m_khOpenApi.GetChejanData( 907);	strData.Trim(); //¸Åµµ¼ö±¸ºÐ 1 ¸Åµµ 2 ¸Å¼ö
			//strData = theApp.m_khOpenApi.GetChejanData( 913);	strData.Trim(); //¸Åµµ¼ö±¸ºÐ 1 ¸Åµµ 2 ¸Å¼ö

			int nStatus = _wtoi(strData); // 2 ¹ÌÃ¼°á ¸ÅµµÃë¼Ò°¡ µÇ¸é »õ·Î ½ÃÀå°¡ ÆÈ±â ¼ÕÀýÀ» À§ÇØ 
			strData = theApp.m_khOpenApi.GetChejanData( 905);	strData.Trim(); //¸Åµµ¼ö±¸ºÐ 1 ¸Åµµ 2 ¸Å¼ö
			TraceOutputW(strData + L"Ãë¼Ò°¡ È®ÀÎ µÇ¿´¾¹´Ï´Ù");

			CString sJongmokCode =  theApp.m_khOpenApi.GetChejanData(9001); //913 ÁÖ¹®ÄÚµå
			sJongmokCode =  sJongmokCode.Mid(1,6);
			CSubject *subject = new CSubject;
			if(m_checkedSubject.Lookup(sJongmokCode,(CObject*&)subject) && !isManual){ //ÁöÁ¤°¡·Î °É¾î³í ¸Åµµ°¡ Ãë¼ÒµÇ¸é ½ÃÀå°¡·Î ÆÈ±â
				CString strRQName = _T("ÁÖ½ÄÁÖ¹®"); //½ÃÀå°¡·Î ÆÈ±â  ¼ÕÀý
				LONG lRet = theApp.m_khOpenApi.SendOrder(strRQName,m_strScrNo,m_AccNo, 2, sJongmokCode,subject->get_count(), 0, L"03",L"");
				//m_checkedSubject.RemoveKey(sJongmokCode);

			}
			/// ¸Åµµ°¡ Ãë¼Ò ‰çÀ¸´Ï ¹ÌÃ¼°á ´Ù½Ã ¹Þ¾Æ¿À±â  ±×·¯´Ï ±î ÇöÀç ¸®½ºÆ®¿¡¼­ Áö¿öÁ®¾ßÁö
			theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);

			//Ã¼°á±¸ºÐ = 0:Ã¼°á+¹ÌÃ¼°áÁ¶È¸, 1:¹ÌÃ¼°áÁ¶È¸, 2:Ã¼°áÁ¶È¸
			//SetInputValue("Ã¼°á±¸ºÐ"	,  "1");
			theApp.m_khOpenApi.SetInputValue(L"Ã¼°á±¸ºÐ", L"1");
			//¸Å¸Å±¸ºÐ = 0:ÀüÃ¼, 1:¸Åµµ, 2:¸Å¼ö
			//SetInputValue("¸Å¸Å±¸ºÐ"	,  "");
			theApp.m_khOpenApi.SetInputValue(L"¸Å¸Å±¸ºÐ", L"0");

			LONG lRet = theApp.m_khOpenApi.CommRqData(L"½Ç½Ã°£¹ÌÃ¼°á¿äÃ»", L"OPT10075", 0, m_strScrNo);
			if (!theApp.IsError(lRet))
			{
			}
			isManual = false;

		}else if(orderStatus == L"Ã¼°á"){
			//TraceOutputW(L"Ã¼°áµÇ¿´½À´Ï´Ù");
			CString sJongmokCode =  theApp.m_khOpenApi.GetChejanData(9001); //913 ÁÖ¹®ÄÚµå
			sJongmokCode =  sJongmokCode.Mid(1,6);
			CString strIndex, strData,strCount,strPrice;
			CString stMarketName =   theApp.m_khOpenApi.GetMasterCodeName(sJongmokCode);
			strData = theApp.m_khOpenApi.GetChejanData( 907);	strData.Trim(); //¸Åµµ¼ö±¸ºÐ 1 ¸Åµµ 2 ¸Å¼ö
			strCount = theApp.m_khOpenApi.GetChejanData( 911);	strData.Trim(); //Ã¼°á·®
			strPrice = theApp.m_khOpenApi.GetChejanData( 910);	strData.Trim(); //Ã¼°á°¡
			CString strOrderNo = theApp.m_khOpenApi.GetChejanData( 9203);	strData.Trim(); //Ã¼°á°¡
			m_mapOrderNo.SetAt(sJongmokCode,strOrderNo);
			CString fmt;
			if(strData == L"2")
				fmt.Format(L"¸Å¼öÁÖ¹®ÀÌ Ã¼°áµÇ¿´½À´Ï´Ù %s ¼ö·® = %s , Ã¼°á°¡ %s",stMarketName,strCount,strPrice);
			else
				fmt.Format(L"¸ÅµµÁÖ¹®ÀÌ Ã¼°áµÇ¿´½À´Ï´Ù %s ¼ö·® = %s , Ã¼°á°¡ %s",stMarketName,strCount,strPrice);


			TraceOutputW(fmt);

			int nPrice = _wtoi(strPrice);
			CSubject * subject = new CSubject(nPrice);
			if(strData == L"2"){
				isRunning = true;
				 //ÃÖÁ¾ Ã¼°áµÈ ¸Å¼ö°¡·Î ÁöÁ¤¸Åµµ °É¾î³öµµ ±¦ÂúÀ»µí
				//m_boughtPrice = nPrice;
				//m_checkedCount += _wtoi(strCount); //Ã¼°áµÈ ¼ö·® ¸Å¹ø ´õÇØÁÖ±â  Àý¹Ý¾¿ Ã¼°áµÉ‹š°¡ ÀÖÀ¸´Ï±ñ
				//CString tmpCount = L"";
				//if(m_checkedData.Lookup(sJongmokCode,tmpCount)){
				//	int nTmpCount = _wtoi(tmpCount);
				//	nTmpCount += _wtoi(strCount);
				//	tmpCount.Format(L"%d",nTmpCount);
				//	m_checkedData.SetAt(sJongmokCode,tmpCount);
				//}else
				//	m_checkedData.SetAt(sJongmokCode,strCount);
				
				
				//m_checkedSubject.SetAt(sJongmokCode,my);
				if(m_checkedSubject.Lookup(sJongmokCode,(CObject*&)subject)){
					int nTempCount = _wtoi(strCount);
					//int orgCount = subject->get_count();
					subject->set_count(nTempCount);
					

					if(subject->is_checked_all()){ //¸Å¼öÁÖ¹®ÀÌ ÀüºÎ Ã¼°áÀÌ µÈÈÄ¿¡ ¸ÅµµÁÖ¹®À» °Ç´Ù ¾Æ´Ï¸é ÀÚ²ÙÀÌ»óÇÏ°Ô ºÎºÐ¸¸ ÁöÁ¤¸Åµµ°¡ µÊ
						//m_checkedCode = sJongmokCode; //Ã¼°áµÈ Á¾¸ñ
						//m_checkedData.SetAt(sJongmokCode,)
						subject->set_price(nPrice);
						//1000 ¾Æ·¡´Â 1 ¾¿ °è»êÇÏ´Ï±ñ pass ±× ÀÌ»óÀº 10 ´ÜÀ§·Î ,´õ ÀÌ»óÀº 50´ÜÀ§·Î ,´õ ÀÌ»óÀº 100´ÜÀ§·Î
						nPrice = nPrice + nPrice * m_sellPercentage /100;
						if(nPrice < 10000 && nPrice > 1000){
							nPrice = nPrice - nPrice % 10 + 10;
						}else if(nPrice < 100000 && nPrice > 10000){
							nPrice = nPrice - nPrice % 50 + 50;
						}else if(nPrice < 1000000 && nPrice > 100000){
							nPrice = nPrice - nPrice % 100 + 100;
						}
						//int sellPrice = nPrice + nPrice * m_sellPercentage /100;
						fmt.Format(L"¼³Á¤µÈ ¸Åµµ ÆÛ¼¾Æ® %d%% Áï ¸Åµµ°¡°Ý = %d",m_sellPercentage,nPrice);
						TraceOutputW(fmt);
						CString strRQName = _T("ÁÖ½ÄÁÖ¹®");
						LONG lRet = theApp.m_khOpenApi.SendOrder(strRQName,m_strScrNo,m_AccNo, 2, sJongmokCode,subject->get_count(), nPrice, L"00", L"");
						TraceOutputW(L"ÁöÁ¤°¡ ÁÖ¹®¿Ï·á °¨½Ã±â±â ÀÛµ¿ ½ÃÀÛ.");
						subject->set_status(false);
						m_checkedSubject.SetAt(sJongmokCode,subject);


						theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);
						lRet = theApp.m_khOpenApi.CommRqData(L"°èÁÂÆò°¡ÀÜ°í³»¿ª¿äÃ»", L"OPW00018", 0, m_strScrNo);
						if (!theApp.IsError(lRet))
						{
						}
						//Sleep(1000);
						// ¸Åµµ°¡ Ãë¼Ò ‰çÀ¸´Ï ¹ÌÃ¼°á ´Ù½Ã ¹Þ¾Æ¿À±â  ±×·¯´Ï ±î ÇöÀç ¸®½ºÆ®¿¡¼­ Áö¿öÁ®¾ßÁö
						theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);

						//Ã¼°á±¸ºÐ = 0:Ã¼°á+¹ÌÃ¼°áÁ¶È¸, 1:¹ÌÃ¼°áÁ¶È¸, 2:Ã¼°áÁ¶È¸
						//SetInputValue("Ã¼°á±¸ºÐ"	,  "1");
						theApp.m_khOpenApi.SetInputValue(L"Ã¼°á±¸ºÐ", L"1");
						//¸Å¸Å±¸ºÐ = 0:ÀüÃ¼, 1:¸Åµµ, 2:¸Å¼ö
						//SetInputValue("¸Å¸Å±¸ºÐ"	,  "");
						theApp.m_khOpenApi.SetInputValue(L"¸Å¸Å±¸ºÐ", L"0");

						lRet = theApp.m_khOpenApi.CommRqData(L"½Ç½Ã°£¹ÌÃ¼°á¿äÃ»", L"OPT10075", 0, m_strScrNo);
						if (!theApp.IsError(lRet))
						{
						}

					}else
					{
						m_checkedSubject.SetAt(sJongmokCode,subject);
					}

				}else{
					subject->set_count(_wtoi(strCount));
					m_checkedSubject.SetAt(sJongmokCode,subject);
				}


				



			}else{
				isRunning = false;
				

				if(m_checkedSubject.Lookup(sJongmokCode,(CObject*&)subject)){
					int nTempCount = _wtoi(strCount);
					if(subject->get_count() == nTempCount){
						TraceOutputW(L"ÁÖ½Ä ´ÙÆÈ·Á¼­ °¨½Ã±â±â ÀÛµ¿ ¸ØÃã.");

						m_checkedSubject.RemoveKey(sJongmokCode);
						m_dealList.DeleteAllItems();
						theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);
						long lRet = theApp.m_khOpenApi.CommRqData(L"°èÁÂÆò°¡ÀÜ°í³»¿ª¿äÃ»", L"OPW00018", 0, m_strScrNo);
						if (!theApp.IsError(lRet))
						{
						}


						theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);

						//Ã¼°á±¸ºÐ = 0:Ã¼°á+¹ÌÃ¼°áÁ¶È¸, 1:¹ÌÃ¼°áÁ¶È¸, 2:Ã¼°áÁ¶È¸
						//SetInputValue("Ã¼°á±¸ºÐ"	,  "1");
						theApp.m_khOpenApi.SetInputValue(L"Ã¼°á±¸ºÐ", L"1");
						//¸Å¸Å±¸ºÐ = 0:ÀüÃ¼, 1:¸Åµµ, 2:¸Å¼ö
						//SetInputValue("¸Å¸Å±¸ºÐ"	,  "");
						theApp.m_khOpenApi.SetInputValue(L"¸Å¸Å±¸ºÐ", L"0");

						lRet = theApp.m_khOpenApi.CommRqData(L"½Ç½Ã°£¹ÌÃ¼°á¿äÃ»", L"OPT10075", 0, m_strScrNo);
						if (!theApp.IsError(lRet))
						{
						}

					}
					
				}



			}


			/// ¸Åµµ°¡ Ãë¼Ò ‰çÀ¸´Ï ¹ÌÃ¼°á ´Ù½Ã ¹Þ¾Æ¿À±â  ±×·¯´Ï ±î ÇöÀç ¸®½ºÆ®¿¡¼­ Áö¿öÁ®¾ßÁö
			//theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);

			////Ã¼°á±¸ºÐ = 0:Ã¼°á+¹ÌÃ¼°áÁ¶È¸, 1:¹ÌÃ¼°áÁ¶È¸, 2:Ã¼°áÁ¶È¸
			////SetInputValue("Ã¼°á±¸ºÐ"	,  "1");
			//theApp.m_khOpenApi.SetInputValue(L"Ã¼°á±¸ºÐ", L"1");
			////¸Å¸Å±¸ºÐ = 0:ÀüÃ¼, 1:¸Åµµ, 2:¸Å¼ö
			////SetInputValue("¸Å¸Å±¸ºÐ"	,  "");
			//theApp.m_khOpenApi.SetInputValue(L"¸Å¸Å±¸ºÐ", L"0");

			//lRet = theApp.m_khOpenApi.CommRqData(L"½Ç½Ã°£¹ÌÃ¼°á¿äÃ»", L"OPT10075", 0, m_strScrNo);
			//if (!theApp.IsError(lRet))
			//{
			//}
		}
	}else if(strGuBun == L"1"){// ÀÜ°íÅëº¸
		//TraceOutputW(L"ÀÜ°íÅëº¸");
		//CString orderStatus =  theApp.m_khOpenApi.GetChejanData(913); //913 ÁÖ¹®»óÅÂ
		//TraceOutputW(orderStatus);
		//CString nRemainedConcludeCount =  theApp.m_khOpenApi.GetChejanData(902); //¹ÌÃ¼°á ³²Àº
		//TraceOutputW(nRemainedConcludeCount);

		//nRemainedConcludeCount =  theApp.m_khOpenApi.GetChejanData(9001); //¹ÌÃ¼°á ³²Àº
		//TraceOutputW(nRemainedConcludeCount);

	}
	
	// ÇöÀç °èÁÂ¹øÈ£
	//TraceOutputW(strAccNo);

	//
	//TraceOutputW(orderNo);

	//
	//TraceOutputW(orderStatus);
	////ÇöÀç ¼öÀÍ·ü Á¶È¸ÇÑ °èÁÂ¹øÈ£¿¡ ÀÖ´Â Ã¼°áµÈ Á¾¸ñ¸¸ ¹ÞÀ» ¼ö ÀÖ°Ô Ã³¸®.
	//if (strAccNo == strAcc)
	//{
	//	if (strGuBun == "4")
	//	{
	//		TraceOutputW(L"º¸À¯Á¾¸ñ ÀçÁ¶È¸");
	//		//OnBtnSearch(); //º¸À¯Á¾¸ñÀ» ÀçÁ¶È¸ÇÑ´Ù.
	//	}
	//}
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
					this->MainOnReceiveChejanData(sGubun, nItemCnt, sFidList);
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

		theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);
		long lRet = theApp.m_khOpenApi.CommRqData(L"°èÁÂÆò°¡ÀÜ°í³»¿ª¿äÃ»", L"OPW00018", 0, m_strScrNo);
		if (!theApp.IsError(lRet))
		{
		}
		//°èÁÂ¹øÈ£ = Àü¹® Á¶È¸ÇÒ º¸À¯°èÁÂ¹øÈ£
		theApp.m_khOpenApi.SetInputValue(L"°èÁÂ¹øÈ£", m_AccNo);

		//Ã¼°á±¸ºÐ = 0:Ã¼°á+¹ÌÃ¼°áÁ¶È¸, 1:¹ÌÃ¼°áÁ¶È¸, 2:Ã¼°áÁ¶È¸
			//SetInputValue("Ã¼°á±¸ºÐ"	,  "1");
		theApp.m_khOpenApi.SetInputValue(L"Ã¼°á±¸ºÐ", L"1");
		//¸Å¸Å±¸ºÐ = 0:ÀüÃ¼, 1:¸Åµµ, 2:¸Å¼ö
			//SetInputValue("¸Å¸Å±¸ºÐ"	,  "");
		theApp.m_khOpenApi.SetInputValue(L"¸Å¸Å±¸ºÐ", L"0");

		lRet = theApp.m_khOpenApi.CommRqData(L"½Ç½Ã°£¹ÌÃ¼°á¿äÃ»", L"OPT10075", 0, m_strScrNo);
		if (!theApp.IsError(lRet))
		{
		}
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
	m_TabControl.InsertItem(4, _T("ÀÏÀÚº°¼öÀÍÇöÈ²"));
	pImageList.Detach();

	tm.mask = TCIF_IMAGE;   //   ¼ÓÉÏÕâ¾ä¾Í¿ÉÒÔÁË   
	for(int i=0; i<4; i++)   
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


	if (!GetNextScreenNum(6))
	{
		return;
	}


	m_incomeDlg.m_strScrNo.Format(L"%04d", m_nScrN0);
	m_incomeDlg.Create(IDD_DIALOG_INCOME,&m_TabControl);

	m_mapScreen.SetAt(m_incomeDlg.m_strScrNo, &m_incomeDlg);

	CRect r;
	m_TabControl.GetClientRect (&r);

	m_buyList.SetWindowPos (NULL,3,22,r.right -8 ,r.bottom-28,SWP_SHOWWINDOW);
	m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW);
	m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW);
	m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
	m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
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
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		break;
	case 1:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		break;
	case 2:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 

		m_topPrice.SendSearch();
		//m_TabControl.SetCurSel(0);
		break;
	case 3:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SendSearch();
		//m_TabControl.SetCurSel(0);
		break;
	case 4:
		m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom -28,SWP_HIDEWINDOW);
		m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_DailyReport.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
		m_incomeDlg.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_SHOWWINDOW ); 
		//m_TabControl.SetCurSel(0);
		m_incomeDlg.GetDailyIncome();
		break;
	}
	*pResult = 0;
}

void CshootStockDlg::InitConcludeList(void)
{
	m_ConcludeList.SetExtendedStyle(LVS_EX_FULLROWSELECT  | LVS_EX_DOUBLEBUFFER);
	m_ConcludeList.ModifyStyle(0,LVS_SINGLESEL); 
	m_ConcludeList.SetGridLines();
	m_ConcludeList.InsertColumn(0,L"ÁÖ¹®",0,70);
	m_ConcludeList.InsertColumn(1,L"Á¾¸ñÄÚµå",0,70);
	m_ConcludeList.InsertColumn(2,L"Á¾¸ñ¸í",0,80);
	m_ConcludeList.InsertColumn(3,L"ÁÖ¹®±¸ºÐ",0,70);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_ConcludeList.InsertColumn(4,L"ÁÖ¹®°¡°Ý",0,60);
	m_ConcludeList.InsertColumn(5,L"¹ÌÃ¼°á¼ö·®",0,70);
	m_ConcludeList.InsertColumn(6,L"¸Å¸Å±¸ºÐ",0,70);
	m_ConcludeList.InsertColumn(7,L"ÇöÀç°¡",0,70);
	m_ConcludeList.InsertColumn(8,L"ÁÖ¹®½Ã°£",0,70);

}

// 	{L"Á¾¸ñ¹øÈ£",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
// 	{L"Á¾¸ñ¸í",				L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
// 	{L"Æò°¡¼ÕÀÍ",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
// 	{L"¼öÀÍ·ü",				L"25",	0,	1,	DT_ZERO_NUMBER,		TRUE,	DT_CENTER,L"",L""}, 
// 	{L"¸ÅÀÔ°¡",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
// 	{L"º¸À¯¼ö·®",			L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
// 	{L"ÇöÀç°¡",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
void CshootStockDlg::InitDealList(void)
{
	m_dealList.SetExtendedStyle(LVS_EX_FULLROWSELECT  | LVS_EX_DOUBLEBUFFER);
	m_dealList.ModifyStyle(0,LVS_SINGLESEL); 
	m_dealList.SetGridLines();
	m_dealList.InsertColumn(0,L"Á¾¸ñÄÚµå",0,70);
	m_dealList.InsertColumn(1,L"Á¾¸ñ¸í",0,80);
	m_dealList.InsertColumn(2,L"Æò°¡¼ÕÀÍ",0,70);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_dealList.InsertColumn(3,L"¼öÀÍ·ü",0,60);
	m_dealList.InsertColumn(4,L"¸ÅÀÔ°¡",0,80);
	m_dealList.InsertColumn(5,L"º¸À¯¼ö·®",0,70);
	m_dealList.InsertColumn(6,L"ÇöÀç°¡",0,70);
	m_dealList.InsertColumn(7,L"¼ö¼ö·áÇÕ",0,70);
	m_dealList.InsertColumn(8,L"¼¼±Ý",0,60);
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


