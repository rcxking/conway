/*
 * conway.cpp
 *
 * Runs Conway's Game of Life simulation forever.
 *
 * Bryant Pong
 * 12/6/20
 */
#include "GridWorld.h"
#include <unistd.h>

int main(void) {
  // Populate world (TODO: Add function to allow user to load in a world)
  GridWorld world(5, 5);
  world.SetAlive(1, 2);
  world.SetAlive(2, 2);
  world.SetAlive(3, 2);
  world.SetAlive(2, 0);
  world.SetAlive(3, 1);

  for (;;) {
    world.DisplayWorld();
    world.GameOfLifeIteration();

    // Sleep half a second to avoid thrashing
    usleep(500000);
  }

  return 0;
}
