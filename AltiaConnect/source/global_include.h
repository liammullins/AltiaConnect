#include "altia.h"
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

/* Custom TYPEDEFS */
typedef std::string AString;

/* Global DEFINES */
#define SERVER_NAME "Altia Connect_v2"
#define SERVER_GUID "41714-41714-41714-41714"
#define DEBUG_CONSOLE_VISIBLE_LINE "\n=====================================================\n"
//29.97
#define ALTIA_FRAME_RATE 20

