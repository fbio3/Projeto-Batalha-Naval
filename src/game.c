#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game.h"
#include "io.h"
#include "board.h"
#include "fleet.h"

// --- Declarações Internas ---
void setup_player(Player *p, int rows, int cols);
void place_ships_auto(Player *p);
void place_ships_manual(Player *p);
int can_place_ship(Board *b, int r, int c, int len, Orientation orient);
void apply_ship(Board *b, int r, int c, int len, Orientation orient, int id);

// --- MENU DE CONFIGURAÇÕES ---
void configure_settings(GameConfig *config) {
    int opcao = 0;
    while (opcao != 3) {
        printf("\n--- CONFIGURACOES ---\n");
        printf("Atuais: \n");
        printf("  [Tamanho do Tabuleiro]: %dx%d\n", config->board_size, config->board_size);
        printf("  [Modo de Posicionamento]: %s\n", (config->placement_mode == 'A' ? "Automatico" : "Manual"));
        
        printf("\nO que deseja alterar?\n");
        printf("1) Alterar Tamanho\n");
        printf("2) Alterar Modo\n");
        printf("3) Voltar ao Menu Principal\n");
        printf("> ");
        
        opcao = read_int(1, 3);

        if (opcao == 1) {
            printf("\nInforme novo tamanho (6 a 26): ");
            config->board_size = read_int(6, 26);
            printf(">> Tamanho atualizado para %d! <<\n", config->board_size);
        }
        else if (opcao == 2) {
            printf("\nInforme novo modo ((M)anual ou (A)utomatico): ");
            config->placement_mode = read_char("MA");
            printf(">> Modo atualizado para %s! <<\n", (config->placement_mode == 'A' ? "Automatico" : "Manual"));
        }
    }
}

// --- Setup do Jogo ---
void setup_game(Game *game, GameConfig config) {
    srand(time(NULL));
    game->config = config;
    
    print_header();
    printf("Iniciando jogo com Tabuleiro %dx%d...\n", config.board_size, config.board_size);
    
    printf("Informe apelido do Jogador 1: ");
    read_string(game->p1.nickname, 32);
    
    printf("Informe apelido do Jogador 2: ");
    read_string(game->p2.nickname, 32);
    
    setup_player(&game->p1, config.board_size, config.board_size);
    setup_player(&game->p2, config.board_size, config.board_size);
    
    if (config.placement_mode == 'A') {
        printf("\n--- Posicionando frotas automaticamente ---\n");
        place_ships_auto(&game->p1);
        place_ships_auto(&game->p2);
        printf("Frotas posicionadas!\n");
    } else {
        printf("\n--- INICIO DO POSICIONAMENTO MANUAL ---\n");
        
        printf("\n>> Vez de %s posicionar seus navios <<\n", game->p1.nickname);
        place_ships_manual(&game->p1);
        
        for(int i=0; i<50; i++) printf("\n"); 
        
        printf("\n>> Vez de %s posicionar seus navios <<\n", game->p2.nickname);
        place_ships_manual(&game->p2);
        
        for(int i=0; i<50; i++) printf("\n");
    }
    
    game->current_player = 1;
    game->game_over = 0;
}

void place_ships_manual(Player *p) {
    for (int i = 0; i < p->fleet.count; i++) {
        Ship *s = &p->fleet.ships[i];
        int placed = 0;
        
        while (!placed) {
            printf("\nTabuleiro de %s:\n", p->nickname);
            print_board(p->board, 1); 
            
            printf("\nPosicione o navio: %s (Tamanho: %d celulas)\n", s->name, s->length);
            
            int r, c;
            printf("Informe a coordenada INICIAL (ex: A1): ");
            
            read_coordinate(&r, &c, p->board->rows, p->board->cols);
            
            printf("Orientacao (H)orizontal [->] ou (V)ertical [v]: ");
            char orient_char = read_char("HV");
            Orientation orient = (orient_char == 'H') ? ORIENT_H : ORIENT_V;
            
            int fim_linha = r + (orient == ORIENT_V ? s->length - 1 : 0);
            int fim_coluna = c + (orient == ORIENT_H ? s->length - 1 : 0);

            if (fim_linha >= p->board->rows || fim_coluna >= p->board->cols) {
                printf("\n>>> ERRO: O navio sai do tabuleiro! <<<\n");
                printf("Voce escolheu %c%d e ele cresce %d casas para %s.\n", 
                       'A' + c, r + 1, s->length, (orient == ORIENT_H ? "a Direita" : "Baixo"));
                
                if (orient == ORIENT_H) 
                    printf("Ele tentou ir ate a coluna %c (o mapa so vai ate %c).\n", 'A' + fim_coluna, 'A' + p->board->cols - 1);
                else 
                    printf("Ele tentou ir ate a linha %d (o mapa so vai ate %d).\n", fim_linha + 1, p->board->rows);
                
                continue; 
            }

            if (!can_place_ship(p->board, r, c, s->length, orient)) {
                printf("\n>>> ERRO: Sobreposicao! Ja existe um navio nesse caminho. <<<\n");
                continue;
            }

            apply_ship(p->board, r, c, s->length, orient, s->id);
            placed = 1;
            printf(">> %s posicionado com sucesso!\n", s->name);
        }
    }
    printf("\nTodos os navios de %s foram posicionados!\n", p->nickname);
}

