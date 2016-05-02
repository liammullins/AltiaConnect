#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\photo.hpp>
#include <opencv2\video.hpp>
#include <opencv2\features2d.hpp>
#include <opencv2\objdetect.hpp>
#include <opencv2\calib3d.hpp>
#include <opencv2\imgcodecs.hpp>
#include <opencv2\videoio.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\ml.hpp>
#include "debug_helper.h"

/*********************************************************************
	Custom typedefs
*********************************************************************/
typedef std::string AString;

/*********************************************************************
	Global Defines
*********************************************************************/
/*
	V1 - Prototype
	V2 - Zero config enabled, basic casting, and streaming to the openCV/ffmpeg libs
	V3 - Bi-directional touch enabled (messy and rough)
*/
#define SERVER_NAME "Altia Connect_V3"
#define SERVER_GUID "41714-41714-41714-41714"
#define DEBUG_CONSOLE_VISIBLE_LINE "\n=====================================================\n"
/* Define framerate */
#define ALTIA_FRAME_RATE 20
/* Direct connection (for now) to device running LiveScreen, or some screen share stream */
//"192.168.1.135"
//"192.168.80.198"
//"192.168.80.230"
#define CLIENT_IP_ADDRESS "192.168.1.128"
/* My Galaxy S4 reports a resolution of 1080x1920
   by converting the pixel coordinates over to a divisor of 4 (in this case), 
   our scaling is much more predictable, along with the touches and swipes
*/
#define ASPECT_RATIO_CALC 4