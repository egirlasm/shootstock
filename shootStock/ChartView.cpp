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
// CChartView dialog

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
}


BEGIN_MESSAGE_MAP(CChartView, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CChartView::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CChartView::OnBnClickedButtonAdd)
	 ON_CONTROL(CVN_MouseMovePlotArea, IDC_CHART_VIEWER, OnMouseMovePlotArea)
END_MESSAGE_MAP()


// CChartView message handlers


BOOL CChartView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	ShowWindow(SW_SHOW);
	// drawChart(&m_ChartViewer);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
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
	generateRandomData(ticker, startDate, endDate, 900);
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

	generateRandomData(ticker, startDate, endDate, 86400);
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
	generateRandomData(ticker, startDate, endDate, 86400 * 7);
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
	generateRandomData(ticker, startDate, endDate, 86400 * 30);
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

/// <summary>
/// A random number generator designed to generate realistic financial data.
/// </summary>
/// <param name="startDate">The starting date/time for the data series.</param>
/// <param name="endDate">The ending date/time for the data series.</param>
/// <param name="resolution">The period of the data series.</param>
void CChartView::generateRandomData(const CString &ticker, double startDate, double endDate, 
	int resolution)
{
	// free the previous data arrays
	//delete[] m_timeStamps;
	//delete[] m_highData;
	//delete[] m_lowData;
	//delete[] m_openData;
	//delete[] m_closeData;
	//delete[] m_volData; 

	// The financial simulator
	FinanceSimulator db(TCHARtoUTF8(ticker), startDate, endDate, resolution);

	// Allocate the data arrays
	m_noOfPoints = db.getTimeStamps().len;
	m_timeStamps = new double[m_noOfPoints];
	m_highData = new double[m_noOfPoints];
	m_lowData = new double[m_noOfPoints];
	m_openData = new double[m_noOfPoints];
	m_closeData = new double[m_noOfPoints];
	m_volData = new double[m_noOfPoints];   

	// Copy data to the data arrays
	memcpy(m_timeStamps, db.getTimeStamps().data, m_noOfPoints * sizeof(double));
	memcpy(m_highData, db.getHighData().data, m_noOfPoints * sizeof(double));
	memcpy(m_lowData, db.getLowData().data, m_noOfPoints * sizeof(double));
	memcpy(m_openData, db.getOpenData().data, m_noOfPoints * sizeof(double));
	memcpy(m_closeData, db.getCloseData().data, m_noOfPoints * sizeof(double));
	memcpy(m_volData, db.getVolData().data, m_noOfPoints * sizeof(double));
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
	// In this demo, we just assume we plot up to the latest time. So endDate is now.
	double endDate = Chart::chartTime2((int)time(0));

	// If the trading day has not yet started (before 9:30am), or if the end date is on
	// on Sat or Sun, we set the end date to 4:00pm of the last trading day     
	while ((fmod(endDate, 86400) < 9 * 3600 + 30 * 60) || 
		(Chart::getChartWeekDay(endDate) == 0)
		|| (Chart::getChartWeekDay(endDate) == 6))
		endDate = endDate - fmod(endDate, 86400) - 86400 + 16 * 3600;

	// The duration selected by the user
// 	int durationInDays = (int)_tcstol((const TCHAR *)m_TimeRange.GetItemDataPtr(
// 		m_TimeRange.GetCurSel()), 0, 0);
	int durationInDays = 180;
	// Compute the start date by subtracting the duration from the end date.
	double startDate;
	if (durationInDays >= 30)
	{
		// More or equal to 30 days - so we use months as the unit
		int YMD = Chart::getChartYMD(endDate);
		int startMonth = (YMD / 100) % 100 - durationInDays / 30;
		int startYear = YMD / 10000;
		while (startMonth < 1)
		{
			--startYear;
			startMonth += 12;
		}
		startDate = Chart::chartTime(startYear, startMonth, 1);
	}
	else
	{
		// Less than 30 days - use day as the unit. The starting point of the axis is
		// always at the start of the day (9:30am). Note that we use trading days, so
		// we skip Sat and Sun in counting the days.
		startDate = endDate - fmod(endDate, 86400) + 9 * 3600 + 30 * 60;
		for (int i = 1; i < durationInDays; ++i)
		{
			if (Chart::getChartWeekDay(startDate) == 1)
				startDate -= 3 * 86400;
			else
				startDate -= 86400;
		}
	}

	// The first moving average period selected by the user.
	CString avgText;
	//m_MovAvg1.GetWindowText(avgText);
	m_avgPeriod1 = 5;
	if (m_avgPeriod1 < 0)
		m_avgPeriod1 = 0;
	if (m_avgPeriod1 > 300)
		m_avgPeriod1 = 300;

	// The second moving average period selected by the user.
	//m_MovAvg2.GetWindowText(avgText);
	m_avgPeriod2 = 20;//(int)_tcstol(avgText, 0, 0);
	if (m_avgPeriod2 < 0)
		m_avgPeriod2 = 0;
	if (m_avgPeriod2 > 300)
		m_avgPeriod2 = 300;

	// We need extra leading data points in order to compute moving averages.
	int extraPoints = (m_avgPeriod1 > m_avgPeriod2) ? m_avgPeriod1 : m_avgPeriod2;
	if (extraPoints < 25)
		extraPoints = 25;

	// Get the data series to compare with, if any.
	//m_CompareWith.GetWindowText(m_compareKey);
	//delete[] m_compareData;
	m_compareData = 0;
	if (getData(m_compareKey, startDate, endDate, durationInDays, extraPoints)) 
	{
		m_compareData = m_closeData;
		m_compareDataLen = m_noOfPoints;
		m_closeData = 0;
	}

	// The data series we want to get.
	//m_TickerSymbol.GetWindowText(m_tickerKey);
	char ch[256];
	CvtToKorean(ch, "카카오");


	m_tickerKey ="asdf";
	if (!getData(m_tickerKey, startDate, endDate, durationInDays, extraPoints)) 
	{
		errMsg(viewer, "Please enter a valid ticker symbol");
		return;
	}

	// We now confirm the actual number of extra points (data points that are before
	// the start date) as inferred using actual data from the database.
	for (extraPoints = 0; extraPoints < m_noOfPoints; ++extraPoints)
	{
		if (m_timeStamps[extraPoints] >= startDate)
			break;
	}

	// Check if there is any valid data
	if (extraPoints >= m_noOfPoints)
	{
		// No data - just display the no data message.
		errMsg(viewer, "No data available for the specified time period");
		return;
	}

	// In some finance chart presentation style, even if the data for the latest day 
	// is not fully available, the axis for the entire day will still be drawn, where
	// no data will appear near the end of the axis.
	int extraTrailingPoints = 0;
	if (m_resolution <= 86400)
	{
		// Add extra points to the axis until it reaches the end of the day. The end
		// of day is assumed to be 16:00 (it depends on the stock exchange).
		double lastTime = m_timeStamps[m_noOfPoints - 1];
		extraTrailingPoints = (int)((16 * 3600 - fmod(lastTime, 86400)) / m_resolution);
		if (extraTrailingPoints > 0)
		{
			double *extendedTimeStamps = new double[m_noOfPoints + extraTrailingPoints];
			memcpy(extendedTimeStamps, m_timeStamps, sizeof(double) * m_noOfPoints);
			for (int i = 0; i < extraTrailingPoints; ++i)
				extendedTimeStamps[m_noOfPoints + i] = lastTime + m_resolution * (i + 1);
			delete[] m_timeStamps;
			m_timeStamps = extendedTimeStamps;
		}
	}

	//
	// At this stage, all data is available. We can draw the chart as according to 
	// user input.
	//

	//
	// Determine the chart size. In this demo, user can select 4 different chart sizes.
	// Default is the large chart size.
	//
	CRect rr;
	this->GetWindowRect(&rr);
	int width = 780;//rr.Width()-20;//780;
	int mainHeight = 255;//rr.Height()-120;// 255;
	int indicatorHeight = 80; //거래량

	CString selectedSize = L"L";// (const TCHAR *)m_ChartSize.GetItemDataPtr(m_ChartSize.GetCurSel());
	if (selectedSize == _T("S"))
	{
		// Small chart size
		width = 450;
		mainHeight = 160;
		indicatorHeight = 60;
	}
	else if (selectedSize == _T("M"))
	{
		// Medium chart size
		width = 620;
		mainHeight = 215;
		indicatorHeight = 70;
	}
	else if (selectedSize == _T("H"))
	{
		// Huge chart size
		width = 1000;
		mainHeight = 320;
		indicatorHeight = 90;
	}

	// Create the chart object using the selected size
	FinanceChart m(width);

	// Set the data into the chart object
	m.setData(DoubleArray(m_timeStamps, m_noOfPoints + extraTrailingPoints), 
		DoubleArray(m_highData, m_noOfPoints), DoubleArray(m_lowData, m_noOfPoints), 
		DoubleArray(m_openData, m_noOfPoints), DoubleArray(m_closeData, m_noOfPoints),
		DoubleArray(m_volData, m_noOfPoints), extraPoints);

	//
	// We configure the title of the chart. In this demo chart design, we put the
	// company name as the top line of the title with left alignment.
	//
	CString companyName;
	//m_TickerSymbol.GetWindowText(companyName);


	companyName =  L"아아라시발";
	m.addPlotAreaTitle(Chart::TopLeft, TCHARtoUTF8(companyName));

	// We displays the current date as well as the data resolution on the next line.
	const char *resolutionText = "";
	if (m_resolution == 30 * 86400)
		resolutionText = "Monthly";
	else if (m_resolution == 7 * 86400)
		resolutionText = "Weekly";
	else if (m_resolution == 86400)
		resolutionText = "Daily";
	else if (m_resolution == 900)
		resolutionText = "15-min";

	char buffer[1024];
	sprintf(buffer, "<*font=arial.ttf,size=8*>%s - %s chart", 
		m.formatValue(Chart::chartTime2((int)time(0)), "mmm dd, yyyy"), resolutionText);
	m.addPlotAreaTitle(Chart::BottomLeft, buffer);

	// A copyright message at the bottom left corner the title area
	m.addPlotAreaTitle(Chart::BottomRight, 
		"<*font=arial.ttf,size=8*>(c) coding by egirlasm");

	//
	// Add the first techical indicator according. In this demo, we draw the first
	// indicator on top of the main chart.
	//
	//addIndicator(&m, L"None",// (const TCHAR *)m_Indicator1.GetItemDataPtr(m_Indicator1.GetCurSel()), 
	//	indicatorHeight);

	//
	// Add the main chart
	//
	m.addMainChart(mainHeight);

	//
	// Set log or linear scale according to user preference
	//
	m.setLogScale(false);

	//
	// Set axis labels to show data values or percentage change to user preference
	//
	if (false)// //m_PercentageScale.GetCheck())
		m.setPercentageAxis();

	//
	// Draw the main chart depending on the chart type the user has selected
	//
	CString selectedType = L"CandleStick";
// = (const TCHAR *)m_ChartType.GetItemDataPtr(m_ChartType.GetCurSel());
	if (selectedType == _T("Close"))
		m.addCloseLine(0x000040);
	else if (selectedType == _T("TP"))
		m.addTypicalPrice(0x000040);
	else if (selectedType == _T("WC"))
		m.addWeightedClose(0x000040);
	else if (selectedType == _T("Median"))
		m.addMedianPrice(0x000040);

	//
	// Add comparison line if there is data for comparison
	//
	if (m_compareData != 0) {
		if (m_compareDataLen > extraPoints) {
			m.addComparison(DoubleArray(m_compareData, m_compareDataLen), 0x0000ff, 
				TCHARtoUTF8(m_compareKey));
		}
	}

	//
	// Add moving average lines.
	//  移动平均线 
	//addMovingAvg(&m,L"SMA", //(const TCHAR *)m_AvgType1.GetItemDataPtr(m_AvgType1.GetCurSel()), 
	//	m_avgPeriod1, 0x663300);
	//addMovingAvg(&m, L"SMA",//(const TCHAR *)m_AvgType2.GetItemDataPtr(m_AvgType2.GetCurSel()), 
	//	m_avgPeriod2, 0x9900ff);

	//
	// Draw the main chart if the user has selected CandleStick or OHLC. We
	// draw it here to make sure it is drawn behind the moving average lines
	// (that is, the moving average lines stay on top.)
	//
	if (selectedType == _T("CandleStick"))
		m.addCandleStick(0x0000ff, 0xff3333);
	else if (selectedType == _T("OHLC"))
		m.addHLOC(0x8000, 0x800000);

	//
	// Add parabolic SAR if necessary
	//
	if (false)//m_ParabolicSAR.GetCheck())
		m.addParabolicSAR(0.02, 0.02, 0.2, Chart::DiamondShape, 5, 0x008800, 0x000000);

	//
	// Add price band/channel/envelop to the chart according to user selection
	//
	//CString selectedBand = L"BB";// (const TCHAR *)m_Band.GetItemDataPtr(m_Band.GetCurSel());
	//if (selectedBand == _T("BB"))
	//	m.addBollingerBand(20, 2, 0x9999ff, 0xc06666ff);
	//else if (selectedBand == _T("DC"))
	//	m.addDonchianChannel(20, 0x9999ff, 0xc06666ff);
	//else if (selectedBand == _T("Envelop"))
	//	m.addEnvelop(20, 0.1, 0x9999ff, 0xc06666ff);

	//
	// Add volume bars to the main chart if necessary
	//
	if (true)//m_Volume.GetCheck())
		m.addVolBars(indicatorHeight, 0x99ff99, 0xff9999, 0xc0c0c0);

	//
	// Add additional indicators as according to user selection.
	//
	addIndicator(&m,L"RSI",// (const TCHAR *)m_Indicator2.GetItemDataPtr(m_Indicator2.GetCurSel()), 
		indicatorHeight);
	//addIndicator(&m, L"None",// (const TCHAR *)m_Indicator3.GetItemDataPtr(m_Indicator3.GetCurSel()), 
	//	indicatorHeight);
	//addIndicator(&m, L"None",// (const TCHAR *)m_Indicator4.GetItemDataPtr(m_Indicator4.GetCurSel()), 
	//	indicatorHeight);

	// Set the chart to the viewer

	XYChart * xChart = (XYChart*)m.getChart(0);
	trackFinance(&m, xChart->getPlotArea()->getRightX());
	viewer->setChart(&m);

	// Set image map (for tool tips) to the viewer
	m.setToolTipDateFormat("[{xLabel|yyyy mmm d}]","[{xLabel|yyyy mmm d}]","[{xLabel|yyyy mmm d}]");
	sprintf(buffer, "title='%s {value|P}'", m.getToolTipDateFormat());
	viewer->setImageMap(m.getHTMLImageMap("", "", buffer));
}




void CChartView::OnBnClickedButtonRefresh()
{
	// TODO: Add your control notification handler code here
	//
	// Sample data for the CandleStick chart.
	//
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
                            "<*font,color=008800*><*img=@triangle,width=8,color=008800*>" :
                            "<*font,color=CC0000*><*img=@invertedtriangle,width=8,color=CC0000*>";

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
        t->draw(plotAreaLeftX + 5, plotAreaTopY + 3, 0x000000, Chart::TopLeft);
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