#include"data.h"
#include"init.h"
#include"phase.h"

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
    printf("%u\n",player->iron);
    printf("%u\n",player->wood);
    printf("%u\n",player->wheat);
    printf("%u\n",player->brick);
    printf("%u\n",player->sheep);
    printf("%u\n",player->knight);
    printf("%u\n",player->U_knight);
    printf("%u\n",player->harvest_card);
    printf("%u\n",player->build_card);
    printf("%u\n",player->steal_card);
    printf("%u\n",player->score_card);
    printf("%u\n",player->U_develop);
    printf("%u\n",player->M_knight);
    printf("%u\n",player->M_road);
    printf("%u\n",player->road.road_build);
    printf("%u\n",player->road.road_hand);
    printf("%u\n",player->city.city_build);
    printf("%u\n",player->city.city_hand);
    printf("%u\n",player->village.village_build);
    printf("%u\n",player->village.village_hand);
    printf("%u\n",player->hand);
    printf("%u\n",player->final_score);
    printf("----------------------------------------->>\n");
    return;
}