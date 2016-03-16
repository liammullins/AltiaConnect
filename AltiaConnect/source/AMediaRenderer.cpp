#include "AMediaRenderer.h"
#include "AMulticastServer.h"

/*----------------------------------------------------------------------
|   globals
+---------------------------------------------------------------------*/
AMulticastServer *multiCastServer;

AMediaRenderer::AMediaRenderer()
{

}
void AMediaRenderer::initMediaRenderer()
{
	multiCastServer = new AMulticastServer();
	multiCastServer->initMCServer(SERVER_NAME, SERVER_GUID);
	ALTIA_LOG_INFO("\r\n\r\nStarted Server:\r\n          Server Name: %s \r\n          "
		"GUID: %s", SERVER_NAME, SERVER_GUID);
}

AMediaRenderer::~AMediaRenderer()
{
	delete multiCastServer;
}
/*
NPT_Result AMediaRenderer::OnAction(PLT_ActionReference& action, const PLT_HttpRequestContext& context)
{
	ALTIA_LOG_INFO("Action Received: %s",action);
	return 1;
}*/
