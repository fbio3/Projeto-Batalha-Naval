#include <stdio.h>
#include "game.h"
#include "io.h"

int main() {
    int option;
    
    // Configurações Padrão
    GameConfig current_config;
    current_config.board_size = 10;
    current_config.placement_mode = 'A'; // Automático por padrão

    do {
        printf("\n=== MENU ===\n");
        printf("1) Novo Jogo\n");
        printf("2) Configuracoes\n");
        printf("3) Sair\n");
        printf("> ");
        option = read_int(1, 3);
        
        if (option == 1) {
            Game game;
            // Passa a configuração atual para o jogo
            setup_game(&game, current_config);
            play_game(&game);
            cleanup_game(&game);
        }
        else if (option == 2) {
            configure_settings(&current_config);
        }
        
    } while (option != 3);
    
    printf("Saindo...\n");
    return 0;
}