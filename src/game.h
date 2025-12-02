#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "fleet.h"

typedef struct {
    int board_size;
    char placement_mode; // 'A' ou 'M'
} GameConfig;

typedef struct {
    Board *board;
    Fleet fleet;
    char nickname[32];
    int shots_fired;
    int hits_count;
} Player;

typedef struct {
    Player p1, p2;
    int current_player;
    int game_over;
    GameConfig config;
} Game;

void configure_settings(GameConfig *config);
void setup_game(Game *game, GameConfig config); // Recebe a config pronta
void play_game(Game *game);
void cleanup_game(Game *game);

#endif