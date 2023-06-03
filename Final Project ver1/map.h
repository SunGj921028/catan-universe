#pragma once
#include <stdint.h>

int8_t map[23][13][5];

void map_point_init(int8_t i,int8_t j,int8_t map_p_type);



void map_init();

int32_t map_print();