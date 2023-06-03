#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include"init.h"
#include"data.h"
#include"choose.h"

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
//develop_card_remain
int develop_card_remain = KNIGHT_CARD_REMAIN + SCORE_CARD_REMAIN + PROGESS_CARD_REAMIN;
//player
sPlayer * p1;
sPlayer * p2;
sPlayer * p3;
sPlayer * p4;

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
    while(1){
        printf("Which one do you choose : ");
        char a=getch();
        if(a=='h' || a=='H'){
            system("xdg-open https://andyventure.com/boardgame-catan/");
        }else if(a=='s' || a=='S'){
            return 1;
        }else if(a=='q' || a=='Q'){
            printf("\n");
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
    title();
    while(1){
        if(startup()){
            CLEAR;
            //init_map();
            //print_map();
            init_region();
            region_num_initial();
            develop_card_init();
            p1 = player_init();
            p2 = player_init();
            p3 = player_init();
            p4 = player_init();
            print_init();
        }
        return 0;
    }
    return 0;
}