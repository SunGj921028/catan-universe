#define _GNU_SOURCE
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#define CLEAR printf("\033[H\033[2J"); //clear terminal
int getch() {
    int ch;
    // struct to hold the terminal settings
    struct termios old_settings, new_settings;
    // take default setting in old_settings
    tcgetattr(STDIN_FILENO, &old_settings);
    // make of copy of it (Read my previous blog to know 
    // more about how to copy struct)
    new_settings = old_settings;
    // change the settings for by disabling ECHO mode
    // read man page of termios.h for more settings info
    new_settings.c_lflag &= ~(ICANON | ECHO);
    // apply these new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    // now take the input in this mode
    ch = getchar();
    // reset back to default settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    return ch;
}//just some copy and paste

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
