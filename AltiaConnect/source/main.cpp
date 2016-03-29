#include "global_include.h"
#include "AMulticastServer.h"
#include <stdio.h>
#include <memory>

AtConnectId connID;
AMulticastServer *multiCastServer;
extern bool processing;

using namespace cv;

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
	/* on cleek */
	if (eventValue == 1)
	{
		/* kick off the server */
		//mediaRenderer->initMediaRenderer();
		multiCastServer = new AMulticastServer();
		multiCastServer->initMCServer(SERVER_NAME, SERVER_GUID);
		ALTIA_LOG_INFO("\n=====================================================\n"
					   "Started Server:\n          "
					   "Server Name: %s \n          "
					   "GUID: %s", SERVER_NAME, SERVER_GUID);
		ALTIA_LOG_INFO(DEBUG_CONSOLE_VISIBLE_LINE);
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

	/* Close connection to GUI.  For DeepScreen this frees resources */
	altiaDisconnect();
	exit(0);
	
}