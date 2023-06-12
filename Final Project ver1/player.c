#include"phase.h"
#include"data.h"
#include"init.h"
#include"color.h"

extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;

//玩家行為
void player_move(){
    printf(RED"#This is Player 1's turn.\e[0m\n");
    //throw dice for player
    //throw_dice(p1,0,1);
    //print_map

    while(1){
        //choose
        PASS;
        printf(BLUE"0 -> End this round!!\n");
        printf("1 -> Build\n");
        printf("2 -> Upgrade the Village to City!!\n");
        printf("3 -> Develop Card\n");
        printf("4 -> Trade\e[0m\n");
        //printf("Trade with Player\n");
        printf("Which move do you want to do ? (0-4): ");
        int32_t cho = 0;
        int32_t cho_move = 0;
        scanf("%d",&cho);
        switch(cho)
        {
            case 0:
                printf(RED"# Player 1's turn end.\e[0m\n");
                return;
            case 1:
                PASS;
                printf(BLUE"0 -> Cancel\n");
                printf("1 -> Build the Village!!\n");
                printf("2 -> Build the Road!!\e[0m\n");
                printf("Which move do you want to do ? (0-2): ");
                scanf("%d",&cho_move);
                if(cho_move==0){
                    printf(RED"Build Action End!!\e[0m\n");
                    break;
                }else if(cho_move==1){
                }else{
                }
                break;
                printf(RED"Build Action End!!\e[0m\n");
            case 2:
                //upgrade
                break;
            case 3:
                PASS;
                printf(BLUE"0 -> Cancel\n");
                printf("1 -> Buy the develop card!!\n");
                printf("2 -> Use the develop card!!\e[0m\n");
                printf("Which move do you want to do ? (0-2): ");
                scanf("%d",&cho_move);
                if(cho_move==0){
                    printf(RED"Develop Card Action End!!\e[0m\n");
                    break;
                }else if(cho_move==1){
                    if(judge_buy_card(p1)){
                        get_develop_card(p1,1);
                    }else{
                        printf("You don't have enough resource to buy!!\n");
                    }
                }else{
                    //use card
                }
                printf(RED"Develop Card Action End!!\e[0m\n");
                break;
            case 4:
                PASS;
                printf(BLUE"0 -> Cancel\n");
                printf("1 -> Trade with Bank!!\n");
                printf("2 -> Trade with Harbor!!\e[0m\n");
                printf("Which move do you want to do ? (0-2): ");
                scanf("%d",&cho_move);
                int32_t trade_cho_give = 0;
                if(cho_move==0){
                    printf(RED"*Trade End*\e[0m\n");
                    break;
                }else if(cho_move==1){
                    //bank
                    list_can_trade(p1,1);
                    while(1){
                        //CLEAR;
                        //printf("-------------------->\n");
                        printf("Which 4 same resource do you want to give ? (0-4): ");
                        scanf("%d",&trade_cho_give);
                        if(trade_judge(p1,1,trade_cho_give)){
                            trade(p1,0,trade_cho_give);
                            break;
                        }else{
                            printf("-->You can't use this resource to trade with Bank!!\n");
                            printf("   You can press y to redo your choice,\n");
                            printf("   Or press n to end this action!\n");
                            PASS;
                            printf("Do you want to keep trading with Bank ? (y or n): ");
                            char cyn[2] = {0};
                            scanf("%s",cyn);
                            if(cyn[0]=='n'||cyn[0]=='N') {break;}
                        }
                    }
                }else{
                    //harbor
                }
                printf(RED"*Trade End*\e[0m\n");
                break;
            default:
                break;
        }
        //CLEAR;
        //print_map()
    }
}