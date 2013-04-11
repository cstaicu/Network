
// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "ServerCfDlg.h"
#include "afxdialogex.h"
#include "D:\\Work\\Proiect\\zeromq-2.1.6\\zeromq-2.1.6\\include\\zmq.hpp"
#include "D:\\Work\\Proiect\\zeromq-2.1.6\\zeromq-2.1.6\\include\\zmq.h"
#pragma comment( lib, "D:\\Work\\Proiect\\zeromq-2.1.6\\zeromq-2.1.6\\builds\\msvc\\Release\\libzmq.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientDlg dialog

BEGIN_DHTML_EVENT_MAP(CClientDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonLogin"), OnButtonLogin)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
	DHTML_EVENT_ONCLICK(_T("ButtonPost"), OnButtonPost)
	DHTML_EVENT_ONCLICK(_T("ButtonReload"), OnButtonReload)
	DHTML_EVENT_ONCLICK(_T("ButtonServer"), OnButtonServer)
END_DHTML_EVENT_MAP()


struct  structsend
{
	char requesttype[2];
	char utilizator[7];  
	char  continut[21];
};

structsend recivedupdates[2];
structsend EnteredUser;
char ServerIPAdd[30] = "tcp://localhost:5555";


CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(CClientDlg::IDD, CClientDlg::IDH, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDHtmlDialog)
END_MESSAGE_MAP()


// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	ShowWindow(SW_NORMAL);
	CenterWindow();
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}



// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CClientDlg::OnButtonLogin(IHTMLElement* /*pElement*/)
{
//	OnOK();

	variant_t userValue, userPass;
		
	IHTMLElement *element = NULL;
	GetElement(L"user", &element);
    element->getAttribute(L"value",0,&userValue);
	GetElement(L"pass", &element);
	element->getAttribute(L"value",0,&userPass);
	WideCharToMultiByte(CP_ACP,0,userValue.bstrVal,-1,EnteredUser.utilizator,7,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,userPass.bstrVal,-1,EnteredUser.continut,21,NULL,NULL);
	zmq::context_t context (1);
	zmq::socket_t socket (context, ZMQ_REQ);

	socket.connect (ServerIPAdd);
	zmq::message_t request(30);
	strcpy(EnteredUser.requesttype,"0");
	memcpy ((char *) request.data (), &EnteredUser, 30);
	socket.send (request);
		//  Get the reply.
	zmq::message_t reply(180);

	socket.recv (&reply);
	
	memcpy(&recivedupdates,reply.data(),180);
	if(strcmp(recivedupdates[0].requesttype,"1") == 0)
	{
	MessageBoxW(L"Hello, you are signed-in in the app",L"Client",NULL);
	GetElement(L"login",&element);
	element->put_className(L"hidden");
	this->ShowUserUpdates();
	}
	else MessageBoxW(L"Wrong Password or Username... Please retry",L"Client",NULL);


	return S_OK;

	
	
/*	if (((StrCmpA(chUPass,checkUser.Parola) == 0) && (StrCmpA(chUser,checkUser.Utilizator)) == 0))
	{
	//	MessageBoxW(L"Buna Catalin esti logat",L"Nice",NULL);
		GetElement(L"login",&element);
//		element->setAttribute(L"style",(variant_t)("display:none;"),0);
		element->put_className(L"hidden");
		this->ShowUserUpdates();		
	}
	else
	*/

}

HRESULT CClientDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}

