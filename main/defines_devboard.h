#pragma once

// SPI pins (e.g. for display, SD card)
#define SPI_MISO    -1
#define SPI_MOSI    23
#define SPI_SCK     18

// SD card pins (in additon to SPI)
#define SD_CS	    -1

// I2C pins (e.g. for IO expander)
#define I2C_SCL		-1
#define I2C_SDA	    -1

// Speaker pin
#define SPEAKER_PIN -1

// Display type that's used
#define DISPLAY_TYPE_ST7735_SPI
//#define DISPLAY_TYPE_ILI9341_8080

// Display pin configuration (depending on type used)
#if defined(DISPLAY_TYPE_ST7735_SPI)
#   define DISPLAY_CS   19
#   define DISPLAY_DC   22
#   define DISPLAY_RST  21
#elif defined(DISPLAY_TYPE_ILI9341_8080)
#   define DISPLAY_CS   21
#   define DISPLAY_DC   19
#   define DISPLAY_RST  22
#   define DISPLAY_WR   18
#   define DISPLAY_RD   -1
#   define DISPLAY_DAT0 23
#   define DISPLAY_DAT1 17
#   define DISPLAY_DAT2 16
#   define DISPLAY_DAT3 15
#   define DISPLAY_DAT4 14
#   define DISPLAY_DAT5 25
#   define DISPLAY_DAT6 26
#   define DISPLAY_DAT7 27
#endif
