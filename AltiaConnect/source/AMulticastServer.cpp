#include "AMulticastServer.h"
#include "AMediaRenderer.h"

AMediaRenderer                 *   altiaMediaRenderer;
extern AMulticastServer        *   multiCastServer;
PLT_DeviceHostReference            altiaMediaRendererDevice;

AMulticastServer::AMulticastServer()
{

}

AMulticastServer::~AMulticastServer()
{
	altiaMediaRenderer->SetByeByeFirst(true);
	delete multiCastServer;
	upnp.Stop();
}

void AMulticastServer::initMCServer(std::string serverName, std::string guid)
{

	altiaMediaRenderer = new AMediaRenderer(serverName.c_str(), false, guid.c_str());
	/* Get copy of returned DeviceHostRef */
	altiaMediaRendererDevice = PLT_DeviceHostReference(altiaMediaRenderer);
	/* Add Device*/
	upnp.AddDevice(altiaMediaRendererDevice);
	/* Start Server */
	upnp.Start();
	/* UPnP server isRunning check */
	if (upnp.IsRunning())
	{
		//ALTIA_LOG_INFO("Server is Running!");
	}

}
