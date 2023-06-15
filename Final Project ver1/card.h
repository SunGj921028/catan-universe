#pragma once
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include"data.h"

//get develop card
void get_develop_card(sPlayer * player, uint8_t player_number);
bool judge_buy_card(sPlayer * player);
void save_develop_card(uint8_t p);

//顯示當下的手牌種類及數量
void develop_card_state(sPlayer * player,uint8_t player_number,uint8_t is_ai);

//用卡階段(已經包入判斷judge和卡片使用的功能) 用卡與否以及是否能夠執行用卡的動作 
int32_t use_card_state(uint8_t player_number,int8_t card_serial_number,uint8_t is_ai);

//用卡階段偵錯 錯誤輸入 亂用卡防範
bool error_detect_use_card_state(sPlayer * player,int8_t card_serial_number, uint8_t is_ai);

//判斷目前的最多騎士卡得分 尚未完成
int32_t judge_the_U_knight();

//尚未完成
int32_t knight_card(sPlayer * player,uint8_t player_number,uint8_t is_ai);

void harvest_card(sPlayer * player, uint8_t p, uint8_t is_ai);

void build_card(sPlayer * player,uint8_t player_number,uint8_t is_ai);

//player1 is the people who uses the steal_card
void steal_card(sPlayer * player1,sPlayer * player2, sPlayer * player3, sPlayer * player4,uint8_t player_number,uint8_t is_ai);
