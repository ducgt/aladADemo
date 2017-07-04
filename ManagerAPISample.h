//+------------------------------------------------------------------+
//|															MT4·çÏÕ¹Ü¿Ø |
//|									 Copyright 2001-2017, Li Jiangwei |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
#pragma once
#ifndef __AFXWIN_H__
   #error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"      // main symbols
//---
#include "MT4ManagerAPI.h"
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
extern CManagerInterface *ExtManager;
extern CManagerInterface *ExtDealer;
extern CManagerInterface *ExtManagerPump;

extern volatile UINT      ExtPumpingMsg;
extern volatile UINT      ExtDealingMsg;
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CManagerAPISampleApp : public CWinApp
  {
private:
   CManagerFactory   m_factory;

public:
                     CManagerAPISampleApp();

   //{{AFX_VIRTUAL(CManagerAPISampleApp)
public:
   virtual BOOL      InitInstance();
   virtual int       ExitInstance();
   //}}AFX_VIRTUAL

   //{{AFX_MSG(CManagerAPISampleApp)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
  };
//{{AFX_INSERT_LOCATION}}
//+------------------------------------------------------------------+
