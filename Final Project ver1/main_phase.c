#include<stdio.h>
#include<stdint.h>
#include"data.h"
#include"phase.h"
#include"init.h"
#include"color.h"

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
extern int develop_card_keep[10];
extern int keep_index;

//player
extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;

void score(uint8_t p){
    sPlayer * player;
    if(p==1) {player = p1;}
    else if(p==2) {player = p2;}
    else if(p==3) {player = p3;}
    else {player = p4;}
    //cal
    uint16_t temp_score = (player->village.village_build * 1) + (player->city.city_build * 2);
    uint8_t knight_score = (player->M_knight == 1) ? 2 : 0;
    uint8_t road_score = (player->M_road==1) ? 2 : 0;
    uint16_t total = temp_score + knight_score + road_score + player->score_card;
    player->final_score = total;

    //judge
    if((player->final_score) >= 10){
        printf(RED"Player %d win this game!!!\e[0m\n",p);
    }
    return;
}

void take_resource_dice(int32_t harvest_resource[2][5]){
    sPlayer * player;
    for(int i=0;i<2;i++){
        for(int j=0;j<5;j++){
            if(j==1) {player = p1;}
            else if(j==2) {player = p2;}
            else if(j==3) {player = p3;}
            else {player = p4;}
            if(harvest_resource[i][0]!=-1){
                if(j!=0){
                    if(harvest_resource[i][0]==0){
                        if((resource[0]-harvest_resource[i][j])>=0){
                            player->iron += harvest_resource[i][j];
                            resource[0] -= harvest_resource[i][j];
                            player->hand += harvest_resource[i][j];
                        }else{
                            player->iron += resource[0];
                            player->hand += resource[0];
                            resource[0] = 0;
                        }
                    }else if(harvest_resource[i][0]==1){
                        if((resource[1]-harvest_resource[i][j])>=0){
                            player->wood += harvest_resource[i][j];
                            resource[1] -= harvest_resource[i][j];
                            player->hand += harvest_resource[i][j];
                        }else{
                            player->wood += resource[1];
                            player->hand += resource[1];
                            resource[1] = 0;
                        }
                    }else if(harvest_resource[i][0]==2){
                        if((resource[2]-harvest_resource[i][j])>=0){
                            player->wheat += harvest_resource[i][j];
                            resource[2] -= harvest_resource[i][j];
                            player->hand += harvest_resource[i][j];
                        }else{
                            player->wheat += resource[2];
                            player->hand += resource[2];
                            resource[2] = 0;
                        }
                    }else if(harvest_resource[i][0]==3){
                        if((resource[3]-harvest_resource[i][j])>=0){
                            player->brick += harvest_resource[i][j];
                            resource[3] -= harvest_resource[i][j];
                            player->hand += harvest_resource[i][j];
                        }else{
                            player->brick += resource[3];
                            player->hand += resource[3];
                            resource[3] = 0;
                        }
                    }else{
                        if((resource[4]-harvest_resource[i][j])>=0){
                            player->sheep += harvest_resource[i][j];
                            resource[4] -= harvest_resource[i][j];
                            player->hand += harvest_resource[i][j];
                        }else{
                            player->sheep += resource[4];
                            player->hand += resource[4];
                            resource[4] = 0;
                        }
                    }
                }
            }
        }
    }
    printf("%d %d %d %d %d\n",p1->iron,p1->wood,p1->wheat,p1->brick,p1->sheep);
    printf("%d %d %d %d %d\n",p2->iron,p2->wood,p2->wheat,p2->brick,p2->sheep);
    printf("%d %d %d %d %d\n",p3->iron,p3->wood,p3->wheat,p3->brick,p3->sheep);
    printf("%d %d %d %d %d\n",p4->iron,p4->wood,p4->wheat,p4->brick,p4->sheep);
    return;
}

int32_t dice(){
    return ((rand()%6+1)+(rand()%6+1));
}

