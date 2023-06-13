#include<stdio.h>
#include<stdint.h>

#include"data.h"
#include"init.h"


extern int source_region[19];
extern int temp_num[18];
extern int region[19];
extern int develop_card_order[25];
extern int develop_index;

//region resource random
void init_region(){
    for (int i=0; i<18; i++){
        int j=i+rand()/(RAND_MAX/(18-i)+1);
        int temp=source_region[j];
        source_region[j]=source_region[i];
        source_region[i]=temp;
    }
    return;
}

//標板塊數字
void region_num_initial(){
    for(int i=0;i<19;i++){
        region[i]=-1;
    }//初始化成-1
    for(int i=0;i<19;i++){
        if(source_region[i]==0){
            region[i]=0;
        }
    }//先標沙漠
    int j=0;
    for(int i=0;i<19;i++){
        //遇到沙漠跳下一個
        if(region[i]==0){
            continue;
        }else{
            region[i]=temp_num[j];
            j++;
        }//否則對應填入
    }
    return;
}

//develop_card random
void develop_card_init(){
    for(int i=0;i<25;i++){
        int j = i + rand() / (RAND_MAX/(25 - i) + 1);
        int temp = develop_card_order[j];
        develop_card_order[j] = develop_card_order[i];
        develop_card_order[i] = temp;
    }
    return;
}

//player init
sPlayer * player_init(){
    sPlayer *pPlayer = calloc(1,sizeof(sPlayer));
    pPlayer->iron = 5;
    pPlayer->wood = 5;
    pPlayer->wheat = 5;
    pPlayer->brick = 5;
    pPlayer->sheep = 5;
    pPlayer->knight = 0;
    pPlayer->U_knight = 0;
    pPlayer->harvest_card = 1;
    pPlayer->build_card = 0;
    pPlayer->steal_card = 1;
    pPlayer->score_card = 1;
    pPlayer->U_develop = 0;
    pPlayer->M_knight = 0;
    pPlayer->M_road = 0;
    pPlayer->city.city_hand = 5;
    pPlayer->city.city_build = 0;
    pPlayer->village.village_hand = 4;
    pPlayer->village.village_build = 0;
    pPlayer->road.road_hand = 15;
    pPlayer->road.road_build = 0;
    pPlayer->hand = 25;
    pPlayer->final_score = 0;
    return pPlayer;
}
