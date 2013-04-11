
// ServerGui.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
struct  structsend
{
	char requesttype[2];
	char utilizator[7];  
	char  continut[21];
};

// CServerGuiApp:
// See ServerGui.cpp for the implementation of this class
//
//bool running = true;

class CServerGuiApp : public CWinApp
{
public:
	CServerGuiApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CServerGuiApp theApp;
DWORD WINAPI ThreadServer(LPVOID lparam);