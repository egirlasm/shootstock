// ChartView.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "ChartView.h"
#include "afxdialogex.h"
#include "chartdir.h"
#include "FinanceChart.h"
#include <math.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <winspool.h>
#include "shootStockDlg.h"
// CChartView dialog

static int nrst = 0;

// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID copylstOPT10001[] = 
{
	{L"종목코드",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"종목명",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	/////////////////////////////////////
	// 현재가 그리드
	{L"현재가",			L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"대비기호",	L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"전일대비",	L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"등락율",		L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"거래량",		L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"거래대비",	L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 1행
	{L"250최고",		L"-1",	0,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"250최고가대비율",L"-1",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"250최고가일",	L"-1",	0,	3,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"액면가",		L"-1",	0,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" 원"}, 
	{L"시가총액",	L"-1",	0,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" 억"}, 
	{L"EPS",			L"-1",	0,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 2행
	{L"250최저",		L"-1",	1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"250최저가대비율",L"-1",	1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"250최저가일",	L"-1",	1,	3,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"자본금",		L"-1",	1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" 억"}, 
	{L"대용가",		L"-1",	1,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"PER",			L"-1",	1,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 3행
	{L"외인소진률",	L"-1",	2,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"%"}, 
	{L"상장주식",	L"-1",	2,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" 천"}, 
	{L"신용비율",	L"-1",	2,	7,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"%"}, 
	{L"결산월",		L"-1",	2,	9,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L"월"}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 4행
	{L"연중최고",	L"-1",	3,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"BPS",			L"-1",	3,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L""}, 
	/////////////////////////////////////
	// 주식기본정보 그리드 5행
	{L"연중최저",	L"-1",	4,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"PBR",			L"-1",	4,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L""}, 
};

// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPT10081[] = 
{
	{L"종목코드",			L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"현재가",				L"-1",	-1,	-1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"거래량",				L"10",	0,	0,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"거래대금",			L"25",	0,	1,	DT_SIGN,		TRUE,	DT_CENTER,L"",L""}, 
	{L"일자",				L"11",	0,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"시가",				L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"고가",				L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"저가",				L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"수정주가구분",		L"-1",	0,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"수정비율",			L"-1",	0,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"대업종구분",			L"-1",	0,	8,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"소업종구분",			L"-1",	0,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" 원"}, 
	{L"종목정보",			L"-1",	0,	10,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" 억"}, 
	{L"수정주가이벤트",		L"-1",	0,	11,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"전일종가",			L"-1",	1,	12,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 

};
// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPT10080[] = 
{
	
	{L"현재가",				L"-1",	-1,	0,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"거래량",				L"10",	0,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"체결시간",			L"25",	0,	2,	DT_NONE,		TRUE,	DT_CENTER,L"",L""}, 
	{L"시가",				L"12",	0,	3,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"고가",				L"13",	0,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"저가",				L"30",	0,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"수정주가구분",		L"-1",	0,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 
	{L"수정비율",			L"-1",	0,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L"%"}, 
	{L"대업종구분",			L"-1",	0,	8,	DT_DATE,		FALSE,	DT_CENTER,L"",L""}, 
	{L"소업종구분",			L"-1",	0,	9,	DT_ZERO_NUMBER,	FALSE,	DT_CENTER,L"",L" 원"}, 
	{L"종목정보",			L"-1",	0,	10,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L" 억"}, 
	{L"수정주가이벤트",		L"-1",	0,	11,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,L"",L""}, 
	{L"전일종가",			L"-1",	1,	12,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,L"",L""}, 

};

IMPLEMENT_DYNAMIC(CChartView, CDialogEx)

CChartView::CChartView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChartView::IDD, pParent)
{

}

CChartView::~CChartView()
{
}

void CChartView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART_VIEWER, m_ChartViewer);
	DDX_Control(pDX, IDC_VIEW_PORT_CTRL, m_ViewPortControl);
	DDX_Control(pDX, IDC_COMBO1, m_cboPrint);
}


BEGIN_MESSAGE_MAP(CChartView, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CChartView::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CChartView::OnBnClickedButtonAdd)
	 ON_CONTROL(CVN_MouseMovePlotArea, IDC_CHART_VIEWER, OnMouseMovePlotArea)
	  ON_CONTROL(CVN_ViewPortChanged, IDC_CHART_VIEWER, OnViewPortChanged)
	  ON_BN_CLICKED(IDC_BUTTON_DAILY, &CChartView::OnBnClickedButtonDaily)
	  ON_BN_CLICKED(IDC_BUTTON_MINUTE, &CChartView::OnBnClickedButtonMinute)
	  ON_BN_CLICKED(IDC_BUTTON1, &CChartView::OnBnClickedButton1)
	  ON_BN_CLICKED(IDC_BUTTON_PRINT, &CChartView::OnBnClickedButtonPrint)
END_MESSAGE_MAP()


// CChartView message handlers
//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CChartView::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("주식일봉차트조회요청"))			// 관심종목정보 설정
	{
		//return;
		CString strData;
		CStringArray arrData;
		
		
		int nFieldCnt = sizeof(lstOPT10081) / sizeof(*lstOPT10081);		// 전체크기 / 원소크기 = 원소개수
		//m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
		// 		//pMain->m_buyList.m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 
		// 		CReportCtrl * pListCtrl = &pMain->m_buyList.m_ListBox;
		strRQName = _T("주식일봉차트");

		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"종목코드");	strData.Trim();
		if(strData.IsEmpty()){
			return; //종목코드가 비여있으면 차트데이터도 비여있음
		}
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		//nCnt = 150;
		double * open = new double[nCnt];
		double * high = new double[nCnt];
		double * low = new double[nCnt];
		double * close = new double[nCnt];
		double * vol = new double[nCnt];
		double * time = new double[nCnt];
		//double open[nCnt],high[nCnt],low[nCnt],close[nCnt],vol[nCnt];
		for (i = 0; i <= nCnt; i++)
		{
			int k = nCnt - i -1;
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10081[j].strKey);	strData.Trim();
				if(j == 2)
					vol[k] = _wtof(strData);
				if(j == 4){
					int y = _wtoi(strData.Mid(0,4));
					int m = _wtoi(strData.Mid(4,2));
					int d = _wtoi(strData.Mid(6,2));
					//DbgStrOutA("%d,%d,%d,%0.2f,k=%d",y,m,d,Chart::chartTime(y,m,d),k);
					time[k] = Chart::chartTime(y,m,d);
				}
					
				if(j == 5)
					open[k] = _wtof(strData);
				if(j == 6)
					high[k] = _wtof(strData);
				if(j == 7)
					low[k] = _wtof(strData);
				if(j == 1)
					close[k] = _wtof(strData);
 			}
		}
		nCnt-=1;
		DoubleArray t_vol(vol,nCnt);
		DoubleArray t_open(open,nCnt);
		DoubleArray t_high(high,nCnt);
		DoubleArray t_low(low,nCnt);
		DoubleArray t_close(close,nCnt);
		DoubleArray t_time(time,nCnt);
		//CChartView * viewer = m_ChartViewer;
		m_timeStamps = t_time;
		m_openData = t_open;
		m_highData = t_high;
		m_lowData = t_low;
		m_closeData = t_close;
		m_volData = t_vol;
		// Set the full x range to be the duration of the data
		//DbgStrOutA("t_time.len = %d",t_time.len);
		m_ChartViewer.setFullRange("x", t_time[0], t_time[t_time.len]);

		// Initialize the view port to show the latest 20% of the time range
		m_ChartViewer.setViewPortWidth(0.2);
		
		m_ChartViewer.setViewPortLeft(1 - m_ChartViewer.getViewPortWidth());

		// Set the maximum zoom to 10 points
		m_ChartViewer.setZoomInWidthLimit(10.0 / t_time.len);

		// Initially set the mouse to drag to scroll mode.
		//m_PointerPB.SetCheck(1);
		m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);

		// Enable mouse wheel zooming by setting the zoom ratio to 1.1 per wheel event
		//m_ChartViewer.setMouseWheelZoomRatio(1.1);
		m_ChartViewer.updateViewPort(true, true);

 		CRect r;
 		GetWindowRect(&r);
 
 		FinanceChart *c = new FinanceChart(r.Width()-50);
 		// Create an XYChart object of size 640 x 70 pixels   
 		// Disable default legend box, as we are using dynamic legend
 		c->setLegendStyle("normal", 8, Chart::Transparent, Chart::Transparent);
 
 		// Set the data into the finance chart object
 		c->setData(m_timeStamps, m_highData, m_lowData, m_openData, m_closeData, m_volData, 30);
 
 		// Add the main chart with 240 pixels in height
 		c->addMainChart(70);
 
 		// Add candlestick symbols to the main chart, using green/red for up/down days
 		c->addCandleStick(0x00ff00, 0xff0000);

		 //Output the chart
		m_ViewPortControl.setChart(c);
		// Output the chart
		
		 m_ViewPortControl.setViewer(&m_ChartViewer);
	}

	if (strRQName == _T("주식분봉차트조회요청"))			// 관심종목정보 설정
	{
		CString strData;
		CStringArray arrData;


		int nFieldCnt = sizeof(lstOPT10080) / sizeof(*lstOPT10080);		// 전체크기 / 원소크기 = 원소개수
		//m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
		// 		//pMain->m_buyList.m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
		// 
		// 		CReportCtrl * pListCtrl = &pMain->m_buyList.m_ListBox;
		strRQName = _T("주식분차트");

		strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName,0, L"종목코드");	strData.Trim();
		if(strData.IsEmpty()){
			return; //종목코드가 비여있으면 차트데이터도 비여있음
		}
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		//nCnt = 150;
		double * open = new double[nCnt];
		double * high = new double[nCnt];
		double * low = new double[nCnt];
		double * close = new double[nCnt];
		double * vol = new double[nCnt];
		double * time = new double[nCnt];
		//double open[nCnt],high[nCnt],low[nCnt],close[nCnt],vol[nCnt];
		strRQName = _T("주식분봉차트조회");
		for (i = 0; i <= nCnt; i++)
		{
			int k = nCnt - i -1;
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10080[j].strKey);	strData.Trim();
				if(j == 1)
					vol[k] = _wtof(strData);
				if(j == 2){
					int y = _wtoi(strData.Mid(0,4));
					int m = _wtoi(strData.Mid(4,2));
					int d = _wtoi(strData.Mid(6,2));
					int h = _wtoi(strData.Mid(8,2));
					int n = _wtoi(strData.Mid(10,2));
					int s = _wtoi(strData.Mid(12,2));
					//DbgStrOutA("%d,%d,%d,%d,%d,%d,%0.2f,k=%d",y,m,d,h,n,s,Chart::chartTime(y,m,d,h,n,s),k);
					time[k] = Chart::chartTime(y,m,d,h,n,s);
				}

				if(j == 3)
					open[k] = _wtof(strData) < 0 ? _wtof(strData) * -1: _wtof(strData);
				if(j == 4)
					high[k] = _wtof(strData) < 0 ? _wtof(strData) * -1: _wtof(strData);
				if(j == 5)
					low[k] = _wtof(strData) < 0 ? _wtof(strData) * -1: _wtof(strData);
				if(j == 0)
					close[k] = _wtof(strData) < 0 ? _wtof(strData) * -1: _wtof(strData);
			}
		}
		nCnt-=1;
		DoubleArray t_vol(vol,nCnt);
		DoubleArray t_open(open,nCnt);
		DoubleArray t_high(high,nCnt);
		DoubleArray t_low(low,nCnt);
		DoubleArray t_close(close,nCnt);
		DoubleArray t_time(time,nCnt);
		//CChartView * viewer = m_ChartViewer;
		m_timeStamps = t_time;
		m_openData = t_open;
		m_highData = t_high;
		m_lowData = t_low;
		m_closeData = t_close;
		m_volData = t_vol;
		// Set the full x range to be the duration of the data
		DbgStrOutA("t_time.len = %d",t_time.len);
		m_ChartViewer.setFullRange("x", t_time[0], t_time[t_time.len]);

		// Initialize the view port to show the latest 20% of the time range
		m_ChartViewer.setViewPortWidth(0.2);

		m_ChartViewer.setViewPortLeft(1 - m_ChartViewer.getViewPortWidth());

		// Set the maximum zoom to 10 points
		m_ChartViewer.setZoomInWidthLimit(10.0 / t_time.len);

		// Initially set the mouse to drag to scroll mode.
		//m_PointerPB.SetCheck(1);
		m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);

		// Enable mouse wheel zooming by setting the zoom ratio to 1.1 per wheel event
		//m_ChartViewer.setMouseWheelZoomRatio(1.1);
		m_ChartViewer.updateViewPort(true, true);

		CRect r;
		GetWindowRect(&r);

		FinanceChart *c = new FinanceChart(r.Width()-50);
		// Create an XYChart object of size 640 x 70 pixels   
		// Disable default legend box, as we are using dynamic legend
		c->setLegendStyle("normal", 8, Chart::Transparent, Chart::Transparent);

		// Set the data into the finance chart object
		c->setData(m_timeStamps, m_highData, m_lowData, m_openData, m_closeData, m_volData, 30);

		// Add the main chart with 240 pixels in height
		c->addMainChart(70);

		// Add candlestick symbols to the main chart, using green/red for up/down days
		c->addCandleStick(0x00ff00, 0xff0000);

		//Output the chart
		m_ViewPortControl.setChart(c);
		// Output the chart

		m_ViewPortControl.setViewer(&m_ChartViewer);
	}
	if (strRQName == _T("주식기본정보요청"))			// 계좌수익률//if (!lstrcmp(sRealType, L"주식체결"))	// 주식체결
	{

		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(copylstOPT10001) / sizeof(*copylstOPT10001);		// 전체크기 / 원소크기 = 원소개수

		strRQName = _T("주식기본정보");




		arrData.RemoveAll();
		for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		{
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, copylstOPT10001[nIdx].strKey);	strData.Trim();
			if(nIdx== 0){
// 				if(strData == m_boardJongmokCode){
// 					//strData = theApp.m_khOpenApi.GetCommRealData(strData, 10);	strData.Trim(); //현재가
// 
// 					m_staticCode = strData;
// 
// 					m_staticName =   theApp.m_khOpenApi.GetMasterCodeName(strData);
// 					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"현재가");	strData.Trim();
// 					m_staticPrice = strData;
// 					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"250최고");	strData.Trim();
// 					m_staticHigh = strData;
// 					m_staticHigh = L"50주최고: "+m_staticHigh.Mid(1,m_staticHigh.GetLength() -1);
// 					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"250최저");	strData.Trim();
// 					m_staticLow = strData;
// 					m_staticLow = L"50주최저: "+m_staticLow.Mid(1,m_staticLow.GetLength() -1);
// 					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"매출액");	strData.Trim();
// 					m_staticSales = L"매출액: "+strData;
// 					strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"영업이익");	strData.Trim();
// 					m_staticProfit = L"영업이익: "+strData;
// 
// 					//TraceOutputW(strData);
// 					UpdateData(FALSE);
// 				}
			}
			arrData.Add(strData);
		}
	}
}
//*******************************************************************/
//! Function Name	: OnReceiveRealDataKhopenapictrl
//! Function			: 실시간 처리
//! Param				: LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CChartView::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
}

