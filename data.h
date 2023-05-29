#ifndef __data_H
#define __data_H

#define VILLAGE_POINT 1
#define CITY_POINT 2
#define SCORE_CARD 1
#define M_KNIGHT 2
#define M_ROAD 2

#define ROCK_REMAIN 19
#define WOOD_REMAIN 19
#define WHEAT_REMAIN 19
#define BRICK_REMAIN 19
#define WOOL_REMAIN 19
#define KNIGHT_CARD_REMAIN 14
#define PROGESS_CARD_REAMIN 6
#define SCORE_CARD_REMAIN 5

typedef struct _sPlayer1{
    uint8_t rock;
    uint8_t wood;
    uint8_t wheat;
    uint8_t brick;
    uint8_t wool;
    uint8_t knight;
    uint8_t knight_used;
    uint8_t develop_card_progress_1;
    uint8_t develop_card_progress_2;
    uint8_t develop_card_progress_3;
    uint8_t develop_card_used;//(<=1 per one turn)
    uint8_t develop_card_score;
    bool special_road;  //(>=5)
    bool special_army;  //(>=3)
    uint8_t city;       //4
    uint8_t village;    //5
    uint8_t road;       //15
    uint8_t hand;
    uint8_t final_score;
} sPlayer1;

typedef struct _sPlayer2{
    uint8_t rock;
    uint8_t wood;
    uint8_t wheat;
    uint8_t brick;
    uint8_t wool;
    uint8_t knight;
    uint8_t knight_used;
    uint8_t develop_card_progress_1;
    uint8_t develop_card_progress_2;
    uint8_t develop_card_progress_3;
    uint8_t develop_card_used;//(<=1 per one turn)
    uint8_t develop_card_score;
    bool special_road;
    bool special_army;
    uint8_t city;
    uint8_t village;
    uint8_t road;
    uint8_t hand;
    uint8_t final_score;
} sPlayer2;

typedef struct _sPlayer3{
    uint8_t rock;
    uint8_t wood;
    uint8_t wheat;
    uint8_t brick;
    uint8_t wool;
    uint8_t knight;
    uint8_t knight_used;
    uint8_t develop_card_progress_1;
    uint8_t develop_card_progress_2;
    uint8_t develop_card_progress_3;
    uint8_t develop_card_used;//(<=1 per one turn)
    uint8_t develop_card_score;
    bool special_road;
    bool special_army;
    uint8_t city;
    uint8_t village;
    uint8_t road;
    uint8_t hand;
    uint8_t final_score;
} sPlayer3;

typedef struct _sPlayer4{
    uint8_t rock;
    uint8_t wood;
    uint8_t wheat;
    uint8_t brick;
    uint8_t wool;
    uint8_t knight;
    uint8_t knight_used;
    uint8_t develop_card_progress_1;
    uint8_t develop_card_progress_2;
    uint8_t develop_card_progress_3;
    uint8_t develop_card_used;//(<=1 per one turn)
    uint8_t develop_card_score;
    bool special_road;
    bool special_army;
    uint8_t city;
    uint8_t village;
    uint8_t road;
    uint8_t hand;
    uint8_t final_score;
} sPlayer4;

#endif
