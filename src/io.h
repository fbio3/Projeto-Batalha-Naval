#ifndef IO_H
#define IO_H

#include "board.h"
#include "game.h"

// Exibição
void print_header();
void print_board(Board *board, int show_hidden);
void print_message(const char *msg);

// Entrada
void read_coordinate(int *row, int *col, int max_rows, int max_cols);

void read_string(char *buffer, int size);
int read_int(int min, int max);
char read_char(const char *options);

#endif