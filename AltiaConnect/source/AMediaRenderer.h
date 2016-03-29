#ifndef MEDIARENDERER
#define MEDIARENDERER

#include "global_include.h"
#include "PltUPnP.h"
#include "PltMediaRenderer.h"
#include "PltService.h"
#include "PltAction.h"


class AMediaRenderer : public PLT_MediaRenderer, 
					   public PLT_MediaRendererDelegate
{

public:
		/* using PLT_MediaRenderer::PLT_MediaRenderer /* doubtful support for this */;
		AMediaRenderer(const char*  friendly_name,
					   bool         show_ip = false,
					   const char*  uuid = NULL,
					   unsigned int port = 0,
					   bool         port_rebind = false);

		~AMediaRenderer();
		/* virtual - overriding OnAction */
		NPT_Result OnAction(PLT_ActionReference &action,const PLT_HttpRequestContext& context);
		/* init Media Renderer public funk */
		void initMediaRenderer();
		//HBITMAP ConvertIplImage2HBITMAP(IplImage* pImage);
		HBITMAP CreateBitmap2(int w, int h, WORD bpp, int nSize);
		void playVideo(std::string videoURI);
		NPT_Result SetupServices();

protected:
	NPT_Result OnSetAVTransportURI(PLT_ActionReference& action);

	// ConnectionManager
	NPT_Result OnGetCurrentConnectionInfo(PLT_ActionReference& action);// { return 0; }
	//nsport
	NPT_Result OnNext(PLT_ActionReference& action){ return 0; };
	NPT_Result OnPause(PLT_ActionReference& action){ return 0; };
	NPT_Result OnPlay(PLT_ActionReference& action) { return 0; };
	NPT_Result OnPrevious(PLT_ActionReference& action) { return 0; };
	NPT_Result OnSeek(PLT_ActionReference& action){ return 0; };
	NPT_Result OnStop(PLT_ActionReference& action) { return 0; };

	NPT_Result OnSetPlayMode(PLT_ActionReference& action) { return 0; };
	//ringControl
	NPT_Result OnSetVolume(PLT_ActionReference& action) { return 0; };
	NPT_Result OnSetVolumeDB(PLT_ActionReference& action) { return 0; };
	NPT_Result OnGetVolumeDBRange(PLT_ActionReference& action) { return 0; };
	NPT_Result OnSetMute(PLT_ActionReference& action) { return 0; };

	

private:
	NPT_Result InitServiceURLs(PLT_Service* service, const char* service_name);
	/*pointer to the AV service for further StateVariable modifications*/
	PLT_Service *m_pAVService;
	PLT_Service *m_pMigrationService;


};
#endif
