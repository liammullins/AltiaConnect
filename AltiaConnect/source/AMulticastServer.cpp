#include "AMulticastServer.h"


AMulticastServer::AMulticastServer()
{
}

AMulticastServer::~AMulticastServer()
{
	upnp.Stop();
}
struct Options {
	const char* friendly_name;
} Options;

NPT_Result AMulticastServer::OnAction(PLT_ActionReference& action, const PLT_HttpRequestContext& context)
{
	ALTIA_LOG_INFO("WOOOOOOT");
	return 1;
}
/*
AMediaRenderer::AMediaRenderer()
{

}
*/
void AMulticastServer::initMCServer(std::string serverName, std::string guid)
{
	/* Define device */ 
	PLT_DeviceHostReference device(
		new PLT_MediaRenderer(Options.friendly_name ? Options.friendly_name : "Altia Connect",
		false,
		"e6572b54-f3c7-2d91-2fb5-b757f2537e21"));
	/* Add Device*/
	upnp.AddDevice(device);
	/* Start Server */
	upnp.Start();
	/* UPnP server isRunning check */
	if (upnp.IsRunning())
	{
		ALTIA_LOG_INFO("Server is Running!");
	}

}
