#include "AMediaRenderer.h"
#include <process.h>
#include <iostream>
#include <stdio.h>
#include <mutex>

bool processing;
std::string _videoURI;
NPT_UInt8 RDR_ConnectionManagerSCPD[];
NPT_UInt8 RDR_AVTransportSCPD[];
NPT_UInt8 RDR_RenderingControlSCPD[];
//extern PushFrameToDll pushFrameToAltia;
extern void PushFrame(char* frame);
/* use the openCV namespace here */
using namespace cv;

AMediaRenderer::AMediaRenderer(const char*  friendly_name,
	bool         show_ip     /* = false */,
	const char*  uuid        /* = NULL */,
	unsigned int port        /* = 0 */,
	bool         port_rebind /* = false */) 
	:
	PLT_MediaRenderer(friendly_name, false, uuid, port, port_rebind)
{
	m_ModelDescription = "Altia Connect Beta Device";
	m_ModelName = "Altia Connect";
	m_ModelURL = "http://www.altia.com";
	m_ManufacturerURL = "http://www.altia.com";
	m_DlnaDoc = "Altia Media Renderer";
	playVideo("DIRECT_LINK");

}
/*----------------------------------------------------------------------
|   PLT_MediaRenderer::OnGetCurrentConnectionInfo
+---------------------------------------------------------------------*/
NPT_Result AMediaRenderer::OnGetCurrentConnectionInfo(PLT_ActionReference& action)
{


	if (NPT_FAILED(action->VerifyArgumentValue("ConnectionID", "0"))) {
		action->SetError(706, "No Such Connection.");
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


NPT_Result AMediaRenderer::SetupServices()
{
	NPT_CHECK(PLT_MediaRenderer::SetupServices());

	return NPT_SUCCESS;
}

HBITMAP ConvertIplImage2HBITMAP(IplImage* pImage)
{
	int bpp = pImage->nChannels * 8;
	if (bpp != 8 && bpp != 24 && bpp != 32)return NULL;

	//assert(Image->width >= 0 && Image->height >= 0 &&
		//(bpp == 8 || bpp == 24 || bpp == 32));
	CvMat dst;
	void* dst_ptr = NULL;
	HBITMAP hbmp = NULL;
	unsigned char buffer[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	BITMAPINFO* bmi = (BITMAPINFO*)buffer;
	BITMAPINFOHEADER* bmih = &(bmi->bmiHeader);

	ZeroMemory(bmih, sizeof(BITMAPINFOHEADER));
	bmih->biSize = sizeof(BITMAPINFOHEADER);
	bmih->biWidth = pImage->width;
	bmih->biHeight = pImage->origin ? abs(pImage->height) :
		-abs(pImage->height);
	bmih->biPlanes = 1;
	bmih->biBitCount = bpp;
	bmih->biCompression = BI_RGB;

	if (bpp == 8) {
		RGBQUAD* palette = bmi->bmiColors;
		int i;
		for (i = 0; i < 256; i++) {
			palette[i].rgbRed = palette[i].rgbGreen = palette[i].rgbBlue
				= (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}

	hbmp = CreateDIBSection(NULL, bmi, DIB_RGB_COLORS, &dst_ptr, 0, 0);
	
	/**/
		cvInitMatHeader(&dst, pImage->height, pImage->width, CV_8UC3,
		dst_ptr, (pImage->width * pImage->nChannels + 3) & -4);

	try
	{
		if (pImage->imageData!=NULL)
		{
			cvConvertImage(pImage, &dst, pImage->origin ? CV_CVTIMG_FLIP : 0);

			DeleteObject(bmi);
			DeleteObject(bmih);
			//DeleteObject(hbmp);
			DeleteObject(&dst);
			DeleteObject(dst_ptr);
		}
	}
	catch (...)
	{
		ALTIA_LOG_INFO("cvInitMat Header issue! Probably a memory leak %p", pImage->imageData);
	}

	return hbmp;

}

HBITMAP AMediaRenderer::CreateBitmap2(int w, int h, WORD bpp, int nSize)
{
	HDC hDC = ::CreateCompatibleDC(0);
	BYTE tmp[sizeof(BITMAPINFO) + 255 * 4];
	BITMAPINFO *bmi = (BITMAPINFO*)tmp;
	HBITMAP hBmp;
	int i;
	memset(bmi, 0, sizeof(BITMAPINFO));
	bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi->bmiHeader.biWidth = w;
	bmi->bmiHeader.biHeight = h;
	bmi->bmiHeader.biPlanes = nSize;
	bmi->bmiHeader.biBitCount = bpp;
	bmi->bmiHeader.biCompression = BI_RGB;
	bmi->bmiHeader.biSizeImage = w*h * 1;
	bmi->bmiHeader.biClrImportant = 0;
	switch (bpp)
	{
	case 8:
		for (i = 0; i < 256; i++)
		{
			bmi->bmiColors[i].rgbBlue = i;
			bmi->bmiColors[i].rgbGreen = i;
			bmi->bmiColors[i].rgbRed = i;
		}
		break;
	case 32:
	case 24:
		((DWORD*)bmi->bmiColors)[0] = 0x00FF0000; /* red mask
												  */
		((DWORD*)bmi->bmiColors)[1] = 0x0000FF00; /* green
												  mask */
		((DWORD*)bmi->bmiColors)[2] = 0x000000FF; /* blue
												  mask */
		break;
	}
	hBmp =
		::CreateDIBSection(hDC, bmi, DIB_RGB_COLORS, NULL, 0, 0);
	::DeleteDC(hDC);
	return hBmp;
}

void grabFrames(VideoCapture *capture)
{
	
	while (true)
	{
		capture->grab();
	}
	
}

void pMovie(void *param)
{

	Mat frame;
	VideoCapture cap;

	//cap.set(CV_CAP_PROP_FOURCC, -1);
	//grabFrames(&cap);
	if (_videoURI == "DIRECT_LINK")
	{
		_videoURI = "http://"CLIENT_IP_ADDRESS":8080/screen.mjpeg";
	}
	if (_videoURI == "CAMERA_LINK")
	{
		cap.open(0);
	}
	else
	{
		cap.open(_videoURI.c_str());
	}

	//_beginthread(grabFrames(&cap), 0, NULL);
	ALTIA_LOG_INFO("Opening Stream...");// %s\n\n", _videoURI.c_str());
	HBITMAP frameBitmap = NULL;
	
	HWND _activeWindow = FindWindow(NULL, "model_AUTOLITE_v39_castdemo_01");
	HDC hDC = GetDC(_activeWindow);
	HDC frameDC = CreateCompatibleDC(hDC);
	SetStretchBltMode(hDC, HALFTONE);

	cap.grab();
	cap >> frame; // get a new frame from source
	IplImage img(frame);
	
	while (true)
	{
		cap.grab();
		cap >> frame;
		if (!frame.empty())
		{
			img = frame;
			try
			{
				frameBitmap = ConvertIplImage2HBITMAP(&img); 

				SelectObject(frameDC, frameBitmap);
				/* this reflects the offset/width/height of the cart. coord system located in the DSN */
				/* img.height+20 is to crop the entire device screen into the demo screen */
				//StretchBlt(hDC, 264, 0, 270, 480, frameDC, 0, 0, img.width, img.height+20, SRCCOPY);
				//printf("size: %i x %i", img.width, img.height);
				/* Our push frame function into the dll that will feed the altiaRedraw event */
				PushFrame(img.imageData);
				/* Need to delete this reference or else HUGE memory leak! */
				DeleteObject(frameBitmap);
			}
			catch (...){}
		}
	}

	SelectObject(frameDC, frameBitmap);
	DeleteDC(frameDC);
	DeleteDC(hDC);

}
void AMediaRenderer::playVideo(std::string videoURI)
{
	_videoURI = videoURI;
	_beginthread(pMovie, 0, NULL);
}
NPT_Result AMediaRenderer::OnSetAVTransportURI(PLT_ActionReference& action)
{
	return NPT_SUCCESS;
}
NPT_Result AMediaRenderer::OnAction(PLT_ActionReference &action, const PLT_HttpRequestContext& context)
{

	/* parse the action name */
	NPT_String name = action->GetActionDesc().GetName();
	
	if (name == "GetProtocolInfo")
	{
		NPT_String type = "";
		ALTIA_LOG_INFO("%s Action Received: %s = %s", context.GetRequest().GetMethod(), name, type);
	}
	// default implementation is using state variable
	if (name == "SetAVTransportURI")
	{
		NPT_String uri;
		NPT_CHECK_WARNING(action->GetArgumentValue("CurrentURI", uri));

		NPT_String metadata;
		NPT_CHECK_WARNING(action->GetArgumentValue("CurrentURIMetaData", metadata));

		PLT_Service* serviceAVT;
		NPT_CHECK_WARNING(FindServiceByType("urn:schemas-upnp-org:service:AVTransport:1", serviceAVT));

		// update service state variables
		serviceAVT->SetStateVariable("AVTransportURI", uri);
		serviceAVT->SetStateVariable("AVTransportURIMetaData", metadata);
		ALTIA_LOG_INFO("\nURI : %s \nMeta Data: %s \n\nServiceAVT: %s\n", uri, metadata, serviceAVT->GetServiceType());

		playVideo(uri.GetChars());

	}
	NPT_COMPILER_UNUSED(context);
	// other actions rely on state variables
	NPT_CHECK_LABEL_WARNING(action->SetArgumentsOutFromStateVariable(), failure);

	return NPT_SUCCESS;

failure:
	action->SetError(401, "No Such Action.");
	return NPT_FAILURE;

}
/**/
void AMediaRenderer::initMediaRenderer()
{

}

AMediaRenderer::~AMediaRenderer()
{
	
}
