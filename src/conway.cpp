/*
 * conway.cpp
 *
 * Runs Conway's Game of Life simulation forever.
 *
 * Bryant Pong
 * 12/6/20
 */
#include "GridWorld.h"
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  // Ensure user specified a valid file to load and size
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <world to load> <# rows> <# cols>"
      << std::endl;
    return -1;
  }

  // Process out world rows and columns
  const size_t numRows = atoi(argv[2]);
  const size_t numCols = atoi(argv[3]);
  const std::string worldName(argv[1]);

  // Populate world
  GridWorld world(numRows, numCols);
  const bool loadSuccess = world.loadWorld(worldName);
  if (!loadSuccess) {
    std::cerr << "ERROR: Unable to load world: " << worldName << std::endl;
    return -1;
  }

  // Track number of iterations run
  long long unsigned int iter = 0;

  // Play the game of life until the world is empty
  while (world.NumAlive() > 0) {
    world.DisplayWorld();
    world.GameOfLifeIteration();
    ++iter;

    // Sleep half a second to avoid thrashing
    usleep(500000);
  }

  std::cout << "Game of Life completed after: " << iter << " iterations" <<
    std::endl;

  return 0;
}
