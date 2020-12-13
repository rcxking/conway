/*
 * GridWorld.cpp
 *
 * Class implementation of a Grid World object used to run Conway's Game of
 * Life.
 *
 * Bryant Pong
 * 12/6/20
 */
#include "GridWorld.h"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// GridWorld::GridWorld()
GridWorld::GridWorld(const size_t rows, const size_t cols) :
  rows_(rows), cols_(cols), size_(rows_ * cols_) {
  board_ = new bool[size_];
  memset(board_, false, sizeof(bool) * size_);
}

// GridWorld::~GridWorld()
GridWorld::~GridWorld() {
  // Deallocate board (if applicable)
  if (board_) {
    delete [] board_;
    board_ = nullptr;
  }
}

// size_t GridWorld::NumAlive()
size_t GridWorld::NumAlive() const {
  // Count the number of "true" (alive) cells
  size_t count = 0;

  for (size_t i = 0; i < size_; ++i) {
    if (board_[i])
      ++count;
  }
  return count;
}

// bool GridWorld::SetAlive()
bool GridWorld::SetAlive(const size_t row, const size_t col) {
  // Range checks
  if (row >= rows_ || col >= cols_)
    return false;

  board_[row * cols_ + col] = true;

  return true;
}

// bool GridWorld::SetDead()
bool GridWorld::SetDead(const size_t row, const size_t col) {
  // Range checks
  if (row >= rows_ || col >= cols_)
    return false;

  board_[row * cols_ + col] = false;

  return true;
}

// bool GridWorld::IsAlive()
bool GridWorld::IsAlive(const size_t row, const size_t col) const {
  // Range checks
  if (row >= rows_ || col >= cols_)
    return false;

  return board_[row * cols_ + col] == true;
}

// size_t GridWorld::NumLiveNeighbors()
size_t GridWorld::NumLiveNeighbors(const long int row, const long int col) const {
  size_t numLive = 0;

  for (long int y = row - 1; y <= row + 1; ++y) {
    for (long int x = col - 1; x <= col + 1; ++x) {
      // Skip examining current cell
      if ((x == col) && (y == row))
        continue;

      long int examineX = x;
      long int examineY = y;

      // Handle wraparound if needed
      if (examineX < 0)
        examineX += cols_;
      else if(examineX >= static_cast<long int>(cols_))
        examineX -= cols_;
      if (examineY < 0)
        examineY += rows_;
      else if (examineY >= static_cast<long int>(rows_))
        examineY -= rows_;

      if (board_[examineY * cols_ + examineX])
        ++numLive;
    }
  }

  return numLive;
}

// void GridWorld::GameOfLifeIteration()
void GridWorld::GameOfLifeIteration() const {
  // Temporary buffer for the iteration results
  bool *results = new bool[size_];
  memcpy(results, board_, sizeof(bool) * size_);

  for (size_t row = 0; row < rows_; ++row) {
    for (size_t col = 0; col < cols_; ++col) {
      const size_t numLiveNeighbors = NumLiveNeighbors(row, col);

      if (IsAlive(row, col)) {
        // (Underpopulation Rule) A live cell with < 2 live neighbors is dead
        if ((numLiveNeighbors < 2) || (numLiveNeighbors > 3))
          results[row * cols_ + col] = false;
      } else {
        // (Reproduction Rule) A dead cell with exactly 3 live neighbors is live
        if (numLiveNeighbors == 3)
          results[row * cols_ + col] = true;
      }
    }
  }

  // Copy the results back to original board
  memcpy(board_, results, sizeof(bool) * size_);

  delete [] results;
}

// void GridWorld::DisplayWorld()
void GridWorld::DisplayWorld() const {
  // Issue terminal control character to clear the screen
  printf("\x1b[2J");
  // Issue terminal control character to move cursor to first line
  printf("\x1b[H");

  for (size_t row = 0; row < rows_; ++row) {
    for (size_t col = 0; col < cols_; ++col) {
      if (board_[row * cols_ + col])
        std::cout << "1 ";
      else
        std::cout << "0 ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

// bool GridWorld::loadWorld()
bool GridWorld::loadWorld(const std::string &worldName) {
  // Ensure worldName file can be opened
  std::ifstream worldFile(worldName);
  if (!worldFile) {
    std::cerr << "ERROR: Unable to load file: " << worldName << " because of "
      "error: " << strerror(errno) << std::endl;
    return false;
  }

  // Read all characters in the file; halt if there's a non-0 or 1 character.
  std::vector<int> buffer;
  std::string nextLine;

  while (std::getline(worldFile, nextLine)) {
    for (size_t i = 0; i < nextLine.length(); ++i) {
      // Ensure only 0/1 characters are present
      if ((nextLine[i] != '0') && (nextLine[i] != '1')) {
        std::cerr << "ERROR: non-0/1 character found in line: " << nextLine <<
          std::endl;
        return false;
      }
      buffer.push_back(static_cast<int>(nextLine[i]) - '0');
    }
  }

  // Ensure number of characters read is equal to world size
  if (buffer.size() != size_) {
    std::cerr << "ERROR: buffer size of: " << buffer.size() << " does not "
      "match size_: " << size_ << std::endl;
    return false;
  }

  // Copy data over
  for (size_t i = 0; i < buffer.size(); ++i) {
    board_[i] = buffer[i];
  }

  return true;
}
