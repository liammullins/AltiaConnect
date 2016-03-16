#ifndef MEDIARENDERER
#define MEDIARENDERER

#include "global_include.h"
#include "PltUPnP.h"
#include "PltMediaRenderer.h"



class AMediaRenderer 
{

public:
	AMediaRenderer();
	//virtual NPT_Result OnAction(PLT_ActionReference& action, const PLT_HttpRequestContext& context);
	//virtual NPT_Result OnAction(PLT_ActionReference& action, const PLT_HttpRequestContext& context);
	virtual ~AMediaRenderer();
	/* init Media Renderer public funk */
	void initMediaRenderer();
	/* think we need access to this */
	//PLT_UPnP upnp;

private:
	

};
#endif
