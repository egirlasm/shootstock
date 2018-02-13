// DailyReport.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "DailyReport.h"
#include "afxdialogex.h"
#include "shootStockDlg.h"

// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPT10086[] = 
{
	{L"날짜",				L"20",	-1,	0,	DT_DATE,	FALSE,	DT_CENTER,	L"",	L""}, 
	{L"시가",				L"20",	-1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_CENTER,	L"",	L""}, 
	{L"고가",				L"10",	-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"저가",				L"25",	-1,	3,	DT_ZERO_NUMBER,		TRUE,	DT_CENTER,	L"",	L""}, 
	{L"종가",				L"11",	-1,	4,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"전일비",				L"13",	-1,	5,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"등락률",				L"14",	-1,	6,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, 
	{L"거래량",				L"14",	-1,	7,	DT_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"개인순매수",			L"14",	-1,	8,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"기관순매수",			L"14",	-1,	9,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"외인순매수",			L"14",	-1,	10,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 

};
// CDailyReport dialog

IMPLEMENT_DYNAMIC(CDailyReport, CDialogEx)

CDailyReport::CDailyReport(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDailyReport::IDD, pParent)
{

}

CDailyReport::~CDailyReport()
{
}

void CDailyReport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_RepotCtrl);
}


BEGIN_MESSAGE_MAP(CDailyReport, CDialogEx)
END_MESSAGE_MAP()


// CDailyReport message handlers


BOOL CDailyReport::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	InitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//*******************************************************************/
//! Function Name	: OnReceiveRealDataKhopenapictrl
//! Function			: 실시간 처리
//! Param				: LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CDailyReport::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CDailyReport::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("일별주가요청"))			// 관심종목정보 설정
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10086) / sizeof(*lstOPT10086);		// 전체크기 / 원소크기 = 원소개수
		//m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
		// 		//pMain->m_buyList.m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 
		// 		CReportCtrl * pListCtrl = &pMain->m_buyList.m_ListBox;
		strRQName = _T("일별주가");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		m_RepotCtrl.SetRedraw(FALSE);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			int dwitem = 0;
			for (j = 0; j < nFieldCnt; j++)
			{
				
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10086[j].strKey);	strData.Trim();
				

				
				if(j == 0){
					int dwCount = m_RepotCtrl.GetItemCount();

					dwitem = m_RepotCtrl.InsertItem(dwCount,strData,0);
				}
				if(lstOPT10086[j].nCol != -1){
					//m_RepotCtrl.SetItem(i,j,1,theApp.removeSign(strData),0,0,0,0);
					m_RepotCtrl.SetItemText(i,j, theApp.ConvDataFormat(lstOPT10086[j].nDataType, strData, lstOPT10086[j].strBeforeData, lstOPT10086[j].strAfterData));
					if(lstOPT10086[j].bTextColor){
						if(strData.GetAt(0) == '+')
							m_RepotCtrl.SetItemTextColor(dwitem,j,RGB(255,0,0));
						else if(strData.GetAt(0) == '-')
							m_RepotCtrl.SetItemTextColor(dwitem,j,RGB(0,0,255));
						else
							m_RepotCtrl.SetItemTextColor(dwitem,j,RGB(0,0,0));
					}
				}
				
			}
		}
		m_RepotCtrl.SetRedraw();
	}
}

void CDailyReport::InitList(void)
{
	m_RepotCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_DOUBLEBUFFER );
	m_RepotCtrl.ModifyStyle(0,LVS_SINGLESEL); 
	m_RepotCtrl.SetGridLines();
	m_RepotCtrl.InsertColumn(0,L"일자",0,70);
	m_RepotCtrl.InsertColumn(1,L"시가",0,80);
	m_RepotCtrl.InsertColumn(2,L"고가",0,70);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_RepotCtrl.InsertColumn(3,L"저가",0,80);
	m_RepotCtrl.InsertColumn(4,L"종가",0,80);
	m_RepotCtrl.InsertColumn(5,L"전일대비",0,80);
	m_RepotCtrl.InsertColumn(6,L"등락률",0,80);
	m_RepotCtrl.InsertColumn(7,L"거래량",LVCFMT_RIGHT,80);

	m_RepotCtrl.InsertColumn(8,L"개인",LVCFMT_RIGHT,80);
	m_RepotCtrl.InsertColumn(9,L"기관",LVCFMT_RIGHT,80);
	m_RepotCtrl.InsertColumn(10,L"외인",LVCFMT_RIGHT,80);
	
}


void CDailyReport::SendSearch(void)
{
		m_RepotCtrl.DeleteAllItems();
		CString strRQName = _T("일별주가요청");
		CString strTRCode = TR_OPT10086;
		//theApp.m_khOpenApi.SetInputValue("종목코드", "113810");
		//계좌번호 = 전문 조회할 보유계좌번호  //51653280
		//theApp.m_khOpenApi.SetInputValue(L"계좌번호"	,  L"8100875411");
		//theApp.m_khOpenApi.SetInputValue("계좌번호"	,  "5165328010");
		//비밀번호 = 사용안함(공백)
		//시장구분 = 000:전체, 001:코스피, 101:코스닥
		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
		theApp.m_khOpenApi.SetInputValue(L"종목코드"	,pMain->m_staticCode );

		COleDateTime tm = COleDateTime::GetCurrentTime();
		CString curDate = tm.Format(L"%Y%m%d");

		//거래대금조건 = 0:전체조회, 3:3천만원이상, 5:5천만원이상, 10:1억원이상, 30:3억원이상, 50:5억원이상, 100:10억원이상, 300:30억원이상, 500:50억원이상, 1000:100억원이상, 3000:300억원이상, 5000:500억원이상
		theApp.m_khOpenApi.SetInputValue(L"조회일자"	,  curDate);

		theApp.m_khOpenApi.SetInputValue(L"표시구분"	,  L"0");
		long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
		CString		strErr;
		if (!theApp.IsError(lRet))
		{
			strErr.Format(_T("주식기본정보요청 에러 [%s][%d]"), strTRCode, lRet);
			OutputDebugString(strErr);
		};
	

}
