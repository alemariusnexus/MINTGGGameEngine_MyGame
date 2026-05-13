#include "engine.h"


LOG_USE_TAG("engine")


void gameSetup();
void gameLoop(float dt);
void onCollision(const GameObjectCollision& coll);

DefaultEngine engine;
Game game;


static void EngineSetup()
{
    DefaultEngine::SetupConfig cfg = {
        .game = &game,

        .sdCardMountPoint = "/sdcard",
        .internalStorageMountPoint = "/storage",

#ifdef MINTGGGAMEENGINE_PORT_ARDUINO
        .spiBase = &SPI_BUS,
#endif

        .pins = {
            .spiMISO = SPI_MISO,
            .spiMOSI = SPI_MOSI,
            .spiSCK = SPI_SCK,

            .screenCS = TFT_CS,
            .screenDC = TFT_DC,
            .screenRST = TFT_RST,

            .sdCardCS = SD_CS,

            .speaker = SPEAKER_PIN
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

static void EngineLoop()
{
    engine.doFrame(&gameLoop);
}



#ifdef MINTGGGAMEENGINE_PORT_ESPIDF

extern "C" {
void app_main()
{
    EngineSetup();
    for (;;) {
        EngineLoop();
    }
}
}

#elif defined(MINTGGGAMEENGINE_PORT_ARDUINO)

void setup()
{
    EngineSetup();
}

void loop()
{
    EngineLoop();
}

#endif
