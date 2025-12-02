#ifndef BOARD_H
#define BOARD_H

typedef enum { CELL_WATER, CELL_SHIP, CELL_HIT, CELL_MISS } CellState;

typedef struct {
    CellState state;
    int ship_id; // -1 se não houver navio
} Cell;

typedef struct {
    int rows, cols;
    Cell *cells; // malloc(rows * cols)
} Board;

Board* create_board(int rows, int cols);
void destroy_board(Board *board);
Cell* get_cell(Board *board, int r, int c);
int is_valid_coordinate(Board *board, int r, int c);

#endif