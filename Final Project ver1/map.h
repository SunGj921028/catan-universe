#pragma once
#include <stdint.h>

extern int8_t map[23][13][5];

extern int8_t init_build_take[5];
extern int8_t init_near_road[4];

void d3_pd(int32_t x,int32_t y);

void map_init();

int32_t map_print(int8_t printer_mood);

int32_t build_village(int32_t player_ID, int32_t point_ID, int8_t is_init, uint8_t is_ai);

int32_t village_upgrade(int32_t player_ID,int32_t point_ID, uint8_t is_ai);

int32_t build_road(int32_t player_ID, int32_t road_ID, uint8_t is_ai);

int32_t harvest(int32_t dice_number,int32_t *harvest_resource_2x5);

int32_t Longest_Path(int32_t player_ID);

int32_t find_port(int32_t player_ID,int32_t *port_array_1x6);