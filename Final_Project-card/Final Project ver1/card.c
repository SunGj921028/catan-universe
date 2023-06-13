#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include"data.h"
#include"card.h"
#include"map.h"
#include"color.h"
#include"phase.h"
#include"init.h"

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

//player
extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;

//顯示當下的手牌種類及數量
void develop_card_state(sPlayer * player,uint8_t player_number,uint8_t is_ai)
{
    if(is_ai==0)
    {
        printf("Player %d :\n",player_number);
        printf(GREEN"knight "YELLOW"harvest_card "L_BLUE"build_card "RED"steal_card " L_GREEN"score_card");
        printf("\n");
        printf(GREEN"%6d "YELLOW"%12d "L_BLUE"%10d "RED"%10d "L_GREEN"%10d",player->knight,player->harvest_card,player->build_card,player->steal_card,player->score_card);
        printf("\n");
        printf(GREEN"used_knight ");
        printf("\n");
        printf(GREEN"%11d ",player->U_knight);
        printf("\n");
        printf(WHITE"\n");
    }
    else
    {
        printf("AI is checking their developing cards\n");
    }
}

int32_t knight_card(sPlayer * player,uint8_t player_number,uint8_t is_ai)
{
 //move thief
}

void harvest_card(sPlayer * player,uint8_t player_number,uint8_t is_ai)
{
    int32_t take_resource1 = 0;  
    int8_t count = 1;
    if(is_ai==0)
    {
        printf("Player uses the harvest_card\n");
        while(count<3)
        {
            while(1)
            {
                printf("Please input the resource serial number you want to get\n");
                printf(GRAY"iron(0) "WHITE"wood(1) "YELLOW"wheat(2) "RED"brick(3) " L_GREEN"wool(4) ");
                printf("\n");
                scanf("%d",&take_resource1);
                if((take_resource1>4)||(take_resource1<0))
                {
                    printf("Error,you should check your input again\n");
                    continue;
                }

                if(resource[take_resource1]==0)
                {
                    printf("the resuorce you choose is none left\n");
                    printf("you should change your input\n");
                    continue;
                }
                else
                {
                    if(take_resource1==0)
                    {
                        player->iron++;
                        resource[take_resource1]--;
                    }
                    else if(take_resource1==1)
                    {
                        player->wood++;
                        resource[take_resource1]--;
                    }            
                    else if(take_resource1==2)
                    {
                        player->wheat++;
                        resource[take_resource1]--;
                    }            
                    else if(take_resource1==3)
                    {
                        player->brick++;
                        resource[take_resource1]--;
                    }            
                    else if(take_resource1==4)
                    {
                        player->sheep++;
                        resource[take_resource1]--;
                    }
                    take_resource1 = 0;
                    count++;
                    break;
                }
            }
        }
    }
        
    else if(is_ai==1)//ai的部份
    {
        while(count<3)
        {
            while(1)
            {
                take_resource1= rand() % 5;
                if(resource[take_resource1]==0)
                {
                    continue;
                }
                else
                {
                    if(take_resource1==0)
                    {
                        player->iron++;
                        resource[take_resource1]--;
                    }
                    else if(take_resource1==1)
                    {
                        player->wood++;
                        resource[take_resource1]--;
                    }            
                    else if(take_resource1==2)
                    {
                        player->wheat++;
                        resource[take_resource1]--;
                    }            
                    else if(take_resource1==3)
                    {
                        player->brick++;
                        resource[take_resource1]--;
                    }            
                    else if(take_resource1==4)
                    {
                        player->sheep++;
                        resource[take_resource1]--;
                    }
                    take_resource1 = 0;
                    count++;
                    break;
                }
            }
        }        
    }
}

void build_card(sPlayer * player,uint8_t player_number,uint8_t is_ai)
{
    int8_t count = 1;
    int32_t road = 0;
    if(is_ai==0)
    {
        printf("Player uses the build_card\n");
        while(count<3)
        {
            while(1)
            {
                printf("Please input the road serial number you want to build\n");
                scanf("%d",&road);
                if(build_road(player_number,road)==0)
                {
                    break;
                }
            }
            road = 0;
            count++;
        }
    }
    else if(is_ai==1)//ai的部份
    {    
        while(count<3)
        {
            while(1)
            {
                road= rand() % 50;//確切的路數量
                if(build_road(player_number,road)==0)
                {
                    break;
                }
            }
            road = 0;
            count++;
        }            
    }    
}