BOOL CChartView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	ShowWindow(SW_SHOW);


	DWORD dwNeeded; 
	DWORD dwReturn; 
	DWORD dwFlag = PRINTER_ENUM_CONNECTIONS | PRINTER_ENUM_LOCAL; 

	EnumPrinters(dwFlag, NULL, 4, NULL, 0, &dwNeeded, &dwReturn); 

	PRINTER_INFO_4* p4; 
	p4 = new PRINTER_INFO_4[dwNeeded]; 
	EnumPrinters(dwFlag, NULL, 4, (PBYTE)p4, dwNeeded, &dwNeeded, &dwReturn); 

	for (int i = 0; i<(int)dwReturn; i++) this->m_cboPrint.AddString(p4[i].pPrinterName); 

	delete []p4; 

	//下面是获取默认打印机
	//构造打印设置对话框对象
	CPrintDialog printDialog(FALSE);                     
	//获取默认打印设备的设备环境
	printDialog.GetDefaults();                             
	//获取当前打印机的名称
	m_DYJ = printDialog.GetDeviceName();   
	// drawChart(&m_ChartViewer);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//
// The ViewPortChanged event handler. This event occurs if the user scrolls or zooms in or 
// out the chart by dragging or clicking on the chart. It can also be triggered by calling
// CChartViewer.updateViewPort.
//
void CChartView::OnViewPortChanged()
{
	// Update the chart if necessary
	if (m_ChartViewer.needUpdateChart())
		drawChart(&m_ChartViewer);
}
/////////////////////////////////////////////////////////////////////////////
// Data source

