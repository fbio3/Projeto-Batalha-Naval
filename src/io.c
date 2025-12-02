#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> 
#include "io.h"
#include "board.h"

void print_header() {
    printf("\n=== BATALHA NAVAL ===\n");
}

void print_board(Board *board, int show_hidden) {
    printf("   ");
    for (int c = 0; c < board->cols; c++) printf("%c ", 'A' + c);
    printf("\n");

    for (int r = 0; r < board->rows; r++) {
        printf("%2d ", r + 1);
        for (int c = 0; c < board->cols; c++) {
            Cell *cell = get_cell(board, r, c);
            char symbol = '~'; 

            if (cell->state == CELL_HIT) symbol = 'X';
            else if (cell->state == CELL_MISS) symbol = '.'; 
            else if (cell->state == CELL_SHIP) {
                if (show_hidden) symbol = 'S'; 
                else symbol = '~'; 
            }
            
            printf("%c ", symbol);
        }
        printf("\n");
    }
}

void read_coordinate(int *row, int *col, int max_rows, int max_cols) {
    char input[100];
    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) < 2) {
            printf("Entrada muito curta. Digite ex: A5\n");
            continue;
        }

        char letter = toupper(input[0]);
        char max_letter = 'A' + max_cols - 1;
        
        if (letter < 'A' || letter > max_letter) {
            printf("Erro: Coluna invalida! Deve ser entre A e %c.\n", max_letter);
            continue;
        }

        int is_numeric = 1;
        for (int i = 1; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                is_numeric = 0;
                break;
            }
        }

        if (!is_numeric) {
            printf("Erro: Formato invalido! Digite apenas Letra e Numero. Ex: C4\n");
            continue;
        }

        int number = atoi(input + 1); 
        
        if (number < 1 || number > max_rows) {
            printf("Erro: Linha invalida! Deve ser entre 1 e %d.\n", max_rows);
            continue;
        }

        *col = letter - 'A';
        *row = number - 1;
        return;
    }
}

void read_string(char *buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; 
}

int read_int(int min, int max) {
    char buffer[100];
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        
        buffer[strcspn(buffer, "\n")] = 0;

        if (strlen(buffer) == 0) {
            continue; // Ignora enter vazio
        }

        // Verifica se TODOS os caracteres são números
        int is_numeric = 1;
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isdigit(buffer[i])) {
                is_numeric = 0;
                break;
            }
        }

        if (!is_numeric) {
            printf("Entrada invalida! Digite apenas numeros.\n> ");
            continue;
        }

        int val = atoi(buffer);
        if (val >= min && val <= max) {
            return val;
        }
        
        printf("Opcao invalida. Escolha entre %d e %d.\n> ", min, max);
    }
}

char read_char(const char *options) {
    char buffer[100];
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        
        if (strlen(buffer) != 1) {
            printf("Digite apenas uma letra (%s): ", options);
            continue;
        }

        char c = toupper(buffer[0]);
        if (strchr(options, c)) return c;
        printf("Opcao invalida. (%s): ", options);
    }
}