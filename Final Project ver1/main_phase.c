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
extern int resource[5][1];
//剩餘騎士卡
extern int knight_remain;
//剩餘進程卡
extern int progress_remain[3][1];
//剩餘加分卡
extern int score_remain;
//發展卡發牌順序
extern int develop_card_order[25];

//player
extern sPlayer * you;
extern sPlayer * A;
extern sPlayer * B;
extern sPlayer * C;


void take_resource(sPlayer * player, int32_t dice){}

int32_t dice(){}

void throw_dice(sPlayer * player){
    int32_t dice_result = dice();
    if(dice_result==7){
    }else{
        take_resource(player,dice_result);
    }
    return;
}