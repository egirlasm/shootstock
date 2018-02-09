// BuyList.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "BuyList.h"
#include "afxdialogex.h"
#include "../CIni_Src/Ini.h"
#include "shootStockDlg.h"
// CBuyList dialog
const CString m_strRealSet = L"주식시세;주식체결";

// {조회 키,		리얼 키,	행, 열, 타입,			색 변경, 정렬, 앞 문자, 뒷 문자}
const stGRID lstOPTKWFID[] = 
{
	{L"종목코드",		L"-1",	-1,	0,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"종목명",			L"-1",	-1,	1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"현재가",			L"0",	-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"전일대비기호",	L"10",	-1,	-1,	DT_SIGN,		TRUE,	DT_CENTER,	L"",	L""}, 
	{L"등락율",			L"2",	-1,	3,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, 
	{L"거래량",			L"5",	-1,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"시가",			L"16",	-1,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"고가",			L"17",	-1,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"저가",			L"18",	-1,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"종가",			L"18",	-1,8,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수호가",			L"18",	-1,	9,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"매도호가",			L"18",	-1,	10,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	/*{L"매수호가",		L"0",	-1,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"전일거래량대비",	L"13",	-1,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, */
};

// 실시간 주문체결(현재가 표시용)
const stGRID lstOPTKWFID_B[] = 
{
	{L"종목코드",		L"-1",	-1,	0,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"종목명",			L"-1",	-1,	1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"현재가",			L"10",	-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"전일대비기호",	L"25",	-1,	-1,	DT_SIGN,		TRUE,	DT_CENTER,	L"",	L""}, 
	{L"등락율",			L"12",	-1,	3,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, 
	{L"거래량",			L"13",	-1,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"시가",			L"16",	-1,	5,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"고가",			L"17",	-1,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"저가",			L"18",	-1,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"종가",			L"18",	-1,8,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수호가",			L"18",	-1,	9,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"매도호가",			L"18",	-1,	10,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	/*{L"전일대비",		L"11",	-1,	-1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"전일거래량대비",	L"30",	-1,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, */
};

const stGRID lstHOGAZAN[] = 
{
	/////////////////////////////////////
	// 총매도/매수 잔량
	{L"호가시간",		L"61",	0,	0,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""},
	{L"매도호가",		L"63",	0,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	/////////////////////////////////////
	// 매도호가
	{L"매도10차선잔량",	L"70",	1,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도10차선호가",	L"50",	1,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매도9차선잔량",	L"69",	2,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도9차선호가",	L"49",	2,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매도8차선잔량",	L"68",	3,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도8차선호가",	L"48",	3,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매도7차선잔량",	L"67",	4,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도7차선호가",	L"47",	4,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매도6차선잔량",	L"66",	5,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도6차선호가",	L"46",	5,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매도5차선잔량",	L"65",	6,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도5차선호가",	L"45",	6,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매도4차선잔량",	L"64",	7,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도4차선호가",	L"44",	7,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매도3차선잔량",	L"63",	8,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도3차선호가",	L"43",	8,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매도2차선잔량",	L"62",	9,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도2차선호가",	L"42",	9,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매도최우선잔량",	L"61",	10,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매도최우선호가",	L"41",	10,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	/////////////////////////////////////
	// 매수호가
	{L"매수최우선호가",	L"51",	11,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매도최우선잔량",	L"71",	11,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매수2차선호가",	L"52",	12,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수2차선잔량",	L"72",	12,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매수3차선호가",	L"53",	13,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수3차선잔량",	L"73",	13,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매수4차선호가",	L"54",	14,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수4차선잔량",	L"74",	14,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매수5차선호가",	L"55",	15,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수5차선잔량",	L"75",	15,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매수6차선호가",	L"56",	16,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수6차선잔량",	L"76",	16,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매수7차선호가",	L"57",	17,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수7차선잔량",	L"77",	17,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매수8차선호가",	L"58",	18,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수8차선잔량",	L"78",	18,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매수9차선호가",	L"59",	19,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수9차선잔량",	L"79",	19,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"매수10차선호가",	L"60",	20,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"매수10차선잔량",	L"80",	20,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	/////////////////////////////////////
	// 총잔량
	{L"총매도잔량",		L"121",	21,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""},
	{L"총매수잔량",		L"125",	21,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
	/////////////////////////////////////
	// 호가잔량기준시간
	{L"호가잔량기준시간",L"21",	21,	1,	DT_TIME,		FALSE,	DT_CENTER,	L"",	L""}, 
	/////////////////////////////////////
	// 시간외 매도/매수 잔량
	{L"시간외매도잔량",	L"131",	22,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""},
	{L"시간외매수잔량",	L"132",	22,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",	L""}, 
};


IMPLEMENT_DYNAMIC(CBuyList, CDialogEx)

CBuyList::CBuyList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBuyList::IDD, pParent)
{

}

CBuyList::~CBuyList()
{
}

void CBuyList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_COMBO1, m_SearchComboList);
}


BEGIN_MESSAGE_MAP(CBuyList, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CBuyList::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CBuyList::OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CBuyList::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CBuyList::OnBnClickedButtonRefresh)
	ON_BN_CLICKED(IDC_ORDER1, &CBuyList::OnBnClickedOrder1)
	ON_BN_CLICKED(IDC_ORDER2, &CBuyList::OnBnClickedOrder2)
	ON_BN_CLICKED(IDC_ORDER3, &CBuyList::OnBnClickedOrder3)
	ON_BN_CLICKED(IDC_BUTTON_SELLALL, &CBuyList::OnBnClickedButtonSellall)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CBuyList::OnBnClickedButtonTest)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CBuyList::OnNMClickList)
END_MESSAGE_MAP()


// CBuyList message handlers


BOOL CBuyList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	InitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CBuyList::InitList(void)
{
	m_ListBox.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_DOUBLEBUFFER );
	m_ListBox.ModifyStyle(0,LVS_SINGLESEL); 
	m_ListBox.SetGridLines();
	m_ListBox.InsertColumn(0,L"코드",0,50);
	m_ListBox.InsertColumn(1,L"종목명",0,80);
	m_ListBox.InsertColumn(2,L"현재가",0,70);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_ListBox.InsertColumn(3,L"등락률",0,80);
	m_ListBox.InsertColumn(4,L"거래량",0,80);
	m_ListBox.InsertColumn(5,L"시가",0,80);
	m_ListBox.InsertColumn(6,L"고가",0,80);
	m_ListBox.InsertColumn(7,L"저가",0,80);
	m_ListBox.InsertColumn(8,L"종가",0,80);
	m_ListBox.InsertColumn(9,L"매수호가",0,80);
	m_ListBox.InsertColumn(10,L"매도호가",0,80);
}





//*******************************************************************/
//! Function Name : SendJongSearch
//! Function      : 종목 조회 요청
//! Param         : int nCodeCount/* = 0*/, CString strCodeList/* = ""*/ : 유형 - "000660;005930;", int nAddType/*= 0*/ 기존 종목조회에서 추가로 종목을 조회할때 여부(0:기본, 5:추가)
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CBuyList::SendJongSearch(int nCodeCount/* = 0*/, CString strCodeList/* = ""*/, int nAddType/*= 0*/)
{
	if (nCodeCount < 1 || strCodeList.GetLength() < 1)
	{
		int i, nCnt = m_ListBox.GetItemCount();
		if (nCnt < 2)
		{
			return;
		}
		nCodeCount = 0;
		for (i = 1; i < nCnt; i++)
		{
			nCodeCount++;
			CString temp = m_ListBox.GetItemText(i, 0) + ";";
			strCodeList += temp;
		}
	}

	if (nCodeCount > 0 && strCodeList.GetLength() > 0)
	{
		CString strRQName = _T("관심종목");
		long lRet = theApp.m_khOpenApi.CommKwRqData(strCodeList, 0, nCodeCount, nAddType, strRQName, m_strScrNo);
		if (!theApp.IsError(lRet))
		{
			return;
		}
	}
}
void CBuyList::GetDataSearch(void)
{

	CString strFileIniPath = QueryExePath() + _T("subject.ini");
	CIni Jongmok(strFileIniPath);
	int i, nCnt =Jongmok.GetInt(L"JONG_CODE",L"COUNT",0)+ 1;
	CString strCode, strIndex, strCodeList = L"";

	
	m_mapJongCode.RemoveAll();

	for (i = 1; i < nCnt; i++)
	{
		strIndex.Format(L"%d", i);
	
		
		CString szItem =  Jongmok.GetString(L"JONG_CODE",strIndex);
		strCode = szItem;		
		strCode.Trim();

		// 종목코드 추가
		m_mapJongCode.SetAt(strCode, strIndex);

		//m_grdKwanSim.SetRowHeight(i, 20);		// 행의 높이 설정
		//m_grdKwanSim.SetItemText(i, 0, strCode);
		int dwCount = m_ListBox.GetItemCount();

		int dwitem = m_ListBox.InsertItem(dwCount,strCode,0);

// 		m_ListBox.SetItem(dwitem,1,1,usrMgr->strData1,0,0,0,0);
// 		m_ListBox.SetItem(dwitem,2,1,usrMgr->strData2,0,0,0,0);
// 		m_ListBox.SetItem(dwitem,3,1,usrMgr->strData3,0,0,0,0);
// 		m_ListBox.SetItem(dwitem,4,1,usrMgr->strData4,0,0,0,0);
		//m_ListCtrl.SetItem(dwitem,4,1,ch,0,0,0,0);
		m_ListBox.SetItemData(dwitem,(DWORD)strCode.GetBuffer());

		if(isOdd(dwitem))
			m_ListBox.SetItemBkColor(dwitem, -1, RGB(241,244,248), FALSE);
		strCodeList += strCode + L";";
	}
	if (!strCodeList.IsEmpty())
	{
		// 종목 조회 요청
		SendJongSearch(nCnt - 1, strCodeList,0);
	}
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CBuyList::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	CString strRQName = sRQName;
	if (strRQName == _T("관심종목"))			// 관심종목정보 설정
	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPTKWFID) / sizeof(*lstOPTKWFID);		// 전체크기 / 원소크기 = 원소개수
		//m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
// 		CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
// 		//pMain->m_buyList.m_ListBox.SetItem(0,0,1,L"asdfasdf",0,0,0,0);
// 
// 		CReportCtrl * pListCtrl = &pMain->m_buyList.m_ListBox;
		strRQName = _T("관심종목정보");
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPTKWFID[j].strKey);	strData.Trim();
// 				pListCtrl->SetItem(i,j,1,strData,0,0,0,0);
// 				if(j == 2){
// 					if(strData.GetAt(0) == '-')
// 						pListCtrl->SetItemTextColor(i,j,RGB(0,0,255));
// 					else
// 						pListCtrl->SetItemTextColor(i,j,RGB(255,0,0));
// 				}
				//pListCtrl->SetItemBkColor(i,j,RGB(255,0,0)); red
				
				//m_grdKwanSim.SetItemFormat(i + 1, lstOPTKWFID[j].nCol, lstOPTKWFID[j].nAlign);
				//m_ListBox.SetItemText(0,j,strData);
				//m_ListBox.SetItem(i,j,1,strData,0,0,0,0);
				arrData.Add(strData);
				
			}
			OnUpdateListData(arrData);
			//SetDataKwanSimGrid(arrData);
		}
