
#include "AMediaRenderer.h"

AMediaRendererDelegate *altiaMediaDelegate;

/*-----------------------------------
-----------------------------------
|   PLT_MediaRenderer::PLT_MediaRenderer
+---------------------------------------------------------------------*/
AMediaRendererDelegate::AMediaRendererDelegate()
{

}
AMediaRenderer::AMediaRenderer(const char*  friendly_name,
	bool         show_ip     /* = false */,
	const char*  uuid        /* = NULL */,
	unsigned int port        /* = 0 */,
	bool         port_rebind /* = false */) 
	:
	PLT_MediaRenderer(friendly_name, false, uuid, port, port_rebind)
{
	m_ModelDescription = "Altia Connect Beta Device";
	m_ModelName = "Altia Connection";
	m_ModelURL = "http://www.altia.com";
	m_DlnaDoc = "DMR-1.50";
	SetDelegate(altiaMediaDelegate);
}

NPT_Result AMediaRenderer::OnAction(PLT_ActionReference &action, const PLT_HttpRequestContext& context)
{
	/* parse the action name */
	NPT_String name = action->GetActionDesc().GetName();
	NPT_String type = "";
	NPT_String serviceType = action->GetArgumentValue("",);
	ALTIA_LOG_INFO("%s Action Received: %s = %s", context.GetRequest().GetMethod(), name, type);
	return 0;
}
/**/
NPT_Result AMediaRendererDelegate::OnPlay(PLT_ActionReference& action)
{
	ALTIA_LOG_INFO("Play! Action Received: %s", action);
	return 0;
}

NPT_Result AMediaRendererDelegate::OnSetAVTransportURI(PLT_ActionReference& action)
{
	ALTIA_LOG_INFO("WOOT! Action Received: %s", action);
	return 0;
}
void AMediaRenderer::initMediaRenderer()
{

}

AMediaRenderer::~AMediaRenderer()
{

}
