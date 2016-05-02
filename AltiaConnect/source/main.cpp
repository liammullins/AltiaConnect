/*
#define NOMINMAX
#include <algorithm>
namespace Gdiplus
{
	using std::min;
	using std::max;
};
*/
#include "global_include.h"
#include "AMulticastServer.h"
#include <stdio.h>
#include <process.h>
#include <fstream>
//#include <atlimage.h>//used for saving bitmap
#include "altiaEx.h"
#include "altia.h"


/*********************************************************************
	Namespaces
*********************************************************************/
using namespace cv;

/*********************************************************************
	Publics (most will be moved or deleted from here)
*********************************************************************/
AtConnectId connID;
AMulticastServer *multiCastServer;
extern bool processing;
int xpos, ypos;
bool haveBoth = false;
WSADATA wsa;
SOCKET touchClientSocket, streamClientSocket;
struct sockaddr_in server;
char *message, server_reply[2000];
int recv_size;
/* Create extern reference so we can push directly to the draw opperation */
//PushFrameToDll pushFrameToAltia;
/* Library handles (to be freed) */
HINSTANCE altiaLibHandle = NULL;
static unsigned long handRaster = 0;
unsigned char *currentFrame = NULL;

/*********************************************************************
	Functions
*********************************************************************/
static AltiaEx_Brush_type single = {
	0, 0, 0xffff
};
static AltiaEx_Brush_type wide = {
	5, 0, 0xffff
};
static AltiaEx_Pattern_type solid = {
	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff
};
//extern void PushFrame(HBITMAP frame);
static int hand_bits[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x800000ff, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x00,
	0x800000ff, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x800000ff, 0x00, 0x800000ff, 0x00, 0x800000ff, 0x00,
	0x00, 0x800000ff, 0x800000ff, 0x00, 0x800000ff, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x800000ff, 0x00, 0x800000ff, 0x00, 0x800000ff, 0x00,
	0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x800000ff, 0x00,
	0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x00,

	0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x800000ff, 0x00,
	0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x00, 0x800000ff, 0x00,

	0x00, 0x00, 0x00, 0x800000ff, 0x00, 0x800000ff, 0x800000ff, 0x00,
	0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x800000ff, 0x00, 0x800000ff,

	0x00, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x00,
	0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x800000ff, 0x00, 0x800000ff,

	0x00, 0x800000ff, 0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x00,
	0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x800000ff,

	0x800000ff, 0x00, 0x800000ff, 0x00, 0x800000ff, 0x00, 0x00, 0x00,
	0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x800000ff,

	0x800000ff, 0x00, 0x00, 0x800000ff, 0x800000ff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x800000ff,

	0x00, 0x800000ff, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x800000ff, 0x00,

	0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x800000ff, 0x00,

	0x00, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x800000ff, 0x00,

	0x00, 0x00, 0x00, 0x00, 0x800000ff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x800000ff, 0x00, 0x00,

	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x800000ff, 0x00, 0x00
};
/*********************************************************************
Save Bitmap to file function (pulled source)
*********************************************************************/
/*

Commented out - this was a function to save the bitmap 
on the other side to make sure we are receiving all frames 
from the client

void SaveBitmapToFile(HBITMAP hbm, LPCTSTR szFileName, BOOL bAutoDelete = FALSE)
{
	PICTDESC pd = { sizeof(pd), PICTYPE_BITMAP };
	pd.bmp.hbitmap = hbm;

	CComPtr<IPicture> pPict = NULL;
	CComPtr<IStream>  pStrm = NULL;
	LONG cbSize = 0;

	BOOL res = FALSE;

	res = SUCCEEDED(::CreateStreamOnHGlobal(NULL, TRUE, &pStrm));
	res = SUCCEEDED(::OleCreatePictureIndirect(&pd, IID_IPicture, bAutoDelete, (void**)&pPict));
	res = SUCCEEDED(pPict->SaveAsFile(pStrm, TRUE, &cbSize));

	if (res)
	{
		// rewind stream to the beginning
		LARGE_INTEGER li = { 0 };
		pStrm->Seek(li, STREAM_SEEK_SET, NULL);

		// write to file
		HANDLE hFile = ::CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
		if (INVALID_HANDLE_VALUE != hFile)
		{
			DWORD dwWritten = 0, dwRead = 0, dwDone = 0;
			BYTE  buf[4096];
			while (dwDone < cbSize)
			{
				if (SUCCEEDED(pStrm->Read(buf, sizeof(buf), &dwRead)))
				{
					::WriteFile(hFile, buf, dwRead, &dwWritten, NULL);
					if (dwWritten != dwRead)
						break;
					dwDone += dwRead;
				}
				else
					break;
			}

			_ASSERT(dwDone == cbSize);
			CloseHandle(hFile);
		}
	}
}
*/
/*********************************************************************
	This is the function that sync's altia design
	drawing with our application
*********************************************************************/
AltiaEx_GraphicState_type gs;
AltiaEx_Coord_type coords[16];
AltiaEx_Rect_type rect;