// 		if (m_cellSelect.row > 0)
// 		{
// 			if (m_cellSelect.row >= m_grdKwanSim.GetRowCount())
// 			{
// 				m_cellSelect.row = m_grdKwanSim.GetRowCount() - 1;
// 			}
// 			m_grdKwanSim.SetFocusCell(m_cellSelect);
// 			m_grdKwanSim.SetSelectedRange(m_cellSelect.row, m_cellSelect.col, m_cellSelect.row, m_cellSelect.col);
// 		}
	}
	else if(strRQName == _T("증거금율별주문가능수량조회요청")){
		CString strData;
		CStringArray arrData;
		int nFieldCnt = 35;// sizeof(lstOPT10012) / sizeof(*lstOPT10012);		// 전체크기 / 원소크기 = 원소개수

		strRQName = _T("증거금율별주문가능수량조회");
		arrData.RemoveAll();
		for (int nIdx = 0; nIdx < nFieldCnt; nIdx++)
		{
			strData.Format(L"%d",nIdx);
			strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0,strData );	strData.Trim();
			if(!strData.IsEmpty()){
				//TraceOutputW(strData);
				OutputDebugString(strData);
			}
			arrData.Add(strData);
		}
	}
	if (strRQName == _T("주식기본정보요청"))			// 계좌수익률//if (!lstrcmp(sRealType, L"주식체결"))	// 주식체결
	{

		//CString strData;

		//strRQName = _T("주식기본정보");

		//strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"종목코드");	strData.Trim();

		//CString strTemp;
		//if (!m_mapJongCode.Lookup(strData, strTemp))
		//{
		//	return;
		//}
		//int nRow = _wtol(strTemp) -1;
		////m_ListBox.SetItem(nRow,5,1,strData,0,0,0,0);
		//
		////if(strData.GetAt(0) == '+')
		////	m_ListBox.SetItemTextColor(dwitem,j,RGB(255,0,0));
		////else if(strData.GetAt(0) == '-')
		////	m_ListBox.SetItemTextColor(dwitem,j,RGB(0,0,255));
		////else
		////	m_ListBox.SetItemTextColor(dwitem,j,RGB(0,0,0));

		//strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"시가");	strData.Trim();
		//m_ListBox.SetItem(nRow,5,1,strData,0,0,0,0);
		//strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"고가");	strData.Trim();
		//m_ListBox.SetItem(nRow,6,1,strData,0,0,0,0);
		//strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, 0, L"시가");	strData.Trim();
		//m_ListBox.SetItem(nRow,7,1,strData,0,0,0,0);
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
void CBuyList::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	/*CString strIndex, strData;
	if (!m_mapJongCode.Lookup(sJongmokCode, strIndex))
	{
		return;
	}

	CString strCode;*/
	//CshootStockDlg* pMain =  (CshootStockDlg*)AfxGetApp()->GetMainWnd();
	//pMain->TraceOutputW(sRealType);
	CString strIndex;
	if (!m_mapJongCode.Lookup(sJongmokCode, strIndex) || m_strRealSet.Find(sRealType) < 0)
	{
		return;
	}

	CString strData;
	CStringArray arrData;
	if (!lstrcmp(sRealType, L"주식시세"))		// 주식시세
	{
		//arrData.Add(sJongmokCode);
		//int i, nFieldCnt = sizeof(lstOPTKWFID) / sizeof(*lstOPTKWFID);		// 전체크기 / 원소크기 = 원소개수
		//for (i = 1; i < nFieldCnt; i++)
		//{
		//	if (_wtoi(lstOPTKWFID[i].strRealKey) < 0)
		//	{
		//		arrData.Add(L"");
		//		continue;
		//	}
		//	strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstOPTKWFID[i].strRealKey));	strData.Trim();
		//	arrData.Add(strData);
		//}
		//SetDataKwanSimGrid(arrData, sRealType);
	}
	else if (!lstrcmp(sRealType, L"주식체결"))	// 주식체결
	{
		arrData.Add(sJongmokCode);
	
		int i, nFieldCnt = sizeof(lstOPTKWFID_B) / sizeof(*lstOPTKWFID_B);		// 전체크기 / 원소크기 = 원소개수
		for (i = 1; i < nFieldCnt; i++)
		{
			if (_wtoi(lstOPTKWFID_B[i].strRealKey) < 0)
			{
				arrData.Add(L"");
				continue;
			}

			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstOPTKWFID_B[i].strRealKey));	strData.Trim();
			arrData.Add(strData);
		}
		//SetDataKwanSimGrid(arrData, sRealType);
		OnUpdateListData(arrData,sRealType);
	}
