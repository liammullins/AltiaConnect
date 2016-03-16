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

void AMulticastServer::initMCServer(std::string serverName, std::string guid)
{

	/* Define device */ 
	altiaMediaRendererDevice = PLT_DeviceHostReference(
		new PLT_MediaRenderer(serverName.c_str(),
		false,
		guid.c_str()));
	/* Add Device*/
	upnp.AddDevice(altiaMediaRendererDevice);
	/* Start Server */
	upnp.Start();
	/* UPnP server isRunning check */
	if (upnp.IsRunning())
	{
		ALTIA_LOG_INFO("Server is Running!");
	}
	

}
