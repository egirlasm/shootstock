// TopPrice.cpp : implementation file
//

#include "stdafx.h"
#include "shootStock.h"
#include "TopPrice.h"
#include "afxdialogex.h"
#include "shootStockDlg.h"
#include "sqlite3/sqlite3.h"
#include <hash_set>
#include "sha1.h"
const stGRID lstOPT10027[] = 
{
	{L"종목분류",			L"-1",	-1,	0,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"종목코드",			L"-1",	-1,	1,	DT_NONE,		FALSE,	DT_LEFT,	L"",	L""}, 
	{L"종목명",				L"0",	-1,	2,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"현재가",				L"10",	-1,	3,	DT_SIGN,		TRUE,	DT_CENTER,	L"",	L""}, 
	{L"전일대비기호",		L"2",	-1,	4,	DT_NUMBER,	TRUE,	DT_RIGHT,	L"",	L"%"}, 
	{L"전일대비",			L"5",	-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""}, 
	{L"등락률",				L"0",	-1,	6,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"매도잔량",			L"13",	-1,	7,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"매수잔량",			L"13",	-1,	8,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"현재거래량",			L"13",	-1,	9,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"체결강도",			L"13",	-1,	10,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
	{L"횟수",				L"13",	-1,	11,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""}, 
};
// CTopPrice dialog

IMPLEMENT_DYNAMIC(CTopPrice, CDialogEx)

CTopPrice::CTopPrice(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTopPrice::IDD, pParent)
	, m_curDate(_T(""))
{
	
}

CTopPrice::~CTopPrice()
{
}

void CTopPrice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_TopList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateCtrl);
}


BEGIN_MESSAGE_MAP(CTopPrice, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CTopPrice::OnRclickList)
	ON_COMMAND(ID_POPMENU_ADD, &CTopPrice::OnPopmenuAdd)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CTopPrice::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CTopPrice::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CTopPrice::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CTopPrice message handlers


BOOL CTopPrice::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	InitList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CTopPrice::InitList(void)
{
	m_TopList.SetExtendedStyle(LVS_EX_FULLROWSELECT |LVS_EX_DOUBLEBUFFER );
	m_TopList.ModifyStyle(0,LVS_SINGLESEL); 
	m_TopList.SetGridLines();
	m_TopList.InsertColumn(0,L"코드",0,50);
	m_TopList.InsertColumn(1,L"종목명",0,80);
	m_TopList.InsertColumn(2,L"현재가",0,100);
	//m_ListBox.InsertColumn(3,L"",0,100);

	m_TopList.InsertColumn(3,L"등락률",0,150);
	m_TopList.InsertColumn(4,L"거래량",0,150);
	m_TopList.InsertColumn(5,L"매수호가",0,100);
	m_TopList.InsertColumn(6,L"거래량대비",0,150);
}

