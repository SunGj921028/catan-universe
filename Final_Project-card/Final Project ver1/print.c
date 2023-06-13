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

void print_init(){
    printf("-------------\n");
    for(int i=0;i<19;i++){
        printf("%d ",source_region[i]);
    }
    printf("\n");
    printf("-------------\n");
    for(int i=0;i<19;i++){
        printf("%d ",region[i]);
    }
    printf("\n");
    printf("-------------\n");
    for(int i=0;i<25;i++){
        printf("%d %d\n",develop_card_order[i],develop_index++);
    }
    develop_index = 0;
    printf("-------------\n");
    printf("%u\n",p1->build_card);
    printf("%u\n",p2->iron);
    printf("%u\n",p3->city.city_hand);
    printf("%u\n",p4->road.road_hand);
    // get_develop_card(p1);
    // printf("%u %u %u %u %u\n",p1->knight,p1->harvest_card,p1->build_card,p1->steal_card,p1->score_card);
    // get_develop_card(p2);
    return;
}