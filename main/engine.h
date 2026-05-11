#pragma once

#include <MINTGGGameEngine.h>

#include "defines.h"
#include "audio.h"
#include "images.h"


using namespace MINTGGGameEngine;

using namespace std::string_literals;


#ifdef ARDUINO
extern ScreenST7735 screen;
#elif defined(ESP_PLATFORM)
extern ScreenHAGL screen;
#endif

extern Game game;
