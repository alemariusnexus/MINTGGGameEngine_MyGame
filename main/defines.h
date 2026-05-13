#pragma once

#ifdef CONFIG_IDF_TARGET_ESP32C3
#   include "defines_esp32c3.h"
#elif defined(CONFIG_IDF_TARGET_ESP32)
#   include "defines_esp32.h"
#else
#   error Unknown ESP32 device for defines.h!
#endif
