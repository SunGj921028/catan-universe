#include"init.h"
#include"data.h"
#include"choose.h"
#include"color.h"
#include"card.h"
#include"map.h"
#include"phase.h"
#include<stdio.h>
#include<stdint.h>

/*0:沙漠 1:丘陵() 2:山脈() 3:草原(sheep) 4:森林(wood) 5:麥田(wheat)*/
int source_region[19] = {0 ,1,1,1, 2,2,2, 3,3,3,3, 4,4,4,4, 5,5,5,5};
//number
int temp_num[18]={5,2,6,3,8,10,9,12,11,4,8,10,9,4,5,6,3,11};
//region number after random 
int region[19]={0};
//develop card
int develop_index = 0;
int develop_card_order[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,3,3,4,4,4,4,4};
//resource
int resource[5] = {
    19,   //rock
    19,   //wood
    19,   //wheat
    19,   //brick
    19    //sheep
};
//knight remain
int knight_remain = KNIGHT_CARD_REMAIN;
//score remani
int score_remain = SCORE_CARD_REMAIN;
//progress remain
//0 -> harvest, 1 -> build, 2 -> steal
int progress_remain[3] = {2,2,2};
//develop_card_keep
int develop_card_keep[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int keep_index = 0;
//player order
int first_player = 0;
//player
sPlayer * p1;
sPlayer * p2;
sPlayer * p3;
sPlayer * p4;
//sPlayer *Player[4]={p1,p2,p3,p4};
int8_t init_build_take[5] = {0,0,0,0,0};
int8_t init_near_road[4] = {-1,-1,-1,-1};
int8_t map[23][13][5];
char extra;
char player_name[20] = {0};
int ai_main_move = 0;

void print_surprise(uint8_t player){
    sPlayer * play;
    if(player==2){ play = p2;}
    else if(player==3){ play = p3;}
    else if(player==4){ play = p4;}

    if(play->final_score >= 5){
        printf(PURPLE"Ha Ha I'm going to win by player %d",player);
    }
    if(play->score_card == 0){
        printf(PURPLE"You think I only have %u point ? ^_^",play->final_score);
    }
    return;
}

void title(){
    CLEAR;
    printf("\033[3C ________        ___      ____________      ___         _       _\n"
       "\033[3C/ _______|      / _ \\    |____    ____|    / _ \\       | \\     | |\n"
      "\033[2C/ /	          / / \\ \\        |  |        / / \\ \\      |  \\    | |\n"
     "\033[1C/ /	         / /   \\ \\       |  |       / /   \\ \\     | | \\   | |\n"
     "\033[1C\\ \\            / /_____\\ \\      |  |      / /_____\\ \\    | |\\ \\  | |\n"
      "\033[2C\\ \\_______   /  _______  \\     |  |     /  _______  \\   | | \\ \\_| |\n"
       "\033[3C\\________| /_/         \\_\\    |__|    /_/         \\_\\  |_|  \\____|\n\n\n");//print title
}

int32_t startup(){
    printf("\033[3CSTART(PRESS S)             HOW TO PLAY(PRESS H)             QUIT(PRESS Q)\n");
    printf("Which one do you choose : ");
    while(1){
        char a=getch();
        if(a=='h' || a=='H'){
            system("xdg-open https://andyventure.com/boardgame-catan/");
        }else if(a=='s' || a=='S'){
            return 1;
        }else if(a=='q' || a=='Q'){
            printf("\n");
            printf(RED"Game End!!\e[0m\n");
            exit(0);
        }else{
            continue;
        }
    }
    CLEAR;
    return 0;
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    //build turn 1 and 2
    bool build = false;
    title();
    if(startup()){
        CLEAR;
        init_region();
        region_num_initial();
        map_init();
        //map_print(0);
        develop_card_init();
        p1 = player_init();
        p2 = player_init();
        p3 = player_init();
        p4 = player_init();
        build = false;
        uint8_t count = 0;
        while(1){
            printf("Please input player's name (small than or equal to 10 letters): ");
            fgets(player_name,20,stdin);
            //printf("%s\n",player_name);
            if(strlen(player_name)>10){
                printf(RED"Wrong format of player's name!!\e[0m\n");
                continue;
            }else{
                player_name[strlen(player_name) - 1] = '\0';
                //printf("%s\n",player_name);
                break;
            }
        }
        CLEAR;
        while(1){
            if(!build) {first_sec_turn(), count = (first_player + 1), build = true;}
            //printf("Start from player %d.\n",count);
            if((count%5) == 1){
                player_move();
                p1->U_develop = 0;
            }else{
                ai_move(count%5); //2 3 4
                sleep(2);
            }
            judge_the_U_knight();
            Longest_Player();
            REFRESH
            print_surprise(count%5);
            PASS;
            count += 1;
            //print_init(count%5);
            if(count == 5) {count = 1;}
        }
    }
    return 0;
}