//player1 is the people who uses the steal_card
void steal_card(sPlayer * player1,sPlayer * player2,sPlayer * player3,sPlayer * player4,uint8_t player_number,uint8_t is_ai)
{
    int32_t take_resource2 = 0;  
    int32_t get_resource = 0;
    if(is_ai==0)
    {
        printf("Player uses the steal_card\n");        
        while(1)
        {
            printf("Please input the resource serial number you want to get\n");
            printf(GRAY"iron(0) "WHITE"wood(1) "YELLOW"wheat(2) "RED"brick(3) " L_GREEN"wool(4) ");
            printf("\n");
            scanf("%d",&take_resource2);
            if((take_resource2>4)||(take_resource2<0))
            {
                printf("Error,you should check your input again\n");
                continue;
            }
            else
            {
                break;
            }                
        }
        if(take_resource2==0)
        {
            get_resource = get_resource + player2->iron;
            player2->iron = 0;
            get_resource = get_resource + player3->iron;
            player3->iron = 0;
            get_resource = get_resource + player4->iron;
            player4->iron = 0;
            player1->iron = player1->iron + get_resource;
        }
        else if(take_resource2==1)
        {
            get_resource = get_resource + player2->wood;
            player2->wood = 0;
            get_resource = get_resource + player3->wood;
            player3->wood = 0;
            get_resource = get_resource + player4->wood;
            player4->wood = 0;
            player1->wood = player1->wood + get_resource;
        }
        else if(take_resource2==2)
        {
            get_resource = get_resource + player2->wheat;
            player2->wheat = 0;
            get_resource = get_resource + player3->wheat;
            player3->wheat = 0;
            get_resource = get_resource + player4->wheat;
            player4->wheat = 0;
            player1->wheat = player1->wheat + get_resource;
        }
        else if(take_resource2==3)
        {
            get_resource = get_resource + player2->brick;
            player2->brick = 0;
            get_resource = get_resource + player3->brick;
            player3->brick = 0;
            get_resource = get_resource + player4->brick;
            player4->brick = 0;
            player1->brick = player1->brick + get_resource;
        }  
        else if(take_resource2==4)
        {
            get_resource = get_resource + player2->sheep;
            player2->sheep = 0;
            get_resource = get_resource + player3->sheep;
            player3->sheep = 0;
            get_resource = get_resource + player4->sheep;
            player4->sheep = 0;
            player1->sheep = player1->sheep + get_resource;
        }     
        get_resource = 0;                          
    }
    
    else if(is_ai==1)//ai的部份
    {           
        take_resource2= rand() % 5;               
        if(take_resource2==0)
        {
            get_resource = get_resource + player2->iron;
            player2->iron = 0;
            get_resource = get_resource + player3->iron;
            player3->iron = 0;
            get_resource = get_resource + player4->iron;
            player4->iron = 0;
            player1->iron = player1->iron + get_resource;
        }
        else if(take_resource2==1)
        {
            get_resource = get_resource + player2->wood;
            player2->wood = 0;
            get_resource = get_resource + player3->wood;
            player3->wood = 0;
            get_resource = get_resource + player4->wood;
            player4->wood = 0;
            player1->wood = player1->wood + get_resource;
        }
        else if(take_resource2==2)
        {
            get_resource = get_resource + player2->wheat;
            player2->wheat = 0;
            get_resource = get_resource + player3->wheat;
            player3->wheat = 0;
            get_resource = get_resource + player4->wheat;
            player4->wheat = 0;
            player1->wheat = player1->wheat + get_resource;
        }
        else if(take_resource2==3)
        {
            get_resource = get_resource + player2->brick;
            player2->brick = 0;
            get_resource = get_resource + player3->brick;
            player3->brick = 0;
            get_resource = get_resource + player4->brick;
            player4->brick = 0;
            player1->brick = player1->brick + get_resource;
        }  
        else if(take_resource2==4)
        {
            get_resource = get_resource + player2->sheep;
            player2->sheep = 0;
            get_resource = get_resource + player3->sheep;
            player3->sheep = 0;
            get_resource = get_resource + player4->sheep;
            player4->sheep = 0;
            player1->sheep = player1->sheep + get_resource;
        }     
        get_resource = 0;               
    }  
}

void score_card(sPlayer * player,uint8_t player_number,uint8_t is_ai)
{
    player->final_score++;
}

