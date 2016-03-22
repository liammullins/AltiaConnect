#ifndef MULTICASTSERVER
#define MULTICASTSERVER

#include "global_include.h"
#include "PltUPnP.h"


class AMulticastServer
{
public: 
	AMulticastServer();
	virtual ~AMulticastServer();
	/* init Media Renderer public funk */
	void initMCServer(std::string serverName, std::string guid);
	/* think we need access to this */
	PLT_UPnP upnp;
};
#endif

