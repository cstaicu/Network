#pragma once

#ifdef _WIN32_WCE
#error "CDHtmlDialog is not supported for Windows CE."
#endif 

// CServerCfDlg dialog

class CServerCfDlg : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CServerCfDlg)
	char *m_szServerIP;
public:
	CServerCfDlg(CWnd* pParent = NULL);   // standard constructor
	CServerCfDlg(char *a_szServerIP, CWnd* pParent = NULL);  
	virtual ~CServerCfDlg();
// Overrides
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	HRESULT OnButtonPrev(IHTMLElement *pElement);

// Dialog Data
	enum { IDD = IDD_SERVERCFDLG, IDH = IDR_HTML_SERVERCFDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
