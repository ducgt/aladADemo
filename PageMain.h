//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2012, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageMain : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageMain)

   // =========================CPageUser   begin======================================================

  private:
	  UserRecord       *m_users = {0};
	  int               m_users_total;
	  int				m_users_total_pre;

	 
  private:
	  MarginLevel      *m_levels;
	  int               m_levels_total;

	  //--------------------------------------
	  UINT				m_NTmp = 6000;
	  char				tmp[6000][6][24];

	  CString			BidAskSymbol[256][3];


	  UINT				InReadINI[5000][3];
	  UINT				NumOfINI = 0;
	  UINT				NumTmpList = 0;
	  int				i_Limit, i_Login;
 
	  CString			LogNameByDate;

	  //点击列头，排序用全局变量
	  static int		sort_column ; // 记录点击的列
	  static bool		method;

	  bool				IsJudgeAndLimitLogin = false;
	 
   // =========================CPageUser   end======================================================

public:

	CPageMain();
    ~CPageMain();

   //{{AFX_DATA(CPageMain)
   enum { IDD=IDD_MANAGER_MAIN };
   CListCtrl         m_Groups;
   CEdit             m_Server;
   CEdit             m_Password;
   CEdit             m_Login;
   CEdit			 m_EDIT7;

   CEdit			 m_Edit1;
   CEdit			 m_Edit2;
   CEdit			 m_Edit3;
   CEdit			 m_Edit4;
   CEdit			 m_Edit5;
   CEdit			 m_Edit6;

   CButton			 m_BnLogin;
   CButton			 m_BnLogout;
   CButton			 m_BnMail;
   CButton			 m_BnNews;
   CButton			 m_BnRights; 
   CButton			 m_BnPump;

   CButton			 m_BnSelect;
   CButton			 m_BnLimit;
   CButton			 m_BnBili;

   int m_ModifyBili;

   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageMain)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageMain)
   virtual BOOL      OnInitDialog();
   afx_msg void      OnConnect();
   afx_msg void      OnLogincmd();
   afx_msg void      OnDisconnect();
   afx_msg void      OnRights();
   afx_msg void      OnReqGroups();
   afx_msg void      OnSendMail();
   afx_msg void      OnSendNews();
   afx_msg void      OnPumping();
   afx_msg void		OnTickGet();

   

   // =========================CPageUser   begin======================================================
   afx_msg void      OnUsersGet();
   
   afx_msg void		FileIniWriteLimit();
   afx_msg void		FileIniReadLimit();

   afx_msg void		OnListTemChangeByUser(int total);
   afx_msg void		OnListReDraw(int nlist);
   afx_msg void		OnGetdispinfo();
  

   afx_msg	void	EnumIniFile(LPCTSTR pFilePath);

   afx_msg	void	OnTimer(UINT nIDEvent);
  
   afx_msg void      OnGetdispinfoUsers(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void      OnDestroy();
   afx_msg void		OnPumpTradesUpdate();
 

   afx_msg bool		OnJudgeEdit1();
   afx_msg bool		OnJudgeEdit5();
   afx_msg bool		OnJudgeServer();
   afx_msg bool		OnJudgeLogin();
   afx_msg bool		OnJudgePassword();

   afx_msg void		OpenNew();
   afx_msg bool		CloseOrderManByOrder(int oder, int voll, char sym[12], int type);
   afx_msg bool		CloseOrderManAll(char sym[12], int login, int orde);
   afx_msg void		OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
   afx_msg void		CPageMain::OnLvnColumnclickxxx(NMHDR *pNMHDR, LRESULT *pResult);


   // 比较函数
   static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
   {
	  
	   // 从参数中提取所需比较lc的两行数据
	   int row1 = (int)lParam1;
	   int row2 = (int)lParam2;
	   CListCtrl* lc = (CListCtrl*)lParamSort;
	   CString lp1 = lc->GetItemText(row1, sort_column);
	   CString lp2 = lc->GetItemText(row2, sort_column);
	   // 比较，对不同的列，不同比较，注意记录前一次排序方向，下一次要相反排序
	   if (sort_column<2)
	   {
		   // int型比较
		   if (method)
			   return atoi(lp1) - atoi(lp2);
		   else
			   return atoi(lp1) - atoi(lp1);
	   }
	   else
	   {
		   // 文字型比较
		   if (method)
			   return lp1.CompareNoCase(lp2);
		   else
			   return lp2.CompareNoCase(lp1);
	   }
	   return 0;
   }




   void			OnResetTemLimit();
   void			OnJudgeAndGetEquity();
   void			OnThreadForJudgeAndLimit();
   bool			OnSetEnableByLogin(int login);
   void			OnDeleteAllByLogin(int login);

   void			OnModifyBili();

   void			OnModifyLimit();

   void			OnSelectAccout();

   void			FileLogWriteNew(CString ss);

   void			FileLogWriteToFile(CString xdFileName, CString ss);

   CString		GetMT4ServerTime(time_t time);
   
   LRESULT		OnPumpingMsg(WPARAM wParam, LPARAM lParam);
   

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  
};
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+





   