int DrawFrame(int objId, void *win, unsigned long mydc,
			  int left, int bottom,
			  int right, int top, int x, int y, int bxoff, int byoff,
			  AltiaEx_Transform_type *trans)
{
	gs.foreground = 0xFFFFFF;
	gs.background = 0xFFFFFF;
	gs.pattern = solid;
	gs.brush = single;
	rect.x0 = 0;
	rect.y0 = 0;
	rect.x1 = 298 - 1;
	rect.y1 = 480 - 1;
	altiaExRectDraw(objId, win, mydc, &gs, &rect, 1, trans);
	//ALTIA_LOG_INFO("Drew Rect? obj: %i",objId);
	if (currentFrame != NULL)
	{
		handRaster = altiaExCreateRaster(298, 480, 24, (298*3), NULL, 0xffffff, 0xff, 0xff00, 0xff0000, 0xff000000, currentFrame, NULL);
		if (handRaster != 0)
		{
			altiaExRasterDraw(objId, currentFrame, mydc, &gs, 298, 480, handRaster, trans);
			ALTIA_LOG_INFO("Frame Drawn");
		}
		return 1;
	}
	return 0;
}

/*********************************************************************
	Init process called within model
*********************************************************************/
extern "C"
{
	int initialize(int objId)
	{


		if (altiaExRegCallback(objId, ALT_REDRAW_CALLBACK,
			(AltiaDACallBkFunc)DrawFrame) == 0)
		{
			ALTIA_LOG_INFO("Redraw setup failed : %s\n", altiaExGetErrorString());
			return 0;
		}

		ALTIA_LOG_INFO("Everything Loaded! DAO Id: %i ",objId);
		return 1;
	}
}
/*********************************************************************
Shared function that passes the current frame
to the altia drawing process
*********************************************************************/
void PushFrame(char* frame)
{
	/* only update if the image is not NULL */
	if (frame != NULL)
	{
		/* 
		   I believe this could have some unintended consequences
		*/
		currentFrame = (unsigned char *)frame;
		//altiaEx
		//SaveBitmapToFile(frame, "liams_test.bmp", true);
	}
	else
	{
		ALTIA_LOG_INFO("Received Frame Error %s\n", altiaExGetErrorString());

	}

}


void hmiProcess(void)
{
	int event_count, i;
	AltiaCharType * event_name = NULL;
	AltiaEventType event_value;
	/* get our pending events*/
	event_count = altiaPending();
	/* run through our events and dispatch */
	for (i = 0; i < event_count; i++)
	{
		altiaNextEvent((AltiaCharType **)(&event_name), &event_value);
		AtDispatchEvent(connID, event_name, event_value);
	}
	xpos = -1;
	ypos = -1;
}

/*********************************************************************
	Receive data in multiple chunks by checking a non-blocking socket
	Timeout in seconds
	*********************************************************************/
int recv_timeout(int timeout)
{
	int size_recv, total_size = 0;
	struct timeval begin, now;
	char chunk[1024];
	double timediff;

	while (1)
	{

		memset(chunk, 0, 1024);  //clear the variable
		if ((size_recv = recv(streamClientSocket, chunk, 1024, 0)) < 0)
		{
			//if nothing was received then we want to wait a little before trying again, 0.1 seconds
			Sleep(100);
			//usleep(100000);
		}
		else
		{
			total_size += size_recv;
			ALTIA_LOG_INFO("%s", chunk);
			//reset beginning time
			//gettimeofday(&begin, NULL);
		}
	}

	return total_size;
}
/*********************************************************************
	Receieve image stream test routine
	*********************************************************************/