/// <summary>
/// Get the timeStamps, highData, lowData, openData, closeData and volData.
/// </summary>
/// <param name="ticker">The ticker symbol for the data series.</param>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
/// <param name="durationInDays">The number of trading days to get.</param>
/// <param name="extraPoints">The extra leading data points needed in order to
/// compute moving averages.</param>
/// <returns>True if successfully obtain the data, otherwise false.</returns>
bool CChartView::getData(const CString &ticker, double startDate,
	double endDate, int durationInDays, int extraPoints)
{
	// This method should return false if the ticker symbol is invalid. In this
	// sample code, as we are using a random number generator for the data, all
	// ticker symbol is allowed, but we still assumed an empty symbol is invalid.
	//if (ticker.IsEmpty())
	//	return false;

	//// In this demo, we can get 15 min, daily, weekly or monthly data depending on
	//// the time range.
	//m_resolution = 86400;
	//if (durationInDays <= 10) 
	//{
	//	// 10 days or less, we assume 15 minute data points are available
	//	m_resolution = 900;

	//	// We need to adjust the startDate backwards for the extraPoints. We assume 
	//	// 6.5 hours trading time per day, and 5 trading days per week.
	//	double dataPointsPerDay = 6.5 * 3600 / m_resolution;
	//	double adjustedStartDate = startDate - fmod(startDate, 86400) - 
	//		(int)(extraPoints / dataPointsPerDay * 7 / 5 + 2.9999999) * 86400;

	//	// Get the required 15 min data
	//	get15MinData(ticker, adjustedStartDate, endDate);
	//}
	//else if (durationInDays >= 4.5 * 360)
	//{
	//	// 4 years or more - use monthly data points.
	//	m_resolution = 30 * 86400;

	//	// Adjust startDate backwards to cater for extraPoints
	//	int YMD = Chart::getChartYMD(startDate);
	//	int adjustedMonth = (YMD / 100) % 100 - extraPoints;
	//	int adjustedYear = YMD / 10000;
	//	while (adjustedMonth < 1)
	//	{
	//		--adjustedYear;
	//		adjustedMonth += 12;
	//	}
	//	double adjustedStartDate = Chart::chartTime(adjustedYear, adjustedMonth, 1);

	//	// Get the required monthly data
	//	getMonthlyData(ticker, adjustedStartDate, endDate);
	//}
	//else if (durationInDays >= 1.5 * 360)
	//{
	//	// 1 year or more - use weekly points. 
	//	m_resolution = 7 * 86400;

	//	//Note that we need to add extra points by shifting the starting weeks backwards
	//	double adjustedStartDate = startDate - (extraPoints * 7 + 6) * 86400;

	//	// Get the required weekly data
	//	getWeeklyData(ticker, adjustedStartDate, endDate);
	//}
	//else
	{
		// Default - use daily points
		m_resolution = 86400;

		// Adjust startDate backwards to cater for extraPoints. We multiply the days 
		// by 7/5 as we assume 1 week has 5 trading days.
		double adjustedStartDate = startDate - fmod(startDate, 86400) - 
			((extraPoints * 7 + 4) / 5 + 2) * 86400;

		// Get the required daily data
		getDailyData(ticker, adjustedStartDate, endDate);
	}

	return true;
}

/// <summary>
/// Get 15 minutes data series into the timeStamps, highData, lowData, openData, closeData 
/// and volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CChartView::get15MinData(const CString &ticker, double startDate, double endDate)
{
	//
	// In this demo, we use a random number generator to generate the data. In practice,
	// you may get the data from a database or by other means. If you do not have 15 
	// minute data, you may modify the "drawChart" method below to not using 15 minute
	// data.
	//
//	generateRandomData(ticker, startDate, endDate, 900);
}

/// <summary>
/// Get daily data series into the timeStamps, highData, lowData, openData, closeData and
/// volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CChartView::getDailyData(const CString &ticker, double startDate, double endDate)
{
	//
	// In this demo, we use a random number generator to generate the data. In practice,
	// you may get the data from a database or by other means. Replace the code below
	// with your own data acquisition code.
	//

//	generateRandomData(ticker, startDate, endDate, 86400);
}


/// <summary>
/// Add an indicator chart to the FinanceChart object. In this demo example, the indicator
/// parameters (such as the period used to compute RSI, colors of the lines, etc.) are hard
/// coded to commonly used values. You are welcome to design a more complex user interface 
/// to allow users to set the parameters.
/// </summary>
/// <param name="m">The FinanceChart object to add the line to.</param>
/// <param name="indicator">The selected indicator.</param>
/// <param name="height">Height of the chart in pixels</param>
static XYChart* addIndicator(FinanceChart *m, CString indicator, int height)
{
	if (indicator == _T("RSI"))
		return m->addRSI(height, 14, 0x800080, 20, 0xff6666, 0x6666ff);
	else if (indicator == _T("StochRSI"))
		return m->addStochRSI(height, 14, 0x800080, 30, 0xff6666, 0x6666ff);
	else if (indicator == _T("MACD"))
		return m->addMACD(height, 26, 12, 9, 0xff, 0xff00ff, 0x8000);
	else if (indicator == _T("FStoch"))
		return m->addFastStochastic(height, 14, 3, 0x6060, 0x606000);
	else if (indicator == _T("SStoch"))
		return m->addSlowStochastic(height, 14, 3, 0x6060, 0x606000);
	else if (indicator == _T("ATR"))
		return m->addATR(height, 14, 0x808080, 0xff);
	else if (indicator == _T("ADX"))
		return m->addADX(height, 14, 0x8000, 0x800000, 0x80);
	else if (indicator == _T("DCW"))
		return m->addDonchianWidth(height, 20, 0xff);
	else if (indicator == _T("BBW"))
		return m->addBollingerWidth(height, 20, 2, 0xff);
	else if (indicator == _T("DPO"))
		return m->addDPO(height, 20, 0xff);
	else if (indicator == _T("PVT"))
		return m->addPVT(height, 0xff);
	else if (indicator == _T("Momentum"))
		return m->addMomentum(height, 12, 0xff);
	else if (indicator == _T("Performance"))
		return m->addPerformance(height, 0xff);
	else if (indicator == _T("ROC"))
		return m->addROC(height, 12, 0xff);
	else if (indicator == _T("OBV"))
		return m->addOBV(height, 0xff);
	else if (indicator == _T("AccDist"))
		return m->addAccDist(height, 0xff);
	else if (indicator == _T("CLV"))
		return m->addCLV(height, 0xff);
	else if (indicator == _T("WilliamR"))
		return m->addWilliamR(height, 14, 0x800080, 30, 0xff6666, 0x6666ff);
	else if (indicator == _T("Aroon"))
		return m->addAroon(height, 14, 0x339933, 0x333399);
	else if (indicator == _T("AroonOsc"))
		return m->addAroonOsc(height, 14, 0xff);
	else if (indicator == _T("CCI"))
		return m->addCCI(height, 20, 0x800080, 100, 0xff6666, 0x6666ff);
	else if (indicator == _T("EMV"))
		return m->addEaseOfMovement(height, 9, 0x6060, 0x606000);
	else if (indicator == _T("MDX"))
		return m->addMassIndex(height, 0x800080, 0xff6666, 0x6666ff);
	else if (indicator == _T("CVolatility"))
		return m->addChaikinVolatility(height, 10, 10, 0xff);
	else if (indicator == _T("COscillator"))
		return m->addChaikinOscillator(height, 0xff);
	else if (indicator == _T("CMF"))
		return m->addChaikinMoneyFlow(height, 21, 0x8000);
	else if (indicator == _T("NVI"))
		return m->addNVI(height, 255, 0xff, 0x883333);
	else if (indicator == _T("PVI"))
		return m->addPVI(height, 255, 0xff, 0x883333);
	else if (indicator == _T("MFI"))
		return m->addMFI(height, 14, 0x800080, 30, 0xff6666, 0x6666ff);
	else if (indicator == _T("PVO"))
		return m->addPVO(height, 26, 12, 9, 0xff, 0xff00ff, 0x8000);
	else if (indicator == _T("PPO"))
		return m->addPPO(height, 26, 12, 9, 0xff, 0xff00ff, 0x8000);
	else if (indicator == _T("UO"))
		return m->addUltimateOscillator(height, 7, 14, 28, 0x800080, 20, 0xff6666, 0x6666ff);
	else if (indicator == _T("Vol"))
		return m->addVolIndicator(height, 0x99ff99, 0xff9999, 0xc0c0c0);
	else if (indicator == _T("TRIX"))
		return m->addTRIX(height, 12, 0xff);
	else
		return 0;
}

/// <summary>
/// Get weekly data series into the timeStamps, highData, lowData, openData, closeData and
/// volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CChartView::getWeeklyData(const CString &ticker, double startDate, double endDate)
{
	//
	// In this demo, we use a random number generator to generate the data. In practice,
	// you may get the data from a database or by other means. If you do not have weekly
	// data, you may call "getDailyData" to get daily data first, and then call 
	// "convertDailyToWeeklyData" to convert it to weekly data, like:
	//
	//      getDailyData(startDate, endDate);
	//      convertDailyToWeeklyData();
	//
//	generateRandomData(ticker, startDate, endDate, 86400 * 7);
}

/// <summary>
/// Get monthly data series into the timeStamps, highData, lowData, openData, closeData and
/// volData arrays.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
void CChartView::getMonthlyData(const CString &ticker, double startDate, double endDate)
{
	//
	// In this demo, we use a random number generator to generate the data. In practice,
	// you may get the data from a database or by other means. If you do not have monthly
	// data, you may call "getDailyData" to get daily data first, and then call 
	// "convertDailyToMonthlyData" to convert it to monthly data, like:
	//
	//      getDailyData(startDate, endDate);
	//      convertDailyToMonthlyData();
	//
//	generateRandomData(ticker, startDate, endDate, 86400 * 30);
}