// 	else if (!lstrcmp(sRealType, L"주식호가잔량"))	// 주식체결
// 	{
// 		arrData.Add(sJongmokCode);
// 		int i, nFieldCnt = sizeof(lstOPTKWFID_B) / sizeof(*lstOPTKWFID_B);		// 전체크기 / 원소크기 = 원소개수
// 		for (i = 1; i < nFieldCnt; i++)
// 		{
// 			if (_wtoi(lstOPTKWFID[i].strRealKey) < 0)
// 			{
// 				arrData.Add(L"");
// 				continue;
// 			}
// 			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstOPTKWFID_B[i].strRealKey));	strData.Trim();
// 			arrData.Add(strData);
// 		}
// 		//SetDataKwanSimGrid(arrData, sRealType);
// 		//OnUpdateListData(arrData,sRealType);
// 	}
// 	else if (!lstrcmp(sRealType, L"주식예상체결"))	// 주식체결
// 	{
// 		arrData.Add(sJongmokCode);
// 		int i, nFieldCnt = sizeof(lstOPTKWFID_B) / sizeof(*lstOPTKWFID_B);		// 전체크기 / 원소크기 = 원소개수
// 		for (i = 1; i < nFieldCnt; i++)
// 		{
// 			if (_wtoi(lstOPTKWFID[i].strRealKey) < 0)
// 			{
// 				arrData.Add(L"");
// 				continue;
// 			}
// 			strData = theApp.m_khOpenApi.GetCommRealData(sJongmokCode, _wtoi(lstOPTKWFID_B[i].strRealKey));	strData.Trim();
// 			arrData.Add(strData);
// 		}
// 		//SetDataKwanSimGrid(arrData, sRealType);
// 		//OnUpdateListData(arrData,sRealType);
// 	}
};

