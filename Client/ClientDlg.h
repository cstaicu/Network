
// ClientDlg.h : header file
//

#pragma once


// CClientDlg dialog
class CClientDlg : public CDHtmlDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CLIENT_DIALOG, IDH = IDR_HTML_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HRESULT OnButtonLogin(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);
	HRESULT OnButtonGoogle(IHTMLElement *pElement);
	HRESULT OnButtonPost(IHTMLElement *pElement);
	HRESULT OnButtonReload(IHTMLElement *pElement);
	const char* OnButtonServer(const char* ServerIP);
	void ShowUserUpdates();
	void SendDataToServer();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
