#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*0:沙漠 1:丘陵 2:山脈 3:草原 4:森林 5:麥田*/
extern int source_region[19];
extern int temp_num[18];
extern int region[19];
//0 knight(14) 1 progress(6) 2 score(5)
extern int develop_card_order[25];
extern int develop_index;
//0 rock 1 wood 2 wheat 3 brick 4 sheep
extern int resource[5];//sum is 95
//knight storage
extern int knight_remain;
//progress storage
extern int progress_remain[3];
//score remain
extern int score_remain;
//develop_card_remain
extern int develop_card_remain;
int first=0;
//初始頁面
int32_t startup();

//region
void init_region();
//標板塊數字
void region_num_initial();
//發展卡洗牌
void develop_card_init();
//print function
void print_init();
