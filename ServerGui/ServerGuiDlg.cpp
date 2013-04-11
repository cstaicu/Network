
// ServerGuiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ServerGui.h"
#include "ServerGuiDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hThread[9];
variant_t m_vtnumart;
// CServerGuiDlg dialog

BEGIN_DHTML_EVENT_MAP(CServerGuiDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
	DHTML_EVENT_ONCLICK(_T("ButtonCreate"), OnButtonCreateUser)
END_DHTML_EVENT_MAP()



CServerGuiDlg::CServerGuiDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CServerGuiDlg::IDD, CServerGuiDlg::IDH, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerGuiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerGuiDlg, CDHtmlDialog)
END_MESSAGE_MAP()


// CServerGuiDlg message handlers

BOOL CServerGuiDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerGuiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServerGuiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CServerGuiDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
//	OnOK();
	IHTMLElement *element;
	
	GetElement(L"NrThreads",&element);
	element->getAttribute(L"value",0,&m_vtnumart);
	
	int i=1;

	for(int j = 0;j<_wtoi(m_vtnumart.bstrVal);j++)
	hThread[j] = CreateThread(NULL,0,ThreadServer,(LPVOID)i,0,NULL);
//	WaitForSingleObject(hThread,INFINITE);
	GetElement(L"serverstatus",&element);
	element->put_innerText(L"Server is up & running");
	return S_OK;
}

HRESULT CServerGuiDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
//	OnCancel();
//	running = false;
	for(int j = 0;j<_wtoi(m_vtnumart.bstrVal);j++)
	{
	TerminateThread(hThread[j],0);
	CloseHandle(hThread[j]);
	}
	IHTMLElement *element;
	GetElement(L"serverstatus",&element);
	element->put_innerText(L"Server is stopped");
	return S_OK;
}

HRESULT CServerGuiDlg::OnButtonCreateUser(IHTMLElement *pElement)
{
	variant_t userValue, userPass;
	structsend EnteredUser;
	IHTMLElement *element = NULL;
	GetElement(L"user", &element);
	element->getAttribute(L"value",0,&userValue);
	GetElement(L"pass", &element);
	element->getAttribute(L"value",0,&userPass);
	WideCharToMultiByte(CP_ACP,0,userValue.bstrVal,-1,EnteredUser.utilizator,7,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,userPass.bstrVal,-1,EnteredUser.continut,21,NULL,NULL);
	FILE *fp;
	fp = fopen("D:\\accounts.dat","ab+");
	strcpy(EnteredUser.requesttype,"1");
	fwrite(&EnteredUser,sizeof(EnteredUser),1,fp);
	fclose(fp);
	return S_OK;
}
