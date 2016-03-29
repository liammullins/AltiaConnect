/*****************************************************************
|
|   Platinum - AV Media Renderer Device
|
| Copyright (c) 2004-2010, Plutinosoft, LLC.
| All rights reserved.
| http://www.plutinosoft.com
|
| This program is free software; you can redistribute it and/or
| modify it under the terms of the GNU General Public License
| as published by the Free Software Foundation; either version 2
| of the License, or (at your option) any later version.
|
| OEMs, ISVs, VARs and other distributors that combine and 
| distribute commercially licensed software with Platinum software
| and do not wish to distribute the source code for the commercially
| licensed software under version 2, or (at your option) any later
| version, of the GNU General Public License (the "GPL") must enter
| into a commercial license agreement with Plutinosoft, LLC.
| licensing@plutinosoft.com
| 
| This program is distributed in the hope that it will be useful,
| but WITHOUT ANY WARRANTY; without even the implied warranty of
| MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
| GNU General Public License for more details.
|
| You should have received a copy of the GNU General Public License
| along with this program; see the file LICENSE.txt. If not, write to
| the Free Software Foundation, Inc., 
| 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
| http://www.gnu.org/licenses/gpl-2.0.html
|
****************************************************************/

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "Neptune.h"
#include "PltMediaRenderer.h"
#include "PltService.h"

NPT_SET_LOCAL_LOGGER("platinum.media.renderer")

