#pragma once
#include <stdint.h>

int8_t map[23][13][5];

void d3_pd(int32_t x,int32_t y);

void map_init();

int32_t map_print(int8_t printer_mood);

int32_t build_village(int32_t player_ID, int32_t point_ID, int8_t is_init);

int32_t build_road(int32_t player_ID, int32_t road_ID);

int32_t harvest(int32_t dice_number,int32_t *harvest_resource);