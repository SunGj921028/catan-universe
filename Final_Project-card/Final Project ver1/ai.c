#include"phase.h"
#include"data.h"
#include"init.h"
#include"color.h"

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
    //3->village    4->upgrade     5->trade
    if(action==0){
        if(judge_buy_card){ return true;}
        else{ return false;}
    }else if(action==1){

    }else if(action==2){

    }else if(action==3){

    }else if(action==4){

    }else if(action==5){}
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
        uint8_t action[6] = {0,1,2,3,4,5};
        for(int i=0;i<6;i++){
            int j=i+rand()/(RAND_MAX/(6-i)+1);
            int temp=action[j];
            action[j]=action[i];
            action[i]=temp;
        }
        for(int i=0;i<6;i++){
            if(judge_ai_action(action[i],p)){
                uint8_t can = rand() % 3;
                //2/3 will do this action
                if(can==1||can==2){
                    if(i==0){
                        get_develop_card(player);
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
                        //trade
                        while(1){
                            uint8_t bank_harbor = rand() % 2;
                            if(bank_harbor==0){
                                //if(){}
                            }else{
                                //if(){}
                            }
                        }
                        printf("ai choose to trade\n");
                        //bank or harbor
                    }
                }
            }
        }
        again_action = rand() % 2;
    }
}