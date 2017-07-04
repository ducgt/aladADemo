//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2012, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#include "stdafx.h"
#include "ManagerAPISample.h"
#include "PageMain.h"
#include "ManagerSheet.h"
#include "dialogs\MailSendDlg.h"
#include "dialogs\NewsSendDlg.h"
#include "dialogs\RequestDlg.h"
#include "dialogs\UserUpdateDlg.h"
#include "dialogs\UserNewDlg.h"
#include "dialogs\UserGroupDlg.h"
#include "dialogs\UserBalanceDlg.h"

#include <string>
#include <thread>

//#include "cstring"

#include "IniFile.h"  


using namespace std;




//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
IMPLEMENT_DYNCREATE(CPageMain, CPropertyPageEx)
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+



// =========================CPageUser   begin======================================================

// 比较函数
int		CPageMain::sort_column = 0;			// 记录点击的列
bool	CPageMain::method;
void CPageMain::OnLvnColumnclickxxx(NMHDR *pNMHDR, LRESULT *pResult)
{

	//char ch1[32];
	//char ch2[32];


	int listcount = m_Groups.GetItemCount();
	int nColumn = m_Groups.GetHeaderCtrl()->GetItemCount();
	CString temp0, temp1, temp2;
	for (int j = 1; j <listcount; j++)
	{
		for (int i = 0; i <listcount - j; i++)
		{
			temp1 = m_Groups.GetItemText(i, 0); //m_list为控件绑定的变量，根据自己的修改
			temp2 = m_Groups.GetItemText(i + 1, 0);
			//int nRe = StrCmpLogicalW(temp1,temp2); //
			int nRe = StrCmpI(temp1, temp2);            //   
			if (method)
			{
				if (nRe < 0)
				{
					for (int n = 0; n <nColumn; n++)
					{
						temp1 = m_Groups.GetItemText(i, n);
						temp2 = m_Groups.GetItemText(i + 1, n);

						const char *ch1 = (LPCTSTR)temp1;
						const char *ch2 = (LPCTSTR)temp2;

						//strncpy(ch1, (LPCTSTR)temp1, sizeof(ch1));
						//strncpy(ch2, (LPCTSTR)temp2, sizeof(ch2));

						m_Groups.SetItemText(i, n, ch2);
						m_Groups.SetItemText(i + 1, n, ch1);
					}
				}
			}
			if (!method)
			{
				if (nRe > 0)
				{
					for (int n = 0; n <nColumn; n++)
					{
						temp1 = m_Groups.GetItemText(i, n);
						temp2 = m_Groups.GetItemText(i + 1, n);

				
						const char *ch1 = (LPCTSTR)temp1;
						const char *ch2 = (LPCTSTR)temp2;
						//strncpy(ch1, (LPCTSTR)temp1, sizeof(ch1));
						//strncpy(ch2, (LPCTSTR)temp2, sizeof(ch2));


						m_Groups.SetItemText(i, n, ch2);
						m_Groups.SetItemText(i + 1, n, ch1);
					}
				}
			}
		}
	}

	/*
	try
	{
		LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		// TODO:在此添加控件通知处理程序代码
		sort_column = pNMLV->iSubItem;//点击的列

		for (int i = 0; i < m_Groups.GetItemCount(); i++)
		{
			m_Groups.SetItemData(i, i);
		}


		//int count = m_Groups.GetItemCount();
		//for (int i = 0; i<count; i++)
		//	m_Groups.SetItemData(i, i); // 每行的比较关键字，此处为列序号（点击的列号），可以设置为其他比较函数的第一二个参数

		m_Groups.SortItems(MyCompareProc, (DWORD_PTR)&m_Groups);//排序第二个参数是比较函数的第三个参数

		method = !method;
		*pResult = 0;
	}catch(double)
	{
	}
	*/
}



void CPageMain::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	for (int i = 0; i < m_Groups.GetItemCount(); ++i)
	{
		if (m_Groups.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			// 第i行被选中
			CString str;
			str.Format("%d", i);
			//AfxMessageBox("您选中第  " + str + "   行");

			m_Edit1.SetWindowText(m_Groups.GetItemText(i, 1));
			m_Edit2.SetWindowText(m_Groups.GetItemText(i, 2));
			m_Edit3.SetWindowText(m_Groups.GetItemText(i, 3));
			m_Edit4.SetWindowText(m_Groups.GetItemText(i, 4));
			m_Edit5.SetWindowText(m_Groups.GetItemText(i, 7));
			m_Edit6.SetWindowText(m_Groups.GetItemText(i, 6));
			//AfxMessageBox("5 列内容是：  " + str + "   行");

			break;
		}	 
	}
	*pResult = 0;
}


bool CPageMain::OnJudgeEdit1()
{
	char char1[32];
	m_Edit1.GetWindowTextA(char1, 32);

	int ans = atoi(char1);

		if (ans == 0)
		{
			AfxMessageBox("账号栏，请填写正确的整数数字！");
			return false;
		}
		else
		{
			i_Login = ans;
			return true;
		}
	
}

bool CPageMain::OnJudgeEdit5()
{
	char char1[32];
	m_Edit5.GetWindowTextA(char1, 32);
	int ans = atoi(char1);
	if (ans == 0 )
	{
		AfxMessageBox("资金限制栏，请填写正确的整数数字");
		return false;
	}
	else
	{
		i_Limit = ans;
		return true;
	}
	
}

bool CPageMain::OnJudgeServer()
{
	return true;
}
bool CPageMain::OnJudgeLogin()
{
	return true;
}
bool CPageMain::OnJudgePassword()
{
	
	return true;
}