//*******************************************************************/
//! Function Name : SetDataKwanSimGrid
//! Function      : 관심 그리드 데이타 설정(관심종목정보 설정)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CBuyList::OnUpdateListData(CStringArray &arrData, CString strRealType/* = ""*/)
{
	// 종목코드에 맞는 행 찾기

	CString strData, strTemp;
	strData = arrData.GetAt(0);
	if (!m_mapJongCode.Lookup(strData, strTemp))
	{
		return;
	}
	m_ListBox.SetRedraw(FALSE);
	// 종목명
	int i, nRow = _wtol(strTemp) -1, nCnt = arrData.GetSize();
 	if (strRealType == "")
 	{
 		CString strName = arrData.GetAt(1);
 		//((CStatic*)GetDlgItem(IDC_EDT_JONGCODE))->GetWindowText(strTemp);	// 종목코드 입력란
//  		if (strTemp == strData)
//  		{
//  			((CStatic*)GetDlgItem(IDC_STC_JONGNAME))->SetWindowText(strName);
//  		}
 		//m_grdKwanSim.SetItemText(nRow, lstOPTKWFID[1].nCol, theApp.ConvDataFormat(lstOPTKWFID[1].nDataType, strName, lstOPTKWFID[1].strBeforeData, lstOPTKWFID[1].strAfterData));
		//m_ListBox.SetItemText(nRow,lstOPTKWFID[0].nCol, theApp.ConvDataFormat(lstOPTKWFID[0].nDataType, strData, lstOPTKWFID[0].strBeforeData, lstOPTKWFID[0].strAfterData));
		m_ListBox.SetItemText(nRow, lstOPTKWFID[1].nCol, theApp.ConvDataFormat(lstOPTKWFID[1].nDataType, strName, lstOPTKWFID[1].strBeforeData, lstOPTKWFID[1].strAfterData));
 	}

	// 데이타 설정
	CString strTempData;
	for (i = 2; i < nCnt; i++)
	{
		strData = arrData.GetAt(i);
		/////////////////////////////////////////////
		// 변경 된 데이터 선택 처리↓↓↓↓↓↓↓↓↓
		if (strRealType != "" && (i == 2 || i == 4 || i == 5))
		{
			strTempData = strData;
			strTempData.Replace(L"+", L"");	strTempData.Replace(L"-", L"");	strTempData.Replace(L".", L"");

			//strTemp = m_grdKwanSim.GetItemText(nRow, lstOPTKWFID[i].nCol);
			strTemp.Replace(L"%", L"");	strTemp.Replace(L"+", L"");	strTemp.Replace(L"-", L"");
			strTemp.Replace(L",", L"");	strTemp.Replace(L".", L"");
			if (strTempData != strTemp)
			{
// 				m_cellSelect.col = lstOPTKWFID[i].nCol;
// 				m_grdKwanSim.SetFocusCell(m_cellSelect);
// 				m_grdKwanSim.SetSelectedRange(nRow, m_cellSelect.col, nRow, m_cellSelect.col);
// 				m_grdKwanSim.Invalidate();
			}
		}
		// 변경 된 데이터 선택 처리↑↑↑↑↑↑↑↑↑
		/////////////////////////////////////////////
		if (lstOPTKWFID_B[i].bTextColor)
		{
			strTemp = arrData.GetAt(3);
			COLORREF tempC = RGB(0,0,255);
			if (strTemp == "1" || strTemp == "2")	// 부호에 따라 색상변경
			{
				strTemp = "1";
				tempC =  RGB(255,0,0);
			}
			else if (strTemp == "4" || strTemp == "5")	// 부호에 따라 색상변경
			{
				strTemp = "-1";
				tempC =  RGB(0,0,255);
			}
			else
			{
				strTemp = "0";
				tempC =  RGB(0,0,0);
			}
			if(lstOPTKWFID_B[i].nCol != -1)
				m_ListBox.SetItemTextColor(nRow,lstOPTKWFID_B[i].nCol,tempC);
			//theApp.SetDataFgColour(&m_grdKwanSim, nRow, lstOPTKWFID[i].nCol, strTemp);
		}
		if (lstOPTKWFID_B[i].nDataType == DT_SIGN)
		{
			//theApp.SetSignData(&m_grdKwanSim, nRow, lstOPTKWFID[i].nCol, strData);
		}
		else
		{
			if (strData.IsEmpty())
			{
				continue;
			}
			if(lstOPTKWFID_B[i].nCol < 2){
				OutputDebugStringA("fuck");
			}
			m_ListBox.SetItemText(nRow,lstOPTKWFID_B[i].nCol, theApp.ConvDataFormat(lstOPTKWFID_B[i].nDataType, strData, lstOPTKWFID_B[i].strBeforeData, lstOPTKWFID_B[i].strAfterData));
			//m_grdKwanSim.SetItemText(nRow, lstOPTKWFID[i].nCol, theApp.ConvDataFormat(lstOPTKWFID[i].nDataType, strData, lstOPTKWFID[i].strBeforeData, lstOPTKWFID[i].strAfterData));
		}
	}
	//m_grdKwanSim.Invalidate();
	//m_ListBox.Invalidate();
	m_ListBox.SetRedraw(true);
}


