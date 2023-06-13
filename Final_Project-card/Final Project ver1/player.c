#include"phase.h"
#include"data.h"
#include"init.h"

extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;

//玩家行為
void player_move(){
    printf("#This is Player 1's turn.\n");
    //throw dice for player
    throw_dice(p1,0,1);
    //print_map

    while(1){
        //choose
        PASS;
        printf("1 -> Build the Village!!\n");
        printf("2 -> Build the Road!!\n");
        printf("3 -> Upgrade the Village to City!!\n");
        printf("4 -> Buy the develop card!!\n");
        printf("5 -> Use the develop card!!\n");
        printf("6 -> Trade with Bank!!\n");
        printf("7 -> Trade with Harbor!!\n");
        printf("8 -> End this round!!\n");
        printf("Which move do you want to do ?(): ");
        int32_t cho = 0;
        scanf("%d",&cho);
        switch(cho)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                if(judge_buy_card(p1)){
                    get_develop_card(p1);
                }
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            default:
                break;
        }
        //CLEAR;
        //print_map()
    }
}