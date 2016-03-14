#include "global_include.h"
#include "AMediaRenderer.h"

AtConnectId connID;

extern "C" void hmiProcess(void)
{
	int event_count, i;

	AltiaCharType * event_name = NULL;
	AltiaEventType event_value;

	event_count = altiaPending();
	for (i = 0; i < event_count; i++)
	{
		altiaNextEvent((AltiaCharType **)(&event_name), &event_value);
		AtDispatchEvent(connID, event_name, event_value);
	}
}

void initApp()
{

	AMediaRenderer *mediaRenderer = new AMediaRenderer;
	LOG_INFO("Started Server...");

}

void main(void)
{
	connID = AtOpenConnection(NULL, NULL, NULL, NULL);
	altiaCacheOutput(1);

	if (connID == 0)
	{
		/* kick off our initialization */
		initApp();
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