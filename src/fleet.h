#ifndef FLEET_H
#define FLEET_H

#include "board.h"

typedef enum { ORIENT_H, ORIENT_V } Orientation;

typedef struct {
    char name[20];
    int length;
    int hits;
    int placed; // 0 ou 1
    int id;
} Ship;

typedef struct {
    Ship *ships;
    int count;
} Fleet;

void init_fleet(Fleet *fleet);
void add_ship(Fleet *fleet, const char* name, int length, int id);
void destroy_fleet(Fleet *fleet);
int all_ships_sunk(Fleet *fleet);

#endif