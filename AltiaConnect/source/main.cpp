#include "global_include.h"
#include "AMulticastServer.h"

AtConnectId connID;
AMulticastServer *multiCastServer;

#define SERVER_NAME "Altia Connect"
#define SERVER_GUID "41714"

void hmiProcess(void)
{
	int event_count, i;
	AltiaCharType * event_name = NULL;
	AltiaEventType event_value;
	/* get our pending events*/
	event_count = altiaPending();
	/* run through our events and dispatch */
	for (i = 0; i < event_count; i++)
	{
		altiaNextEvent((AltiaCharType **)(&event_name), &event_value);
		AtDispatchEvent(connID, event_name, event_value);
	}
}

void on_PhoneClicked(AtConnectId connectId, char *name,
	                 AltiaEventType eventValue, AtPointer data)
{
	if (eventValue == 1)
	{
		/* instantiate new server instance - need to gaurd this operation */
		multiCastServer = new AMulticastServer();
		multiCastServer->initMCServer(SERVER_NAME, SERVER_GUID);
		ALTIA_LOG_INFO("\r\n\r\nStarted Server:\r\n          Server Name: %s \r\n          "
					   "GUID: %s","Altia Connect","41714");
	}
	else
	{
		/* Delete our instance. The destructor takes care of the connection */
		//delete multiCastServer;
		//ALTIA_LOG_INFO("Closed Server:\r\n          Server Name: %s \r\n          GUID: %s", "Altia Connect", "41714");
	}
}


void initMainLogic(void)
{
	/* phone button - start server */
	AtAddCallback(connID, "ms_phone_icon_clicked", (AtCallbackProc)on_PhoneClicked, NULL);
}



void main(void)
{
	connID = AtOpenConnection(NULL, NULL, NULL, NULL);
	altiaCacheOutput(1);

	if (connID == 0)
	{
		/* kick off our initialization */
		initMainLogic();
		while (1)
		{
			hmiProcess();
			Sleep(20); //20ms delay
		}
	}
	else
	{
		printf("issue");
		Sleep(2000);
	}

	delete multiCastServer;
	/* Close connection to GUI.  For DeepScreen this frees resources */
	altiaDisconnect();
	exit(0);
	
}