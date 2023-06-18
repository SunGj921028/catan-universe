#include"phase.h"
#include"data.h"
#include"init.h"
#include"color.h"
#include"map.h"
#include"card.h"

extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;

//玩家行為
void player_move(){
    //print_map
    map_log_update(1,"'s turn.",-1);
    //map_print(0);
    sleep(1);
    //throw dice for player
    throw_dice(p1,0,1);
    REFRESH

    while(1){
        //choose
        PASS;
        printf(L_BLUE"0 -> End this round!!\n");
        printf("1 -> Build\n");
        printf("2 -> Upgrade the Village to City!!\n");
        printf("3 -> Develop Card\n");
        printf("4 -> Trade\e[0m\n");
        printf("Which move do you want to do ? (0-4): ");
        int32_t cho = 0;
        int32_t cho_move = 0;
        int32_t village_number = 0;
        int32_t road_number = 0;
        int32_t redo = 0;
        int32_t can_build[54] = {0};
        if((scanf("%d",&cho)) == 0){
            REFRESH
            printf(RED"Wrong Input!!\e[0m\n");
            while (getchar() != '\n');
            continue;
        }else{
            if(scanf("%c",&extra)==1 && extra != '\n'){
                REFRESH
                printf(RED"Wrong Input!!\e[0m\n");
                while (getchar() != '\n');
                continue;
            }
        }
        if(cho<0 || cho>4){
            REFRESH
            printf(RED"Wrong Input!!\e[0m\n");
            continue;
        }
        switch(cho)
        {
            case 0:
                map_log_update(1,"'s turn end.",-1);
                if(keep_index!=0){
                    save_develop_card(1);
                    p1->U_develop = 0;
                }
                REFRESH
                sleep(2);
                return;
            case 1:
                PASS;
                while(1){
                    printf(L_BLUE"0 -> Cancel\n");
                    printf("1 -> Build the Village!!\n");
                    printf("2 -> Build the Road!!\e[0m\n");
                    printf("Which move do you want to do ? (0-2): ");
                    if((scanf("%d",&cho_move)) == 0){
                        REFRESH
                        printf(RED"Wrong Input!!\e[0m\n");
                        while (getchar() != '\n');
                        continue;
                    }else{
						if(scanf("%c",&extra)==1 && extra != '\n'){
                            REFRESH
							printf(RED"Wrong Input!!\e[0m\n");
							while (getchar() != '\n');
							continue;
						}else{
                            if(cho_move<0 || cho_move>2){
                                REFRESH
                                printf(RED"Wrong Input!!\e[0m\n");
                                continue;
                            }
                            break;
                        }
					}
                }
                if(cho_move==0){
                    REFRESH
                    printf(RED"Build Action End!!\e[0m\n");
                    sleep(1);
                    break;
                }else if(cho_move==1){
                    if(!judge_build(p1,0,1,&can_build[0])){
                        REFRESH
                        printf(RED"You don't have enough resource to build village!!\e[0m\n");
                        break;
                    }
                    while(1){
                        map_print(1);
                        printf("Which point you want to build Village ? (0-53): ");
                        if((scanf("%d",&village_number)) == 0){
                            printf(RED"Wrong Input!!\e[0m\n");
                            while (getchar() != '\n');
                            continue;
                        }else{
                            if(scanf("%c",&extra)==1 && extra != '\n'){
                                printf(RED"Wrong Input!!\e[0m\n");
                                while (getchar() != '\n');
                                continue;
                            }
                        }
                        if(build_village(1,village_number,0,0) == -1){
                            while(1){
                                printf("Do you want keep building village ? (0 or 1): ");
                                if((scanf("%d",&redo)) == 0){
                                    printf(RED"Wrong Input!!\e[0m\n");
                                    while (getchar() != '\n');
                                    continue;
                                }else{
                                    if(scanf("%c",&extra)==1 && extra != '\n'){
                                        printf(RED"Wrong Input!!\e[0m\n");
                                        while (getchar() != '\n');
                                        continue;
                                    }else{
                                        if(redo<0||redo>1){
                                            REFRESH
                                            printf(RED"Wrong Input!!\n");
                                            continue;
                                        }
                                        break;
                                    }
                                }
                            }
                            if(redo==1){
                                continue;
                            }else{break;}
                        }else{
                            p1->wheat--;
                            p1->brick--;
                            p1->wood--;
                            p1->sheep--;
                            p1->hand -= 4;
                            p1->village.village_build++;
                            p1->village.village_hand--;
                            break;
                        }
                    }
                    REFRESH
                }else if(cho_move==2){
                    if(!judge_build(p1,1,1,&can_build[0])){
                        REFRESH
                        printf(RED"You don't have enough resource to build road!!\e[0m\n");
                        break;
                    }
                    while(1){
                        map_print(2);
                        printf("Which point you want to build Road ? (0-71): ");
                        if((scanf("%d",&road_number)) == 0){
                            printf(RED"Wrong Input!!\e[0m\n");
                            while (getchar() != '\n');
                            continue;
                        }else{
                            if(scanf("%c",&extra)==1 && extra != '\n'){
                                printf(RED"Wrong Input!!\e[0m\n");
                                while (getchar() != '\n');
                                continue;
                            }
                        }
                        if(build_road(1,road_number,0) == -1){
                            while(1){
                                printf("Do you want keep building road ? (0 or 1): ");
                                if((scanf("%d",&redo)) == 0){
                                    printf(RED"Wrong Input!!\e[0m\n");
                                    while (getchar() != '\n');
                                    continue;
                                }else{
                                    if(scanf("%c",&extra)==1 && extra != '\n'){
                                        printf(RED"Wrong Input!!\e[0m\n");
                                        while (getchar() != '\n');
                                        continue;
                                    }else{
                                        if(redo<0||redo>1){
                                            REFRESH
                                            printf(RED"Wrong Input!!\e[0m\n");
                                            continue;
                                        }
                                        break;
                                    }
                                }
                            }
                            if(redo==1){
                                continue;
                            }else{
                                break;
                            }
                        }else{
                            p1->wood--;
                            p1->brick--;
                            p1->hand -= 2;
                            p1->road.road_build++;
                            p1->road.road_hand--;
                            break;
                        }
                    }
                }
                REFRESH
                break;
            case 2:
                //upgrade
                if(!judge_build(p1,2,1,&can_build[0])){
                    REFRESH
                    printf(RED"You don't have enough resource to upgrade your village!!\e[0m\n");
                    break;
                }
                while(1){
                    map_print(1);
                    printf("Which Village you want to Upgrade ? (0-53): ");
                    if((scanf("%d",&village_number)) == 0){
                        printf(RED"Wrong Input!!\e[0m\n");
                        while (getchar() != '\n');
                        continue;
                    }else{
						if(scanf("%c",&extra)==1 && extra != '\n'){
							printf(RED"Wrong Input!!\e[0m\n");
							while (getchar() != '\n');
							continue;
						}
					}
                    if(village_upgrade(1,village_number,0) != -1){
                        p1->wheat -= 2;
                        p1->iron -= 3;
                        p1->hand -= 5;
                        p1->city.city_build++;
                        p1->city.city_hand--;
                        p1->village.village_build--;
                        p1->village.village_hand++;
                        break;
                    }else{
                        while(1){
                            printf("Do you want keep Upgrading Village ? (0 or 1): ");
                            if((scanf("%d",&redo)) == 0){
                                printf(RED"Wrong Input!!\e[0m\n");
                                while (getchar() != '\n');
                                continue;
                            }else{
                                if(scanf("%c",&extra)==1 && extra != '\n'){
                                    printf(RED"Wrong Input!!\e[0m\n");
                                    while (getchar() != '\n');
                                    continue;
                                }else{
                                    if(redo<0||redo>1){
                                        REFRESH
                                        printf(RED"Wrong Input!!\e[0m\n");
                                        continue;
                                    }
                                    break;
                                }
                            }
                        }
                        if(redo==1){
                            continue;
                        }else{
                            break;
                        }
                    }
                }
                REFRESH
                break;
            case 3:
                PASS;
                while(1){
                    REFRESH
                    printf(L_BLUE"0 -> Cancel\n");
                    printf("1 -> Buy the develop card!!\n");
                    printf("2 -> Use the develop card!!\e[0m\n");
                    printf("Which move do you want to do ? (0-2): ");
                    if((scanf("%d",&cho_move)) == 0){
                        printf(RED"Wrong Input!!\e[0m\n");
                        while (getchar() != '\n');
                        continue;
                    }else{
						if(scanf("%c",&extra)==1 && extra != '\n'){
							printf(RED"Wrong Input!!\e[0m\n");
							while (getchar() != '\n');
							continue;
						}else{
                            if(cho_move<0 || cho_move>2){
                                printf(RED"Wrong Input!!\e[0m\n");
                                continue;
                            }else{
                                break;
                            }
                        }
					}
                }
                if(cho_move==0){
                    REFRESH
                    printf(RED"Develop Card Action End!!\e[0m\n");
                    break;
                }else if(cho_move==1){
                    if(judge_buy_card(p1)){
                        get_develop_card(p1,1);
                        //printf("%d\n",keep_index);
                    }else{
                        printf(RED"You don't have enough resource to buy!!\e[0m\n");
                    }
                    REFRESH
                }else if(cho_move==2){
                    //use card
                    int cho_card = 0;
                    while(1){
                        REFRESH
                        develop_card_state(p1,1,0);
                        printf("Which develop card you want to use ? (0-3): ");
                        if((scanf("%d",&cho_card)) == 0){
                            printf(RED"Wrong Input!!\e[0m\n");
                            while (getchar() != '\n');
                            continue;
                        }else{
                            if(scanf("%c",&extra)==1 && extra != '\n'){
                                printf(RED"Wrong Input!!\e[0m\n");
                                while (getchar() != '\n');
                                continue;
                            }else{
                                if(cho_card<0 || cho_card>3){
                                    printf(RED"Wrong Input Of using card!!\e[0m\n");
                                    continue;
                                }else{
                                    break;
                                }
                            }
                        }
                    }
                    if(use_card_state(1,cho_card,0)==-1){
                        REFRESH
                        printf(RED"You can't use any card in this round!!\e[0m\n");
                        break;
                    }
                    REFRESH
                }
                REFRESH
                break;
            case 4:
                while(1){
                    REFRESH
                    PASS;
                    printf(L_BLUE"0 -> Cancel\n");
                    printf("1 -> Trade with Bank!!\n");
                    printf("2 -> Trade with Harbor!!\n");
                    printf("3 -> Trade with Player!!\e[0m\n");
                    printf("Which move do you want to do ? (0-3): ");
                    if((scanf("%d",&cho_move)) == 0){
                        printf(RED"Wrong Input!!\e[0m\n");
                        while (getchar() != '\n');
                        continue;
                    }else{
						if(scanf("%c",&extra)==1 && extra != '\n'){
							printf(RED"Wrong Input!!\e[0m\n");
							while (getchar() != '\n');
							continue;
						}else{
                            if(cho_move<0 || cho_move>3){
                                printf(RED"Wrong Input!!\e[0m\n");
                                continue;
                            }else{
                                break;
                            }
                        }
					}
                }
                int32_t trade_cho_give = 0;
                if(cho_move==0){
                    REFRESH
                    printf(RED"*Trade End*\e[0m\n");
                    break;
                }else if(cho_move==1){
                    REFRESH
                    //bank
                    if(list_can_trade(p1,1,0)==-1){
                        printf(RED"You don't have any resource can be traded.\e[0m\e[0m\n");
                        break;
                    }
                    while(1){
                        printf("Which 4 same resource do you want to give ? (0-4): ");
                        if((scanf("%d",&trade_cho_give)) == 0){
                            printf(RED"Wrong Input!!\e[0m\n");
                            while (getchar() != '\n');
                            continue;
                        }else{
                            if(scanf("%c",&extra)==1 && extra != '\n'){
                                printf(RED"Wrong Input!!\e[0m\n");
                                while (getchar() != '\n');
                                continue;
                            }
                        }
                        if(trade_cho_give<0 || trade_cho_give>4){
                            printf(RED"Wrong Input!!\e[0m\n");
                            continue;
                        }
                        if(trade_judge(p1,1,trade_cho_give)){
                            trade(p1,0,trade_cho_give,1);
                            break;
                        }else{
                            REFRESH
                            printf(YELLOW"-->You can't use this resource to trade with Bank!!\n");
                            printf("   You can press y to redo your choice,\n");
                            printf("   Or press n to end this action!\e[0m\n");
                            PASS;
                            char cyn[20] = {0};
                            while(1){
                                printf("Do you want to keep trading with Bank ? (y or n): ");
                                fgets(cyn,20,stdin);
                                cyn[strlen(cyn)-1] = '\0';
                                if(strlen(cyn)!=1){ printf(RED"Wrong Input!!\e[0m\n");fflush(stdout);continue;}
                                if(cyn[0]=='n'||cyn[0]=='N') {break;}
                                if(cyn[0]=='y'||cyn[0]=='Y') {break;}
                            }
                            if(cyn[0]=='n'||cyn[0]=='N') {break;}
                        }
                    }
                    REFRESH
                }else if(cho_move==2){
                    REFRESH
                    //harbor
                    //list the harbor you can trade and ask which or do you want
                    int32_t harbor_cho = 0;
                    int32_t port[6] = {0};
                    find_port(1,&port[0]);
                    bool ok = false;
                    for(int i=0;i<6;i++){
                        if(port[i]==1){ok = true; break;}
                    }
                    while(ok){
                        printf("1 -> Trade by 2:1\n");
                        printf("2 -> Trade by 3:1\n");
                        printf("Which harbor you want to trade with ? (1 or 2): ");
                        if((scanf("%d",&harbor_cho)) == 0){
                            printf(RED"Wrong Input!!\e[0m\n");
                            while (getchar() != '\n');
                            continue;
                        }else{
                            if(scanf("%c",&extra)==1 && extra != '\n'){
                                printf(RED"Wrong Input!!\e[0m\n");
                                while (getchar() != '\n');
                                continue;
                            }
                        }
                        if(harbor_cho!=1 && harbor_cho!=2){ printf(RED"Wrong Input!!\e[0m\n"); continue;}
                        //judge
                        bool can_trade = false;
                        if(harbor_cho==1){
                            for(int i=0;i<5;i++){
                                if(port[i]==1){ can_trade = true; break;}
                            }
                        }else if(harbor_cho==2){
                            if(port[5]==1){
                                break;
                            }
                        }
                        if(!can_trade){
                            REFRESH
                            if(harbor_cho==1){
                                printf(RED"You don't have (2:1) harbor.\e[0m\n");
                            }else if(harbor_cho==2){
                                printf(RED"You don't have (3:1) harbor.\e[0m\n");
                            }
                        }else{break;}
                    }
                    //cho_type 1->(2:1) 2->(3:1)
                    //list_can_trade(p1,harbor_cho);
                    if(ok){
                        int32_t res_cho = 0;
                        if(harbor_cho==1){
                            while(1){
                                REFRESH
                                printf(PURPLE"iron(0) "CYAN"wood(1) "YELLOW"wheat(2) "RED"brick(3) " L_GREEN"wool(4)\e[0m\n");
                                printf("Which same resource do you want to give for 2 to 1 trade? (0-4): ");
                                if((scanf("%d",&res_cho)) == 0){
                                    printf(RED"Wrong Input!!\e[0m\n");
                                    while (getchar() != '\n');
                                    continue;
                                }else{
                                    if(scanf("%c",&extra)==1 && extra != '\n'){
                                        printf(RED"Wrong Input!!\e[0m\n");
                                        while (getchar() != '\n');
                                        continue;
                                    }
                                }
                                if(res_cho<0 || res_cho>4){
                                    printf(RED"Wrong Input!!\e[0m\n");
                                    continue;
                                }
                                if(port[res_cho]!=1 || (trade_judge(p1,2,res_cho))==false){
                                    printf(RED"You can't use this resource to trade!!\e[0m\n");
                                    continue;
                                }else{
                                    break;
                                }
                            }
                        }else{
                            while(1){
                                REFRESH
                                printf(PURPLE"iron(0) "CYAN"wood(1) "YELLOW"wheat(2) "RED"brick(3) " L_GREEN"wool(4)\e[0m\n");
                                printf("Which same resource do you want to give for 3 to 1 trade? (0-4): ");
                                if((scanf("%d",&res_cho)) == 0){
                                    printf(RED"Wrong Input!!\e[0m\n");
                                    while (getchar() != '\n');
                                    continue;
                                }else{
                                    if(scanf("%c",&extra)==1 && extra != '\n'){
                                        printf(RED"Wrong Input!!\e[0m\n");
                                        while (getchar() != '\n');
                                        continue;
                                    }
                                }
                                if(res_cho<0 || res_cho>4){
                                    printf(RED"Wrong Input!!\e[0m\n");
                                    continue;
                                }
                                if((trade_judge(p1,3,res_cho))==false){
                                    printf(RED"You can't use this resource to trade!!\e[0m\n");
                                    continue;
                                }else{
                                    break;
                                }
                            }
                        }
                        trade(p1,0,res_cho,harbor_cho+1);
                        REFRESH
                    }else{
                        REFRESH
                        printf(RED"You don't have any harbor!!\e[0m\n");
                    }
                    sleep(1);
                    REFRESH
                }else if(cho_move==3){
                }else{
                    printf(RED"Wrong Input!!\e[0m\n");
                }
                break;
            default:
                printf(RED"Wrong Input!!\e[0m\n");
                break;
        }
    }
}
