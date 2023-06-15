#include"data.h"
#include"init.h"
#include"phase.h"
#include"map.h"
#include"card.h"

extern int source_region[19];
extern int temp_num[18];
extern int region[19];
extern int develop_card_order[25];
extern int develop_index;

extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;

void print_init(uint8_t p){
    sPlayer * player;
    if(p==1) {player = p1;}
    else if(p==2) {player = p2;}
    else if(p==3) {player = p3;}
    else {player = p4;}
    printf("-------------\n");
    // for(int i=0;i<19;i++){
    //     printf("%d ",source_region[i]);
    // }
    // printf("\n");
    // printf("-------------\n");
    // for(int i=0;i<19;i++){
    //     printf("%d ",region[i]);
    // }
    // printf("\n");
    // printf("-------------\n");
    // for(int i=0;i<25;i++){
    //     printf("%d %d\n",develop_card_order[i],develop_index++);
    // }
    // develop_index = 0;
    // printf("-------------\n");
    printf("player %d\n",p);
    printf("iron = %u\n",player->iron);
    printf("wood = %u\n",player->wood);
    printf("wheat = %u\n",player->wheat);
    printf("brick = %u\n",player->brick);
    printf("sheep = %u\n",player->sheep);
    printf("knight card = %u\n",player->knight);
    printf("U_knight = %u\n",player->U_knight);
    printf("harvest = %u\n",player->harvest_card);
    printf("build_card = %u\n",player->build_card);
    printf("steal_card = %u\n",player->steal_card);
    printf("score_card = %u\n",player->score_card);
    printf("U_develop = %u\n",player->U_develop);
    printf("M_knight = %u\n",player->M_knight);
    printf("M_road = %u\n",player->M_road);
    printf("road_build = %u\n",player->road.road_build);
    printf("road_hand = %u\n",player->road.road_hand);
    printf("city_build = %u\n",player->city.city_build);
    printf("city_hand = %u\n",player->city.city_hand);
    printf("village_build = %u\n",player->village.village_build);
    printf("village_hand = %u\n",player->village.village_hand);
    printf("hand = %u\n",player->hand);
    printf("final_score = %u\n",player->final_score);
    printf("----------------------------------------\n");
    printf("iron remain = %d\n",resource[0]);
    printf("wood remain = %d\n",resource[1]);
    printf("wheat remain = %d\n",resource[2]);
    printf("brick remain = %d\n",resource[3]);
    printf("wool remain = %d\n",resource[4]);
    printf("----------------------------------------\n");
    printf("knight remain = %d\n",knight_remain);
    printf("harvest remain = %d\n",progress_remain[0]);
    printf("build remain = %d\n",progress_remain[1]);
    printf("steal remain = %d\n",progress_remain[2]);
    printf("score remain = %d\n",score_remain);
    printf("----------------------------------------->>\n");
    return;
}