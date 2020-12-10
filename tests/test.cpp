/*
 * test.cpp
 *
 * Unit tests to ensure the Game of Life's rules are followed.  Requires the
 * "catch.hpp" test library.
 *
 * Bryant Pong
 * 12/6/20
 */

// Tell Catch to provide its own "main" function
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "GridWorld.h"

SCENARIO("a grid is created", "[GridWorld]") {
  GIVEN("A gridworld is constructed with size 5x6") {
    THEN("It is constructed without errors") {
      REQUIRE_NOTHROW(GridWorld(5, 6));
    }
  }

  GIVEN("A gridworld is constructed with size 5x6") {
    GridWorld world(5, 6);
    THEN("It is initialized with the correct arguments") {
      REQUIRE(world.GetRows()  == 5);
      REQUIRE(world.GetCols()  == 6);
      REQUIRE(world.GetSize()  == 30);
      REQUIRE(world.GetBoard() != nullptr);
      REQUIRE(world.NumAlive() == 0);
    }
  }

  GIVEN("An empty gridworld of size 3x4") {
    GridWorld world(3, 4);
    WHEN("A dead cell is set alive") {
      const bool ret = world.SetAlive(1, 1);
      THEN("The cell is now alive") {
        REQUIRE(ret                 == true);
        REQUIRE(world.IsAlive(1, 1) == true);
        REQUIRE(world.NumAlive()    == 1);
      }
    }
    WHEN("A cell off the grid is set alive") {
      const bool ret = world.SetAlive(9001, 9001);
      THEN("The cell is not set") {
        REQUIRE(ret                       == false);
        REQUIRE(world.IsAlive(9001, 9001) == false);
        REQUIRE(world.NumAlive()          == 0);
      }
    }
    WHEN("An alive cell is set dead") {
      const bool ret1 = world.SetAlive(1, 1);
      const bool ret2 = world.SetDead(1, 1);
      THEN("The cell is dead") {
        REQUIRE(ret1                == true);
        REQUIRE(ret2                == true);
        REQUIRE(world.IsAlive(1, 1) == false);
        REQUIRE(world.NumAlive()    == 0);
      }
    }
  }
}

// Game of Life Rule Tests
SCENARIO("the game of life is run", "[GridWorld]") {
  GIVEN("a populated board") {
    GridWorld world(3, 1);
    world.SetAlive(0, 0);
    world.SetAlive(1, 0);
    world.SetAlive(2, 0);

    WHEN("the number of live neighbors are computed") {
      const size_t numLive1 = world.NumLiveNeighbors(0, 0);
      const size_t numLive2 = world.NumLiveNeighbors(1, 0);
      const size_t numLive3 = world.NumLiveNeighbors(2, 0);
      THEN("the number of live neighbors is correctly computed") {
        REQUIRE(numLive1 == 8);
        REQUIRE(numLive2 == 8);
        REQUIRE(numLive3 == 8);
      }
    }
  }

  GIVEN("a populated board") {
    GridWorld world(5, 5);
    world.SetAlive(1, 2);
    world.SetAlive(2, 2);
    world.SetAlive(3, 2);

    WHEN("a single iteration of game of life is run") {
      world.GameOfLifeIteration();
      THEN("the game of life rules are followed correctly") {
        for (size_t row = 0; row < world.GetRows(); ++row) {
          for (size_t col = 0; col < world.GetCols(); ++col) {
            if (((row == 2) && (col == 1)) ||
                ((row == 2) && (col == 2)) ||
                ((row == 2) && (col == 3)))
              REQUIRE(world.IsAlive(row, col) == true);
            else
              REQUIRE(world.IsAlive(row, col) == false);
          }
        }
      }
    }
  }
}
