#include "engine.h"


LOG_USE_TAG("engine")


#define SPI_MAX_TRANSFER_SIZE   4092


void gameSetup();
void gameLoop(float dt);
void postDraw(float dt);
void onCollision(const GameObjectCollision& coll);

DefaultEngine engine;
Game game;


void EngineSetup()
{
    engine.earlySetup();
    DelayTaskMs(1000);

    spi_host_device_t spiHost = SPI2_HOST;

#if defined(DISPLAY_TYPE_ST7735_SPI)
    ScreenST7735::Config screenCfg;
    ScreenST7735::initConfig(screenCfg);
    screenCfg.spiHost               = spiHost;
    screenCfg.spiMaxTransferSize    = SPI_MAX_TRANSFER_SIZE;
    screenCfg.pins.cs               = DISPLAY_CS;
    screenCfg.pins.dc               = DISPLAY_DC;
    screenCfg.pins.rst              = DISPLAY_RST;
    Screen* screen = new ScreenST7735(screenCfg);
#elif defined(DISPLAY_TYPE_ILI9341_8080)
    ScreenILI9341::Config screenCfg;
    ScreenILI9341::initConfig(screenCfg);
    screenCfg.pins.cs       = DISPLAY_CS;
    screenCfg.pins.dc       = DISPLAY_DC;
    screenCfg.pins.rst      = DISPLAY_RST;
    screenCfg.pins.wr       = DISPLAY_WR;
    screenCfg.pins.rd       = DISPLAY_RD;
    screenCfg.pins.dat[0]   = DISPLAY_DAT0;
    screenCfg.pins.dat[1]   = DISPLAY_DAT1;
    screenCfg.pins.dat[2]   = DISPLAY_DAT2;
    screenCfg.pins.dat[3]   = DISPLAY_DAT3;
    screenCfg.pins.dat[4]   = DISPLAY_DAT4;
    screenCfg.pins.dat[5]   = DISPLAY_DAT5;
    screenCfg.pins.dat[6]   = DISPLAY_DAT6;
    screenCfg.pins.dat[7]   = DISPLAY_DAT7;
    Screen* screen = new ScreenILI9341(screenCfg);
#else
    Screen* screen = new ScreenNull;
#endif

    DefaultEngine::SetupConfig cfg = {
        .game = &game,

        .appID = "mygame",

        .sdCardMountPoint = "/sdcard",
        .internalStorageMountPoint = "/storage",

        .screen = screen,

        .spiHost = spiHost,
        .spiMaxTransferSize = SPI_MAX_TRANSFER_SIZE,

        .pins = {
            .spiMISO    = SPI_MISO,
            .spiMOSI    = SPI_MOSI,
            .spiSCK     = SPI_SCK,

            .sdCardCS   = SD_CS,

            .speaker    = SPEAKER_PIN
        }
    };

    //engine.setPrintFrameStatistics(true);
    engine.setup(&cfg);

    game.setCollisionCallback(&onCollision);

    LogInfo("Running gameSetup()...");
    gameSetup();
    LogInfo("Finished gameSetup().");

    LogInfo("Running main loop...");
}

void EngineLoop()
{
    engine.doFrame(&gameLoop, &postDraw);
}


MINTGGGAMEENGINE_STARTUP_CODE()
