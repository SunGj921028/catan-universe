#pragma once
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<time.h>
#include"data.h"

#define PASS printf("----------------------------------->\n")
#define CLEAR printf("\033[H\033[2J") //clear terminal

#define REFRESH CLEAR; \
                map_print(0);

//first round and second round
void first_sec_turn();

//score
void score(uint8_t p);

//play dice
//take resource and see the pirate's move
void throw_dice(sPlayer * player, uint8_t is_ai, uint8_t player_number);
//dice random
int32_t dice();
void show_dice_v1(int dice);
void show_dice_v2(int dice);

//search and judge to take the resource
void take_resource_dice(int32_t harvest_resource[2][5]);

//ai
void ai_move(int p);
bool judge_ai_action(uint8_t action, uint8_t player_number);

//thief move
bool judge_five(char input[30]);
void thief_action(sPlayer * player, uint8_t is_ai, uint8_t player_number);
void check_hand();
void print_player_hands(sPlayer * player, uint8_t n);
void input_key(sPlayer * player, uint8_t p_number, int num);
void throw_card(sPlayer * player, uint8_t arr[], size_t n);
int32_t move_robbor(int32_t block_id,int32_t *nearby_player_5x1, uint8_t is_ai);
void steal_resource(uint8_t player_cho, sPlayer * player);

//real player
void player_move();

//trade
//trade option
//1->bank 2->harbor(2:1) 3->harbor(3:1)
void list_can_trade(sPlayer * player, uint8_t trade_option);
bool trade_judge(sPlayer * player, uint8_t trade_option, uint8_t type);
//trade type->bank(1) harbor2:1(2) harbor3:1(3)
void trade(sPlayer * player, uint8_t is_ai, uint8_t give_type, uint8_t trade_type);
void trade_player();