/// <summary>
/// Creates a dummy chart to show an error message.
/// </summary>
/// <param name="viewer">The WinChartViewer to display the error message.</param>
/// <param name="msg">The error message</param>
static void errMsg(CChartViewer* viewer, const char *msg)
{
	MultiChart m(400, 200);
	m.addTitle(Chart::Center, msg, "Arial", 10)->setMaxWidth(m.getWidth());
	viewer->setChart(&m);
}


/////////////////////////////////////////////////////////////////////////////
// Chart Creation

/// <summary>
/// Add a moving average line to the FinanceChart object.
/// </summary>
/// <param name="m">The FinanceChart object to add the line to.</param>
/// <param name="avgType">The moving average type (SMA/EMA/TMA/WMA).</param>
/// <param name="avgPeriod">The moving average period.</param>
/// <param name="color">The color of the line.</param>
static LineLayer* addMovingAvg(FinanceChart *m, CString avgType, int avgPeriod, int color)
{
	if (avgPeriod > 1)
	{
		if (avgType == _T("SMA"))
			return m->addSimpleMovingAvg(avgPeriod, color);
		else if (avgType == _T("EMA"))
			return m->addExpMovingAvg(avgPeriod, color);
		else if (avgType == _T("TMA"))
			return m->addTriMovingAvg(avgPeriod, color);
		else if (avgType == _T("WMA"))
			return m->addWeightedMovingAvg(avgPeriod, color);
	}

	return 0;
}
static void CvtToKorean(char ch[256], string str)
{
	wstring wstr;
	USES_CONVERSION;
	wstr = wstring(A2W(str.c_str()));
	const wchar_t* strUni = wstr.c_str();
	WideCharToMultiByte(CP_UTF8, 0, strUni, -1, ch, sizeof(char) * 255, 0, 0);
}
/*[출처] [ChartDir] 차트디렉터 한글 사용 (변수를 이용한)|작성자 Many Photos*/


