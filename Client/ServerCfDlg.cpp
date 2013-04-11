// ServerCfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ServerCfDlg.h"


// CServerCfDlg dialog

IMPLEMENT_DYNCREATE(CServerCfDlg, CDHtmlDialog)

	CServerCfDlg::CServerCfDlg( CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CServerCfDlg::IDD, CServerCfDlg::IDH, pParent)
{
}

CServerCfDlg::CServerCfDlg(char *a_szServerIP, CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CServerCfDlg::IDD, CServerCfDlg::IDH, pParent)
{
		m_szServerIP = a_szServerIP;
}

CServerCfDlg::~CServerCfDlg()
{
}

void CServerCfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CServerCfDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

HRESULT CServerCfDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	IHTMLElement *Element;
	variant_t m_vtnewvalue;
	GetElement(L"ServerValue",&Element);
	Element->getAttribute(L"value",0,&m_vtnewvalue);
	WideCharToMultiByte(CP_ACP,0,m_vtnewvalue.bstrVal,-1,m_szServerIP,21,NULL,NULL);
	OnOK();
	return S_OK;
}

HRESULT CServerCfDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}


HRESULT CServerCfDlg::OnButtonPrev(IHTMLElement *pElement)
{
	IHTMLElement *Element;
	variant_t m_vtoldvalue;
	m_vtoldvalue.SetString(m_szServerIP);
	GetElement(L"ServerValue",&Element);
	Element->setAttribute(L"value",m_vtoldvalue);
	return S_OK;
}

BEGIN_MESSAGE_MAP(CServerCfDlg, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CServerCfDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOKServ"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancelServ"), OnButtonCancel)
	DHTML_EVENT_ONCLICK(_T("PrevServ"), OnButtonPrev)
END_DHTML_EVENT_MAP()



// CServerCfDlg message handlers

