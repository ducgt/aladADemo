//+------------------------------------------------------------------+
//|                                  MetaTrader 4 Manager API Sample |
//|                   Copyright 2001-2012, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#define MAIL_BODY_MAX_SIZE   (256*1024)               // макс. размер тела письма
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CPageMailbox : public CPropertyPageEx
  {
   DECLARE_DYNCREATE(CPageMailbox)

public:
                     CPageMailbox();
                    ~CPageMailbox();

   //{{AFX_DATA(CPageMailbox)
   enum { IDD=IDD_MANAGER_MAIL };
   CListCtrl         m_Mails;
   //}}AFX_DATA

   //{{AFX_VIRTUAL(CPageMailbox)
protected:
   virtual void      DoDataExchange(CDataExchange* pDX);
   //}}AFX_VIRTUAL

protected:
   //{{AFX_MSG(CPageMailbox)
   virtual BOOL      OnInitDialog();
   void              ReadHtmlBody(LPCSTR html_source);
   //}}AFX_MSG
   afx_msg LRESULT   OnPumpingMsg(WPARAM wParam,LPARAM lParam);
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
