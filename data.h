#ifndef __data_H
#define __data_H

#define VILLAGE_POINT 1
#define CITY_POINT 2
#define SCORE_CARD 1
#define M_KNIGHT 2
#define M_ROAD 2

//resource
uint8_t rock = 19;
uint8_t wood = 19;
uint8_t wheat = 19;
uint8_t brick = 19;
uint8_t wool = 19;
//develope card
uint8_t knight_card = 14;
uint8_t progress_card = 6;
uint8_t score_card = 5;

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