#include "engine.h"


// TFT-Display
SPIClass tftSPI = SPIClass(HSPI);
Adafruit_ST7735 tft = Adafruit_ST7735(&tftSPI, TFT_CS, TFT_DC, TFT_RST); // SPI, CS, DC, RST

// Basisspiel
ScreenST7735 screen(&tft);
Game game;


// In der Sketchdatei zu definieren!
void gameSetup();
void gameLoop(float dt);
void onCollision(const GameObjectCollision& coll);


void setup() {

  // ********** PERIPHERAL SETUP **********

  Serial.begin(115200);
  
  Wire.begin();

  tftSPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS); // SCK, MISO, MOSI, CS

  // SD-Karte initialisieren (falls vorhanden)
  if (SD_CS >= 0) {
    if (!SD.begin(SD_CS)) {
      Serial.println("SD init failed.");
      while (true);
    }
  }

  // Engine starten
  screen.begin();
  game.begin(screen);
  game.audio().begin(SPEAKER_PIN);
  game.input().begin(10);


  // ********** GAME SETUP **********

  // Funktion festlegen, die bei Kollision zweiter GameObject aufgerufen wird
  game.setCollisionCallback(onCollision);

  gameSetup();
}

void loop() {
  // ********** GAME LOGIC **********

  // Vergangene Zeit seit letztem Frame berechnen (delta time, in Sekunden)
  float dt = game.getFrameTime() * 1e-3f;

  gameLoop(dt);

  game.checkCollisions(); // Kollisionsprüfung
  game.draw(); // GameObjects zeichnen
  game.sleepNextFrame(); // Warten bis zum nächsten Frame
}
