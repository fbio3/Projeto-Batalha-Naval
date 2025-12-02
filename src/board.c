#include <stdlib.h>
#include <stdio.h>
#include "board.h"

Board* create_board(int rows, int cols) {
    Board *b = (Board*) malloc(sizeof(Board));
    if (!b) return NULL;

    b->rows = rows;
    b->cols = cols;
    // Alocação dinâmica do array de células (linearizado)
    b->cells = (Cell*) malloc(rows * cols * sizeof(Cell));
    
    if (!b->cells) {
        free(b);
        return NULL;
    }

    // Inicialização
    for (int i = 0; i < rows * cols; i++) {
        b->cells[i].state = CELL_WATER;
        b->cells[i].ship_id = -1;
    }

    return b;
}

void destroy_board(Board *board) {
    if (board) {
        if (board->cells) {
            free(board->cells); // Libera o array de células
        }
        free(board); // Libera a struct do tabuleiro
    }
}

Cell* get_cell(Board *board, int r, int c) {
    if (!is_valid_coordinate(board, r, c)) return NULL;
    // Aritmética de ponteiros para acessar matriz linearizada
    return &board->cells[r * board->cols + c];
}

int is_valid_coordinate(Board *board, int r, int c) {
    return (r >= 0 && r < board->rows && c >= 0 && c < board->cols);
}