//*******************************************************************/
//! Function Name : OnReceiveTrDataKhopenapictrl
//! Function      : 조회 응답 처리
//! Param         : LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CTopPrice::OnReceiveTrDataKhopenapictrl(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrcode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	m_TopList.SetRedraw(FALSE);
	CString strRQName = sRQName;
	if (strRQName == _T("전일대비등락률상위요청"))		// +		strRQName	"전일대비등락률상위요청 "	ATL::CStringT<char,StrTraitMFC_DLL<char,ATL::ChTraitsCRT<char> > >

	{
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10027) / sizeof(*lstOPT10027);;		// 전체크기 / 원소크기 = 원소개수

		strRQName = _T("전일대비등락률상위");
		arrData.RemoveAll();
		int i, j, nCnt = theApp.m_khOpenApi.GetRepeatCnt(sTrcode, strRQName);
		m_ArrTopdata = new TopData[nCnt];
		m_ArrCount = nCnt;
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				//
				strData = theApp.m_khOpenApi.GetCommData(sTrcode, strRQName, i, lstOPT10027[j].strKey);	strData.Trim();
				//m_grdKwanSim.SetItemFormat(i + 1, lstOPTKWFID[j].nCol, lstOPTKWFID[j].nAlign);
				arrData.Add(strData);
				
				//종목코드 추가
				if(j == 1){
					CString strCode = strData, strIndex;
					strIndex.Format(L"%d", i);
					m_mapJongCode.SetAt(strCode, strIndex);
					m_ArrTopdata[i].strCode = strData;
				}
			}
			if(!arrData.GetAt(1).IsEmpty()){
				int dwCount = m_TopList.GetItemCount();

				int dwitem = m_TopList.InsertItem(dwCount,arrData.GetAt(1),0);

				m_TopList.SetItem(dwitem,1,1,arrData.GetAt(2),0,0,0,0);
				m_TopList.SetItem(dwitem,2,1,arrData.GetAt(3),0,0,0,0);
				m_TopList.SetItem(dwitem,3,1,arrData.GetAt(6),0,0,0,0);

				m_ArrTopdata[i].strRate = arrData.GetAt(6);

				m_TopList.SetItem(dwitem,4,1,arrData.GetAt(9),0,0,0,0);
				m_TopList.SetItem(dwitem,5,1,arrData.GetAt(11),0,0,0,0);

				//m_TopList.SetItemData(dwitem,(DWORD)strCode.GetBuffer());

				if(isOdd(dwitem))
					m_TopList.SetItemBkColor(dwitem, -1, RGB(241,244,248), FALSE);
			}

			//OnUpdateListData(arrData);
		}





		//SetDataJongInfoGrid(arrData);
	}
	m_TopList.SetRedraw();
}
//*******************************************************************/
//! Function Name	: OnReceiveRealDataKhopenapictrl
//! Function			: 실시간 처리
//! Param				: LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData
//! Return				: void
//! Create				: , 2015/05/07
//! Comment			: 
//******************************************************************/
void CTopPrice::OnReceiveRealDataKhopenapictrl(LPCTSTR sJongmokCode, LPCTSTR sRealType, LPCTSTR sRealData)
{
	return;
	CString strIndex, strData;
	if (!m_mapJongCode.Lookup(sJongmokCode, strIndex))
	{
		return;
	}

	CString strCode;



};


//*******************************************************************/
//! Function Name : SetDataKwanSimGrid
//! Function      : 관심 그리드 데이타 설정(관심종목정보 설정)
//! Param         : CStringArray &arrData, CString strRealType/* = ""*/
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CTopPrice::OnUpdateListData(CStringArray &arrData, CString strRealType/* = ""*/)
{
	// 종목코드에 맞는 행 찾기
	CString strData, strTemp;
	strData = arrData.GetAt(1);
	if (!m_mapJongCode.Lookup(strData, strTemp))
	{
		return;
	}

	// 종목명
	int i, nRow = _wtol(strTemp) -1, nCnt = arrData.GetSize();
	if (strRealType == "")
	{
		CString strName = arrData.GetAt(1);
		m_TopList.SetItemText(nRow, lstOPT10027[1].nCol, theApp.ConvDataFormat(lstOPT10027[1].nDataType, strName, lstOPT10027[1].strBeforeData, lstOPT10027[1].strAfterData));
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
		if (lstOPT10027[i].bTextColor)
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
				tempC =  RGB(255,255,255);
			}
			if(lstOPT10027[i].nCol != -1)
				m_TopList.SetItemTextColor(nRow,lstOPT10027[i].nCol,tempC);
			//theApp.SetDataFgColour(&m_grdKwanSim, nRow, lstOPTKWFID[i].nCol, strTemp);
		}
		if (lstOPT10027[i].nDataType == DT_SIGN)
		{
			//theApp.SetSignData(&m_grdKwanSim, nRow, lstOPTKWFID[i].nCol, strData);
		}
		else
		{
			if (strData.IsEmpty())
			{
				continue;
			}
			m_TopList.SetItemText(nRow,lstOPT10027[i].nCol, theApp.ConvDataFormat(lstOPT10027[i].nDataType, strData, lstOPT10027[i].strBeforeData, lstOPT10027[i].strAfterData));
			//m_grdKwanSim.SetItemText(nRow, lstOPTKWFID[i].nCol, theApp.ConvDataFormat(lstOPTKWFID[i].nDataType, strData, lstOPTKWFID[i].strBeforeData, lstOPTKWFID[i].strAfterData));
		}
	}
	//m_grdKwanSim.Invalidate();
}