void CBuyList::OnBnClickedButtonSearch()
{
	// TODO: Add your control notification handler code here
	// 종목코드 입력 여부
	CString strFileIniPath = QueryExePath() + _T("subject.ini");
	CIni Jongmok(strFileIniPath);

	CString strCode, strIndex;
	m_SearchComboList.GetWindowTextW(strCode);
	
	if (strCode.GetLength() != 6)
	{
		AfxMessageBox(L"종목코드 6자를 입력 해 주세요~!");
		m_SearchComboList.SetFocus();
		return;
	}

	if (m_mapJongCode.Lookup(strCode, strIndex))
	{
		AfxMessageBox(L"이미 등록 된 종목입니다.");
		/*CCellID cureentCell(atoi(strIndex), 0);
		m_grdKwanSim.SetFocusCell(cureentCell);
		m_grdKwanSim.SetSelectedRange(cureentCell.row, 0, cureentCell.row, 7);*/
		m_SearchComboList.SetFocus();
		return;
	}

// 	CString strFileName = theApp.m_sAppPath + "/data/kwansim.ini";
// 	int nCnt = ::GetPrivateProfileInt("JONG_CODE", "COUNT", 0,strFileName) + 1;
	int nCnt =Jongmok.GetInt(L"JONG_CODE",L"COUNT",0)+ 1;
	// 종목코드 갯수 추가
	strIndex.Format(L"%d", nCnt);
	//::WritePrivateProfileString("JONG_CODE", "COUNT", strIndex, strFileName);
	Jongmok.WriteString(L"JONG_CODE", L"COUNT", strIndex);
	// 종목코드 추가
	Jongmok.WriteString(L"JONG_CODE", strIndex, strCode);
	
	m_mapJongCode.SetAt(strCode, strIndex);

	// 행 추가
	//m_grdKwanSim.InsertRow("", -1);
	//m_grdKwanSim.SetRowHeight(1, 20);		// 행의 높이 설정
	//m_grdKwanSim.SetItemFormat(lstOPTKWFID[nCnt].nRow, lstOPTKWFID[nCnt].nCol, lstOPTKWFID[nCnt].nAlign);
	//m_grdKwanSim.SetItemText(nCnt, 0, strCode);
	int dwCount = m_ListBox.GetItemCount();

	int dwitem = m_ListBox.InsertItem(dwCount,strCode,0);

	// 		m_ListBox.SetItem(dwitem,1,1,usrMgr->strData1,0,0,0,0);
	// 		m_ListBox.SetItem(dwitem,2,1,usrMgr->strData2,0,0,0,0);
	// 		m_ListBox.SetItem(dwitem,3,1,usrMgr->strData3,0,0,0,0);
	// 		m_ListBox.SetItem(dwitem,4,1,usrMgr->strData4,0,0,0,0);
	//m_ListCtrl.SetItem(dwitem,4,1,ch,0,0,0,0);
	m_ListBox.SetItemData(dwitem,(DWORD)strCode.GetBuffer());

	if(isOdd(dwitem))
		m_ListBox.SetItemBkColor(dwitem, -1, RGB(241,244,248), FALSE);

	// 종목 조회 요청
	SendJongSearch(1, strCode, 5);
}


