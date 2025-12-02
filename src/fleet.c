#include <stdlib.h>
#include <string.h>
#include "fleet.h"

void init_fleet(Fleet *fleet) {
    fleet->ships = NULL;
    fleet->count = 0;
}

// REALLOC
void add_ship(Fleet *fleet, const char* name, int length, int id) {
    fleet->count++;
    fleet->ships = (Ship*) realloc(fleet->ships, fleet->count * sizeof(Ship));
    
    Ship *new_ship = &fleet->ships[fleet->count - 1];
    strncpy(new_ship->name, name, 19);
    new_ship->length = length;
    new_ship->hits = 0;
    new_ship->placed = 0;
    new_ship->id = id;
}

void destroy_fleet(Fleet *fleet) {
    if (fleet->ships) {
        free(fleet->ships);
        fleet->ships = NULL;
    }
    fleet->count = 0;
}

int all_ships_sunk(Fleet *fleet) {
    for (int i = 0; i < fleet->count; i++) {
        if (fleet->ships[i].hits < fleet->ships[i].length) {
            return 0; // Ainda há navios vivos
        }
    }
    return 1;
}