/*----------------------------------------------------------------------
|   external references
+---------------------------------------------------------------------*/
extern NPT_UInt8 RDR_ConnectionManagerSCPD[];
extern NPT_UInt8 RDR_AVTransportSCPD[];
extern NPT_UInt8 RDR_RenderingControlSCPD[];

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::PLT_MediaRenderer
+---------------------------------------------------------------------*/
PLT_MediaRenderer::PLT_MediaRenderer(const char*  friendly_name,
                                     bool         show_ip     /* = false */, 
                                     const char*  uuid        /* = NULL */, 
                                     unsigned int port        /* = 0 */,
                                     bool         port_rebind /* = false */) :	
    PLT_DeviceHost("/", 
                   uuid, 
                   "urn:schemas-upnp-org:device:MediaRenderer:1", 
                   friendly_name, 
                   show_ip, 
                   port, 
                   port_rebind)
{
    m_ModelDescription = "Plutinosoft AV Media Renderer Device";
    m_ModelName        = "AV Renderer Device";
    m_ModelURL         = "http://www.plutinosoft.com/platinum";
    m_DlnaDoc          = "DMR-1.50";
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::~PLT_MediaRenderer
+---------------------------------------------------------------------*/
PLT_MediaRenderer::~PLT_MediaRenderer()
{
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::SetupServices
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::SetupServices()
{
    NPT_Reference<PLT_Service> service;

    {
        /* AVTransport */
        service = new PLT_Service(
            this,
            "urn:schemas-upnp-org:service:AVTransport:1", 
            "urn:upnp-org:serviceId:AVTransport",
            "AVTransport",
            "urn:schemas-upnp-org:metadata-1-0/AVT/");
        NPT_CHECK_FATAL(service->SetSCPDXML((const char*) RDR_AVTransportSCPD));
        NPT_CHECK_FATAL(AddService(service.AsPointer()));

        service->SetStateVariableRate("LastChange", NPT_TimeInterval(0.2f));
        service->SetStateVariable("A_ARG_TYPE_InstanceID", "0"); 

        // GetCurrentTransportActions
        service->SetStateVariable("CurrentTransportActions", "Play,Pause,Stop,Seek,Next,Previous");

        // GetDeviceCapabilities
        service->SetStateVariable("PossiblePlaybackStorageMedia", "NONE,NETWORK,HDD,CD-DA,UNKNOWN,RTSP,RTP,h264,MIRROR");
        service->SetStateVariable("PossibleRecordStorageMedia", "NOT_IMPLEMENTED");
        service->SetStateVariable("PossibleRecordQualityModes", "NOT_IMPLEMENTED");

        // GetMediaInfo
        service->SetStateVariable("NumberOfTracks", "0");
        service->SetStateVariable("CurrentMediaDuration", "01:00:00");
        service->SetStateVariable("AVTransportURI", "");
        service->SetStateVariable("AVTransportURIMetadata", "");;
        service->SetStateVariable("NextAVTransportURI", "NOT_IMPLEMENTED");
        service->SetStateVariable("NextAVTransportURIMetadata", "NOT_IMPLEMENTED");
        service->SetStateVariable("PlaybackStorageMedium", "NONE");
        service->SetStateVariable("RecordStorageMedium", "NOT_IMPLEMENTED");
		service->SetStateVariable("RecordMediumWriteStatus", "NOT_IMPLEMENTED");

        // GetPositionInfo
		service->SetStateVariable("mirror", "h264");
        service->SetStateVariable("CurrentTrack", "0");
        service->SetStateVariable("CurrentTrackDuration", "00:00:00");
        service->SetStateVariable("CurrentTrackMetadata", "");
        service->SetStateVariable("CurrentTrackURI", "");
        service->SetStateVariable("RelativeTimePosition", "00:00:00"); 
        service->SetStateVariable("AbsoluteTimePosition", "00:00:00");
        service->SetStateVariable("RelativeCounterPosition", "2147483647"); // means NOT_IMPLEMENTED
        service->SetStateVariable("AbsoluteCounterPosition", "2147483647"); // means NOT_IMPLEMENTED

        // disable indirect eventing for certain state variables
        PLT_StateVariable* var;
        var = service->FindStateVariable("RelativeTimePosition");
        if (var) var->DisableIndirectEventing();
        var = service->FindStateVariable("AbsoluteTimePosition");
        if (var) var->DisableIndirectEventing();
        var = service->FindStateVariable("RelativeCounterPosition");
        if (var) var->DisableIndirectEventing();
        var = service->FindStateVariable("AbsoluteCounterPosition");
        if (var) var->DisableIndirectEventing();

        // GetTransportInfo
        service->SetStateVariable("TransportState", "NO_MEDIA_PRESENT");
        service->SetStateVariable("TransportStatus", "OK");
        service->SetStateVariable("TransportPlaySpeed", "1");

        // GetTransportSettings
        service->SetStateVariable("CurrentPlayMode", "NORMAL");
        service->SetStateVariable("CurrentRecordQualityMode", "NOT_IMPLEMENTED");
        
        service.Detach();
        service = NULL;
    }

    {
        /* ConnectionManager */
        service = new PLT_Service(
            this,
            "urn:schemas-upnp-org:service:ConnectionManager:1", 
            "urn:upnp-org:serviceId:ConnectionManager",
            "ConnectionManager");
        NPT_CHECK_FATAL(service->SetSCPDXML((const char*) RDR_ConnectionManagerSCPD));
        NPT_CHECK_FATAL(AddService(service.AsPointer()));

        service->SetStateVariable("CurrentConnectionIDs", "0");

        // put all supported mime types here instead
        //service->SetStateVariable("SinkProtocolInfo", "http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVMED_PRO,http-get:*:video/x-ms-asf:DLNA.ORG_PN=MPEG4_P2_ASF_SP_G726,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVMED_FULL,http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_MED,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVMED_BASE,http-get:*:audio/L16;rate=44100;channels=1:DLNA.ORG_PN=LPCM,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_PS_PAL,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_PS_NTSC,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVHIGH_PRO,http-get:*:audio/L16;rate=44100;channels=2:DLNA.ORG_PN=LPCM,http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_SM,http-get:*:video/x-ms-asf:DLNA.ORG_PN=VC1_ASF_AP_L1_WMA,http-get:*:audio/x-ms-wma:DLNA.ORG_PN=WMDRM_WMABASE,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVHIGH_FULL,http-get:*:audio/x-ms-wma:DLNA.ORG_PN=WMAFULL,http-get:*:audio/x-ms-wma:DLNA.ORG_PN=WMABASE,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVSPLL_BASE,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_PS_NTSC_XAC3,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMDRM_WMVSPLL_BASE,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVSPML_BASE,http-get:*:video/x-ms-asf:DLNA.ORG_PN=MPEG4_P2_ASF_ASP_L5_SO_G726,http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_LRG,http-get:*:audio/mpeg:DLNA.ORG_PN=MP3,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_PS_PAL_XAC3,http-get:*:audio/x-ms-wma:DLNA.ORG_PN=WMAPRO,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG1,http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_TN,http-get:*:video/x-ms-asf:DLNA.ORG_PN=MPEG4_P2_ASF_ASP_L4_SO_G726,http-get:*:audio/L16;rate=48000;channels=2:DLNA.ORG_PN=LPCM,http-get:*:audio/mpeg:DLNA.ORG_PN=MP3X,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVSPML_MP3,http-get:*:video/x-ms-wmv:*");
		service->SetStateVariable("SinkProtocolInfo", "http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_SM,rtsp-rtp-udp:*:image/jpeg:DLNA.ORG_PN=JPEG_SM,http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_MED,rtsp-rtp-udp:*:image/jpeg:DLNA.ORG_PN=JPEG_MED,http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_LRG,rtsp-rtp-udp:*:image/jpeg:DLNA.ORG_PN=JPEG_LRG,http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_TN,rtsp-rtp-udp:*:image/jpeg:DLNA.ORG_PN=JPEG_TN,http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_SM_ICO,rtsp-rtp-udp:*:image/jpeg:DLNA.ORG_PN=JPEG_SM_ICO,http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_LRG_ICO,rtsp-rtp-udp:*:image/jpeg:DLNA.ORG_PN=JPEG_LRG_ICO,http-get:*:image/png:DLNA.ORG_PN=PNG_TN,rtsp-rtp-udp:*:image/png:DLNA.ORG_PN=PNG_TN,http-get:*:image/png:DLNA.ORG_PN=PNG_SM_ICO,rtsp-rtp-udp:*:image/png:DLNA.ORG_PN=PNG_SM_ICO,http-get:*:image/png:DLNA.ORG_PN=PNG_LRG_ICO,rtsp-rtp-udp:*:image/png:DLNA.ORG_PN=PNG_LRG_ICO,http-get:*:image/png:DLNA.ORG_PN=PNG_LRG,rtsp-rtp-udp:*:image/png:DLNA.ORG_PN=PNG_LRG,http-get:*:audio/mpeg:DLNA.ORG_PN=MP3,rtsp-rtp-udp:*:audio/mpeg:DLNA.ORG_PN=MP3,http-get:*:audio/L16:DLNA.ORG_PN=LPCM,rtsp-rtp-udp:*:audio/L16:DLNA.ORG_PN=LPCM,http-get:*:audio/x-ms-wma:DLNA.ORG_PN=WMABASE,rtsp-rtp-udp:*:audio/x-ms-wma:DLNA.ORG_PN=WMABASE,http-get:*:audio/x-ms-wma:DLNA.ORG_PN=WMAFULL,rtsp-rtp-udp:*:audio/x-ms-wma:DLNA.ORG_PN=WMAFULL,http-get:*:audio/x-ms-wma:DLNA.ORG_PN=WMAPRO,rtsp-rtp-udp:*:audio/x-ms-wma:DLNA.ORG_PN=WMAPRO,http-get:*:audio/mp4:DLNA.ORG_PN=AAC_ISO,rtsp-rtp-udp:*:audio/mp4:DLNA.ORG_PN=AAC_ISO,http-get:*:audio/mp4:DLNA.ORG_PN=AAC_ISO_320,rtsp-rtp-udp:*:audio/mp4:DLNA.ORG_PN=AAC_ISO_320,http-get:*:audio/vnd.dolby.dd-raw:DLNA.ORG_PN=AC3,rtsp-rtp-udp:*:audio/vnd.dolby.dd-raw:DLNA.ORG_PN=AC3,http-get:*:audio/3gpp:DLNA.ORG_PN=AAC_ISO,rtsp-rtp-udp:*:audio/3gpp:DLNA.ORG_PN=AAC_ISO,http-get:*:audio/3gpp:DLNA.ORG_PN=AAC_ISO_320,rtsp-rtp-udp:*:audio/3gpp:DLNA.ORG_PN=AAC_ISO_320,http-get:*:audio/vnd.dlna.adts:DLNA.ORG_PN=AAC_ADTS,rtsp-rtp-udp:*:audio/vnd.dlna.adts:DLNA.ORG_PN=AAC_ADTS,http-get:*:audio/vnd.dlna.adts:DLNA.ORG_PN=AAC_ADTS_320,rtsp-rtp-udp:*:audio/vnd.dlna.adts:DLNA.ORG_PN=AAC_ADTS_320,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG1,rtsp-rtp-udp:*:video/mpeg:DLNA.ORG_PN=MPEG1,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_PS_NTSC,rtsp-rtp-udp:*:video/mpeg:DLNA.ORG_PN=MPEG_PS_NTSC,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_PS_PAL,rtsp-rtp-udp:*:video/mpeg:DLNA.ORG_PN=MPEG_PS_PAL,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_SD_NA_ISO,rtsp-rtp-udp:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_SD_NA_ISO,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_HD_NA_ISO,rtsp-rtp-udp:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_HD_NA_ISO,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_SD_EU_ISO,rtsp-rtp-udp:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_SD_EU_ISO,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_SD_KO_ISO,rtsp-rtp-udp:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_SD_KO_ISO,http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_HD_KO_ISO,rtsp-rtp-udp:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_HD_KO_ISO,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_NA,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_NA,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_NA_T,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_NA_T,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_NA,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_NA,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_NA_T,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_NA_T,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_EU,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_EU,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_EU_T,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_EU_T,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_KO,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_KO,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_KO_T,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_SD_KO_T,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_KO,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_KO,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_KO_T,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_KO_T,http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_JP_T,rtsp-rtp-udp:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_JP_T,http-get:*:video/mp4:DLNA.ORG_PN=MPEG4_P2_MP4_SP_AAC,rtsp-rtp-udp:*:video/mp4:DLNA.ORG_PN=MPEG4_P2_MP4_SP_AAC,http-get:*:video/mp4:DLNA.ORG_PN=AVC_MP4_BL_CIF15_AAC,rtsp-rtp-udp:*:video/mp4:DLNA.ORG_PN=AVC_MP4_BL_CIF15_AAC,http-get:*:video/mp4:DLNA.ORG_PN=AVC_MP4_BL_CIF15_AAC_520,rtsp-rtp-udp:*:video/mp4:DLNA.ORG_PN=AVC_MP4_BL_CIF15_AAC_520,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVMED_BASE,rtsp-rtp-udp:*:video/x-ms-wmv:DLNA.ORG_PN=WMVMED_BASE,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVMED_FULL,rtsp-rtp-udp:*:video/x-ms-wmv:DLNA.ORG_PN=WMVMED_FULL,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVMED_PRO,rtsp-rtp-udp:*:video/x-ms-wmv:DLNA.ORG_PN=WMVMED_PRO,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVHIGH_FULL,rtsp-rtp-udp:*:video/x-ms-wmv:DLNA.ORG_PN=WMVHIGH_FULL,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVHIGH_PRO,rtsp-rtp-udp:*:video/x-ms-wmv:DLNA.ORG_PN=WMVHIGH_PRO,http-get:*:video/x-ms-wmv:DLNA.ORG_PN=WMVHM_BASE,rtsp-rtp-udp:*:video/x-ms-wmv:DLNA.ORG_PN=WMVHM_BASE,http-get:*:image/gif:*,rtsp-rtp-udp:*:image/gif:*,http-get:*:audio/x-wav:*,rtsp-rtp-udp:*:audio/x-wav:*,http-get:*:audio/lpcm:*,rtsp-rtp-udp:*:audio/lpcm:*,http-get:*:audio/x-aac:*,rtsp-rtp-udp:*:audio/x-aac:*,http-get:*:audio/m4a:*,rtsp-rtp-udp:*:audio/m4a:*,http-get:*:application/ogg:*,rtsp-rtp-udp:*:application/ogg:*,http-get:*:video/avi:*,rtsp-rtp-udp:*:video/avi:*,http-get:*:video/mp1s:*,rtsp-rtp-udp:*:video/mp1s:*,http-get:*:video/mp2p:*,rtsp-rtp-udp:*:video/mp2p:*,http-get:*:video/mp2t:*,rtsp-rtp-udp:*:video/mp2t:*,http-get:*:video/mpeg2:*,rtsp-rtp-udp:*:video/mpeg2:*,http-get:*:video/dvd:*,rtsp-rtp-udp:*:video/dvd:*,http-get:*:video/quicktime:*,rtsp-rtp-udp:*:video/quicktime:*,http-get:*:video/mpeg4:*,rtsp-rtp-udp:*:video/mpeg4:*,http-get:*:video/mp4:*,rtsp-rtp-udp:*:video/mp4:*,http-get:*:video/m4t:*,rtsp-rtp-udp:*:video/m4t:*,http-get:*:audio/x-mpegurl:*,rtsp-rtp-udp:*:audio/x-mpegurl:*,http-get:*:audio/x-ms-wax:*,rtsp-rtp-udp:*:audio/x-ms-wax:*,http-get:*:audio/x-scpls:*,rtsp-rtp-udp:*:audio/x-scpls:*,http-get:*:application/t5:*,rtsp-rtp-udp:*:application/t5:*,http-get:*:video/x-matroska:*,rtsp-rtp-udp:*:video/x-matroska:*,http-get:*:video/youtube:*,rtsp-rtp-udp:*:video/youtube:*");
		service->SetStateVariable("SourceProtocolInfo", "");
        
        service.Detach();
        service = NULL;
    }

    {
        /* RenderingControl */
        service = new PLT_Service(
            this,
            "urn:schemas-upnp-org:service:RenderingControl:1", 
            "urn:upnp-org:serviceId:RenderingControl",
            "RenderingControl",
            "urn:schemas-upnp-org:metadata-1-0/RCS/");
        NPT_CHECK_FATAL(service->SetSCPDXML((const char*) RDR_RenderingControlSCPD));
        NPT_CHECK_FATAL(AddService(service.AsPointer()));

        service->SetStateVariableRate("LastChange", NPT_TimeInterval(0.2f));

        service->SetStateVariable("Mute", "0");
        service->SetStateVariableExtraAttribute("Mute", "Channel", "Master");
        service->SetStateVariable("Volume", "100");
        service->SetStateVariableExtraAttribute("Volume", "Channel", "Master");
        service->SetStateVariable("VolumeDB", "0");
        service->SetStateVariableExtraAttribute("VolumeDB", "Channel", "Master");

        service->SetStateVariable("PresetNameList", "FactoryDefaults");
        
        service.Detach();
        service = NULL;
    }

    return NPT_SUCCESS;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnAction
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnAction(PLT_ActionReference&          action, 
                            const PLT_HttpRequestContext& context)
{
    NPT_COMPILER_UNUSED(context);

    /* parse the action name */
    NPT_String name = action->GetActionDesc().GetName();

    // since all actions take an instance ID and we only support 1 instance
    // verify that the Instance ID is 0 and return an error here now if not
    NPT_String serviceType = action->GetActionDesc().GetService()->GetServiceType();
    if (serviceType.Compare("urn:schemas-upnp-org:service:AVTransport:1", true) == 0) {
        if (NPT_FAILED(action->VerifyArgumentValue("InstanceID", "0"))) {
            action->SetError(718, "Not valid InstanceID");
            return NPT_FAILURE;
        }
    }
	serviceType = action->GetActionDesc().GetService()->GetServiceType();
	if (serviceType.Compare("urn:schemas-upnp-org:service:RenderingControl:1", true) == 0) {
		if (NPT_FAILED(action->VerifyArgumentValue("InstanceID", "0"))) {
			action->SetError(702, "Not valid InstanceID");
			return NPT_FAILURE;
		}
	}

	/* Is it a ConnectionManager Service Action ? */
	if (name.Compare("GetCurrentConnectionInfo", true) == 0) {
		return OnGetCurrentConnectionInfo(action);
	}  

	/* Is it a AVTransport Service Action ? */
    if (name.Compare("Next", true) == 0) {
        return OnNext(action);
    }
    if (name.Compare("Pause", true) == 0) {
        return OnPause(action);
    }
    if (name.Compare("Play", true) == 0) {
        return OnPlay(action);
    }
    if (name.Compare("Previous", true) == 0) {
        return OnPrevious(action);
    }
    if (name.Compare("Seek", true) == 0) {
        return OnSeek(action);
    }
    if (name.Compare("Stop", true) == 0) {
        return OnStop(action);
    }
    if (name.Compare("SetAVTransportURI", true) == 0) {
        return OnSetAVTransportURI(action);
    }
    if (name.Compare("SetPlayMode", true) == 0) {
        return OnSetPlayMode(action);
    }

    /* Is it a RendererControl Service Action ? */
    if (name.Compare("SetVolume", true) == 0) {
          return OnSetVolume(action);
    }
	if (name.Compare("SetVolumeDB", true) == 0) {
		return OnSetVolumeDB(action);
    }
	if (name.Compare("GetVolumeDBRange", true) == 0) {
		return OnGetVolumeDBRange(action);

	}
    if (name.Compare("SetMute", true) == 0) {
          return OnSetMute(action);
    }

    // other actions rely on state variables
    NPT_CHECK_LABEL_WARNING(action->SetArgumentsOutFromStateVariable(), failure);
    return NPT_SUCCESS;

failure:
    action->SetError(401,"No Such Action.");
    return NPT_FAILURE;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnGetCurrentConnectionInfo
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnGetCurrentConnectionInfo(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnGetCurrentConnectionInfo(action);
    }
    
    if (NPT_FAILED(action->VerifyArgumentValue("ConnectionID", "0"))) {
        action->SetError(706,"No Such Connection.");
        return NPT_FAILURE;
    }

    if (NPT_FAILED(action->SetArgumentValue("RcsID", "0"))){
        return NPT_FAILURE;
    }
    if (NPT_FAILED(action->SetArgumentValue("AVTransportID", "0"))) {
        return NPT_FAILURE;
    }
    if (NPT_FAILED(action->SetArgumentOutFromStateVariable("ProtocolInfo"))) {
        return NPT_FAILURE;
    }
    if (NPT_FAILED(action->SetArgumentValue("PeerConnectionManager", "/"))) {
        return NPT_FAILURE;
    }
    if (NPT_FAILED(action->SetArgumentValue("PeerConnectionID", "-1"))) {
        return NPT_FAILURE;
    }
    if (NPT_FAILED(action->SetArgumentValue("Direction", "Input"))) {
        return NPT_FAILURE;
    }
    if (NPT_FAILED(action->SetArgumentValue("Status", "Unknown"))) {
        return NPT_FAILURE;
    }

    return NPT_SUCCESS;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnNext
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnNext(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnNext(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnPause
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnPause(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnPause(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnPlay
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnPlay(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnPlay(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnPrevious
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnPrevious(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnPrevious(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnSeek
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnSeek(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnSeek(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnStop
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnStop(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnStop(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnSetAVTransportURI
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnSetAVTransportURI(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnSetAVTransportURI(action);
    }
    
    // default implementation is using state variable
    NPT_String uri;
    NPT_CHECK_WARNING(action->GetArgumentValue("CurrentURI", uri));

    NPT_String metadata;
    NPT_CHECK_WARNING(action->GetArgumentValue("CurrentURIMetaData", metadata));
    
    PLT_Service* serviceAVT;
    NPT_CHECK_WARNING(FindServiceByType("urn:schemas-upnp-org:service:AVTransport:1", serviceAVT));

    // update service state variables
    serviceAVT->SetStateVariable("AVTransportURI", uri);
    serviceAVT->SetStateVariable("AVTransportURIMetaData", metadata);

    return NPT_SUCCESS;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnSetPlayMode
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnSetPlayMode(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnSetPlayMode(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnSetVolume
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnSetVolume(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnSetVolume(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnSetVolumeDB
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnSetVolumeDB(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnSetVolumeDB(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnGetVolumeDBRange
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnGetVolumeDBRange(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnGetVolumeDBRange(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}

/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnSetMute
+---------------------------------------------------------------------*/
NPT_Result
PLT_MediaRenderer::OnSetMute(PLT_ActionReference& action)
{
    if (m_Delegate) {
        return m_Delegate->OnSetMute(action);
    }
    return NPT_ERROR_NOT_IMPLEMENTED;
}