void throw_dice(sPlayer * player, uint8_t is_ai, uint8_t player_number){
    int32_t dice_result = dice();
    if(!is_ai){ printf("p1 throw %d points\n",dice_result);}
    else{ printf("p%d throw %d points\n",player_number,dice_result);}
    //printf("%d\n",dice_result);
    //harvest resource array
    int32_t harvest_resource[2][5];
    harvest_resource[0][0] = 0;
    harvest_resource[0][1] = 1;
    harvest_resource[0][2] = 1;
    harvest_resource[0][3] = 1;
    harvest_resource[0][4] = 1;
    harvest_resource[1][0] = 4;
    harvest_resource[1][1] = 2;
    harvest_resource[1][2] = 4;
    harvest_resource[1][3] = 5;
    harvest_resource[1][4] = 2;
    //test
    //dice_result = 7;
    if(dice_result==7){
        //thief action
        thief_action(player,is_ai);
    }else{
        //harvest(dice_result,&harvest_resource[0][0]);
        take_resource_dice(harvest_resource);
    }
    return;
}

void list_can_trade(sPlayer * player, uint8_t trade_option){
    //1->bank
    //2->harbor
    bool line = false;
    if(trade_option==1){
        printf("___________________________________\n");
        if(player->iron >= 4){
            line = true;
            printf("|");
            printf(PURPLE"You can use iron to trade.\e[0m\t  ");
            printf("|\n");
        }
        if(player->wood >= 4){
            line = true;
            printf("|");
            printf(CYAN"You can use wood to trade.\e[0m\t  ");
            printf("|\n");
        }
        if(player->wheat >= 4){
            line = true;
            printf("|");
            printf(YELLOW"You can use wheat to trade.\e[0m\t  ");
            printf("|\n");
        }
        if(player->brick >= 4){
            line = true;
            printf("|");
            printf(RED"You can use brick to trade.\e[0m\t  ");
            printf("|\n");
        }
        if(player->sheep >= 4){
            line = true;
            printf("|");
            printf(L_GREEN"You can use wool(sheep) to trade.\e[0m");
            printf("|\n");
        }
        if(line){
            printf("-----------------------------------\n");
        }
    }else{}
    //printf("------------------>\n");
    printf(PURPLE"iron(0) "CYAN"wood(1) "YELLOW"wheat(2) "RED"brick(3) " L_GREEN"wool(4)\e[0m\n");
    // printf(PURPLE"0 -> iron\n");
    // printf(CYAN"1 -> wood\n");
    // printf(YELLOW"2 -> wheat\n");
    // printf(RED"3 -> brick\n");
    // printf(L_GREEN"4 -> wool(sheep)\e[0m\n");
    return;
}

bool trade_judge(sPlayer * player, uint8_t trade_option, uint8_t type){
    uint8_t resource_to_trade = 0;
    if(type==0) { resource_to_trade = player->iron;}
    else if(type==1) { resource_to_trade = player->wood;}
    else if(type==2) { resource_to_trade = player->wheat;}
    else if(type==3) { resource_to_trade = player->brick;}
    else { resource_to_trade = player->sheep;}

    if(trade_option==1){
        if(resource_to_trade >= 4){ return true;}
        else{ return false;}
    }else{}
}

void trade(sPlayer * player, uint8_t is_ai, uint8_t give_type){
    int32_t trade_cho = -1;
    uint8_t *temp[5]={&(player->iron),&(player->wood),&(player->wheat),&(player->brick),&(player->sheep)};
    if(!is_ai){
        printf("Which resource you want to get ? (0-4): ");
        scanf("%d",&trade_cho);
    }else{
        while(1){
            trade_cho = rand() % 5;
            if(trade_cho!=give_type){ break;}
        }
    }
    *(temp[give_type]) -= 4;
    *(temp[trade_cho]) += 1;
    player->hand -= 3;
    resource[give_type] += 4;
    resource[trade_cho] -= 1;
    printf("%d %d %d %d %d\n",player->iron,player->wood,player->wheat,player->brick,player->sheep);
    printf("%d\n",player->hand);
    return;
}