/// <summary>
/// Draw the chart according to user selection and display it in the ChartViewer.
/// </summary>
/// <param name="viewer">The ChartViewer object to display the chart.</param>
void CChartView::drawChart(CChartViewer *viewer)
{
	

//	double viewPortStartDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft());
//	double viewPortEndDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft() +
//		viewer->getViewPortWidth());
//
//	DbgStrOutA("viewPortStartDate = %0.2f,viewPortEndDate = %0.2f",viewPortStartDate,viewPortEndDate);
//	// Get the array indexes that corresponds to the visible start and end dates
//	int startIndex = (int)floor(Chart::bSearch(m_timeStamps, viewPortStartDate));
//	int endIndex = (int)ceil(Chart::bSearch(m_timeStamps, viewPortEndDate));
//	int noOfPoints = endIndex - startIndex + 1;
//
//	DbgStrOutA("startIndex = %d,endIndex = %d,noOfPoints %d",startIndex,endIndex,noOfPoints);
//	//XYChart *c = new XYChart(640, 400);
//
//	DoubleArray viewPortTimeStamps = DoubleArray(m_timeStamps.data + startIndex, noOfPoints);
//	DoubleArray viewPortDataSeriesA = DoubleArray(m_highData.data + startIndex, noOfPoints);
//	DoubleArray viewPortDataSeriesB = DoubleArray(m_lowData.data + startIndex, noOfPoints);
//	DoubleArray viewPortDataSeriesC = DoubleArray(m_openData.data + startIndex, noOfPoints);
//	DoubleArray viewPortDataSeriesD = DoubleArray(m_closeData.data + startIndex, noOfPoints);
//	
	CRect r;
	GetWindowRect(&r);
//	XYChart *c = new XYChart(r.Width()-50, r.Height()-350);
//
//
//	CandleStickLayer *layer = c->addCandleStickLayer(viewPortDataSeriesA, viewPortDataSeriesB,
//		viewPortDataSeriesC,viewPortDataSeriesD, 0x00ff00, 0xff0000);
//
//	// Set the line width to 2 pixels
//	layer->setLineWidth(2);
//
//	// Create a FinanceChart object of width 720 pixels
//	//FinanceChart *c = new FinanceChart(r.Width()-50);
//	//XYChart*pl = c->addMainChart(r.Height()-350);
//	//XYChart * pl = (XYChart*)c->getChart();
//	//pl->setPlotArea(0,0, pl->getWidth() - 300, pl->getHeight() - 92, 0xffffff, -1, Chart::Transparent, 0xffffff, 0xffffff);
//	// Add a title to the chart
//	//c->addTitle("Finance Chart Demonstration");
//	
//	// Disable default legend box, as we are using dynamic legend
//	//c->setLegendStyle("normal", 8, Chart::Transparent, Chart::Transparent);
//
//	// Set the data into the finance chart object
//	//c->setData(m_timeStamps, m_highData, m_lowData, m_openData, m_closeData, m_volData, 30);
//
//
//	// Add the main chart with 240 pixels in height
//
//	
//
//	//Axis * ppp = ((XYChart*)c->getChart())->xAxis();
//	//viewer->syncDateAxisWithViewPort("x",ppp);
//
//	// Add a 10 period simple moving average to the main chart, using brown color
//	//c->addSimpleMovingAvg(5, 0x1A8D21);
//
//	// Add a 20 period simple moving average to the main chart, using purple color
//	//c->addSimpleMovingAvg(20, 0x9900ff);
//	//c->addSimpleMovingAvg(60, 0x8C85E4);
//	// Add candlestick symbols to the main chart, using green/red for up/down days
//	//c->addCandleStick( 0xff0000,0x0000ff);
//
//	// Add 20 days bollinger band to the main chart, using light blue (9999ff) as the border and
//	// semi-transparent blue (c06666ff) as the fill color
//	//c->addBollingerBand(20, 2, 0x9999ff, 0xc06666ff);
//
//	// Add a 75 pixels volume bars sub-chart to the bottom of the main chart, using green/red/grey for
//	// up/down/flat days
//	//c->addVolBars(75, 0xff0000, 0x0000ff, 0x808080);
//
//	// Append a 14-days RSI indicator chart (75 pixels high) after the main chart. The main RSI line
//	// is purple (800080). Set threshold region to +/- 20 (that is, RSI = 50 +/- 25). The upper/lower
//	// threshold regions will be filled with red (ff0000)/blue (0000ff).
//	//c->addRSI(75, 14, 0x800080, 20, 0xff0000, 0x0000ff);
//
//	// Append a MACD(26, 12) indicator chart (75 pixels high) after the main chart, using 9 days for
//	// computing divergence.
//	//c->addMACD(75, 26, 12, 9, 0x0000ff, 0xff00ff, 0x008000);
//
//	// Include track line with legend for the latest data values
//	//trackFinance(c, ((XYChart *)c->getChart(0))->getPlotArea()->getRightX());
//
//	// Assign the chart to the WinChartViewer
//	//viewer->setChart(c);
//	
//// 	c->setPlotArea(55, 55, c->getWidth() - 80, c->getHeight() - 92, c->linearGradientColor(0, 55, 0, 
//// 		c->getHeight() - 35, 0xf0f6ff, 0xa0c0ff), -1, Chart::Transparent, 0xffffff, 0xffffff);
//
//	delete viewer->getChart();
//	viewer->setChart(c);
	double viewPortStartDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft());
	double viewPortEndDate = viewer->getValueAtViewPort("x", viewer->getViewPortLeft() +
		viewer->getViewPortWidth());
	DbgStrOutA("viewPortStartDate = %0.2f,viewPortEndDate = %0.2f",viewPortStartDate,viewPortEndDate);
	// Get the array indexes that corresponds to the visible start and end dates
	int startIndex = (int)floor(Chart::bSearch(m_timeStamps, viewPortStartDate));
	int endIndex = (int)ceil(Chart::bSearch(m_timeStamps, viewPortEndDate));
	int noOfPoints = endIndex - startIndex + 2;
		DbgStrOutA("startIndex = %d,endIndex = %d,noOfPoints %d",startIndex,endIndex,noOfPoints);
	//	//XYChart *c = new XYChart(640, 400);
	// Extract the part of the data array that are visible.
	DoubleArray viewPortTimeStamps = DoubleArray(m_timeStamps.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesA = DoubleArray(m_openData.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesB = DoubleArray(m_closeData.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesC = DoubleArray(m_highData.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesD = DoubleArray(m_lowData.data + startIndex, noOfPoints);
	DoubleArray viewPortDataSeriesE = DoubleArray(m_volData.data + startIndex, noOfPoints);
	//
	// At this stage, we have extracted the visible data. We can use those data to plot the chart.
	//
	FinanceChart *c = new FinanceChart(r.Width()-50);

	// Add a title to the chart
	c->addTitle("Finance Chart Demonstration");

	// Disable default legend box, as we are using dynamic legend
	//c->setLegendStyle("normal", 8, Chart::Transparent, Chart::Transparent);

	// Set the data into the finance chart object
	c->setData(viewPortTimeStamps, viewPortDataSeriesC, viewPortDataSeriesD, viewPortDataSeriesA, viewPortDataSeriesB, viewPortDataSeriesE, 30);

	// Add the main chart with 240 pixels in height
	c->addMainChart(r.Height()-350);
	 c->addCandleStick(0xff0000,0x0000ff);
	 c->addVolBars(75, 0xff0000, 0x0000ff, 0x808080);
	 trackFinance(c, ((XYChart *)c->getChart(0))->getPlotArea()->getRightX());
	///////////////////////////////////////////////////////////////////////////////////////
	// Configure overall chart appearance. 
	///////////////////////////////////////////////////////////////////////////////////////

	// Create an XYChart object of size 650 x 350 pixels, with a white (ffffff) background and grey 
	// (aaaaaa) border
	//XYChart *c = new XYChart(r.Width()-50, r.Height()-350, 0xffffff, 0xaaaaaa);

	// Set the plotarea at (55, 55) with width 90 pixels less than chart width, and height 90 pixels
	// less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
	// as background. Set border to transparent and grid lines to white (ffffff).
	//c->setPlotArea(55, 55, c->getWidth() - 90, c->getHeight() - 90, 0xffffff, -1, Chart::Transparent, 0xffffff, 0xffffff);

	// As the data can lie outside the plotarea in a zoomed chart, we need enable clipping.
	//c->setClipping();

	//// Add a title to the chart using 18 pts Times New Roman Bold Italic font
	//c->addTitle("   Zooming and Scrolling with Track Line (2)", "timesbi.ttf", 18);

	//// Add a legend box at (55, 30) using horizontal layout. Use 8pts Arial Bold as font. Set the
	//// background and border color to Transparent and use line style legend key.
	//LegendBox *b = c->addLegend(55, 30, false, "arialbd.ttf", 8);
	//b->setBackground(Chart::Transparent);
	//b->setLineStyleKey();

	//// Set the axis stem to transparent
	//c->xAxis()->setColors(Chart::Transparent);
	//c->yAxis()->setColors(Chart::Transparent);

	//// Add axis title using 10pts Arial Bold Italic font
	//c->yAxis()->setTitle("Ionic Temperature (C)", "arialbi.ttf", 10);

	///////////////////////////////////////////////////////////////////////////////////////
	// Add data to chart
	///////////////////////////////////////////////////////////////////////////////////////
		//CRect r;
		//GetWindowRect(&r);
		//XYChart *c = new XYChart(r.Width()-50, r.Height()-350);
	
	
	/*	CandleStickLayer *layer = c->addCandleStickLayer(viewPortDataSeriesC, viewPortDataSeriesD,
			viewPortDataSeriesA,viewPortDataSeriesB, 0x0000ff, 0xff0000);*/

		
	
		// Set the line width to 2 pixels
		//layer->setLineWidth(2);
		//c->addBarLayer(viewPortDataSeriesE, 0x00c000
		//	)->setUseYAxis2();
		// c->xAxis()->setDateScale(m_timeStamps.data[startIndex],m_timeStamps.data[startIndex + noOfPoints]);
		////c->xAxis()->
		// c->xAxis()->setLabelFormat("{value|yy/mm}");
	// 
	// In this example, we represent the data by lines. You may modify the code below to use other
	// representations (areas, scatter plot, etc).
	//

	// Add a line layer for the lines, using a line width of 2 pixels
	//LineLayer *layer = c->addLineLayer();
	//layer->setLineWidth(2);

	//// In this demo, we do not have too many data points. In real code, the chart may contain a lot
	//// of data points when fully zoomed out - much more than the number of horizontal pixels in this
	//// plot area. So it is a good idea to use fast line mode.
	//layer->setFastLineMode();

	//// Now we add the 3 data series to a line layer, using the color red (ff0000), green
	//// (00cc00) and blue (0000ff)
	//layer->setXData(viewPortTimeStamps);
	//layer->addDataSet(viewPortDataSeriesA, 0xff3333, "Alpha");
	//layer->addDataSet(viewPortDataSeriesB, 0x008800, "Beta");
	//layer->addDataSet(viewPortDataSeriesC, 0x3333CC, "Gamma");

	///////////////////////////////////////////////////////////////////////////////////////
	// Configure axis scale and labelling
	///////////////////////////////////////////////////////////////////////////////////////

	// Set the x-axis as a date/time axis with the scale according to the view port x range.
	//viewer->syncDateAxisWithViewPort("x", c->xAxis());

	//
	// In this demo, the time range can be from a few years to a few days. We demonstrate how to set
	// up different date/time format based on the time range.
	//

	// If all ticks are yearly aligned, then we use "yyyy" as the label format.
	//c->xAxis()->setFormatCondition("align", 360 * 86400);
	//c->xAxis()->setLabelFormat("{value|yyyy}");

	//// If all ticks are monthly aligned, then we use "mmm yyyy" in bold font as the first 
	//// label of a year, and "mmm" for other labels.
	//c->xAxis()->setFormatCondition("align", 30 * 86400);
	//c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "<*font=bold*>{value|mmm yyyy}", 
	//	Chart::AllPassFilter(), "{value|mmm}");

	//// If all ticks are daily algined, then we use "mmm dd<*br*>yyyy" in bold font as the 
	//// first label of a year, and "mmm dd" in bold font as the first label of a month, and
	//// "dd" for other labels.
	//c->xAxis()->setFormatCondition("align", 86400);
	//c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), 
	//	"<*block,halign=left*><*font=bold*>{value|mmm dd<*br*>yyyy}", 
	//	Chart::StartOfMonthFilter(), "<*font=bold*>{value|mmm dd}");
	//c->xAxis()->setMultiFormat(Chart::AllPassFilter(), "{value|dd}");

	//// For all other cases (sub-daily ticks), use "hh:nn<*br*>mmm dd" for the first label of
	//// a day, and "hh:nn" for other labels.
	//c->xAxis()->setFormatCondition("else");
	//c->xAxis()->setMultiFormat(Chart::StartOfDayFilter(), 
	//	"<*font=bold*>{value|hh:nn<*br*>mmm dd}", Chart::AllPassFilter(), "{value|hh:nn}");

	///////////////////////////////////////////////////////////////////////////////////////
	// Output the chart
	///////////////////////////////////////////////////////////////////////////////////////

	// We need to update the track line too. If the mouse is moving on the chart (eg. if 
	// the user drags the mouse on the chart to scroll it), the track line will be updated
	// in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
	/*if ((!viewer->isInMouseMoveEvent()) && viewer->isMouseOnPlotArea())
		trackLineLabel(c, viewer->getPlotAreaMouseX());*/

	delete viewer->getChart();
	viewer->setChart(c);

}




void CChartView::OnBnClickedButtonRefresh()
{
	// TODO: Add your control notification handler code here
	//
	// Sample data for the CandleStick chart.
	//
	drawChart(&m_ChartViewer);
	return;
	double highData[] = {2043, 2039, 2076, 2064, 2048, 2058, 2070, 2033, 2027, 2029, 2071, 2085,
		2034, 2031, 2056, 2128, 2180, 2183, 2192, 2213, 2230, 2281, 2272};

	double lowData[] = {1931, 1921, 1985, 2028, 1986, 1994, 1999, 1958, 1943, 1944, 1962, 2011,
		1975, 1962, 1928, 2059, 2112, 2103, 2151, 2127, 2123, 2152, 2212};

	double openData[] = {2000, 1957, 1993, 2037, 2018, 2021, 2045, 2009, 1959, 1985, 2008, 2048,
		2006, 2010, 1971, 2080, 2116, 2137, 2170, 2172, 2171, 2191, 2240};

	double closeData[] = {1950, 1991, 2026, 2029, 2004, 2053, 2011, 1962, 1987, 2019, 2040, 2016,
		1996, 1985, 2006, 2113, 2142, 2167, 2158, 2201, 2188, 2231, 2242};

	// The labels for the CandleStick chart
	const char *labels[] = {"Mon 1", "Tue 2", "Wed 3", "Thu 4", "Fri 5", "Mon 8", "Tue 9", "Wed 10",
		"Thu 11", "Fri 12", "Mon 15", "Tue 16", "Wed 17", "Thu 18", "Fri 19", "Mon 22", "Tue 23",
		"Wed 24", "Thu 25", "Fri 26", "Mon 29", "Tue 30", "Wed 31"};

	// Create a XYChart object of size 600 x 350 pixels
	XYChart *c = new XYChart(600, 350);

	// Set the plotarea at (50, 25) and of size 500 x 250 pixels. Enable both the horizontal and
	// vertical grids by setting their colors to grey (0xc0c0c0)
	c->setPlotArea(50, 25, 500, 250)->setGridColor(0xc0c0c0, 0xc0c0c0);

	// Add a title to the chart
	c->addTitle("Universal Stock Index on Jan 2001");

	// Add a custom text at (50, 25) (the upper left corner of the plotarea). Use 12pt Arial
	// Bold/blue (4040c0) as the font.
	c->addText(50, 25, "(c) Global XYZ ABC Company", "arialbd.ttf", 12, 0x4040c0);

	// Add a title to the x axis
	c->xAxis()->setTitle("Jan 2001");

	// Set the labels on the x axis. Rotate the labels by 45 degrees.
	c->xAxis()->setLabels(StringArray(labels, (int)(sizeof(labels) / sizeof(labels[0])))
		)->setFontAngle(45);

	// Add a title to the y axis
	c->yAxis()->setTitle("Universal Stock Index");

	// Draw the y axis on the right hand side of the plot area
	c->setYAxisOnRight(true);

	// Add a CandleStick layer to the chart using green (00ff00) for up candles and red (ff0000) for
	// down candles
	CandleStickLayer *layer = c->addCandleStickLayer(DoubleArray(highData, (int)(sizeof(highData) /
		sizeof(highData[0]))), DoubleArray(lowData, (int)(sizeof(lowData) / sizeof(lowData[0]))),
		DoubleArray(openData, (int)(sizeof(openData) / sizeof(openData[0]))), DoubleArray(closeData,
		(int)(sizeof(closeData) / sizeof(closeData[0]))), 0x00ff00, 0xff0000);

	// Set the line width to 2 pixels
	layer->setLineWidth(2);

	// Output the chart
	//c->makeChart("candlestick.png");
	

	m_ChartViewer.setChart(c);
	
	// Output the chart
	//c->makeChart("simplepie.png");

	//free up resources
	delete c;
	

}

//
// Draw finance chart track line with legend
//
void CChartView::trackFinance(MultiChart *m, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = m->initDynamicLayer();

    // It is possible for a FinanceChart to be empty, so we need to check for it.
    if (m->getChartCount() == 0)
        return ;

    // Get the data x-value that is nearest to the mouse
    int xValue = (int)(((XYChart *)m->getChart(0))->getNearestXValue(mouseX));

    // Iterate the XY charts (main price chart and indicator charts) in the FinanceChart
    XYChart *c = 0;
    for(int i = 0; i < m->getChartCount(); ++i) {
        c = (XYChart *)m->getChart(i);

        // Variables to hold the legend entries
        ostringstream ohlcLegend;
        vector<string> legendEntries;

        // Iterate through all layers to find the highest data point
        for(int j = 0; j < c->getLayerCount(); ++j) {
            Layer *layer = c->getLayerByZ(j);
            int xIndex = layer->getXIndexOf(xValue);
            int dataSetCount = layer->getDataSetCount();

            // In a FinanceChart, only layers showing OHLC data can have 4 data sets
            if (dataSetCount == 4) {
                double highValue = layer->getDataSet(0)->getValue(xIndex);
                double lowValue = layer->getDataSet(1)->getValue(xIndex);
                double openValue = layer->getDataSet(2)->getValue(xIndex);
                double closeValue = layer->getDataSet(3)->getValue(xIndex);

                if (closeValue != Chart::NoValue) {
                    // Build the OHLC legend
					ohlcLegend << "      <*block*>";
					ohlcLegend << "Open: " << c->formatValue(openValue, "{value|P4}");
					ohlcLegend << ", High: " << c->formatValue(highValue, "{value|P4}"); 
					ohlcLegend << ", Low: " << c->formatValue(lowValue, "{value|P4}"); 
					ohlcLegend << ", Close: " << c->formatValue(closeValue, "{value|P4}");

                    // We also draw an upward or downward triangle for up and down days and the %
                    // change
                    double lastCloseValue = layer->getDataSet(3)->getValue(xIndex - 1);
                    if (lastCloseValue != Chart::NoValue) {
                        double change = closeValue - lastCloseValue;
                        double percent = change * 100 / closeValue;
                        string symbol = (change >= 0) ?
                            "<*font,color=cc0000*><*img=@triangle,width=8,color=cc0000*>" :
                            "<*font,color=0000ff*><*img=@invertedtriangle,width=8,color=0000ff*>";

                        ohlcLegend << "  " << symbol << " " << c->formatValue(change, "{value|P4}");
						ohlcLegend << " (" << c->formatValue(percent, "{value|2}") << "%)<*/font*>";
                    }

					ohlcLegend << "<*/*>";
                }
            } else {
                // Iterate through all the data sets in the layer
                for(int k = 0; k < layer->getDataSetCount(); ++k) {
                    DataSet *dataSet = layer->getDataSetByZ(k);

                    string name = dataSet->getDataName();
                    double value = dataSet->getValue(xIndex);
                    if ((0 != name.size()) && (value != Chart::NoValue)) {

                        // In a FinanceChart, the data set name consists of the indicator name and its
                        // latest value. It is like "Vol: 123M" or "RSI (14): 55.34". As we are
                        // generating the values dynamically, we need to extract the indictor name
                        // out, and also the volume unit (if any).

						// The volume unit
						string unitChar;

                        // The indicator name is the part of the name up to the colon character.
						int delimiterPosition = (int)name.find(':');
                        if (name.npos != delimiterPosition) {
							
							// The unit, if any, is the trailing non-digit character(s).
							int lastDigitPos = (int)name.find_last_of("0123456789");
							if ((name.npos != lastDigitPos) && (lastDigitPos + 1 < (int)name.size()) &&
								(lastDigitPos > delimiterPosition))
								unitChar = name.substr(lastDigitPos + 1);

							name.resize(delimiterPosition);
                        }

                        // In a FinanceChart, if there are two data sets, it must be representing a
                        // range.
                        if (dataSetCount == 2) {
                            // We show both values in the range in a single legend entry
                            value = layer->getDataSet(0)->getValue(xIndex);
                            double value2 = layer->getDataSet(1)->getValue(xIndex);
                            name = name + ": " + c->formatValue(min(value, value2), "{value|P3}");
							name = name + " - " + c->formatValue(max(value, value2), "{value|P3}");
                        } else {
                            // In a FinanceChart, only the layer for volume bars has 3 data sets for
                            // up/down/flat days
                            if (dataSetCount == 3) {
                                // The actual volume is the sum of the 3 data sets.
                                value = layer->getDataSet(0)->getValue(xIndex) + layer->getDataSet(1
                                    )->getValue(xIndex) + layer->getDataSet(2)->getValue(xIndex);
                            }

                            // Create the legend entry
                            name = name + ": " + c->formatValue(value, "{value|P3}") + unitChar;
                        }

                        // Build the legend entry, consist of a colored square box and the name (with
                        // the data value in it).
						ostringstream legendEntry;
						legendEntry << "<*block*><*img=@square,width=8,edgeColor=000000,color=" 
							<< hex << dataSet->getDataColor() << "*> " << name << "<*/*>";
                        legendEntries.push_back(legendEntry.str());
                    }
                }
            }
        }

        // Get the plot area position relative to the entire FinanceChart
        PlotArea *plotArea = c->getPlotArea();
        int plotAreaLeftX = plotArea->getLeftX() + c->getAbsOffsetX();
        int plotAreaTopY = plotArea->getTopY() + c->getAbsOffsetY();

		// The legend begins with the date label, then the ohlcLegend (if any), and then the
		// entries for the indicators.
		ostringstream legendText;
		legendText << "<*block,valign=top,maxWidth=" << (plotArea->getWidth() - 5) 
			<< "*><*font=arialbd.ttf*>[" << c->xAxis()->getFormattedLabel(xValue, "mmm dd, yyyy")
			<< "]<*/font*>" << ohlcLegend.str();
		for (int i = ((int)legendEntries.size()) - 1; i >= 0; --i) {
			legendText << "      " << legendEntries[i];
		}
		legendText << "<*/*>";

        // Draw a vertical track line at the x-position
        d->vline(plotAreaTopY, plotAreaTopY + plotArea->getHeight(), c->getXCoor(xValue) +
            c->getAbsOffsetX(), d->dashLineColor(0x000000, 0x0101));

        // Display the legend on the top of the plot area
        TTFText *t = d->text(legendText.str().c_str(), "arial.ttf", 8);
        t->draw(plotAreaLeftX + 5, plotAreaTopY + 20, 0x000000, Chart::TopLeft);
		t->destroy();
    }
}

void CChartView::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	m_ChartViewer.updateViewPort(true, false);      
}
//
// Draw track cursor when mouse is moving over plotarea
//
void CChartView::OnMouseMovePlotArea()
{
	trackFinance((MultiChart *)m_ChartViewer.getChart(), m_ChartViewer.getPlotAreaMouseX());
	m_ChartViewer.updateDisplay();
}

void CChartView::SendSearch(void)
{
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strRQName = _T("주식일봉차트조회요청");
	theApp.m_khOpenApi.SetInputValue(L"종목코드"	, pMain->m_boardJongmokCode);
	CString t = COleDateTime::GetCurrentTime().Format(L"%Y%m%d");
	//비밀번호 = 사용안함(공백)
	theApp.m_khOpenApi.SetInputValue(L"기준일자"	, t);

	//비밀번호입력매체구분 = 00
	theApp.m_khOpenApi.SetInputValue(L"수정주가구분"	,  L"1");

	long ret =  theApp.m_khOpenApi.CommRqData(strRQName,L"OPT10081",0,m_strScrNo);
	theApp.IsError(ret);
}


void CChartView::OnBnClickedButtonDaily()
{
	//delete m_ChartViewer.getChart();
	// TODO: Add your control notification handler code here
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strRQName = _T("주식일봉차트조회요청");
	theApp.m_khOpenApi.SetInputValue(L"종목코드"	, pMain->m_boardJongmokCode);
	CString t = COleDateTime::GetCurrentTime().Format(L"%Y%m%d");
	//비밀번호 = 사용안함(공백)
	theApp.m_khOpenApi.SetInputValue(L"기준일자"	, t);

	//비밀번호입력매체구분 = 00
	theApp.m_khOpenApi.SetInputValue(L"수정주가구분"	,  L"1");

	long ret =  theApp.m_khOpenApi.CommRqData(strRQName,L"OPT10081",0,m_strScrNo);
	theApp.IsError(ret);
}


void CChartView::OnBnClickedButtonMinute()
{
	//delete m_ChartViewer.getChart();
	// TODO: Add your control notification handler code here
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strRQName = _T("주식분봉차트조회요청");
	theApp.m_khOpenApi.SetInputValue(L"종목코드"	, pMain->m_boardJongmokCode);
	
	//비밀번호 = 사용안함(공백)
	theApp.m_khOpenApi.SetInputValue(L"틱범위"	, L"3");

	//비밀번호입력매체구분 = 00
	theApp.m_khOpenApi.SetInputValue(L"수정주가구분"	,  L"1");

	long ret =  theApp.m_khOpenApi.CommRqData(strRQName,L"OPT10080",0,m_strScrNo);
	theApp.IsError(ret);
}


void CChartView::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
}
BOOL CChartView::GetPrinterDevice(LPTSTR pszPrinterName, HGLOBAL* phDevNames, HGLOBAL* phDevMode) 
{ 
	// if NULL is passed, then assume we are setting app object's 
	// devmode and devnames 
	if (phDevMode == NULL || phDevNames == NULL) 
		return FALSE; 

	// Open printer 
	HANDLE hPrinter; 
	if (OpenPrinter(pszPrinterName, &hPrinter, NULL) == FALSE) 
		return FALSE; 

	// obtain PRINTER_INFO_2 structure and close printer 
	DWORD dwBytesReturned, dwBytesNeeded; 
	GetPrinter(hPrinter, 2, NULL, 0, &dwBytesNeeded); 
	PRINTER_INFO_2* p2 = (PRINTER_INFO_2*)GlobalAlloc(GPTR, 
		dwBytesNeeded); 
	if (GetPrinter(hPrinter, 2, (LPBYTE)p2, dwBytesNeeded, 
		&dwBytesReturned) == 0) { 
			GlobalFree(p2); 
			ClosePrinter(hPrinter); 
			return FALSE; 
	} 
	ClosePrinter(hPrinter); 

	// Allocate a global handle for DEVMODE 
	HGLOBAL  hDevMode = GlobalAlloc(GHND, sizeof(*p2->pDevMode) + 
		p2->pDevMode->dmDriverExtra); 
	ASSERT(hDevMode); 
	DEVMODE* pDevMode = (DEVMODE*)GlobalLock(hDevMode); 
	ASSERT(pDevMode); 

	// copy DEVMODE data from PRINTER_INFO_2::pDevMode 
	memcpy(pDevMode, p2->pDevMode, sizeof(*p2->pDevMode) + 
		p2->pDevMode->dmDriverExtra); 
	GlobalUnlock(hDevMode); 

	// Compute size of DEVNAMES structure from PRINTER_INFO_2's data 
	DWORD drvNameLen = lstrlen(p2->pDriverName)+1;  // driver name 
	DWORD ptrNameLen = lstrlen(p2->pPrinterName)+1; // printer name 
	DWORD porNameLen = lstrlen(p2->pPortName)+1;    // port name 

	// Allocate a global handle big enough to hold DEVNAMES. 
	HGLOBAL hDevNames = GlobalAlloc(GHND, 
		sizeof(DEVNAMES) + 
		(drvNameLen + ptrNameLen + porNameLen)*sizeof(TCHAR)); 
	ASSERT(hDevNames); 
	DEVNAMES* pDevNames = (DEVNAMES*)GlobalLock(hDevNames); 
	ASSERT(pDevNames); 

	// Copy the DEVNAMES information from PRINTER_INFO_2 
	// tcOffset = TCHAR Offset into structure 
	int tcOffset = sizeof(DEVNAMES)/sizeof(TCHAR); 
	ASSERT(sizeof(DEVNAMES) == tcOffset*sizeof(TCHAR)); 

	pDevNames->wDriverOffset = tcOffset; 
	memcpy((LPTSTR)pDevNames + tcOffset, p2->pDriverName, 
		drvNameLen*sizeof(TCHAR)); 
	tcOffset += drvNameLen; 

	pDevNames->wDeviceOffset = tcOffset; 
	memcpy((LPTSTR)pDevNames + tcOffset, p2->pPrinterName, 
		ptrNameLen*sizeof(TCHAR)); 
	tcOffset += ptrNameLen; 

	pDevNames->wOutputOffset = tcOffset; 
	memcpy((LPTSTR)pDevNames + tcOffset, p2->pPortName, 
		porNameLen*sizeof(TCHAR)); 
	pDevNames->wDefault = 0; 

	GlobalUnlock(hDevNames); 
	GlobalFree(p2);   // free PRINTER_INFO_2 

	// set the new hDevMode and hDevNames 
	*phDevMode = hDevMode; 
	*phDevNames = hDevNames; 
	return TRUE; 
} 

void CChartView::OnBnClickedButtonPrint()
{
	// TODO: Add your control notification handler code here
	int nWidth;
	int nHeight;
	CClientDC dc(this); //this->pImgWnd
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	CRect rect;
	GetClientRect(rect);
	nWidth = rect.Width();
	nHeight = rect.Height();

	CBitmap BMP;
	BMP.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = MemDC.SelectObject(&BMP);
	MemDC.BitBlt(0, 0, nWidth, nHeight, &dc, 0, 0, SRCCOPY);

	HANDLE hDib;
	LPSTR pDib;
	LPBITMAPINFO lpBitInfo;
	HANDLE hlpBitInfo;
	//CBitmap BMP;

	//BMP.LoadBitmap(IDB_BITMAP1);

	hDib=GlobalAlloc(GHND,nWidth*nHeight*3);
	pDib=(LPSTR)GlobalLock(hDib);
	hlpBitInfo=GlobalAlloc(GHND,sizeof(BITMAPINFOHEADER)+ sizeof(BITMAPINFO));
	lpBitInfo=(LPBITMAPINFO)GlobalLock(hlpBitInfo);

	//BITMAPINFO
	lpBitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpBitInfo->bmiHeader.biWidth = nWidth;
	lpBitInfo->bmiHeader.biHeight = nHeight;
	lpBitInfo->bmiHeader.biPlanes = 1;
	lpBitInfo->bmiHeader.biBitCount = 24;
	lpBitInfo->bmiHeader.biCompression = BI_RGB;
	lpBitInfo->bmiHeader.biSizeImage = nWidth * nHeight * 3;
	lpBitInfo->bmiHeader.biXPelsPerMeter = 0;
	lpBitInfo->bmiHeader.biYPelsPerMeter = 0;
	lpBitInfo->bmiHeader.biClrUsed = 0;
	lpBitInfo->bmiHeader.biClrImportant = 0; 
	////BITMAPINFO 

	HDC hdc=::GetDC(this->m_hWnd);
	GetDIBits(hdc, (HBITMAP)BMP, 0, nHeight, pDib, lpBitInfo, DIB_RGB_COLORS);
	::ReleaseDC(this->m_hWnd, hdc);

	static DOCINFO docinfo= {sizeof(DOCINFO), _T("IMAGE"), NULL};

	CPrintDialog dlg(FALSE);
	if(dlg.DoModal()== IDCANCEL)
		return; 

	HDC hpdc= dlg.GetPrinterDC();
	int cx, cy ;

	cy=GetDeviceCaps(hpdc,VERTRES);
	cx=GetDeviceCaps(hpdc,HORZRES);

	if(StartDoc(hpdc,&docinfo))
	{
		if(StartPage(hpdc))
		{
			StretchDIBits(hpdc,
				0, 0, cx, cy, 0, 0, nWidth, nHeight, pDib, lpBitInfo, DIB_RGB_COLORS,SRCCOPY);
			EndPage(hpdc);
		}
		EndDoc(hpdc);
	}
	::RestoreDC(hpdc, -1); 

		//
		//
		// Design and implementation cinoban@yahoo.com
		// 13 Jan 2000 15:14
		//
	//CString strMessage; 

	////m_DYJStr  被打印的字符串
	//strMessage = L"test爱神的箭夫卡就收到了开发阿喀琉斯的经历可是大家付款了房间阿拉丁健身房flak即使对方爱上了看见对方开了多少积分拉开圣诞节风口浪尖上的立刻解放立刻啊圣诞节分厘卡是";
	//strMessage += "\r\n";       //添加结尾，方便后面循环读取打印数据 

	////this->GetDlgItem(IDC_COMBO1)->GetWindowText(strPrintDevice); 

	////打印配置界面的按钮可用性，因为后台打印，其实这个配置没什么意义 
	//DWORD dwFlag = PD_ALLPAGES | PD_NOPAGENUMS | PD_USEDEVMODECOPIES | PD_HIDEPRINTTOFILE;     

	////CPrintDialog实例化，因为MFC的打印设备无关性，可以理解为这就是一台打印机
	//CPrintDialog pPrintdlg(FALSE, dwFlag, this);                                            

	//HGLOBAL hDevMode = NULL; 
	//HGLOBAL hDevNames = NULL; 

	////获得指定打印机的配置、名字
	//if (GetPrinterDevice(m_DYJ.GetBuffer(0), &hDevNames, &hDevMode))               
	//	AfxGetApp()->SelectPrinter(hDevNames, hDevMode); 
	//else 
	//	AfxMessageBox(_T("Failed to select custom printer")); 

	//m_DYJ.ReleaseBuffer(); 

	////让pPrintdlg使用我们指定的打印机
	//pPrintdlg.m_pd.hDevMode = hDevMode;                                                      
	//pPrintdlg.m_pd.hDevNames = hDevNames; 

	//CDC dc; 
	////后台打印创建法，如果需要弹出打印对话框，请用DoModal
	//dc.Attach(pPrintdlg.CreatePrinterDC());                                                  

	////下面的内容网上很多，就不解释了
	//DOCINFO di;                                                                              
	//di.cbSize = sizeof(DOCINFO); 
	//di.lpszDocName = _T("有驱打印测试"); 
	//di.lpszDatatype = NULL; 
	//di.lpszOutput = NULL; 
	//di.fwType = 0; 

	//dc.StartDoc(&docinfo); 
	//dc.StartPage(); 
	//dc.SetMapMode(MM_TEXT); 

	//CRect recPrint(0, 0, dc.GetDeviceCaps(LOGPIXELSX), dc.GetDeviceCaps(LOGPIXELSY)); 
	//dc.DPtoLP(&recPrint); 
	//dc.SetWindowOrg(0, 0); 

	//CDC * chart =m_ChartViewer.GetDC();

	//CFont newFont; 
	////设置字体和字体大小
	//VERIFY(newFont.CreatePointFont(50, _T("宋体"), &dc)); 
	//CFont* oldFont = dc.SelectObject(&newFont); 

	//dc.SetTextAlign(TA_TOP | TA_LEFT); 

	//CString strPrint; 
	//int nIndex = 0; 
	//int x = 20;  //设置侧边间距
	//int y = 50; 
	//CSize textSize; 
	////根据当前字体的宽、高，后面以此高度为行高
	//textSize = dc.GetTextExtent(_T("00"), 2);                            

	////将IDC_EDIT1编辑框中内容打印，支持换行，一次换行等于'\r\n'，所以在开头strMessage += _T("\r\n")
	//while ((nIndex = strMessage.Find(_T("\r\n"))) > -1)                   
	//{ 
	//	strPrint = strMessage.Left(nIndex); 
	//	strMessage = strMessage.Mid(nIndex+2); 

	//	dc.TextOut(x, y, strPrint); 

	//	//下移一行，行高为字体高度
	//	y += textSize.cy;                                                
	//} 

	//dc.SelectObject(oldFont); 
	//newFont.DeleteObject(); 
	//dc.SelectObject();
	//dc.EndPage(); 
	//dc.EndDoc(); 
	//DeleteDC(dc.Detach()); 
	return;
//		CString strWords;
//
//	// This is a rectangle control
//	CWnd* pWnd = GetDlgItem(IDC_CHART_VIEWER);
//
//	CDC* dc;
//	CDC memoriDC;
//	CBitmap memBMP;
//	CBitmap* pOldBMP;
//	CFont fnt;
//	CFont* pOldFnt;
//	CRect rect;
//	CRect rectMemory;
//	CSize zMetrix;
//
//	//
//	//
//	//
//	CPrintDialog pdlg(FALSE);
//	DOCINFO di;
//	CDC prnDC;
//
//	di.cbSize = sizeof(DOCINFO);
//	di.lpszDocName = L"This string will appear in Printer Queue";
//		di.lpszOutput = NULL;
//	di.lpszDatatype = NULL;
//	di.fwType = 0;
//
//	//
//	// Get current printer setting
//	//
//	pdlg.GetDefaults();
//
//
//	//
//	dc = pWnd->GetDC();
//	pWnd->GetClientRect(&rect);
//
//	// DC printer???
//	if( !prnDC.Attach(pdlg.GetPrinterDC()) )
//		AfxMessageBox(L"Invalid Printer DC");
//	memoriDC.CreateCompatibleDC(&prnDC); // Create DC for Preview
//
//		//
//		// Get the resolution of Screen and Current DefaultPrinter
//		//
//		int iPrnX = prnDC.GetDeviceCaps(HORZRES);
//	int iPrnY = prnDC.GetDeviceCaps(VERTRES);
//	int iMonX = dc->GetDeviceCaps(HORZRES); // Device Target is Monitor
//		int iMonY = dc->GetDeviceCaps(VERTRES);
//
//
//	rectMemory.top = 0;
//	rectMemory.left = 0;
//	rectMemory.bottom = iPrnY;
//	rectMemory.right = iPrnX;
//
//	//
//	// Create a Memory Bitmap that is compatible with the Printer DC
//		// then select or make the bitmap as current GDI active object
//		//
//		memBMP.CreateCompatibleBitmap(&prnDC,
//		rectMemory.Width(), rectMemory.Height());
//	pOldBMP = memoriDC.SelectObject(&memBMP);
//
//	//
//	// Clear memory DC or in other words
//	// paint the bitmap with white colour and transparent text
//		//
//		memoriDC.SetBkMode(TRANSPARENT);
//	memoriDC.SetTextColor(RGB(0, 0, 0));
//	memoriDC.PatBlt(0, 0, rectMemory.Width(),
//		rectMemory.Height(), WHITENESS);
//
//	//
//	// Prepare the font
//	//
//	int iPointz = 100;
//	fnt.CreatePointFont(iPointz, L"OCR A", &memoriDC);
//	strWords.Format(L"This is line number    ");        //Test string
//		pOldFnt = memoriDC.SelectObject(&fnt);
//	zMetrix = memoriDC.GetTextExtent(strWords);
//	int iPos = 0;
//
//	//
//	// Write string or Paint something
//	//
//	int iMaksimal = 0;
//	int iLineHeight = 1;
//	int iLoop;
//	CString strPuncak;
//
//	//
//	// Calculate how many lines we could fit
//	//
//	for(iLoop = 1; iLoop < 100; iLoop++)
//	{
//		if( ((zMetrix.cy+iLineHeight)*iLoop) < iPrnY )
//			iMaksimal++;
//	}
//
//	strPuncak.Format(L"Maximum Amount of line(s) for %d points are %d lines", iPointz, iMaksimal);
//
//		//
//		//
//		//
//		for(iLoop = 0; iLoop < iMaksimal; iLoop++)
//		{
//			strWords.Format(L"This is line %d", iLoop);
//			memoriDC.TextOut(0, iLoop*(zMetrix.cy+iLineHeight),
//				strWords);
//		}
//
//		//
//		// Reseting font
//		//
//		memoriDC.SelectObject(pOldFnt);
//
//		//
//		// Calculate ratio
//		//
//		float fXRatio = (float) iMonX/iPrnX;
//		float fYRatio = (float) iMonY/iPrnY;
//
//
//		//  iLebar = Width
//		//  iTinggi = Height
//		//  iXPosisiPreview = horisontal location of preview
//		//  iYPosisiPreview = vertical location of preview
//		//
//		int iLebar = rect.Width()*fXRatio;
//		int iTinggi = rect.Height()*fYRatio;
//		int iXPosisiPreview = (rect.Width() - iLebar)/2;
//		int iYPosisiPreview = (rect.Height() - iTinggi)/2;
//		CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
//		CPen* pOldPen;
//
//		//
//		// Create an outline
//		//
//		pOldPen = dc->SelectObject(&pen);
//		dc->Rectangle(iXPosisiPreview, iYPosisiPreview ,
//			iXPosisiPreview + iLebar + 2 , iYPosisiPreview +
//			iTinggi + 2);
//		dc->SelectObject(pOldPen);
//
//		//
//		// Put in the box
//		//
//		dc->StretchBlt(iXPosisiPreview , iYPosisiPreview ,
//			iLebar, iTinggi,
//			&memoriDC, 0, 0, rectMemory.Width(),
//			rectMemory.Height(), SRCCOPY);
//
//		//
//		// Cleaning Up
//		//
//		fnt.DeleteObject();
//		memoriDC.SelectObject(pOldBMP);
//		memoriDC.DeleteDC();
//		memBMP.DeleteObject();
//		prnDC.Detach();
//
//		//
//		pWnd->ReleaseDC(dc);
}
