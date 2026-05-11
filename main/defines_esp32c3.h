#pragma once

// SPI pins (e.g. for TFT, SD card)
#define SPI_BUS     SPI
#define SPI_MISO    9
#define SPI_MOSI    10
#define SPI_SCK     8

// TFT pins (in addition to SPI)
#define TFT_CS	    20
#define TFT_RST     -1
#define TFT_DC      2

// SD card pins (in additon to SPI)
#define SD_CS	    21

// I2C pins (e.g. for IO expander)
#define I2C_SCL		7
#define I2C_SDA		6

// Speaker pin
#define SPEAKER_PIN 5

//#define MOUNT_SPIFFS
