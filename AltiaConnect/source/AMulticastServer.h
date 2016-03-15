#ifndef MULTICASTSERVER
#define MULTICASTSERVER

#include "global_include.h"
#include "PltUPnP.h"
#include "PltMediaRenderer.h"

class AMulticastServer
{
public: 
	AMulticastServer();
	virtual ~AMulticastServer();

	virtual NPT_Result OnAction(PLT_ActionReference& action, const PLT_HttpRequestContext& context);
	/* init Media Renderer public funk */
	void initMCServer(std::string serverName, std::string guid);
	/* think we need access to this */
	PLT_UPnP upnp;
};
#endif

