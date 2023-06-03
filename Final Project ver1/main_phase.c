#include<stdio.h>
#include<stdint.h>
#include"data.h"
#include"phase.h"
#include"init.h"

//有number的region
extern int region[19];
//紀錄資源的region
extern int source_region[19];
//庫存的資源
extern int resource[5];
//剩餘騎士卡
extern int knight_remain;
//剩餘進程卡
extern int progress_remain[3];
//剩餘加分卡
extern int score_remain;
//發展卡發牌順序
extern int develop_card_order[25];
extern int develop_index;

//player
// extern sPlayer * p1;
// extern sPlayer * p2;
// extern sPlayer * p3;
// extern sPlayer * p4;

// void get_develop_card(sPlayer * player){
//     if(develop_index==0){
//         player -> knight += 1;
//         knight_remain--;
//     }else if(develop_index==1){
//         player -> harvest_card += 1;
//         progress_remain[0]--;
//     }else if(develop_index==2){
//         player -> build_card += 1;
//         progress_remain[1]--;
//     }else if(develop_index==3){
//         player -> steal_card += 1;
//         progress_remain[2]--;
//     }else{
//         player -> score_card += 1;
//         score_remain--;
//         // player -> final_score += 1;
//     }
//     develop_index++;
//     return;
// }

void take_resource(sPlayer * player, int32_t dice){}

int32_t dice(){
    return ((rand()%6+1)+(rand()%6+1));
}

void throw_dice(sPlayer * player){
    int32_t dice_result = dice();
    if(dice_result==7){
    }else{
        take_resource(player,dice_result);
    }
    return;
}