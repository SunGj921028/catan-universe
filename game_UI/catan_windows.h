#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#define CLEAR printf("\033[H\033[2J"); //clear terminal

typedef struct{
    uint32_t rock;
    uint32_t wood;
    uint32_t wheat;
    uint32_t brick;
    uint32_t wool;
    uint32_t knight;
    uint32_t develop_card_progress;
    uint32_t develop_card_score;
    bool special_road;
    bool special_army;
    uint32_t city;
    uint32_t village;
    uint32_t road;
    uint32_t hand;
    uint32_t final_score;
}Player;

typedef struct{
    int wheat_field;
    int forest;
    int grassland;
    int mountain;
    int hill;
    int desert;
}Field;

void startup();
int choosemode();
void startstory();
void map_initial();
void trade();
void build();
void hands();
void resource();
void diceroll();
void score_calculate(Player *player);