// --- Funções Auxiliares ---
void setup_player(Player *p, int rows, int cols) {
    p->board = create_board(rows, cols);
    p->shots_fired = 0;
    p->hits_count = 0;
    init_fleet(&p->fleet);
    add_ship(&p->fleet, "Porta-avioes", 5, 0);
    add_ship(&p->fleet, "Encouracado", 4, 1);
    add_ship(&p->fleet, "Cruzador 1", 3, 2);
    add_ship(&p->fleet, "Cruzador 2", 3, 3);
    add_ship(&p->fleet, "Destroyer 1", 2, 4);
    add_ship(&p->fleet, "Destroyer 2", 2, 5);
}

void place_ships_auto(Player *p) {
    for (int i = 0; i < p->fleet.count; i++) {
        Ship *s = &p->fleet.ships[i];
        int placed = 0;
        while (!placed) {
            int r = rand() % p->board->rows;
            int c = rand() % p->board->cols;
            Orientation o = (rand() % 2 == 0) ? ORIENT_H : ORIENT_V;
            if (can_place_ship(p->board, r, c, s->length, o)) {
                apply_ship(p->board, r, c, s->length, o, s->id);
                placed = 1;
            }
        }
    }
}

int can_place_ship(Board *b, int r, int c, int len, Orientation orient) {
    int dr = (orient == ORIENT_V) ? 1 : 0;
    int dc = (orient == ORIENT_H) ? 1 : 0;
    for (int i = 0; i < len; i++) {
        int nr = r + i * dr;
        int nc = c + i * dc;
        if (!is_valid_coordinate(b, nr, nc)) return 0;
        if (get_cell(b, nr, nc)->state != CELL_WATER) return 0;
    }
    return 1;
}

void apply_ship(Board *b, int r, int c, int len, Orientation orient, int id) {
    int dr = (orient == ORIENT_V) ? 1 : 0;
    int dc = (orient == ORIENT_H) ? 1 : 0;
    for (int i = 0; i < len; i++) {
        Cell *cell = get_cell(b, r + i * dr, c + i * dc);
        cell->state = CELL_SHIP;
        cell->ship_id = id;
    }
}

void play_game(Game *game) {
    while (!game->game_over) {
        Player *attacker = (game->current_player == 1) ? &game->p1 : &game->p2;
        Player *defender = (game->current_player == 1) ? &game->p2 : &game->p1;
        
        printf("\n-- Turno de %s --\n", attacker->nickname);
        print_board(defender->board, 0); 
        
        int r, c;
        printf("Digite coordenada do tiro: ");
        
        read_coordinate(&r, &c, defender->board->rows, defender->board->cols);
        
        Cell *target = get_cell(defender->board, r, c);
        
        if (target->state == CELL_HIT || target->state == CELL_MISS) {
            printf("Voce ja atirou ai! Perdeu a vez.\n");
        } else if (target->state == CELL_SHIP) {
            target->state = CELL_HIT;
            attacker->hits_count++;
            if (target->ship_id != -1) {
                defender->fleet.ships[target->ship_id].hits++;
                if (defender->fleet.ships[target->ship_id].hits == defender->fleet.ships[target->ship_id].length) {
                    printf("Resultado: AFUNDOU %s!\n", defender->fleet.ships[target->ship_id].name);
                } else {
                    printf("Resultado: ACERTOU!\n");
                }
            }
        } else {
            target->state = CELL_MISS;
            printf("Resultado: AGUA.\n");
        }
        attacker->shots_fired++;
        
        if (all_ships_sunk(&defender->fleet)) {
            printf("\n*** FIM DE JOGO ***\n");
            printf("Vencedor: %s\n", attacker->nickname);
            float acc = (attacker->shots_fired > 0) ? (float)attacker->hits_count / attacker->shots_fired * 100.0 : 0;
            printf("Tiros: %d | Acertos: %d | Precisao: %.1f%%\n", attacker->shots_fired, attacker->hits_count, acc);
            game->game_over = 1;
        } else {
            game->current_player = (game->current_player == 1) ? 2 : 1;
        }
    }
}

void cleanup_game(Game *game) {
    destroy_board(game->p1.board);
    destroy_board(game->p2.board);
    destroy_fleet(&game->p1.fleet);
    destroy_fleet(&game->p2.fleet);
}