void CClientDlg::ShowUserUpdates()
{
	IHTMLElement *element;
	GetElement(L"update",&element);
	element->put_className(L"visible");
//	element->removeAttribute(L"class");
//	LPCTSTR lpsUrl;
	variant_t m_vtTextin, m_vtPublisher;
	char m_sAddedBy[40] = " Published by "; 

	strcat(m_sAddedBy, recivedupdates[0].utilizator);
	m_vtTextin.SetString(recivedupdates[0].continut);
	m_vtPublisher.SetString(m_sAddedBy);

	GetElement(L"update1",&element);
	element->put_innerText(m_vtTextin.bstrVal);
	GetElement(L"added1",&element);
	element->put_innerText(m_vtPublisher.bstrVal);


	strcpy(m_sAddedBy," Published by ");
	strcat(m_sAddedBy, recivedupdates[1].utilizator);
	m_vtTextin.SetString(recivedupdates[1].continut);
	m_vtPublisher.SetString(m_sAddedBy);

	GetElement(L"update2",&element);
	element->put_innerText(m_vtTextin.bstrVal);
	GetElement(L"added2",&element);
	element->put_innerText(m_vtPublisher.bstrVal);

	strcpy(m_sAddedBy," Published by ");
	strcat(m_sAddedBy, recivedupdates[2].utilizator);
	m_vtTextin.SetString(recivedupdates[2].continut);
	m_vtPublisher.SetString(m_sAddedBy);

	GetElement(L"update3",&element);
	element->put_innerText(m_vtTextin.bstrVal);
	GetElement(L"added3",&element);
	element->put_innerText(m_vtPublisher.bstrVal);


	strcpy(m_sAddedBy," Published by ");
	strcat(m_sAddedBy, recivedupdates[3].utilizator);
	m_vtTextin.SetString(recivedupdates[3].continut);
	m_vtPublisher.SetString(m_sAddedBy);

	GetElement(L"update4",&element);
	element->put_innerText(m_vtTextin.bstrVal);
	GetElement(L"added4",&element);
	element->put_innerText(m_vtPublisher.bstrVal);

	strcpy(m_sAddedBy," Published by ");
	strcat(m_sAddedBy, recivedupdates[4].utilizator);
	m_vtTextin.SetString(recivedupdates[4].continut);
	m_vtPublisher.SetString(m_sAddedBy);

	GetElement(L"update5",&element);
	element->put_innerText(m_vtTextin.bstrVal);
	GetElement(L"added5",&element);
	element->put_innerText(m_vtPublisher.bstrVal);


	strcpy(m_sAddedBy," Published by ");
	strcat(m_sAddedBy, recivedupdates[5].utilizator);
	m_vtTextin.SetString(recivedupdates[5].continut);
	m_vtPublisher.SetString(m_sAddedBy);

	GetElement(L"update6",&element);
	element->put_innerText(m_vtTextin.bstrVal);
	GetElement(L"added6",&element);
	element->put_innerText(m_vtPublisher.bstrVal);

	return;

}

HRESULT CClientDlg::OnButtonPost(IHTMLElement *pElement)
{
  IHTMLElement *Element;
  variant_t PostedMessage;
  structsend DataToSend;
  //VARIANT_BOOL *pfSuccess;
  GetElement(L"newpost",&Element);
  
  Element->getAttribute(L"value",0,&PostedMessage);
  strcpy(DataToSend.continut,"");
  WideCharToMultiByte(CP_ACP,0,PostedMessage.bstrVal,-1,DataToSend.continut,21,NULL,NULL);
  if(!(strcmp(DataToSend.continut,"") == 0))	
  {
	  strcpy(DataToSend.requesttype,"3");
	  strcpy(DataToSend.utilizator,EnteredUser.utilizator);
	 
	  zmq::context_t context (1);
	  zmq::socket_t socket (context, ZMQ_REQ);
	   socket.connect (ServerIPAdd);
	  zmq::message_t request(30);
	  memcpy ((char *) request.data (), &DataToSend, 30);
	  socket.send (request);
	  GetElement(L"newpost",&Element);
	  Element->put_innerText(L"");
	  //  Get the reply.
	  zmq::message_t reply(60);
	  socket.recv (&reply);
  }

  return S_OK;
}

HRESULT CClientDlg::OnButtonReload(IHTMLElement *pElement) 
{
	structsend IdListToReload;
	strcpy(IdListToReload.requesttype,"4");
	strcpy(IdListToReload.utilizator,EnteredUser.utilizator);
	//nu ma intereseaza continut in cazul asta
	strcpy(IdListToReload.continut,"");
	zmq::context_t context (1);
	zmq::socket_t socket(context, ZMQ_REQ);
	socket.connect (ServerIPAdd);
	zmq::message_t request(30);
	memcpy((char *) request.data (), &IdListToReload, 30);
	socket.send(request);
	zmq::message_t reply(180);
	socket.recv (&reply);
	memcpy(&recivedupdates,reply.data(),180);
	ShowUserUpdates();
	return S_OK;
}

const char* CClientDlg::OnButtonServer(const char* ServerIP)
{
	CServerCfDlg dlg(ServerIPAdd);
	dlg.DoModal();	
	return S_OK;
}
	void CClientDlg::SendDataToServer()
	{
		//  One I/O thread in the thread pool will do.
		zmq::context_t context (1);
		zmq::socket_t socket (context, ZMQ_REQ);
		socket.connect ("tcp://localhost:5555");

		//  Do 10 requests, waiting each time for a response
		for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
			zmq::message_t request (12);
			memcpy ((void *) request.data (), "Avion 1234", 12);
			socket.send (request);
			//  Get the reply.
			zmq::message_t reply;
			socket.recv (&reply);

		}
	}

	/*	BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
		{
			if(pMsg->message==WM_KEYDOWN || pMsg->message==WM_KEYUP)
			{
				if( pMsg->wParam==VK_ESCAPE || pMsg->wParam==VK_RETURN)
				{
					pMsg->wParam=NULL;
					return FALSE;
				}
	      	}
			else return TRUE;
		
		return CDHtmlDialog::PreTranslateMessage(pMsg);
		}
	*/
	