void CBuyList::OnBnClickedButtonDel()
{
	// TODO: Add your control notification handler code here
	CString strFileIniPath = QueryExePath() + _T("subject.ini");
	CIni Jongmok(strFileIniPath);
	CString strJongCode = L"";
	TCHAR strIndex[10] ={0};
	int nCnt = m_ListBox.GetItemCount();
	for(int i=0; i<m_ListBox.GetItemCount(); i++)
	{
		if( m_ListBox.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{

			_itow(i+1,strIndex,10);
			strJongCode = m_ListBox.GetItemText(i,0);
			//Jongmok.DeleteKey(L"JONG_CODE",strIndex);
			//AfxMessageBox(strText);
			CString strTemp;
			strTemp.Format(L"관심종목 [%s %s] 을 삭제 하겠습니까?", 
				 m_ListBox.GetItemText(i,0), 
				 m_ListBox.GetItemText(i,1));
			if (MessageBox(strTemp, L"관심종목 삭제", MB_ICONQUESTION | MB_YESNO) == IDNO)
			{
				return;
			}

			nCnt--;
			//m_grdKwanSim.DeleteRow(m_cellSelect.row);
			m_ListBox.DeleteItem(i);
			m_ListBox.Invalidate();
			//Jongmok.DeleteKey(L"JOMG_CODE",strIndex);
			DeleteFile(strFileIniPath);
			//m_mapJongCode.RemoveAll();

			//
			//// 종목코드 갯수 추가
			CString strIndex, strCode;
			strIndex.Format(L"%d", nCnt);
			//::WritePrivateProfileString("JONG_CODE", "COUNT", strIndex, strFileName);
			Jongmok.WriteString(L"JONG_CODE",L"COUNT",strIndex);
			// 종목 재설정
			int i;
			for (i = 1; i <= nCnt; i++)
			{
				strIndex.Format(L"%d", i);
				strCode = m_ListBox.GetItemText(i-1, 0);

				// 종목코드 추가
				//::WritePrivateProfileString("JONG_CODE", strIndex, strCode, strFileName);
				Jongmok.WriteString(L"JONG_CODE",strIndex,strCode);
				m_mapJongCode.SetAt(strCode, strIndex);
			}

			//SendJongSearch();		// 종목 조회 요청
		}
	}
}


void CBuyList::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
}


