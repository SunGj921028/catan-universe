#include"phase.h"
#include"data.h"
#include"init.h"
#include"color.h"
#include"card.h"

extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;
extern int resource[5];//sum is 95

//判斷6個行為可不可以做
bool judge_ai_action(uint8_t action, uint8_t player_number){
    sPlayer * player;
    if(player_number==1) {player = p1;}
    else if(player_number==2) {player = p2;}
    else if(player_number==3) {player = p3;}
    else {player = p4;}
    //0->get        1->use         2->road
    //3->village    4->upgrade     5->trade(bank)
    //6->trade(harbor)(2:1)     7->trade(harbor)(3:1)
    if(action==0){
        if(judge_buy_card(player)){ return true;}
    }else if(action==1){
        //can reset ai's hard
        //use
        uint8_t chance = 0;
        uint8_t cho_of_card = 0;
        uint8_t cho_arr[4] = {0};
        while(chance<4){
            cho_of_card = rand() % 4;
            if(cho_arr[cho_of_card]!=0){ continue;}
            if(use_card_state(player_number,cho_of_card,1)==-1){ cho_arr[cho_of_card]++;}
            chance++;
        }
    }else if(action==2){
        //build road
    }else if(action==3){
        //build village
    }else if(action==4){
        //upgrade village
    }else if(action==5 || action==6 || action==7){
        int32_t option = 0;
        if(action!=5){ option = (action==6) ? 2 : 3;}
        else { option = 1;}
        printf("option is %d\n",option);
        uint8_t resource_type[5] = {0};
        for(int i=0;i<5;i++){
            int j = i + rand()/(RAND_MAX/(5-i)+1);
            int temp = resource_type[j];
            resource_type[j] = resource_type[i];
            resource_type[i] = temp;
        }
        for(int i=0;i<5;i++){
            if(trade_judge(player,option,resource_type[i])){ trade(player,1,resource_type[i],option); return true;}
        }
    }

    return false;
}

void ai_move(int p){
    printf("#This is Player %d's turn.\n",p);
    //which player
    sPlayer * player;
    if(p == 2) {player = p2;}
    else if(p == 3) {player = p3;}
    else {player = p4;}

    //throw dice for ai(p)
    throw_dice(player,1,p);     //dice -> take resource or thief
    //hard pattern:
    //run 6 action again
    uint8_t again_action = 1;
    while(again_action){
        //random action order
        //can reset ai's hard
        uint8_t action[8] = {0,1,2,3,4,5,6,7};
        for(int i=0;i<8;i++){
            int j = i + rand()/(RAND_MAX/(8-i)+1);
            int temp = action[j];
            action[j] = action[i];
            action[i] = temp;
        }
        for(int i=0;i<8;i++){
            if(judge_ai_action(action[i],p)){
                uint8_t can = rand() % 3;
                //2/3 will do this action
                if(can==1||can==2){
                    if(i==0){
                        get_develop_card(player,p);
                        printf("ai choose to get develop card\n");
                    }else if(i==1){
                        //use card
                        printf("ai choose to use develop card\n");
                    }else if(i==2){
                        //build road
                        //random 0-71
                        printf("ai build road\n");
                        /*while(1){
                            int32_t road_rand = rand() % 72;
                            printf("ai build road\n");
                        }*/
                    }else if(i==3){
                        //build village
                        //random 0-53
                        printf("ai build village\n");
                        /*while(1){
                            int32_t V_ran = rand() % 54;
                            printf("ai build village\n");
                        }*/
                    }else if(i==4){
                        //upgrade
                        //Need to find which can be upgraded
                        printf("ai upgrade its village to city\n");
                    }else if(i==5){
                        printf(RED"Player %d chooses to trade with bank!!\e[0m\n",p);
                    }else if(i==6){
                        printf(RED"Player %d chooses to trade with harbor(2:1)!!\e[0m\n",p);
                    }else if(i==7){
                        printf(RED"Player %d chooses to trade with harbor(3:1)!!\e[0m\n",p);
                    }
                }
            }
        }
        again_action = rand() % 2;
    }
    if(keep_index!=0){
        save_develop_card(p);
        player->U_develop = 0;
    }
}