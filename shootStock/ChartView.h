#pragma once

#include "chartdir.h"
#include "ChartViewer.h"
// CChartView dialog

class CChartView : public CDialogEx
{
	DECLARE_DYNAMIC(CChartView)

public:
	CChartView(CWnd* pParent = NULL);   // standard constructor
	virtual ~CChartView();

// Dialog Data
	enum { IDD = IDD_DIALOG_CHART };
	CString							m_strScrNo;
	// The ticker symbol, timeStamps, volume, high, low, open and close data    
	CString m_tickerKey;
	DoubleArray m_timeStamps;	
	DoubleArray m_volData;
	DoubleArray m_highData;
	DoubleArray m_lowData;
	DoubleArray m_openData;
	DoubleArray m_closeData;
	int m_noOfPoints;


	// An extra data series to compare with the close data
	CString m_compareKey;
	double *m_compareData;
	int m_compareDataLen;


	// The resolution of the data in seconds. 1 day = 86400 seconds.
	int m_resolution;

	// The moving average periods
	int m_avgPeriod1;
	int m_avgPeriod2;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	void OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData);
	void OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);

	virtual BOOL OnInitDialog();
	CChartViewer m_ChartViewer;
	void trackFinance(MultiChart *m, int mouseX);
	virtual void drawChart(CChartViewer *viewer);
	virtual bool getData(const CString &ticker, double startDate, double endDate,
		int durationInDays, int extraPoints);
	virtual void get15MinData(const CString &ticker, double startDate, double endDate);
	virtual void getDailyData(const CString &ticker, double startDate, double endDate);
	virtual void getWeeklyData(const CString &ticker, double startDate, double endDate);
	virtual void getMonthlyData(const CString &ticker, double startDate, double endDate);

	
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnMouseMovePlotArea();
	afx_msg void OnViewPortChanged();	
	void SendSearch(void);
	CViewPortControl m_ViewPortControl;
	afx_msg void OnBnClickedButtonDaily();
	afx_msg void OnBnClickedButtonMinute();
	afx_msg void OnBnClickedButton1();
};
