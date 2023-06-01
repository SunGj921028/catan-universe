#ifndef __data_H
#define __data_H

#define VILLAGE_POINT 1
#define CITY_POINT 2
#define SCORE_CARD 1
#define M_KNIGHT 2
#define M_ROAD 2

#define IRON_REMAIN 19
#define WOOD_REMAIN 19
#define WHEAT_REMAIN 19
#define BRICK_REMAIN 19
#define WOOL_REMAIN 19
#define KNIGHT_CARD_REMAIN 14
#define PROGESS_CARD_REAMIN 6
#define SCORE_CARD_REMAIN 5

#include<stdint.h>

typedef struct _sVillage{
    uint8_t village_hand;
    uint8_t village_build;
} sVillage;

typedef struct _sCity{
    uint8_t city_hand;
    uint8_t city_build;
} sCity;

typedef struct _sRoad{
    uint8_t road_hand;
    uint8_t road_build;
} sRoad;

typedef struct _sPlayer{
    uint8_t iron;
    uint8_t wood;
    uint8_t wheat;
    uint8_t brick;
    uint8_t sheep;
    uint8_t knight;      //騎士卡(0)
    uint8_t U_knight;
    uint8_t harvest_card;//豐收之年(1)
    uint8_t build_card;  //道路建造(2)
    uint8_t steal_card;  //壟斷市場(3)
	uint8_t score_card;  //分數卡(4)
    uint8_t U_develop;   //(<=1 per one turn)
    uint8_t M_knight;    //(>=5)
    uint8_t M_road;      //(>=3)
    sRoad road;
    sCity city;
    sVillage village;
    uint8_t hand;
    uint8_t final_score;
} sPlayer;

sPlayer * player_init();

extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;

#endif