void CBuyList::OnBnClickedButtonRefresh()
{
	// TODO: Add your control notification handler code here
}


BOOL CBuyList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)   
		return TRUE;
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)   
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CBuyList::OnBnClickedButtonSellall()
{
	// TODO: Add your control notification handler code here
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();

	CString strRQName = _T("주식주문");

	int nCount = pMain->m_OrderList.GetSize();

	CString strHavingCount = L"";
	CString strKey, strScrType;
	POSITION pos =  pMain->m_OrderList.GetStartPosition();
	while (pos != NULL)
	{
		strHavingCount= L"";
		pMain->m_OrderList.GetNextAssoc(pos, strKey, strScrType);
		if (pMain->m_OrderList.Lookup(strKey, strHavingCount) && _wtoi(strHavingCount))
		{
			 int sellCount = _wtoi(strHavingCount);
			theApp.m_khOpenApi.SendOrder(strRQName,pMain->m_strScrNo, pMain->m_AccNo, 2, strKey, sellCount, 0, L"03", L"");
		}
	}
	//CString strData =  theApp.m_khOpenApi.GetChejanData(9001);
	//CString strRQName = _T("주식주문");
	//theApp.m_khOpenApi.SendOrder(strRQName,pMain->m_strScrNo, L"8100875411", 1, strJongCode, buyCount, 0, L"03", L"")
}

void CBuyList::OnBnClickedButtonTest()
{
	// TODO: Add your control notification handler code here

	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strRQName = _T("증거금율별주문가능수량조회요청");
	theApp.m_khOpenApi.SetInputValue(L"계좌번호"	, pMain->m_AccNo);

	//비밀번호 = 사용안함(공백)
		theApp.m_khOpenApi.SetInputValue(L"비밀번호"	,  L"");

	//비밀번호입력매체구분 = 00
		theApp.m_khOpenApi.SetInputValue(L"비밀번호입력매체구분"	,  L"2419");

	theApp.m_khOpenApi.SetInputValue(L"종목번호"	,  L"007370");
	theApp.m_khOpenApi.SetInputValue(L"매수가격"	,  L"7230");

	long ret =  theApp.m_khOpenApi.CommRqData(strRQName,L"OPW00011",0,m_strScrNo);
	theApp.IsError(ret);
}

