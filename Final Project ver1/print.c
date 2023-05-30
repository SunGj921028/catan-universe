#include"data.h"
#include"init.h"

extern int source_region[19];
extern int temp_num[18];
extern int region[19];
extern int develop_card_order[25];
extern int develop_index;

extern sPlayer * you;
extern sPlayer * A;
extern sPlayer * B;
extern sPlayer * C;

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
    printf("-------------\n");
    printf("%u\n",you->build_card);
    printf("%u\n",A->iron);
    printf("%u\n",B->city.city_hand);
    printf("%u\n",C->road.road_hand);
    return;
}