void receiveImage(void *param)
{

	int FileCounter = 0;
	bool flg = true;
	char * fileComplete;
	char * filesizeBuffer;
	FILE *temp;
	WSADATA wsa;
	SOCKET new_socket = NULL;
	struct sockaddr_in server, client;
	int stSize;
	char *message;
	u_long iMode = 1;

	/* Create our socket instances */
	ioctlsocket(new_socket, FIONBIO, &iMode);
	ioctlsocket(streamClientSocket, FIONBIO, &iMode);
	ALTIA_LOG_INFO("Initialising Winsock...");
	/* Make sure that winsock is init'ed - probably don't need this */
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		ALTIA_LOG_INFO("Failed. Error Code : %d", WSAGetLastError());
		return;
	}

	ALTIA_LOG_INFO("Initialised.\n");

	//Create a socket
	if ((streamClientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		ALTIA_LOG_INFO("Could not create socket : %d", WSAGetLastError());
	}

	ALTIA_LOG_INFO("Socket created.\n");
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(41715);

	//Bind
	if (bind(streamClientSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		ALTIA_LOG_INFO("Bind failed with error code : %d", WSAGetLastError());
	}

	ALTIA_LOG_INFO("Bind done\n");

	//Listen to incoming connections
	listen(streamClientSocket, 3);

	//Accept and incoming connection
	ALTIA_LOG_INFO("Waiting for incoming connections...");

	stSize = sizeof(struct sockaddr_in);
	new_socket = accept(streamClientSocket, (struct sockaddr *)&client, &stSize);
	if (new_socket == INVALID_SOCKET)
	{
		ALTIA_LOG_INFO("accept failed with error code : %d", WSAGetLastError());
	}

	ALTIA_LOG_INFO("Connection accepted");


	//while (true)
	//{
	bool wait = true;
	char    recvbuff[1024 * 600];/* allocate ~600kb - streaming in bigger chunks won't happen */
	int     ret, nLeft, idx;
	ret = 1;/* init with 1 to get our loop going */
	nLeft = 0;
	idx = 0;
	ALTIA_LOG_INFO("\nAccepting Data...\n");
	/*  this is our check for data coming in. As long as it isn't 0, keep it coming
		probaby need to check for buffer overrun here as things mature
		*/
	while (ret > 0)
	{
		ret = recv(new_socket, recvbuff, sizeof(recvbuff), 0);
		idx += ret;
		ALTIA_LOG_INFO("\nrecv: %i\ntotal:%i\n", ret, idx);

		if (ret == SOCKET_ERROR || ret == 0)
		{
			ALTIA_LOG_INFO("\nDone : %d\n", WSAGetLastError());
			//Sleep(2000);
			recvbuff[idx] = '\0';
			// Error handler
			break;
		}
	}

	std::ofstream("ss.webp", std::ios::binary).write(recvbuff, idx);
	closesocket(streamClientSocket);
	closesocket(new_socket);
	ALTIA_LOG_INFO("\n\nss.webp saved\n\n");
}

/*********************************************************************
	Get HINST, and then ProcAddress of PushFrame
	*********************************************************************/
HINSTANCE loadAltiaCastLibrary(/*std::string dllName*/)
{

	HINSTANCE hinstDll = LoadLibrary("AltiaMediaRenderer.dll");
	ALTIA_LOG_INFO("Loading AltiaConnect Library...\n");

	if (!hinstDll)
	{
		ALTIA_LOG_INFO("Could not load library\n");
		return NULL;
	}

	ALTIA_LOG_INFO("AltiaMediaRenderer Library Loaded\n");
	/* Get the process address */
	//pushFrameToAltia = (PushFrameToDll)GetProcAddress(hinstDll, "PushFrame");
	/* Let's check to see if we actually got the
	*  process Address or notify
	
	if (pushFrameToAltia == NULL)
	{
		ALTIA_LOG_INFO("Could not load pushFrame function\n");
	}
	else
	{
		ALTIA_LOG_INFO("PushFrame Function Loaded\n");
	}*/
	/*  return even if the getprocess returns NULL - can still declare a valid hinst later
		and need the handle to release the library
		*/
	return hinstDll;

}

/*********************************************************************
	Callback for phone/radio click
	*********************************************************************/
void on_PhoneClicked(AtConnectId connectId, char *name,
	AltiaEventType eventValue, AtPointer data)
{
	/* on cleek */
	std::string anim_name = name;
	if (eventValue == 1 && anim_name == "ms_phone_icon_clicked")
	{
		/* Grab our handle from the loaded dll here, so we can release later */
		//altiaLibHandle = loadAltiaCastLibrary();
		/* kick off the server */
		multiCastServer = new AMulticastServer();
		multiCastServer->initMCServer(SERVER_NAME, SERVER_GUID);
		ALTIA_LOG_INFO("\n=====================================================\n"
			"Started Server:\n          "
			"Server Name: %s \n          "
			"GUID: %s\n=====================================================\n", SERVER_NAME, SERVER_GUID);

		//_beginthread(receiveImage, 0, NULL);
		//Connect to remote server

	}
	if (eventValue == 1 && anim_name == "ms_radio_btn_down")
	{
		//Can attach some logic to the radio button

	}

}

/*********************************************************************
   The method that sends the touch event to the device. The calculation
   includes room for scaling from the device
*********************************************************************/
void sendTouch()
{

	/* convert our coordinates over and reset, just in case something happens with the socket,
	   we can continue with correct next touch
	   */
	int fx = (xpos * ASPECT_RATIO_CALC);
	int fy = (ypos * ASPECT_RATIO_CALC);
	/* reset */
	xpos = -1;
	ypos = -1;
	/* create coordinates */
	char temp[64] = { 0 };

	sprintf_s(temp, "%i %i", fx, fy);
	/* Let's change the 's' socket name to something else more descriptive */
	touchClientSocket = socket(AF_INET, SOCK_STREAM, 0);
	/* Make sure socket is valid first */
	if (touchClientSocket == INVALID_SOCKET)
	{
		ALTIA_LOG_INFO("\nCould not create socket : %d\n", WSAGetLastError()); return;
	}
	/* Set our struct with the address information */
	server.sin_addr.s_addr = inet_addr(CLIENT_IP_ADDRESS);
	server.sin_family = AF_INET;
	server.sin_port = htons(41714);
	/* Perform the actual sending over the socket, to the android client */
	if (connect(touchClientSocket, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		ALTIA_LOG_INFO("Connect failed %d", WSAGetLastError()); return;
	}

	if (send(touchClientSocket, temp, strlen(temp), 0) < 0)
	{
		ALTIA_LOG_INFO("Send failed %d", WSAGetLastError()); return;
	}

	closesocket(touchClientSocket);
	ALTIA_LOG_INFO("\n\Touch Sent:\nX: %i\nY: %i\n", fx, fy);

}
/*********************************************************************
	Rename, as this is the touch event received from the cart coord
	system
*********************************************************************/
void touchEvent(AtConnectId connectId, char *name,
	AltiaEventType eventValue, AtPointer data)
{
	std::string test(name);
	/* get both coordinates before we can continue (one at a time) */
	if (test == "x_release")
	{
		xpos = eventValue;
	}
	if (test == "y_release")
	{
		ypos = eventValue;
	}
	/* we have both coordinates - fire the touch event */
	if (xpos > -1 && ypos > -1)
	{
		//ALTIA_LOG_INFO("Current X/Y: %i %i\n", xpos, ypos);
		sendTouch();
	}

}

/*********************************************************************
	AddCallbacks and init logic here
*********************************************************************/
void initMainLogic(void)
{
	//initialize(3007);
	/* phone button - start server */
	AtAddCallback(connID, "ms_radio_btn_down", (AtCallbackProc)on_PhoneClicked, NULL);
	AtAddCallback(connID, "ms_phone_icon_clicked", (AtCallbackProc)on_PhoneClicked, NULL);
	AtAddCallback(connID, "x_release", (AtCallbackProc)touchEvent, NULL);
	AtAddCallback(connID, "y_release", (AtCallbackProc)touchEvent, NULL);
	xpos = -1;
	ypos = -1;
	//Init Winsock? Maybe not necessary..
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		ALTIA_LOG_INFO("Failed. Error Code : %d", WSAGetLastError());
	}

}

/*********************************************************************
	Main Entry and stimulus processing
*********************************************************************/
void main(void)
{
	/* Open Altia connection */
	connID = AtOpenConnection(NULL, NULL, NULL, NULL);
	altiaCacheOutput(true);
	/* Start checking for stimulus after hooking up Callbacks */
	if (connID == 0)
	{
		/* Kick off our initialization */
		initMainLogic();
		while (true)
		{
			hmiProcess();
			Sleep(5);
		}
	}
	else
	{
		ALTIA_LOG_INFO("issue");
		Sleep(2000);
	}

	/* Free the library */
	//FreeLibrary(altiaLibHandle);
	/* Close connection to GUI.  For DeepScreen this frees resources */
	altiaDisconnect();
	exit(0);

}