//買卡階段 買卡與否以及是否能夠執行買卡的動作
int32_t buy_card_state(sPlayer * player,uint8_t player_number,uint8_t is_ai)
{
    int32_t buy_card_state = 0;
    if(is_ai==0)
    {
        while(1)
        {
            printf("Do you want to buy some developing card ??\n");
            printf("Yes(1) No(0)\n");
            scanf("%d",&buy_card_state);
            if((buy_card_state>1)||(buy_card_state<0))
            {
                printf("Error,you should check your input again\n");
                continue;
            }
            else
            {
                break;
            } 
        }
        if(buy_card_state==1)
        {
            if((judge_buy_card(player)))
            {
                get_develop_card(player);
                player->U_develop = 1; //借用一下 表有買卡
            }
            else
            {
                printf("Error,you should check your resource again\n");
            }
            printf("Ending the buy card state\n");
        }
        else
        {
            printf("Ending the buy card state\n");
        }

    }
    else if(is_ai==1)//ai的部份
    {     
        buy_card_state= rand() % 2;  
        if(buy_card_state==1)
        {
            if((judge_buy_card(player)))
            {
                get_develop_card(player);
                player->U_develop = 1; //借用一下 表有買卡
            }
        }
    }        
}

//用卡階段偵錯 錯誤輸入 亂用卡防範  true表可用此卡 false表不可用此卡
bool error_detect_use_card_state(sPlayer * player,int8_t card_serial_number,uint8_t is_ai)
{
    if(is_ai==0)
    {
        if((player->U_develop = 1))//這裡表是否有買過卡
        {
            player->U_develop = 0;// 這裡開始表使用過幾次卡
            if(card_serial_number==0)
            {
                if((card_serial_number==develop_card_order[develop_index-1])&&(player->knight = 1))
                {
                    return false;
                }
                else if((player->knight != 1)&&(player->knight > 1))
                {
                    player->U_develop++;
                    return true;
                }
            }
            else if(card_serial_number==1)
            {
                if((card_serial_number==develop_card_order[develop_index-1])&&(player->harvest_card = 1))
                {
                    return false;
                }
                else if((player->harvest_card != 1)&&(player->harvest_card > 1))
                {
                    player->U_develop++;
                    return true;
                }                                
            }
            else if(card_serial_number==2)
            {
                if((card_serial_number==develop_card_order[develop_index-1])&&(player->build_card = 1))
                {
                    return false;
                }    
                else if((player->build_card != 1)&&(player->build_card > 1))
                {
                    player->U_develop++;
                    return true;
                }                            
            }
            else if(card_serial_number==3)
            {
                if((card_serial_number==develop_card_order[develop_index-1])&&(player->steal_card = 1))
                {
                    return false;
                } 
                else if((player->steal_card != 1)&&(player->steal_card > 1))
                {
                    player->U_develop++;
                    return true;
                }                               
            }                                    
        }
        else
        {   
            player->U_develop = 0;// 這裡開始表使用過幾次卡
            if(card_serial_number==0)
            {
                if((player->knight < 1))
                {
                    return false;
                }
                else if((player->knight >= 1))
                {
                    player->U_develop++;
                    return true;
                }
            }
            else if(card_serial_number==1)
            {
                if((player->harvest_card < 1))
                {
                    return false;
                }
                else if((player->harvest_card >= 1))
                {
                    player->U_develop++;                    
                    return true;
                }                                
            }
            else if(card_serial_number==2)
            {
                if((player->build_card < 1))
                {
                    return false;
                }    
                else if((player->build_card >= 1))
                {
                    player->U_develop++;                    
                    return true;
                }                            
            }
            else if(card_serial_number==3)
            {
                if((player->steal_card < 1))
                {
                    return false;
                } 
                else if((player->steal_card >= 1))
                {
                    player->U_develop++;                    
                    return true;
                }                               
            }                  
        } 
    }
    else if(is_ai==1)//ai的部份
    {    
        if((player->U_develop = 1))//這裡表是否有買過卡
        {
            player->U_develop = 0;// 這裡開始表使用過幾次卡
            if(card_serial_number==0)
            {
                if((card_serial_number==develop_card_order[develop_index-1])&&(player->knight = 1))
                {
                    return false;
                }
                else if((player->knight != 1)&&(player->knight > 1))
                {
                    player->U_develop++;
                    return true;
                }
            }
            else if(card_serial_number==1)
            {
                if((card_serial_number==develop_card_order[develop_index-1])&&(player->harvest_card = 1))
                {
                    return false;
                }
                else if((player->harvest_card != 1)&&(player->harvest_card > 1))
                {
                    player->U_develop++;
                    return true;
                }                                
            }
            else if(card_serial_number==2)
            {
                if((card_serial_number==develop_card_order[develop_index-1])&&(player->build_card = 1))
                {
                    return false;
                }    
                else if((player->build_card != 1)&&(player->build_card > 1))
                {
                    player->U_develop++;
                    return true;
                }                            
            }
            else if(card_serial_number==3)
            {
                if((card_serial_number==develop_card_order[develop_index-1])&&(player->steal_card = 1))
                {
                    return false;
                } 
                else if((player->steal_card != 1)&&(player->steal_card > 1))
                {
                    player->U_develop++;
                    return true;
                }                               
            }                                    
        }
        else
        {   
            player->U_develop = 0;// 這裡開始表使用過幾次卡
            if(card_serial_number==0)
            {
                if((player->knight < 1))
                {
                    return false;
                }
                else if((player->knight >= 1))
                {
                    player->U_develop++;
                    return true;
                }
            }
            else if(card_serial_number==1)
            {
                if((player->harvest_card < 1))
                {
                    return false;
                }
                else if((player->harvest_card >= 1))
                {
                    player->U_develop++;                    
                    return true;
                }                                
            }
            else if(card_serial_number==2)
            {
                if((player->build_card < 1))
                {
                    return false;
                }    
                else if((player->build_card >= 1))
                {
                    player->U_develop++;                    
                    return true;
                }                            
            }
            else if(card_serial_number==3)
            {
                if((player->steal_card < 1))
                {
                    return false;
                } 
                else if((player->steal_card >= 1))
                {
                    player->U_develop++;                    
                    return true;
                }                               
            }                  
        }            
    }    
}
//用卡階段 用卡與否以及是否能夠執行用卡的動作 --卡片記得 player1 is the people who is in the use card state
int32_t use_card_state(sPlayer * player1,sPlayer * player2,sPlayer * player3,sPlayer * player4,uint8_t player_number,int8_t card_serial_number,uint8_t is_ai)
{
    if(is_ai==0)
    {
        if(error_detect_use_card_state(player1,card_serial_number,is_ai))
        {
            if((card_serial_number==0)&&(player1->U_develop==1))
            {
                player1->knight--;
                knight_card(player1,player_number,is_ai);
                printf("Ending the use card state\n");
                player1->U_develop=0;
                return 0;
            }
            else if((card_serial_number==1)&&(player1->U_develop==1))
            {
                player1->harvest_card--;
                harvest_card(player1,player_number,is_ai);
                printf("Ending the use card state\n");
                player1->U_develop=0;
                return 0;                       
            }
            else if((card_serial_number==2)&&(player1->U_develop==1))
            {
                player1->build_card--;
                build_card(player1,player_number,is_ai); 
                printf("Ending the use card state\n");
                player1->U_develop=0;                
                return 0;                        
            }
            else if((card_serial_number==3)&&(player1->U_develop==1))
            {
                player1->steal_card--;
                steal_card(player1,p2,p3,p4,player_number,is_ai);
                printf("Ending the use card state\n");
                player1->U_develop=0;                   
                return 0;                                       
            }
        }
        else
        {
            printf("Error,using the wrong card\n");
            printf("Ending the use card state\n");     
            return 100;        
        }
    }
    else if(is_ai==1)//ai的部份
    {
        if(error_detect_use_card_state(player1,card_serial_number,is_ai))
        {
            if((card_serial_number==0)&&(player1->U_develop==1))
            {
                player1->knight--;
                knight_card(player1,player_number,is_ai);
                player1->U_develop=0;
                return 0;
            }
            else if((card_serial_number==1)&&(player1->U_develop==1))
            {
                player1->harvest_card--;
                harvest_card(player1,player_number,is_ai);
                player1->U_develop=0;
                return 0;                       
            }
            else if((card_serial_number==2)&&(player1->U_develop==1))
            {
                player1->build_card--;
                build_card(player1,player_number,is_ai); 
                player1->U_develop=0;                
                return 0;                        
            }
            else if((card_serial_number==3)&&(player1->U_develop==1))
            {
                player1->steal_card--;
                steal_card(player1,player2,player3,player4,player_number,is_ai);
                player1->U_develop=0;                   
                return 0;                                       
            }
        }
        else
        {    
            return 100;        
        }                
    }        
}


