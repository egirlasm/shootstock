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
	int noOfDays = 100;

	// To compute moving averages starting from the first day, we need to get extra data points before
	// the first day
	int extraDays = 30;

	// In this exammple, we use a random number generator utility to simulate the data. We set up the
	// random table to create 6 cols x (noOfDays + extraDays) rows, using 9 as the seed.
	RanTable rantable(9, 6, noOfDays + extraDays);

	// Set the 1st col to be the timeStamp, starting from Sep 4, 2011, with each row representing one
	// day, and counting week days only (jump over Sat and Sun)
	rantable.setDateCol(0, Chart::chartTime(2011, 9, 4), 86400, true);

	// Set the 2nd, 3rd, 4th and 5th columns to be high, low, open and close data. The open value
	// starts from 100, and the daily change is random from -5 to 5.
	rantable.setHLOCCols(1, 100, -5, 5);

	// Set the 6th column as the vol data from 5 to 25 million
	rantable.setCol(5, 50000000, 250000000);

	// Now we read the data from the table into arrays
	DoubleArray timeStamps = rantable.getCol(0);
	DoubleArray highData = rantable.getCol(1);
	DoubleArray lowData = rantable.getCol(2);
	DoubleArray openData = rantable.getCol(3);
	DoubleArray closeData = rantable.getCol(4);
	DoubleArray volData = rantable.getCol(5);

	// Create a FinanceChart object of width 720 pixels
	FinanceChart *c = new FinanceChart(720);

	// Add a title to the chart
	c->addTitle("Finance Chart Demonstration");

	// Disable default legend box, as we are using dynamic legend
	c->setLegendStyle("normal", 8, Chart::Transparent, Chart::Transparent);

	// Set the data into the finance chart object
	c->setData(timeStamps, highData, lowData, openData, closeData, volData, extraDays);

	// Add the main chart with 240 pixels in height
	c->addMainChart(240);

	// Add a 10 period simple moving average to the main chart, using brown color
	c->addSimpleMovingAvg(10, 0x663300);

	// Add a 20 period simple moving average to the main chart, using purple color
	c->addSimpleMovingAvg(20, 0x9900ff);

	// Add candlestick symbols to the main chart, using green/red for up/down days
	c->addCandleStick(0x00ff00, 0xff0000);

	// Add 20 days bollinger band to the main chart, using light blue (9999ff) as the border and
	// semi-transparent blue (c06666ff) as the fill color
	c->addBollingerBand(20, 2, 0x9999ff, 0xc06666ff);

	// Add a 75 pixels volume bars sub-chart to the bottom of the main chart, using green/red/grey for
	// up/down/flat days
	c->addVolBars(75, 0x99ff99, 0xff9999, 0x808080);

	// Append a 14-days RSI indicator chart (75 pixels high) after the main chart. The main RSI line
	// is purple (800080). Set threshold region to +/- 20 (that is, RSI = 50 +/- 25). The upper/lower
	// threshold regions will be filled with red (ff0000)/blue (0000ff).
	c->addRSI(75, 14, 0x800080, 20, 0xff0000, 0x0000ff);

	// Append a MACD(26, 12) indicator chart (75 pixels high) after the main chart, using 9 days for
	// computing divergence.
	c->addMACD(75, 26, 12, 9, 0x0000ff, 0xff00ff, 0x008000);

	// Include track line with legend for the latest data values
	trackFinance(c, ((XYChart *)c->getChart(0))->getPlotArea()->getRightX());

	// Assign the chart to the WinChartViewer
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