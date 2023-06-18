#include"phase.h"
#include"data.h"
#include"init.h"
#include"color.h"
#include"card.h"
#include"map.h"

extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;
extern int resource[5];//sum is 95

void some_ai_logic(sPlayer * player, uint8_t type){
    //0->village
    //1->road
    //2->upgrade
    //3->buy
    //4->hand check
}

//判斷6個行為可不可以做
bool judge_ai_action(uint8_t action, uint8_t player_number){
    sPlayer * player;
    if(player_number==1) {player = p1;}
    else if(player_number==2) {player = p2;}
    else if(player_number==3) {player = p3;}
    else if(player_number==4) {player = p4;}
    int32_t village_cho = 0;
    int32_t road_cho = 0;
    uint8_t chance = 0;
    //0->get        1->use         2->road
    //3->village    4->upgrade     5->trade(bank)
    //6->trade(harbor)(2:1)     7->trade(harbor)(3:1)
    if(action==0){
        if(judge_buy_card(player)){ return true;}
    }else if(action==1){
        //can reset ai's hard
        //use
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
        if(judge_build(player,1,player_number)){
            return true;
        }else{ return false;}
    }else if(action==3){
        //build village
        if(judge_build(player,0,player_number)){
            return true;
        }else{ return false;}
    }else if(action==4){
        //upgrade village
        if(judge_build(player,2,player_number)){
            return true;
        }else{ return false;}
    }else if(action==5 || action==6 || action==7){
        int port[6] = {0};
        find_port(player_number,&port[0]);
        int32_t option = 0;
        if(action!=5){ option = (action==6) ? 2 : 3;}
        else { option = 1;}
        //printf("option is %d\n",option);
        uint8_t resource_type[5] = {0,1,2,3,4};
        for(int i=0;i<5;i++){
            int j = i + rand()/(RAND_MAX/(5-i)+1);
            int temp = resource_type[j];
            resource_type[j] = resource_type[i];
            resource_type[i] = temp;
        }
        for(int i=0;i<5;i++){
            if(player->hand >= 7){
                if(trade_judge(player,option,resource_type[i])){
                    if(action==6){
                        if(port[resource_type[i]] == 1){
                            trade(player,1,resource_type[i],option);
                        }
                    }else if(action==7){
                        if(port[5] == 1){
                            trade(player,1,resource_type[i],option);
                        }
                    }else if(action==5){
                        trade(player,1,resource_type[i],option);
                    }
                    return true;
                }
            }
        }
    }
    // }else if(action==8){
    //     // if(player->hand >= 5){
    //     //     int32_t td = rand() % 
    //     // }
    // }
    return false;
}

void ai_move(int p){
    //print_init(p);
    map_log_update(p,"'s turn.",-1);
    REFRESH
    //which player
    sPlayer * player;
    if(p == 2) {player = p2;}
    else if(p == 3) {player = p3;}
    else if(p == 4) {player = p4;}

    //throw dice for ai(p)
    throw_dice(player,1,p);     //dice -> take resource or thief
    //hard pattern:
    //run 6 action again
    uint8_t again_action = 0;
    while((again_action==0)){
        //random action order
        //can reset ai's hard
        uint8_t action[8] = {0,1,2,3,4,5,6,7};
        for(int i=0;i<8;i++){
            int j = i + rand()/(RAND_MAX/(8-i)+1);
            int temp = action[j];
            action[j] = action[i];
            action[i] = temp;
        }
        // for(int i=0;i<8;i++){
        //     printf("%u ",action[i]);
        // }
        // printf("\n");
        for(int i=0;i<8;i++){
            sleep(1);
            if(judge_ai_action(action[i],p)){
                uint8_t can = rand() % 3;
                //2/3 will do this action
                if(can==1||can==2){
                    printf("ai's action is %u ",action[i]);
                    printf("\n");
                    //printf("B\n");
                    if(i==0){
                        get_develop_card(player,p);
                        map_log_update(p,"choose to get develop card",-1);
                        REFRESH
                        sleep(1);
                    }else if(i==1){
                        //use card
                        //have done
                        map_log_update(p,"choose to use develop card",-1);
                        REFRESH
                        sleep(1);
                    }else if(i==2){
                        //build road
                        //random 0-71
                        uint8_t count = 0;
                        while(count<30){
                            int32_t road_rand = rand() % 72;
                            if(build_road(p,road_rand,1)!=-1){
                                player->wood -= 1;
                                player->brick -= 1;
                                player->hand -= 2;
                                resource[1] += 1;
                                resource[3] += 1;
                                player->road.road_build += 1;
                                player->road.road_hand -= 1;
                                //map_log_update(p,"build a road",-1);
                                sleep(1);
                                break;
                            }
                            count++;
                        }
                    }else if(i==3){
                        //build village
                        //random 0-53
                        uint8_t count_V = 0;
                        while(count_V<25){
                            int32_t V_ran = rand() % 54;
                            if(build_village(p,V_ran,0,1)!=-1){
                                (player->brick) -= 1;
                                (player->wheat) -= 1;
                                (player->wood) -= 1;
                                (player->sheep) -= 1;
                                resource[1] += 1;
                                resource[2] += 1;
                                resource[3] += 1;
                                resource[5] += 1;
                                player->hand -= 4;
                                (player->village.village_build) += 1;
                                (player->village.village_hand) -= 1;
                                //map_log_update(p,"build a village",-1);
                                sleep(1);
                                break;
                            }
                            count_V++;
                        }
                    }else if(i==4){
                        //upgrade
                        //Need to find which can be upgraded
                        uint8_t count_u = 0;
                        while(count_u<25){
                            int32_t UP_vil = rand() % 54;
                            if(village_upgrade(p,UP_vil,1)){
                                player->wheat -= 2;
                                player->iron -= 3;
                                resource[2] += 2;
                                resource[0] += 3;
                                player->hand -= 5;
                                player->city.city_build++;
                                player->city.city_hand--;
                                player->village.village_build--;
                                player->village.village_hand++;
                                //map_log_update(p,"upgrade its village to city.",-1);
                                break;
                            }
                            count_u++;
                        }
                        sleep(1);
                    }else if(i==5){
                        map_log_update(p,"chooses to trade with bank.",-1);
                        REFRESH
                        sleep(1);
                    }else if(i==6){
                        map_log_update(p,"chooses to trade with harbor(2:1).",-1);
                        REFRESH
                        sleep(1);
                    }else if(i==7){
                        map_log_update(p,"chooses to trade with harbor(3:1).",-1);
                        REFRESH
                        sleep(1);
                    }
                }
            }
        }
        //again_action = rand() % 3;
        again_action = 1;
    }
    if(keep_index!=0){
        save_develop_card(p);
    }
    player->U_develop = 0;
    sleep(1);
    return;
}