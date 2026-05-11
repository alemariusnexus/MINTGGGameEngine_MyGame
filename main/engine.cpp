#include "engine.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#ifdef MINTGGGAMEENGINE_PORT_ESPIDF
#include "esp_heap_caps.h"
#include "nvs_flash.h"

#include <hagl.h>
#include <hagl_hal.h>
#endif


#define PRINT_FRAME_STATISTICS


LOG_USE_TAG("engine")


#ifdef MINTGGGAMEENGINE_PORT_ARDUINO
SPIClass spi = SPIClass(SPI_BUS);
Adafruit_ST7735 tft = Adafruit_ST7735(&spi, TFT_CS, TFT_DC, TFT_RST);
ScreenST7735 screen(tft);
#elif defined(MINTGGGAMEENGINE_PORT_ESPIDF)
ScreenHAGL screen;
#endif


Game game;


void gameSetup();
void gameLoop(float dt);
void onCollision(const GameObjectCollision& coll);


#ifdef MINTGGGAMEENGINE_PORT_ESPIDF

void HeapCapsAllocFailedHook (
    size_t reqSize,
    uint32_t caps,
    const char *funcName
) {
    LogError(TAG, "Failed to allocate %u bytes with 0x%X caps (%s)",
        static_cast<unsigned int>(reqSize), caps, funcName);
}

#endif


static void EngineSetup()
{
#ifdef MINTGGGAMEENGINE_PORT_ESPIDF
    heap_caps_register_failed_alloc_callback(&HeapCapsAllocFailedHook);
#endif

    TimerInit();

#ifdef MINTGGGAMEENGINE_PORT_ARDUINO
    Serial.begin(115200);
#elif defined(MINTGGGAMEENGINE_PORT_ESPIDF)
    esp_err_t nvsRes = nvs_flash_init();
    if (nvsRes == ESP_ERR_NVS_NO_FREE_PAGES || nvsRes == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        nvsRes = nvs_flash_init();
    }
    if (nvsRes != ESP_OK) {
        LogError(TAG, "Error initializing NVS: %s", esp_err_to_name(nvsRes));
    }
#endif

    LogInfo(TAG, "Initializing screen...");
    screen.begin();
    game.begin(screen);

    LogInfo(TAG, "Initializing audio...");
    game.audio().begin(SPEAKER_PIN);

    LogInfo(TAG, "Initializing input...");
    game.input().begin();

    LogInfo(TAG, "Initializing network...");
    game.network().begin();

    LogInfo(TAG, "Initializing storage...");
    StorageEngine::getInstance().begin();

    game.setCollisionCallback(&onCollision);

#ifdef MINTGGGAMEENGINE_PORT_ARDUINO
    spi.begin(SPI_SCK, SPI_MISO, SPI_MOSI, TFT_CS);
#endif

#ifdef MINTGGGAMEENGINE_PORT_ESPIDF
#ifdef MOUNT_SPIFFS
	LogInfo(TAG, "Mounting SPIFFS...");
    StorageEngine::getInstance().mountSPIFFS();
#endif
#endif

	if (SD_CS >= 0) {
		LogInfo(TAG, "Mounting SD card...");
		bool sdMountOk = false;	
#ifdef MINTGGGAMEENGINE_PORT_ESPIDF
		sdMountOk = StorageEngine::getInstance().mountSDCard (
			"",
			static_cast<spi_host_device_t>(CONFIG_MIPI_DISPLAY_SPI_HOST),
			SD_CS
			);
#elif defined(MINTGGGAMEENGINE_PORT_ARDUINO)
		sdMountOk = StorageEngine::getInstance().mountSDCard (
			"",
			spi,
			SD_CS
			);
#endif
		if (!sdMountOk) {
			LogError(TAG, "Error mounting SD card. Trying to continue anyway...");
		}
	}

    LogInfo(TAG, "Running gameSetup()...");
    gameSetup();
    LogInfo(TAG, "Finished gameSetup().");

    LogInfo(TAG, "Running main loop...");
}

static void EngineLoop()
{
    game.beginFrame();

    float dt = game.getFrameTime() * 1e-3f;

    timer_ustick_t gameLoopTime = TimerGetTickcountUs();
    gameLoop(dt);

    timer_ustick_t checkCollTime = TimerGetTickcountUs();
    game.checkCollisions(); // Kollisionsprüfung

    timer_ustick_t drawTime = TimerGetTickcountUs();
    Game::DrawStats drawStats;
    game.draw(&drawStats); // GameObjects zeichnen

    timer_ustick_t endTime = TimerGetTickcountUs();

#ifdef PRINT_FRAME_STATISTICS
    LogInfo(TAG,
        "Frame Stats   -   total: %uus   -   gameLoop: %uus, checkCollisions: %uus, draw: %uus   -   "
        "fill: %uus, objs: %uus, colls: %uus, rays: %uus, texts: %uus, comm: %uus",

        (uint32_t) (endTime-gameLoopTime),

        (uint32_t) (checkCollTime-gameLoopTime),
        (uint32_t) (drawTime-checkCollTime),
        (uint32_t) (endTime-drawTime),

        drawStats.timeFillUs,
        drawStats.timeObjectsUs,
        drawStats.timeCollidersUs,
        drawStats.timeRaysUs,
        drawStats.timeTextsUs,
        drawStats.timeCommitUs
        );
#endif

    game.endFrame();

    game.sleepNextFrame(); // Warten bis zum nächsten Frame
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