void CTopPrice::SendSearch(void)
{
	m_TopList.DeleteAllItems();
	CString strRQName = _T("전일대비등락률상위요청");
	CString strTRCode = TR_OPT10027;
	//theApp.m_khOpenApi.SetInputValue("종목코드", "113810");
	//계좌번호 = 전문 조회할 보유계좌번호  //51653280
	//theApp.m_khOpenApi.SetInputValue(L"계좌번호"	,  L"8100875411");
	//theApp.m_khOpenApi.SetInputValue("계좌번호"	,  "5165328010");
	//비밀번호 = 사용안함(공백)
	//시장구분 = 000:전체, 001:코스피, 101:코스닥
	theApp.m_khOpenApi.SetInputValue(L"시장구분"	,  L"000");

	//정렬구분 = 1:상승률, 2:상승폭, 3:하락률, 4:하락폭
	theApp.m_khOpenApi.SetInputValue(L"정렬구분"	,  L"1");

	//거래량조건 = 0000:전체조회, 0010:만주이상, 0050:5만주이상, 0100:10만주이상, 0150:15만주이상, 0200:20만주이상, 0300:30만주이상, 0500:50만주이상, 1000:백만주이상
	theApp.m_khOpenApi.SetInputValue(L"거래량조건"	,  L"0");

	//종목조건 = 0:전체조회, 1:관리종목제외, 4:우선주+관리주제외, 3:우선주제외, 5:증100제외, 6:증100만보기, 7:증40만보기, 8:증30만보기, 9:증20만보기, 11:정리매매종목제외
	theApp.m_khOpenApi.SetInputValue(L"종목조건"	,  L"0");

	//신용조건 = 0:전체조회, 1:신용융자A군, 2:신용융자B군, 3:신용융자C군, 4:신용융자D군, 9:신용융자전체
	theApp.m_khOpenApi.SetInputValue(L"신용조건"	,  L"0");

	//상하한포함 = 0:불 포함, 1:포함
	theApp.m_khOpenApi.SetInputValue(L"상하한포함"	,  L"1");

	//가격조건 = 0:전체조회, 1:1천원미만, 2:1천원~2천원, 3:2천원~5천원, 4:5천원~1만원, 5:1만원이상, 8:1천원이상
	theApp.m_khOpenApi.SetInputValue(L"가격조건"	,  L"0");

	//거래대금조건 = 0:전체조회, 3:3천만원이상, 5:5천만원이상, 10:1억원이상, 30:3억원이상, 50:5억원이상, 100:10억원이상, 300:30억원이상, 500:50억원이상, 1000:100억원이상, 3000:300억원이상, 5000:500억원이상
	theApp.m_khOpenApi.SetInputValue(L"거래대금조건"	,  L"0");


	long lRet = theApp.m_khOpenApi.CommRqData(strRQName, strTRCode, 0, m_strScrNo);
	CString		strErr;
	if (!theApp.IsError(lRet))
	{
		strErr.Format(_T("주식기본정보요청 에러 [%s][%d]"), strTRCode, lRet);
		OutputDebugString(strErr);
	};
}


BOOL CTopPrice::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)   
		return TRUE;
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)   
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CTopPrice::OnRclickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );

		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU1 ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );
	} 
	*pResult = 0;
}


void CTopPrice::OnPopmenuAdd()
{
	// TODO: Add your command handler code here
	CString str;
	for(int i=0; i<m_TopList.GetItemCount(); i++)
	{
		if( m_TopList.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			str.Format(_T("选中了第%d行"), i);
			CString strText = m_TopList.GetItemText(i,0);
			CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
			pMain->m_buyList.OnBnClickedButtonAdd(strText);
			pMain->m_TabControl.SetCurSel(0);

			CRect r;
			pMain->m_TabControl.GetClientRect (&r);
			pMain->m_buyList.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28 ,SWP_SHOWWINDOW);
			pMain->m_curPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
			pMain->m_topPrice.SetWindowPos (NULL,3,22,r.right-8,r.bottom-28,SWP_HIDEWINDOW ); 
			//AfxMessageBox(strText);
		}
	}
}


