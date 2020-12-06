#ifndef __GRIDWORLD_H__
#define __GRIDWORLD_H__
/*
 * GridWorld.h
 *
 * Class definition of a Grid World used to run Conway's Game of Life.
 *
 * Bryant Pong
 * 12/6/20
 */
#include <cstddef> // size_t definition
class GridWorld {
public:
  GridWorld(const size_t rows, const size_t cols);
  ~GridWorld();

  /**
   * @brief Computes the number of alive cells on the board.
   * @return size_t: Number of alive cells
   */
  size_t NumAlive() const;

  //! Set the specified cell to alive (true)
  bool SetAlive(const size_t row, const size_t col);
  bool SetDead(const size_t row, const size_t col);
  bool IsAlive(const size_t row, const size_t col) const;

  /**
   * @brief Computes the number of neighbors (wrapping around to the other side
   * of the world if needed) to the cell specified at [row, col].
   *
   * @param row, col: Row and Column of the cell to compute neighbors of.
   */
  size_t NumLiveNeighbors(const long int row, const long int col) const;

  /**
   * @brief Runs a single iteration of the Game of Life.
   */
  void GameOfLifeIteration() const;

  void DisplayWorld() const;

  // Accessors
  inline size_t GetRows() const { return rows_; }
  inline size_t GetCols() const { return cols_; }
  inline size_t GetSize() const { return size_; }
  inline bool  *GetBoard() const { return board_; }

private:
  // Make default constructor unaccessible because user needs to define size
  GridWorld() = delete;

  //! Number of rows of the world
  size_t rows_;

  //! Number of columns of the world
  size_t cols_;

  //! Total number of cells in the world
  size_t size_;

  //! Dynamically-allocated memory of the world
  bool *board_;
};
#endif
