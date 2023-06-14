#pragma once
#include <stdint.h>

int8_t map[23][13][5];

int8_t init_build_take[5];

void d3_pd(int32_t x,int32_t y);

void map_init();

int32_t map_print(int8_t printer_mood);

int32_t build_village(int32_t player_ID, int32_t point_ID, int8_t is_init);

int32_t village_upgrade(int32_t player_ID,int32_t point_ID);

int32_t build_road(int32_t player_ID, int32_t road_ID);

int32_t harvest(int32_t dice_number,int32_t *harvest_resource_2x5);

int32_t move_robbor(int32_t block_id,int32_t *nearby_player_5x1);

int32_t Longest_Path(int32_t player_ID);