void CTopPrice::OnBnClickedButtonPrev()
{
	// TODO: Add your control notification handler code here
	//m_DateCtrl
	//BackupToSqlite();
}


void CTopPrice::OnBnClickedButtonNext()
{
	// TODO: Add your control notification handler code here

}
int print_result(void* data, int n_columns, char** column_values, char** column_names)
{
	//if (!column_names_printed) {
	//print_row(n_columns, column_names);
	//column_names_printed = 1;
	//}

	//print_row(n_columns, column_values);

	return 0;
}
#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */
unsigned hash_str(const char* s)
{
	unsigned h = FIRSTH;
	while (*s) {
		h = (h * A) ^ (s[0] * B);
		s++;
	}
	return h; // or return h % C;
}
const char* getHash(TCHAR* param1,TCHAR* param2)
{
	USES_CONVERSION;
	char* chart_curdate = W2A(param1);
	char* char_strcode =  W2A(param2);
	char szKey[MAX_PATH] = {0};
	strcpy(szKey,chart_curdate);
	strcat(szKey,char_strcode);
	string szHash = sha256(szKey);
	char * ret = new char[szHash.length()];
	strcpy(ret,szHash.c_str());
	return ret;
}


void CTopPrice::BackupToSqlite(void)
{
	CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
	pMain->TraceOutputA("save to db....");
	sqlite3* db = NULL;
	char* errMsg = NULL;

	char** dbResult;
	int rows;
	int columns;
	int n = 0;
	//CString strFileIniPath = QueryExePath() + _T("data.db");

	int sqlResult = sqlite3_open(m_szPath.c_str(), &db);
	if (sqlResult == SQLITE_OK)
	{
		
		__try{
			
			char * szSql = new char[MAX_PATH];

			for (int i =0 ;i < m_ArrCount; i++)
			{

				const char* zsKey = getHash(m_curDate.GetBuffer(),m_ArrTopdata[i].strCode.GetBuffer());
				sprintf_s(szSql, MAX_PATH, "INSERT INTO topstock (id,shakey,t_time,t_code,p_rate) VALUES (NULL,'%s','%ws','%ws','%ws') ",zsKey,m_curDate,m_ArrTopdata[i].strCode,m_ArrTopdata[i].strRate);
				/*_TraceA(szSql);*/
				//delete zsKey;
				sqlResult = sqlite3_exec(db, szSql, print_result, NULL, &errMsg);
				//sqlResult = sqlite3_exec(db, "SELECT * FROM sysid INNER JOIN softpaq ON sysid.softpaqnumber = softpaq.softpaqnumber INNER JOIN os ON sysid.softpaqnumber = os.softpaqnumber WHERE sysid.sysid = '225A' AND softpaq.type = 'Application' group by softpaq.softpaqnumber", print_result, NULL, &errMsg);
				if (sqlResult == SQLITE_OK){
					//MessageBox(NULL, L"alskdjfas", L"lsakdfj", MB_OK);
					//_TraceA("SQLITE_OK Devices.db");
					//SortSqlData();
					pMain->TraceOutputA("save ok....");
				}
				else{
					//_TraceA(errMsg);
					CshootStockDlg *pMain=(CshootStockDlg *)AfxGetApp()->GetMainWnd();
					pMain->TraceOutputA(errMsg);
				}
			}


		}
		__except (EXCEPTION_EXECUTE_HANDLER){
			//_TraceA("sqlite failed");
		}

	}

	sqlite3_close(db);
	pMain->TraceOutputA("save compolete");
}


void CTopPrice::OnBnClickedButtonSave()
{
	// TODO: Add your control notification handler code here
	USES_CONVERSION;
	CString strFileIniPath = QueryExePath() + _T("data.db");
	
	m_szPath = W2A(strFileIniPath);
	CString t = COleDateTime::GetCurrentTime().Format(L"%Y%m%d");
	m_curDate = t;
	BackupToSqlite();
}