void CBuyList::OnBnClickedOrder1()
{
	// TODO: Add your control notification handler code here
	// 매매구분 취득(1:신규매수, 2:신규매도 3:매수취소, 4:매도취소, 5:매수정정, 6:매도정정)
	// 거래구분 취득
	// 0:지정가, 3:시장가, 5:조건부지정가, 6:최유리지정가, 7:최우선지정가, 
	// 10:지정가IOC, 13:시장가IOC, 16:최유리IOC, 20:지정가FOK, 23:시장가FOK, 
	// 26:최유리FOK, 61:장개시전시간외, 62:시간외단일가매매, 81:장후시간외종가
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strJongCode = L"";
	CString nowPrice = L"";
	for(int i=0; i<m_ListBox.GetItemCount(); i++)
	{
		if( m_ListBox.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{

			strJongCode = m_ListBox.GetItemText(i,0);
			nowPrice = m_ListBox.GetItemText(i,2);
			
			//AfxMessageBox(strText);
		}
	}
	if(!theApp.g_MyMoney){
		AfxMessageBox(L"you have no money or not input the password dammit! fuck!");
		return;
	}
	CString strRQName = _T("주식주문");
	long lRet;
	nowPrice.Replace(L",",L"");
	int buyCount = theApp.g_MyMoney / _wtoi(nowPrice) -1;
	pMain->m_boughtCount = buyCount;
	CString fmt;
	fmt.Format(L"주식종목 %s ,주식가능수 %d, 주식 현재가 %s",strJongCode,buyCount,nowPrice);
	pMain->TraceOutputW(fmt);
	lRet = theApp.m_khOpenApi.SendOrder(strRQName, pMain->m_strScrNo,pMain->m_AccNo, 1, strJongCode, buyCount, 0, L"03", L"");
}


void CBuyList::OnBnClickedOrder2()
{
	// TODO: Add your control notification handler code here
}


void CBuyList::OnBnClickedOrder3()
{
	// TODO: Add your control notification handler code here
}


void CBuyList::OnBnClickedButtonAdd(CString t_strCode)
{
	CString strFileIniPath = QueryExePath() + _T("subject.ini");
	CIni Jongmok(strFileIniPath);

	CString strCode = t_strCode, strIndex;
	
	
	if (strCode.GetLength() != 6)
	{
		AfxMessageBox(L"종목코드 6자를 입력 해 주세요~!");
		m_SearchComboList.SetFocus();
		return;
	}

	if (m_mapJongCode.Lookup(strCode, strIndex))
	{
		AfxMessageBox(L"이미 등록 된 종목입니다.");
		/*CCellID cureentCell(atoi(strIndex), 0);
		m_grdKwanSim.SetFocusCell(cureentCell);
		m_grdKwanSim.SetSelectedRange(cureentCell.row, 0, cureentCell.row, 7);*/
		m_SearchComboList.SetFocus();
		return;
	}

// 	CString strFileName = theApp.m_sAppPath + "/data/kwansim.ini";
// 	int nCnt = ::GetPrivateProfileInt("JONG_CODE", "COUNT", 0,strFileName) + 1;
	int nCnt =Jongmok.GetInt(L"JONG_CODE",L"COUNT",0)+ 1;
	// 종목코드 갯수 추가
	strIndex.Format(L"%d", nCnt);
	//::WritePrivateProfileString("JONG_CODE", "COUNT", strIndex, strFileName);
	Jongmok.WriteString(L"JONG_CODE", L"COUNT", strIndex);
	// 종목코드 추가
	Jongmok.WriteString(L"JONG_CODE", strIndex, strCode);
	
	m_mapJongCode.SetAt(strCode, strIndex);

	// 행 추가
	//m_grdKwanSim.InsertRow("", -1);
	//m_grdKwanSim.SetRowHeight(1, 20);		// 행의 높이 설정
	//m_grdKwanSim.SetItemFormat(lstOPTKWFID[nCnt].nRow, lstOPTKWFID[nCnt].nCol, lstOPTKWFID[nCnt].nAlign);
	//m_grdKwanSim.SetItemText(nCnt, 0, strCode);
	int dwCount = m_ListBox.GetItemCount();

	int dwitem = m_ListBox.InsertItem(dwCount,strCode,0);

	// 		m_ListBox.SetItem(dwitem,1,1,usrMgr->strData1,0,0,0,0);
	// 		m_ListBox.SetItem(dwitem,2,1,usrMgr->strData2,0,0,0,0);
	// 		m_ListBox.SetItem(dwitem,3,1,usrMgr->strData3,0,0,0,0);
	// 		m_ListBox.SetItem(dwitem,4,1,usrMgr->strData4,0,0,0,0);
	//m_ListCtrl.SetItem(dwitem,4,1,ch,0,0,0,0);
	m_ListBox.SetItemData(dwitem,(DWORD)strCode.GetBuffer());

	if(isOdd(dwitem))
		m_ListBox.SetItemBkColor(dwitem, -1, RGB(241,244,248), FALSE);

	// 종목 조회 요청
	SendJongSearch(1, strCode, 5);
}









void CBuyList::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	CshootStockDlg * pMain = (CshootStockDlg *)AfxGetApp()->GetMainWnd();
	CString strJongCode = L"";
	CString nowPrice = L"";
	for(int i=0; i<m_ListBox.GetItemCount(); i++)
	{
		if( m_ListBox.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			strJongCode = m_ListBox.GetItemText(i,0);
			pMain->m_boardJongmokCode = strJongCode;
			theApp.m_khOpenApi.SetInputValue(L"종목코드",strJongCode);
			theApp.m_khOpenApi.CommRqData(L"주식기본정보요청",L"OPT10001",0,pMain->m_strScrNo);
		}
	}
	*pResult = 0;
}
