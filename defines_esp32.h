#pragma once

// SPI pins (e.g. for TFT, SD card)
#define SPI_BUS   SPI
#define SPI_MISO  -1
#define SPI_MOSI  23
#define SPI_SCK   18

// TFT pins (in addition to SPI)
#define TFT_CS		19
#define TFT_RST   21
#define TFT_DC    22

// SD card pins (in additon to SPI)
#define SD_CS		  -1

// I2C pins (e.g. for IO expander)
#define I2C_SCL		-1
#define I2C_SDA		-1

// Speaker pin
#define SPEAKER_PIN   -1
