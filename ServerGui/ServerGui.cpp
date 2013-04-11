
// ServerGui.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ServerGui.h"
#include "ServerGuiDlg.h"

#include "D:\\Work\\Proiect\\zeromq-2.1.6\\zeromq-2.1.6\\include\\zmq.hpp"
#include "D:\\Work\\Proiect\\zeromq-2.1.6\\zeromq-2.1.6\\include\\zmq.h"
#pragma comment( lib, "D:\\Work\\Proiect\\zeromq-2.1.6\\zeromq-2.1.6\\builds\\msvc\\Release\\libzmq.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerGuiApp

BEGIN_MESSAGE_MAP(CServerGuiApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CServerGuiApp construction

CServerGuiApp::CServerGuiApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CServerGuiApp object

CServerGuiApp theApp;


// CServerGuiApp initialization

BOOL CServerGuiApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CServerGuiDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

DWORD WINAPI ThreadServer(LPVOID lparam)
{
	  void *context = zmq_init (1);

    //  Socket to talk to clients
    void *responder = zmq_socket (context, ZMQ_REP);
    zmq_bind (responder, "tcp://*:5555");


	FILE *fp;
	int numar;
	structsend checkUser;
	structsend receivedData;
	
    while (1) {
        //  Wait for next request from client
        zmq_msg_t request;
        zmq_msg_init (&request);
        zmq_recv (responder, &request, 0);
		
       // strcpy(primit,(char *)&request);
		memcpy(&receivedData,&request.vsm_data,30);
		
		//verific daca a fost request de login
		if (strcmp(receivedData.requesttype,"0") == 0)
		{
			fp = fopen("D:\\accounts.dat","ab+");
	//	printf ("Received user %s \n", receivedData.utilizator);
    //  printf ("Received pass %s \n", receivedData.continut);

		numar = 0;
		while (!(feof(fp)))
		{
			fread(&checkUser,sizeof(checkUser),1,fp);
			if (((strcmp(receivedData.continut,checkUser.continut) == 0) && (strcmp(receivedData.utilizator,checkUser.utilizator)) == 0))
			{
			
				numar=1;
			//	printf("E in baza \n");
				
				break;
			}
		}
		rewind(fp);
	    fclose(fp);
		zmq_msg_close (&request);

        //  Do some 'work'
     

        //  Send reply back to client
		zmq_msg_t reply;
		zmq_msg_init_size (&reply, 180);

		structsend sendupdates[6];
		
		if (numar == 1)
		{
		FILE *fpu;
		fpu = fopen("D:\\updates.dat","ab+");
		for (int i=0;i<6;i++)
		{
		fread(&sendupdates[i],sizeof(structsend),1,fpu);
		strcpy(sendupdates[i].requesttype,"1");
		}
		memcpy (zmq_msg_data (&reply),&sendupdates, 180);
		fclose(fpu);
		}
		else memcpy (zmq_msg_data (&reply), "0", 2);   
		
		zmq_send (responder, &reply, 0);
		zmq_msg_close (&reply);
		}

		else if(strcmp(receivedData.requesttype,"3") == 0)
				{
				/*	fp = fopen("D:\\updates.dat","rb+");
					printf ("Received user %s \n", receivedData.utilizator);
					printf ("Received message %s \n", receivedData.continut);
					rewind(fp);
					fwrite(&receivedData,sizeof(structsend),1,fp);
					fclose(fp);
					zmq_msg_close (&request);
					zmq_msg_t reply;
					zmq_msg_init_size (&reply, 1);
					zmq_send (responder, &reply, 0);
					zmq_msg_close (&reply);
				*/
					FILE *fp=fopen("D:\\updates.dat","rb");
					int len;
					void *data=NULL;
					if(fp){
						fseek(fp,0,SEEK_END);
						len=ftell(fp);
						fseek(fp,0,SEEK_SET);
						data=malloc(len);
						fread(data,1,len,fp);
						fp=freopen("D:\\updates.dat","wb",fp);
					}else fp=fopen("D:\\updates.dat","wb");
				//	printf ("Received user %s \n", receivedData.utilizator);
				//	printf ("Received message %s \n", receivedData.continut);
					rewind(fp);
					fwrite(&receivedData,sizeof(structsend),1,fp);
					if(data){
						fwrite(data,1,len,fp);
						free(data);
					}
					fclose(fp);
					zmq_msg_close (&request);
					zmq_msg_t reply;
					zmq_msg_init_size (&reply, 1);
					zmq_send (responder, &reply, 0);
					zmq_msg_close (&reply);
				

				}
			else if(strcmp(receivedData.requesttype,"4") == 0)
			{
				FILE *fpx;
				structsend sendupdates[6];
				zmq_msg_close (&request);
				zmq_msg_t reply;
				zmq_msg_init_size (&reply, 180);


				fpx = fopen("D:\\updates.dat","rb");
				//fseek(fpu,sizeof(structsend),SEEK_SET);
				rewind(fpx);
				for (int i=0;i<6;i++)
				{
					fread(&sendupdates[i],sizeof(structsend),1,fpx);
					strcpy(sendupdates[i].requesttype,"2");
				}
				memcpy (zmq_msg_data (&reply),&sendupdates, 180);
				zmq_send (responder, &reply, 0);
				zmq_msg_close (&reply);
				fclose(fpx);

		
		    }
    }
    //  We never get here but if we did, this would be how we end
    zmq_close (responder);
    zmq_term (context);
    return 0;
 

}