void CPageMain::FileIniWriteLimit()
{
	
		CString AccountLimit = "AccountLimit";
		TCHAR szFilePath[MAX_PATH + 1];
		GetModuleFileName(NULL, szFilePath, MAX_PATH);
		(_tcsrchr(szFilePath, _T('\\')))[1] = 0;		//删除文件名，只获得路径
		CString path = szFilePath;
		path += ("appname.ini");

		CFile file;
		CFileFind finder;								//查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
		BOOL ifFind = finder.FindFile(path);
		if (!ifFind)
		{
			file.Open(path, CFile::modeWrite | CFile::modeCreate);
			file.Close();
		}

		{
			CString StrName;
			CString StrLimit;

			StrName.Format("%d", i_Login);
			StrLimit.Format("%d", i_Limit);

			if (WritePrivateProfileString(AccountLimit, StrName, StrLimit, path)  != 0)
			{
				CString message = StrName + _T(" 账号修改资金限制为：")+ StrLimit;
				FileLogWriteNew(message);
			}
		}
		FileIniReadLimit();
	
}

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnResetTemLimit()
{
	for (int n = 0; n<NumOfINI; n++)
	{
		if (InReadINI[n][1] > 0)
		{
			char loginn[32];
			_snprintf(loginn, sizeof(loginn) - 1, "%d", InReadINI[n][0]);
			for (int i = 0; i<m_users_total; i++)
			{
				if (strcmp(loginn, tmp[i][1]) == 0)
				{
					InReadINI[n][2] = i;
					_snprintf(tmp[i][5], sizeof(tmp[i][5]) - 1, "%d", InReadINI[n][1]);
					break;
				}
				if (i == m_users_total - 1)
				{
					//tmp[i][5] = '0';
				}
			}
		}
	}
}

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::FileIniReadLimit()
{
	CString AccountLimit = "AccountLimit";

	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径
	CString path = szFilePath;
	path += ("appname.ini");
	//AfxMessageBox(path);

	CFile file;
	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(path);
	if (!ifFind)
	{
		file.Open(path, CFile::modeWrite | CFile::modeCreate);
		file.Close();
	}
	{
		EnumIniFile(path);
		OnResetTemLimit();
		//OnListReDraw(m_users_total);

		/*
		CString StrName = "10001";
		int age;
		age = ::GetPrivateProfileInt(AccountLimit, StrName, 0, path);

		CString StrLimit;
		StrLimit.Format("%d", age);
		*/
	}
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::EnumIniFile(LPCTSTR pFilePath)
{
	UINT LAccount = 0;
	UINT key = 0;
	NumOfINI = 0;


	// TODO: Add your control notification handler code here  
	TCHAR strAppNameTemp[1024];	//所有AppName的返回值  
	TCHAR strKeyNameTemp[1024];	//对应每个AppName的所有KeyName的返回值  
	TCHAR strReturnTemp[1024];	//返回值  
	DWORD dwKeyNameSize;		//对应每个AppName的所有KeyName的总长度  
	

	for (int n = 0; n<5000; n++)
	{
		InReadINI[n][0] = NULL;
		InReadINI[n][1] = NULL;
	}


								//所有AppName的总长度  
	DWORD dwAppNameSize = GetPrivateProfileString(NULL, NULL, NULL, strAppNameTemp, 1024, pFilePath);
	if (dwAppNameSize>0)
	{
		TCHAR *pAppName = new TCHAR[dwAppNameSize];
		int nAppNameLen = 0;	//每个AppName的长度  
		for (int i = 0; i<dwAppNameSize; i++)
		{
			pAppName[nAppNameLen++] = strAppNameTemp[i];
			if (strAppNameTemp[i] == '\0')
			{
				//OutputDebugString(pAppName);
				//OutputDebugString(_T("/r/n"));
				dwKeyNameSize = GetPrivateProfileString(pAppName, NULL, NULL, strKeyNameTemp, 1024, pFilePath);
				if (dwAppNameSize>0)
				{   
					TCHAR *pKeyName = new TCHAR[dwKeyNameSize];
					int nKeyNameLen = 0;    //每个KeyName的长度  
					for (int j = 0; j<dwKeyNameSize; j++)
					{
						pKeyName[nKeyNameLen++] = strKeyNameTemp[j];
						if (strKeyNameTemp[j] == '\0')
						{
							//OutputDebugString(pKeyName);
							//OutputDebugString(_T("="));
							if (GetPrivateProfileString(pAppName, pKeyName, NULL, strReturnTemp, 1024, pFilePath))
							{
								//OutputDebugString(strReturnTemp);
							}
								

								LAccount = atoi(pKeyName);
								key = atoi(strReturnTemp);
								if (LAccount != 0 && key != 0)
								{
									InReadINI[NumOfINI][0] = LAccount;
									InReadINI[NumOfINI][1] = key;
								}
								/*
								CString StrName;
								CString StrLimit;
								StrName.Format("%s", pKeyName);
								StrLimit.Format("%s", strReturnTemp);
								CString s1 = StrName + _T(" :string ") + StrLimit;

								CString StrName1;
								CString StrLimit1;
								StrName1.Format("%d", InReadINI[Num][0]);
								StrLimit1.Format("%d", InReadINI[Num][1]);
								CString s2 = StrName1 + _T(" : int ") +StrLimit1;


								CString ii;
								ii.Format("%d", Num);
								CString s3 = ii + _T("  ") +s1 + _T("          ") + s2;
							
								AfxMessageBox(s3);

								*/
								



							memset(pKeyName, 0, dwKeyNameSize);
							nKeyNameLen = 0;


							NumOfINI = NumOfINI + 1;
							//OutputDebugString(_T("/r/n"));
						}
					}
					delete[]pKeyName;
				}
				memset(pAppName, 0, dwAppNameSize);
				nAppNameLen = 0;
			}
		}
		delete[]pAppName;
	}
}


//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+




void CPageMain::OpenNew()
{
	int            res = RET_ERROR;
	TradeTransInfo info = { 0 };
	ZeroMemory(&info, sizeof(info));
	//---
	info.type = TT_BR_ORDER_OPEN;      // Transaction type
	info.cmd = OP_BUY_LIMIT;          // Command type
	info.orderby = 1007;                  // Login
	strcpy(info.symbol, "EURUSD");       // Symbol
	info.volume = 1;                   // Volume
	info.price = 0.2900;                // Price
										//---
	if ((res = ExtManager->TradeTransaction(&info)) != RET_OK)
	{
		printf("Order open failed: %d (%s)\n", res, ExtManager->ErrorDescription(res));
		//return(-1);
	}
	else
	{
		printf("Order has been opened\n");
	}
	
}



void CPageMain::OnModifyBili()
{
	
	
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnModifyLimit()
{
	if (OnJudgeEdit1())
	if (OnJudgeEdit5())
	{
		char char1[32];
		m_Edit1.GetWindowTextA(char1, 32);
		for (int i = 0; i < m_NTmp; i++)
		{
			if (strcmp(tmp[i][1], char1) == 0)
			{
				FileIniWriteLimit();
				break;
			}
			if (i == (m_NTmp -1))
			{
				AfxMessageBox("你要修改的账户不存在！");
			}
		}
	}
	//FileIniReadLimit();
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnSelectAccout()
{
	int i = 0;
	if (OnJudgeEdit1())
	{
		m_Edit2.SetWindowText("");
		m_Edit3.SetWindowText("");
		m_Edit4.SetWindowText("");
		m_Edit5.SetWindowText("");
		m_Edit6.SetWindowText("");

		char char1[32];
		m_Edit1.GetWindowTextA(char1, 32);
		for (int i = 0; i < m_NTmp; i++)
		{
			if (strcmp(tmp[i][1], char1) == 0)
			{
				m_Edit1.SetWindowText(m_Groups.GetItemText(i, 1));
				m_Edit2.SetWindowText(m_Groups.GetItemText(i, 2));
				m_Edit3.SetWindowText(m_Groups.GetItemText(i, 3));
				m_Edit4.SetWindowText(m_Groups.GetItemText(i, 4));
				m_Edit5.SetWindowText(m_Groups.GetItemText(i, 7));
				m_Edit6.SetWindowText(m_Groups.GetItemText(i, 6));
				break;
			}
		}
		//AfxMessageBox("您输入的账号不存在！");
	}
}


//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
LRESULT CPageMain::OnPumpingMsg(WPARAM wParam, LPARAM)
{
	if (wParam == PUMP_UPDATE_USERS) OnUsersGet();
	if (wParam == PUMP_UPDATE_BIDASK) OnTickGet();
	if (wParam == PUMP_UPDATE_TRADES ) OnPumpTradesUpdate();
	return(0);
}

void CPageMain::OnPumpTradesUpdate()
{
	
}

/*
void CPageMain::OnSetListDataByMarginCall(int total)
{
	m_Groups.DeleteAllItems();
	for (int i = 0; i < total; i++)
	{
		//CString tmp = "";
		const int N = total + 1;
		char tmp[1000][7][64];

		//tmp.Format("%d", i);
		_snprintf(tmp[i][0], sizeof(tmp[i][0]) - 1, "1 : %d", i);
		m_Groups.InsertItem(i, tmp[i][0]);

		//tmp.Format("%d", m_users[i].login);
		_snprintf(tmp[i][1], sizeof(tmp[i][1]) - 1, "%d", m_levels[i].login);
		m_Groups.SetItemText(i, 1, tmp[i][1]);
		
		//tmp.Format("%s", m_users[i].name);
		COPY_STR(tmp[i][2], m_levels[i].name);
		m_Groups.SetItemText(i, 2, tmp[i][2]);

		//tmp.Format("%s", m_users[i].group);
		COPY_STR(tmp[i][3], m_levels[i].group);
		m_Groups.SetItemText(i, 3, tmp[i][3]);
		
		if (m_levels[i].leverage>0) _snprintf(tmp[i][4], sizeof(tmp[i][4]) - 1, "1 : %d", m_levels[i].leverage);
		m_Groups.SetItemText(i, 4, tmp[i][4]);

		_snprintf(tmp[i][5], sizeof(tmp[i][5]) - 1, "%.02lf", m_levels[i].equity);
		m_Groups.SetItemText(i, 5, tmp[i][5]);

	}

}
*/
void CPageMain::OnTickGet()
{
	SymbolInfo si[32];
	int        total = 0, pos = -1;
	LVFINDINFO lvfi = { LVFI_STRING };
	CString    sFormat, sPrice;
	CString		ss1;

	while ((total = ExtManagerPump->SymbolInfoUpdated(si, 32))>0)
	{
		for (int i = 0; i<total; i++)
		{
			ss1.Format("%s", si[i].symbol);
			if (ss1.Compare("") == 0)
			{
				break;
			}
			for (int j = 0; j < 256; j++)
			{
				if (ss1.Compare(BidAskSymbol[j][0]) == 0)
				{
					BidAskSymbol[j][0].Format("%s", si[i].symbol);
					sFormat.Format(_T("%%.%dlf"), si[i].digits);
					BidAskSymbol[j][1].Format(sFormat, si[i].bid);
					BidAskSymbol[j][2].Format(sFormat, si[i].ask);

					break;




					//_snprintf(BidAskSymbol[i][1], sizeof(BidAskSymbol[i][1]) - 1, "%.02lf", m_users[i].balance);
					//lvfi.psz = si[i].symbol;
					//if ((pos = m_Symbols.FindItem(&lvfi))<0) continue;
					//COPY_STR(BidAskSymbol[i][0], si[i].symbol);
					//BidAskSymbol[i][1] = sPrice.GetBuffer(sPrice.GetBufferSetLength());
					//	.GetBufferLen());
					//COPY_STR(BidAskSymbol[i][1], sPrice);
					//m_Symbols.SetItemText(pos, 1, sPrice);
					//m_Symbols.SetItemText(pos, 2, sPrice);

				}
				if (BidAskSymbol[j][0].Compare("") == 0)
				{
					BidAskSymbol[j][0].Format("%s", si[i].symbol);
					sFormat.Format(_T("%%.%dlf"), si[i].digits);
					BidAskSymbol[j][1].Format(sFormat, si[i].bid);
					BidAskSymbol[j][2].Format(sFormat, si[i].ask);
					break;
				}
			}
		}
	}
}

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnUsersGet()
{
	if (m_users != NULL)
	{
		ExtManager->MemFree(m_users);
		m_users = NULL;
		m_users_total = 0;
	}
	m_users = ExtManagerPump->UsersGet(&m_users_total);

	OnListTemChangeByUser(m_users_total);
	OnListReDraw(m_users_total);
	/*
	if (m_users_total_pre != m_users_total)
	{
		OnResetTemLimit;
	}
	*/
	m_users_total_pre = m_users_total;
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnListTemChangeByUser(int total)
{
	NumTmpList = 0;
	for (int i = 0; i < total; i++)
	{
		_snprintf(tmp[i][0], sizeof(tmp[i][0]) - 1, "%d", i);
		_snprintf(tmp[i][1], sizeof(tmp[i][1]) - 1, "%d", m_users[i].login);
		 COPY_STR(tmp[i][2], m_users[i].name);
		_snprintf(tmp[i][3], sizeof(tmp[i][3]) - 1, "%.02lf", m_users[i].balance);
		_snprintf(tmp[i][4], sizeof(tmp[i][4]) - 1, "1:%d", m_users[i].leverage);
		_snprintf(tmp[i][5], sizeof(tmp[i][5]) - 1, "%d", 0);
		// COPY_STR(tmp[i][5], m_users[i].group);
		NumTmpList++;
	}
	//刷新资金限制数值
	OnResetTemLimit();
}

void CPageMain::OnThreadForJudgeAndLimit()
{
	while (true)
	{
		if (IsJudgeAndLimitLogin)
		{
			OnJudgeAndGetEquity();
		}
	}
}

void CPageMain::OnJudgeAndGetEquity()
{
	int	login1;
	const int	*lgin;
	int		total = 1;
	int		*totl = &total;
	int		num = 0;
	UserRecord UserR = { 0 };
	UserRecord* UR = &UserR;

	MarginLevel ML = { 0 };
	MarginLevel *ml = &ML;

	//检查限制ini文件的每个值
	for (int n = 0; n < NumOfINI; n++)
	{
		//如果限制值 》 0
		if (InReadINI[n][1] > 1)
		{
			//从标记位置前两个数开始 查找账户
			num = InReadINI[n][2];
			if (num < 2)
			{
				num = 2;
			}
			//对list control 中每个user的 equity 进行检测
			for (int i = num-2; i < m_users_total; i++)
			{
				if (m_users[i].login == InReadINI[n][0])
				{
					//设置listn control里显示的资金限制项
					const int login = m_users[i].login;
					ZeroMemory(&ML, sizeof(ML));
					int a = ExtManager->MarginLevelRequest(login, ml);
					double equity = ml->equity;
					_snprintf(tmp[i][3], sizeof(tmp[i][3]) - 1, "%.02lf", equity);

					if (equity > 0 && equity <= InReadINI[n][1])
					{
						//判断账户是否Enable并禁止账户
						login1 = m_users[i].login;
						lgin = &login1;
						ZeroMemory(&UserR, sizeof(UserR));
						UR = ExtManager->UserRecordsRequest(lgin, totl);

						if (UR->enable_read_only == FALSE)
						{
							//把 OnSetEnableByLogin  提上来==============================   begin        20170609===============
							//当执行禁止账户时，先关闭所有订单
							OnDeleteAllByLogin(m_users[i].login);

							//执行禁止账户操作
							//UserRecord UserR = { 0 };
							//UserRecord* UR = &UserR;
							//ZeroMemory(&UserR, sizeof(UserR));
							//UR = ExtManager->UserRecordsRequest(ln, tl);

							//将 此 login 置为 不可用，并杠杆设置为1 

							CString account;
							account.Format("%d", m_users[i].login);
							CString str;

							UR->enable_read_only = TRUE;
							UR->leverage = 1;

							int err = ExtManager->UserRecordUpdate(UR);
							if (err == RET_OK)
							{
								str = account + _T(" 账户低于资金限制，被禁止！");
								FileLogWriteNew(str);
								break;
							}
							else
							{
								str = account + _T("禁止账户没有成功！");
								FileLogWriteNew(str);
								break;
							}
						}
						break;
					}
				}
			}
		}
	}
}


void CPageMain::OnDeleteAllByLogin(int login)
{
	//得到 LPCSTR的 login
	int ii = login;
	char aa[32];
	_snprintf_s(aa, sizeof(aa) - 1, "%d", ii);
	LPCSTR loginName = aa;

	//得到所有订单信息
	int total = 0;
	TradeRecord tradeR;
	TradeRecord *TR = &tradeR;
	ZeroMemory(TR, sizeof(tradeR));


	TR = ExtManager->AdmTradesRequest(loginName, 1, &total);
	if (TR && total > 0)
	{
		for (int i = 0; i < total; i++)
		{
			//已开单，实行关闭操作
			if (TR[i].cmd == OP_BUY || TR[i].cmd == OP_SELL)
			{
				int order = TR[i].order;
				int vol = TR[i].volume;
				int itype = TR[i].cmd;
				int logi = TR[i].login;
				//关单函数
				if (total == 1)
				{
					CloseOrderManByOrder(order, vol, TR[i].symbol, itype);
				}
				if (CloseOrderManAll(TR[i].symbol, logi, order) == false)
				{
					CloseOrderManByOrder(order, vol, TR[i].symbol, itype);
				}
			}
			else
			{
				//挂单等未开单， 实行删除操作
				const int* Order = &(TR[i].order);
				const int  tl = total;
				if (ExtManager->AdmTradesDelete(Order, tl) == RET_OK)
				{
					CString account;
					account.Format("%d", TR[i].order);
					CString str = account + _T(" 删除成功。");
					FileLogWriteNew(str);
				}
			}
		}
	}
	ExtManager->MemFree(TR);
	TR = NULL;
}
bool CPageMain::CloseOrderManAll(char sym[12], int login, int orde)
{
	//type = TT_BR_ORDER_CLOSE_ALL
	//symbol = symbol name
	//order_by = the login of the client, for whom the transaction is performed

	TradeTransInfo info = {0};

	info.type = TT_BR_ORDER_CLOSE_ALL;
	strcpy(info.symbol, sym);
	info.orderby = login;

	int res = ExtManager->TradeTransaction(&info);
	if (res != RET_OK)
	{
		CString account ;
		account.Format("%d", orde);
		CString abc = account + _T(" 关单未成功！");
		FileLogWriteNew(abc);
		return false;
	}
	else
	{
		CString account ;
		account.Format("%d", orde);
		CString str = account + _T(" 关单成功。");
		FileLogWriteNew(str);
		return true;
	}
}
bool CPageMain::CloseOrderManByOrder(int oder, int voll, char sym[12], int type)
{
	//Close regular Order (assumes login: the account of the user, trades[i] information about the ith user trade)
	TradeTransInfo info = { 0 };

	//if (ticksTotal > 0)
	{

		info.type = TT_BR_ORDER_CLOSE;
		info.order = oder;
		info.volume = voll;
		strcpy(info.symbol, sym);
		
		for (int j = 0; j < 256; j++)
		{
			if (BidAskSymbol[j][0].Compare("") == 0)
			{
				break;
			}
			if (strcmp(sym,BidAskSymbol[j][0]) ==0  )
			{
				if (type = OP_BUY)
				{
					double a = atof(BidAskSymbol[j][1]);
					info.price = a;
					break;
				}
				if (type = OP_SELL)
				{
					double a = atof(BidAskSymbol[j][2]);
					info.price = a;
					break;
				}
			}
		}
		
		int res = ExtManager->TradeTransaction(&info);
		if (res != RET_OK)
		{
			CString account;
			account.Format("%d", info.order);
			CString abc = account +  _T(" 关单未成功！");
			//AfxMessageBox(ExtManager->ErrorDescription(res));
			FileLogWriteNew(abc);
			return false;
		}
		else
		{
			CString account;
			account.Format("%d", info.order);
			CString str = account + _T(" 关单成功。");
			FileLogWriteNew(str);
			return true;
		}

		/*
		TickRequest tr;
		TickInfo *TickR;
		//TickRecord *tickRecord = &TickR;

		int ticksTotal;
		//__time32_t now;
		__time32_t now = ExtManager->ServerTime();

		tr.flags = TICK_FLAG_NORMAL;
		tr.from = now - 10000000;
		tr.to = now;

		LPCSTR             symbol = (LPCSTR)sym;
		//tickRecord = ExtManager->TicksRequest(&tr, &ticksTotal);
		TickR = ExtManagerPump->TickInfoLast(symbol, &ticksTotal);
		*/
		/*
		if (type == OP_BUY)
		{
		info.cmd = OP_SELL;
		info.price = tickRecord[ticksTotal - 1].bid;
		}
		else if (type == OP_SELL)
		{
		info.cmd = OP_BUY;
		info.price = tickRecord[ticksTotal - 1].ask;
		}
		ExtManager->MemFree(TickR);
		*/
	}
}


void CPageMain::OnListReDraw(int nlist)
{
	//m_Groups.LockWindowUpdate();
	m_Groups.SetRedraw(FALSE);
	m_Groups.DeleteAllItems();
	//m_Groups.UnlockWindowUpdate();
	m_Groups.SetItemCount(nlist);

	//for (int i = 0; i < nlist; i++)
	{
		//m_Groups.InsertItem(i, tmp[i][0]);
		//m_Groups.SetItemText(i, 0, _T("1111"));
		//m_Groups.SetItemText(i, 0, tmp[i][0]);
		//m_Groups.SetItemText(i, 1, tmp[i][1]);
		//m_Groups.SetItemText(i, 2, tmp[i][2]);
		//m_Groups.SetItemText(i, 3, tmp[i][3]);
		//m_Groups.SetItemText(i, 4, tmp[i][4]);
		//m_Groups.SetItemText(i, 5, tmp[i][5]);

		//tmp.Format("%d", m_users[i].login);
		//_snprintf(tmp[i][1], sizeof(tmp[i][1]) - 1, "%d", m_users[i].login);
		//tmp.Format("%s", m_users[i].name);
		//COPY_STR(tmp[i][2], m_users[i].name);
		//_snprintf(tmp[i][3], sizeof(tmp[i][3]) - 1, "%.02lf", m_users[i].balance);
		//_snprintf(tmp[i][4], sizeof(tmp[i][4]) - 1, "%.02lf", m_users[i].prevmonthequity);
		//COPY_STR(tmp[i][5], m_users[i].group);
		//if (m_users[i].leverage>0) _snprintf(tmp[i][6], sizeof(tmp[i][6]) - 1, "%d", m_users[i].leverage);
	}
	m_Groups.SetRedraw(TRUE);
}

void CPageMain::OnGetdispinfoUsers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LV_DISPINFO* pDI = (LV_DISPINFO*)pNMHDR;
	if (pResult != NULL) *pResult = 0;
	//---
	//CString tmpp;
	char tmpp[256] = "";
	int  i = pDI->item.iItem;
	if (i<0 || i >= m_users_total) return;
	//---
	if (pDI->item.mask&LVIF_TEXT)
	{
		switch (pDI->item.iSubItem)
		{
			case 0: 
				//tmpp.Format("%s", tmp[i][0]);

				COPY_STR(tmpp, tmp[i][0]);
				//_snprintf(tmpp, sizeof(tmpp) - 1, "%d", 555); 
				break;
			case 1: 

				//tmpp.Format("%s", tmp[i][1]);
				COPY_STR(tmpp, tmp[i][1]);
				//COPY_STR(tmpp, "666");  
				break;
			case 2: 
				//tmpp.Format("%s", tmp[i][2]);
				COPY_STR(tmpp, tmp[i][2]);
				//COPY_STR(tmp, m_users[i].group); 
				break;
			case 3: 
				
				COPY_STR(tmpp, tmp[i][3]);
				//if (m_users[i].leverage>0) _snprintf(tmp, sizeof(tmp) - 1, "1 : %d", m_users[i].leverage); 
				break;
			case 4: 
				
				COPY_STR(tmpp, tmp[i][4]);
				break;
			case 5:
				
				COPY_STR(tmpp, tmp[i][5]);
				break;
			default: 
				break;
		}
		//char a[100];
		
		//strncpy(a, (LPCTSTR)tmpp, sizeof(a));
		pDI->item.pszText = tmpp;
	}

}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnDestroy()
{
	if (m_users != NULL) 
	{ 
		ExtManager->MemFree(m_users); 
		m_users = NULL; 
		m_users_total = 0; 
	}
	if (m_levels != NULL) 
	{ 
		ExtManagerPump->MemFree(m_levels); 
		m_levels = NULL; 
		m_levels_total = 0; 
	}
	//*tmp = NULL;
	KillTimer(1);
	CPropertyPageEx::OnDestroy();
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::FileLogWriteNew(CString ss)
{
	UpdateData(true);          // 获取数据
	UpdateData(false);         // 更新数据
	CString MTTime = GetMT4ServerTime(ExtManager->ServerTime());
	CString str;
	str.Format(ss);
	MTTime += str;
	MTTime += ("\r\n");            // 回车换行
	m_EDIT7.SetSel(0, 0);
	m_EDIT7.ReplaceSel(MTTime);  // 在最后一行添加新的内容
	CString LogFileName = _T("\\log\\") + LogNameByDate;
	FileLogWriteToFile(LogFileName, MTTime);
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::FileLogWriteToFile(CString xdFileName, CString ss)
{
	//按行写入指定的log文件

	CString aa = xdFileName;
	CString bb = ss;

	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径
	CString str_url = szFilePath;
	str_url += (aa);
	//AfxMessageBox(str_url);


	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用  
	BOOL ifFind = finder.FindFile(str_url);
	if (!ifFind)
	{
		CStdioFile file;
		file.Open(str_url, CFile::modeCreate | CFile::modeWrite);
		file.WriteString("-----------begin-----------\r\n");
		file.WriteString(bb);
		file.Close();
	}
	else
	{
		CStdioFile file;
		file.Open(str_url, CFile::modeWrite);
		file.SeekToEnd();
		file.WriteString(bb);
		file.Close();
	}
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CString CPageMain::GetMT4ServerTime(time_t tim)
{
	time_t tm = tim;
	struct tm *local;
	CString stime;
	int nYear, nMonth, nDate, nHour, nMin, nSec;
	local = localtime(&tm);
	nYear = local->tm_year + 1900;
	nMonth = local->tm_mon + 1;
	nDate = local->tm_mday;
	nHour = local->tm_hour;
	nMin = local->tm_min;
	nSec = local->tm_sec;
	CTime ptime(nYear, nMonth, nDate, nHour, nMin, nSec);
	stime = ptime.Format("%Y-%m-%d %H:%M:%S : ");

	//给日志起按日期的文件名
	LogNameByDate = ptime.Format("%Y-%m-%d") + _T(".txt");
	return(stime);
}
// =========================CPageUser   end======================================================











CPageMain::CPageMain() : CPropertyPageEx(CPageMain::IDD)

, m_ModifyBili(0)
{
   //{{AFX_DATA_INIT(CPageMain)
   //}}AFX_DATA_INIT
   m_psp.dwFlags&=~PSP_HASHELP;
  }
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
CPageMain::~CPageMain()
{
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::DoDataExchange(CDataExchange* pDX)
	{
		CPropertyPageEx::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CPageMain)
		DDX_Control(pDX, IDC_GROUPS, m_Groups);
		DDX_Control(pDX, IDC_SERVER, m_Server);
		DDX_Control(pDX, IDC_PASSWORD, m_Password);
		DDX_Control(pDX, IDC_LOGIN, m_Login);
		DDX_Control(pDX, IDC_EDIT7, m_EDIT7);


		DDX_Control(pDX, IDC_EDIT1, m_Edit1);
		DDX_Control(pDX, IDC_EDIT2, m_Edit2);
		DDX_Control(pDX, IDC_EDIT3, m_Edit3);
		DDX_Control(pDX, IDC_EDIT4, m_Edit4);
		DDX_Control(pDX, IDC_EDIT5, m_Edit5);
		DDX_Control(pDX, IDC_EDIT6, m_Edit6);

		DDX_Control(pDX, IDC_LOGINCMD, m_BnLogin);
		DDX_Control(pDX, IDC_DISCONNECT, m_BnLogout);
		DDX_Control(pDX, IDC_SEND_MAIL, m_BnMail);
		DDX_Control(pDX, IDC_SEND_NEWS, m_BnNews);
		DDX_Control(pDX, IDC_PUMPING, m_BnPump);
   
		DDX_Control(pDX, IDC_RIGHTS, m_BnRights);

		DDX_Control(pDX, IDC_BUTTON1, m_BnSelect);
		DDX_Control(pDX, IDC_BUTTON2, m_BnLimit);
		DDX_Control(pDX, IDC_BUTTON3, m_BnBili);

		//}}AFX_DATA_MAP
	}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BEGIN_MESSAGE_MAP(CPageMain, CPropertyPageEx)
	//{{AFX_MSG_MAP(CPageUser)
	//ON_BN_CLICKED(IDC_USERS_GET, OnUsersGet)
	//ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)

	ON_WM_DESTROY()
	//{{AFX_MSG_MAP(CPageMain)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_LOGINCMD, OnLogincmd)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_RIGHTS, OnRights)
	ON_BN_CLICKED(IDC_REQ_GROUPS, OnReqGroups)
	ON_BN_CLICKED(IDC_SEND_MAIL, OnSendMail)
	ON_BN_CLICKED(IDC_SEND_NEWS, OnSendNews)
	ON_BN_CLICKED(IDC_PUMPING, OnPumping)


	ON_BN_CLICKED(IDC_BUTTON3, OnModifyBili)
	ON_BN_CLICKED(IDC_BUTTON1, OnSelectAccout)
	ON_BN_CLICKED(IDC_BUTTON2, OnModifyLimit)


	// =========================CPageUser   begin======================================================
	ON_NOTIFY(LVN_GETDISPINFO, IDC_GROUPS, &CPageMain::OnGetdispinfoUsers)
	
	ON_NOTIFY(NM_DBLCLK, IDC_GROUPS, &CPageMain::OnNMDblclkList1)
	//ON_NOTIFY(LVN_COLUMNCLICK, IDC_GROUPS, &CPageMain::OnLvnColumnclickxxx)
	//ON_NOTIFY(LVN_GETDISPINFO, IDC_GROUPS, OnGetdispinfo)
	ON_WM_TIMER()
	
	// =========================CPageUser   end======================================================
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(ExtPumpingMsg, OnPumpingMsg)
END_MESSAGE_MAP()
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
BOOL CPageMain::OnInitDialog()
{
	   CRect rc;
	   int   cx;

	   CPropertyPageEx::OnInitDialog();

	   m_users = NULL;
	   m_users_total = 0;

	   m_levels = NULL;
	   m_levels_total = 0;

	   /*
	   m_Server.SetWindowText("118.190.173.119:443");
	   m_Login.SetWindowText("5");
	   m_Password.SetWindowText("zhu2000");
	   */
	  
	   m_Server.SetWindowText("103.242.101.168:443");
	   m_Login.SetWindowText("88");
	   m_Password.SetWindowText("FengkonG1234");

	   
	   //按钮初始化相关
	   m_Edit1.EnableWindow(FALSE);
	   m_Edit2.EnableWindow(FALSE);
	   m_Edit3.EnableWindow(FALSE);
	   m_Edit4.EnableWindow(FALSE);
	   m_Edit5.EnableWindow(FALSE);
	   m_Edit6.EnableWindow(FALSE);

	   m_BnSelect.EnableWindow(FALSE);
	   m_BnLimit.EnableWindow(FALSE);
	   m_BnBili.EnableWindow(FALSE);


	   //m_Login.EnableWindow(FALSE);
	   //m_Server.EnableWindow(FALSE);
	   m_BnLogout.EnableWindow(FALSE);
	   m_BnLogin.EnableWindow(TRUE);
	   m_BnNews.EnableWindow(FALSE);
	   m_BnMail.EnableWindow(FALSE);
	   m_BnPump.EnableWindow(FALSE);
	   m_BnRights.EnableWindow(FALSE);



			//List初始化相关----------------------------------
			m_Groups.SetExtendedStyle(m_Groups.GetExtendedStyle() | LVS_EX_DOUBLEBUFFER | LVS_OWNERDATA);

			m_Groups.ModifyStyle(0, LVS_OWNERDATA | LVS_REPORT | LVS_SINGLESEL);

			m_Groups.SetExtendedStyle(LVS_EX_FULLROWSELECT);
			//m_Groups.SetExtendedStyle(LVS_SHOWSELALWAYS);
			m_Groups.GetClientRect(&rc); cx=rc.Width()/6;
			m_Groups.InsertColumn(0,"爆仓线", LVCFMT_LEFT, cx);
			m_Groups.InsertColumn(1,"账号",  LVCFMT_LEFT,cx);
			m_Groups.InsertColumn(2,"姓名",LVCFMT_LEFT,cx);
			m_Groups.InsertColumn(3,"净值",LVCFMT_LEFT,cx);
			m_Groups.InsertColumn(4, "杠杆", LVCFMT_LEFT, cx);
			m_Groups.InsertColumn(5, "资金限制", LVCFMT_LEFT, cx);
			//List初始化相关----------------------------------
   
		   SetTimer(1, 2500, NULL);
		   FileIniReadLimit();
		


		   return(TRUE);
}


//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnTimer(UINT nIDEvent)    //添加定时器响应消息
{
	if (ExtManager->IsConnected() == 0)
	{
		BOOL bEnabled = m_BnLogin.IsWindowEnabled();
		if (bEnabled == FALSE)
		{
			OnLogincmd();
		}
	}

	//IsJudgeAndLimitLogin = true;

	//std::thread t1(&CPageMain::OnJudgeAndGetEquity, this);
	//t1.detach();


	OnJudgeAndGetEquity();
	//OnListReDraw(m_users_total);
}

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnConnect()
{
	char server[128]="";
	m_Server.GetWindowText(server,sizeof(server)-1);
	int res=ExtManager->Connect(server);
	MessageBox(ExtManager->ErrorDescription(res),"Connect");

}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnLogincmd()
{
	int            res = RET_ERROR;
	
	char server[128] = "";
	m_Server.GetWindowText(server, sizeof(server) - 1);
	if ((res = ExtManager->Connect(server)) != RET_OK)
	{
		MessageBox(ExtManager->ErrorDescription(res), "Connect");
		FileLogWriteNew("网络没有连接成功！");
	}
	else
	{
		int  login = 0;
		char pass[16] = "";
		login = GetDlgItemInt(m_Login.GetDlgCtrlID(), NULL, FALSE);
		m_Password.GetWindowText(pass, sizeof(pass) - 1);
		if ((res = ExtManager->Login(login, pass)) != RET_OK)
		{
			MessageBox(ExtManager->ErrorDescription(res), "Login");
			FileLogWriteNew("网络连接成功！ 但登录账户错误!");
		}
		else
		{
			//MessageBox(ExtManager->ErrorDescription(res), "Login");
			m_BnLogin.EnableWindow(FALSE);
			m_BnLogout.EnableWindow(TRUE);
			m_BnRights.EnableWindow(TRUE);
			m_Edit1.EnableWindow(TRUE);
			m_Edit5.EnableWindow(TRUE);

			m_BnSelect.EnableWindow(TRUE);
			m_BnLimit.EnableWindow(TRUE);
			m_BnBili.EnableWindow(TRUE);
			FileLogWriteNew("登录成功！");
		}
	}
	//进入推送模式
	OnPumping();
}
	
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
//#define USE_PUMP_FUNC
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnPumping()
{
	int  login=0,res=RET_ERROR;
	char server[128]="",pass[16]="";

	m_Server.GetWindowText(server,sizeof(server)-1);
	login=GetDlgItemInt(m_Login.GetDlgCtrlID(),NULL,FALSE);
	m_Password.GetWindowText(pass,sizeof(pass)-1);

	if(ExtManagerPump->IsConnected()!=FALSE) return;
	res=ExtManagerPump->Connect(server);
	if(res==RET_OK)
	{
			res=ExtManagerPump->Login(login,pass);
		#ifdef USE_PUMP_FUNC
			if(res==RET_OK) res=ExtManagerPump->PumpingSwitch(CManagerSheet::PumpingFunc,NULL,0,0);
		#else
			if(res==RET_OK) res=ExtManagerPump->PumpingSwitch(NULL,GetParent()->GetSafeHwnd(),ExtPumpingMsg,0);
		#endif
	}
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnDisconnect()
	{
		int res=ExtManager->Disconnect();
		if (ExtManagerPump->IsConnected())
		{
			res = ExtManagerPump->Disconnect();
		}
   
		MessageBox(ExtManager->ErrorDescription(res), "Disconnect");
		m_BnLogin.EnableWindow(TRUE);
		m_BnLogout.EnableWindow(FALSE);
		m_BnRights.EnableWindow(FALSE);
		FileLogWriteNew("登出成功！");
   
	}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnRights()
{
	ConManager man={0};
	CString    str;

	int res=ExtManager->ManagerRights(&man);
	if(res!=RET_OK) { MessageBox(ExtManager->ErrorDescription(res),"ManagerRights"); return; }

	if(man.admin  !=FALSE) str+="admin\n";
	if(man.manager!=FALSE) str+="manager\n";
	if(man.money  !=FALSE) str+="money\n";
	if(man.online !=FALSE) str+="online\n";
	if(man.riskman!=FALSE) str+="riskman\n";
	if(man.broker !=FALSE) str+="broker\n";
	if(man.logs   !=FALSE) str+="logs\n";
	if(man.reports!=FALSE) str+="reports\n";
	if(man.trades !=FALSE) str+="trades\n";
	if(man.news   !=FALSE) str+="news\n";
	if(man.email  !=FALSE) str+="email\n";
	if(man.market_watch!=FALSE) str+="market watch\n";
	if(man.see_trades  !=FALSE) str+="see trades\n";

	MessageBox(str,"ManagerRights");
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnReqGroups()
{
	ConGroup *groups=NULL;
	int       total =0;
	CString   str;

	groups=ExtManager->GroupsRequest(&total);
	if(groups==NULL || total==0) { MessageBox("No groups","GroupsRequest"); return; }

	m_Groups.DeleteAllItems();
	for(int i=0; i<total; i++)
	{
		m_Groups.InsertItem(i,groups[i].group);
		m_Groups.SetItemText(i,1,groups[i].company);
		str.Format("%d%% / %d%%",groups[i].margin_call,groups[i].margin_stopout);
		m_Groups.SetItemText(i,2,str);
	}

	ExtManager->MemFree(groups); 
	groups=NULL;
}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnSendMail()
{
	ConManager man={0};

	if(ExtManager->ManagerRights(&man)!=RET_OK) return;
	if(man.login<=0 || man.email==FALSE)        return;

	CMailSendDlg dlg(&man);
	dlg.DoModal();

}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void CPageMain::OnSendNews()
	{
		ConManager man={0};
		if(ExtManager->ManagerRights(&man)!=RET_OK || man.news==FALSE) return;
		CNewsSendDlg dlg;
		dlg.DoModal();
	}
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
