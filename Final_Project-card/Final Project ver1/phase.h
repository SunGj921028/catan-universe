#pragma once
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include"data.h"

#define PASS printf("------------------------------>\n")
#define CLEAR printf("\033[H\033[2J") //clear terminal

//play dice
//take resource and see the pirate's move
void throw_dice(sPlayer * player, uint8_t is_ai, uint8_t player_number);
//dice random
int32_t dice();

//search and judge to take the resource
void take_resource_dice(int32_t harvest_resource[2][5]);

//get develop card
void get_develop_card(sPlayer * player);
bool judge_buy_card(sPlayer * player);

//ai
void ai_move(int p);
bool judge_ai_action(uint8_t action, uint8_t player_number);

//thief move
void thief_action(sPlayer * player, uint8_t is_ai);
void check_hand();
void print_player_hands(sPlayer * player, uint8_t n);
void input_key(sPlayer * player, uint8_t p_number, int num);
void throw_card(sPlayer * player, uint8_t arr[], size_t n);
void move_thief(sPlayer * player, uint8_t is_ai);

//real player
void player_move();
