#include "engine.h"

#include "images.h"


// Tags für GameObjects definieren. Dient z.B. dazu, die Art von
// GameObject zu definieren (z.B. Player, Enemy, Bullet, ...), und
// gezielt nach bestimmten GameObjects suchen zu können.
enum GameObjectTag {
};


void gameSetup() {
  // Wird nach dem Start der Engine aufgerufen (analog zu setup())
}

void gameLoop(float dt) {
  // Wird einmal pro Frame aufgerufen (analog zu loop())
}

void onCollision(const GameObjectCollision& coll) {
  // Wird aufgerufen, wenn zwei GameObjects miteinander kollidieren
}
