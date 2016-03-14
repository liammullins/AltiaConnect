#include "AMediaRenderer.h"
#include "PltUPnP.h"
#include "PltMediaRenderer.h"

/*----------------------------------------------------------------------
|   globals
+---------------------------------------------------------------------*/
struct Options {
	const char* friendly_name;
} Options;

AMediaRenderer::AMediaRenderer()
{

	PLT_UPnP upnp;
	PLT_DeviceHostReference device(
		new PLT_MediaRenderer(Options.friendly_name ? Options.friendly_name : "Altia Connect Point",
		false,
		"e6572b54-f3c7-2d91-2fb5-b757f2537e21"));
	upnp.AddDevice(device);
	bool added = true;

	upnp.Start();

}


AMediaRenderer::~AMediaRenderer()
{
}

