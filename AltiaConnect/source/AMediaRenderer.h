#ifndef MEDIARENDERER
#define MEDIARENDERER

#include "global_include.h"
#include "PltUPnP.h"
#include "PltMediaRenderer.h"

class AMediaRenderer : public PLT_MediaRenderer
{
	
public:
	AMediaRenderer();
	//virtual NPT_Result OnAction(PLT_ActionReference& action, const PLT_HttpRequestContext& context);
	
	virtual ~AMediaRenderer();
	/* init Media Renderer public funk */
	void AMediaRenderer::initMediaRenderer();
	/* think we need access to this */
	PLT_UPnP upnp;
};
#endif
