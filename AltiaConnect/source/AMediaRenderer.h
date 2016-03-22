#ifndef MEDIARENDERER
#define MEDIARENDERER

#include "global_include.h"
#include "PltUPnP.h"
#include "PltMediaRenderer.h"
#include "PltService.h"


class AMediaRendererDelegate : public PLT_MediaRendererDelegate
{
public:
	AMediaRendererDelegate();
	~AMediaRendererDelegate() {}

	// ConnectionManager
	NPT_Result OnGetCurrentConnectionInfo(PLT_ActionReference& action) = 0;

	//nsport
	NPT_Result OnNext(PLT_ActionReference& action){ return 0; };
	NPT_Result OnPause(PLT_ActionReference& action){ return 0; };
	NPT_Result OnPlay(PLT_ActionReference& action) ;
	NPT_Result OnPrevious(PLT_ActionReference& action) { return 0; };
	NPT_Result OnSeek(PLT_ActionReference& action){ return 0; };
	NPT_Result OnStop(PLT_ActionReference& action) { return 0; };
	NPT_Result OnSetAVTransportURI(PLT_ActionReference& action) ;
	NPT_Result OnSetPlayMode(PLT_ActionReference& action) { return 0; };

	//ringControl
	NPT_Result OnSetVolume(PLT_ActionReference& action) { return 0; };
	NPT_Result OnSetVolumeDB(PLT_ActionReference& action) { return 0; };
	NPT_Result OnGetVolumeDBRange(PLT_ActionReference& action) { return 0; };
	NPT_Result OnSetMute(PLT_ActionReference& action) { return 0; };
};

class AMediaRenderer : public PLT_MediaRenderer
{

public:
		//using PLT_MediaRenderer::PLT_MediaRenderer /* doubtful support for this */;
		AMediaRenderer(const char*  friendly_name,
					   bool         show_ip = false,
					   const char*  uuid = NULL,
					   unsigned int port = 0,
					   bool         port_rebind = false);

	/* virtual - overriding OnAction */
	NPT_Result OnAction(PLT_ActionReference &action,const PLT_HttpRequestContext& context);
	/* virtual - overriding OnSetAVTransport */
	/* virtual - doesn't seem to work */
	//void SetDelegate(AMediaRendererDelegate* delegate) { m_Delegate = delegate; }
	//virtual NPT_Result OnAction(PLT_ActionReference& action, const PLT_HttpRequestContext& context);
	~AMediaRenderer();
	/* init Media Renderer public funk */
	void initMediaRenderer();

private:
	PLT_MediaRendererDelegate * m_Delegate;

};
#endif
