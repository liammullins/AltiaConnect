#include "AMulticastServer.h"
#include "AMediaRenderer.h"

AMediaRenderer                 *   altiaMediaRenderer;
extern AMediaRendererDelegate         *   altiaMediaDelegate;
extern AMulticastServer        *   multiCastServer;
PLT_DeviceHostReference            altiaMediaRendererDevice;

AMulticastServer::AMulticastServer()
{

}

AMulticastServer::~AMulticastServer()
{
	delete multiCastServer;
	upnp.Stop();
}

//NPT_CHECK(PLT_MediaRenderer::SetupServices());

void AMulticastServer::initMCServer(std::string serverName, std::string guid)
{

	altiaMediaRenderer = new AMediaRenderer(serverName.c_str(), false, guid.c_str());
	/* Get copy of returned DeviceHostRef */
	altiaMediaRendererDevice = PLT_DeviceHostReference(altiaMediaRenderer);
	altiaMediaRenderer->SetDelegate(altiaMediaDelegate);
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
