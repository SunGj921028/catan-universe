#include"data.h"
#include"card.h"
//#include"map.h"
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


bool judge_buy_card(sPlayer * player){
    if((player->wheat <= 0) || (player->iron <= 0) || (player->sheep <= 0)){
        return false;
    }
    return true;
}
void save_develop_card(uint8_t p){
    sPlayer * player;
    if(p==1) {player = p1;}
    else if(p==2) {player = p2;}
    else if(p==3) {player = p3;}
    else {player = p4;}
    for(int i=0;i<10;i++){
        if(develop_card_keep[i]==-1){
            keep_index = 0;
            break;
        }
        if(develop_card_keep[i]==0){
            player->knight += 1;
        }else if(develop_card_keep[i]==1){
            player->harvest_card += 1;
        }else if(develop_card_keep[i]==2){
            player->build_card += 1;
        }else if(develop_card_keep[i]==3){
            player->steal_card += 1;
        }else if(develop_card_keep[i]==4){
            player->score_card += 1;
        }
    }
    for(int i=0;i<10;i++){
        develop_card_keep[i] = -1;
    }
    return;
}
void get_develop_card(sPlayer * player, uint8_t player_number){
    //printf("*%d %d\n",develop_card_order[develop_index],develop_index);
    if(develop_card_order[develop_index]==0){
        develop_card_keep[keep_index] = 0;
        knight_remain--;
    }else if(develop_card_order[develop_index]==1){
        develop_card_keep[keep_index] = 1;
        progress_remain[0]--;
    }else if(develop_card_order[develop_index]==2){
        develop_card_keep[keep_index] = 2;
        progress_remain[1]--;
    }else if(develop_card_order[develop_index]==3){
        develop_card_keep[keep_index] = 3;
        progress_remain[2]--;
    }else{
        develop_card_keep[keep_index] = 4;
        score_remain--;
    }
    player->wheat--;
    player->sheep--;
    player->iron--;
    player->hand -= 3;
    //not sure
    resource[0]++;
    resource[2]++;
    resource[4]++;
    printf("%u %u %u %u\n",player->knight,player->harvest_card,player->build_card,player->steal_card);
    printf(PURPLE"Player %d buy a develop card!!\e[0m\n",player_number);
    printf("---------------\n");
    keep_index++;
    develop_index++;
    return;
}
//顯示當下的手牌種類及數量
void develop_card_state(sPlayer * player, uint8_t player_number, uint8_t is_ai)
{
    if(is_ai==0)
    {
        printf("Player %d :\n",player_number);
        printf(GREEN"knight(0) "YELLOW"harvest_card(1) "L_BLUE"build_card(2) "RED"steal_card(3) " L_GREEN"score_card(4)");
        printf("\n");
        printf(GREEN"%9d "YELLOW"%15d "L_BLUE"%13d "RED"%13d "L_GREEN"%13d",player->knight,player->harvest_card,player->build_card,player->steal_card,player->score_card);
        printf("\n");
        printf(GREEN"used_knight ");
        printf("\n");
        printf(GREEN"%11d ",player->U_knight);
        printf("\n");
        printf(WHITE"\n");
    }
    else
    {
        printf("AI is checking their developing cards...\n");
    }
    return;
}

int32_t knight_card(sPlayer * player,uint8_t player_number,uint8_t is_ai)
{
 //move thief
}

void harvest_card(sPlayer * player, uint8_t p, uint8_t is_ai)
{
    int32_t take_resource1 = 0;  
    int8_t count = 1;
    printf(RED"Player %d uses the harvest_card\e[0m\n",p);
    while(count<3)
    {
        while(1)
        {
            if(is_ai==0){
                printf("Please input the resource serial number you want to get(%dth resource)\n",count);
                printf(GRAY"iron(0) "WHITE"wood(1) "YELLOW"wheat(2) "RED"brick(3) " L_GREEN"wool(4)\e[0m");
                printf("\n");
                scanf("%d",&take_resource1);
                if((take_resource1>4)||(take_resource1<0))
                {
                    printf("Error,you should check your input again\n");
                    continue;
                }
            }else{
                take_resource1 = rand() % 5;
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

void build_card(sPlayer * player,uint8_t player_number,uint8_t is_ai)
{
    int8_t count = 1;
    int32_t road = 0;
    if(is_ai==0)
    {
        printf("Player 1 uses the build_card\n");
        while(count<3)
        {
            while(1)
            {
                printf("Please input the road serial number you want to build\n");
                scanf("%d",&road);
                // if(build_road(player_number,road)==0)
                // {
                //     break;
                // }
            }
            road = 0;
            count++;
        }
    }
    else if(is_ai==1)//ai的部份
    {    
        printf("Player %d uses the build_card\n",player_number);
        while(count<3)
        {
            while(1)
            {
                road= rand() % 72;//確切的路數量
                // if(build_road(player_number,road)==0)
                // {
                //     break;
                // }
            }
            road = 0;
            count++;
        }            
    }    
}

//player1 is the people who uses the steal_card
void steal_card(sPlayer * player1,sPlayer * player2, sPlayer * player3, sPlayer * player4, uint8_t player_number, uint8_t is_ai)
{
    int32_t take_resource2 = 0;
    int32_t get_resource = 0;
    printf("Player %d uses the steal_card\n",player_number);
    while(1)
    {
        if(is_ai==0){
            printf("Please input the resource serial number you want to get\n");
            printf(GRAY"iron(0) "WHITE"wood(1) "YELLOW"wheat(2) "RED"brick(3) " L_GREEN"wool(4)\e[0m\n");
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
        }else{
            take_resource2 = rand() % 5;
        }
    }
    if(take_resource2==0)
    {
        get_resource = get_resource + player2->iron;
        player2->hand -= player2->iron;
        player2->iron = 0;
        get_resource = get_resource + player3->iron;
        player3->hand -= player3->iron;
        player3->iron = 0;
        get_resource = get_resource + player4->iron;
        player4->hand -= player4->iron;
        player4->iron = 0;
        player1->iron = player1->iron + get_resource;
        player1->hand += get_resource;
    }
    else if(take_resource2==1)
    {
        get_resource = get_resource + player2->wood;
        player2->hand -= player2->wood;
        player2->wood = 0;
        get_resource = get_resource + player3->wood;
        player3->hand -= player3->wood;
        player3->wood = 0;
        get_resource = get_resource + player4->wood;
        player4->hand -= player4->wood;
        player4->wood = 0;
        player1->wood = player1->wood + get_resource;
        player1->hand += get_resource;
    }
    else if(take_resource2==2)
    {
        get_resource = get_resource + player2->wheat;
        player2->hand -= player2->wheat;
        player2->wheat = 0;
        get_resource = get_resource + player3->wheat;
        player3->hand -= player3->wheat;
        player3->wheat = 0;
        get_resource = get_resource + player4->wheat;
        player4->hand -= player4->wheat;
        player4->wheat = 0;
        player1->wheat = player1->wheat + get_resource;
        player1->hand += get_resource;
    }
    else if(take_resource2==3)
    {
        get_resource = get_resource + player2->brick;
        player2->hand -= player2->brick;
        player2->brick = 0;
        get_resource = get_resource + player3->brick;
        player3->hand -= player3->brick;
        player3->brick = 0;
        get_resource = get_resource + player4->brick;
        player4->hand -= player4->brick;
        player4->brick = 0;
        player1->brick = player1->brick + get_resource;
        player1->hand += get_resource;
    }  
    else if(take_resource2==4)
    {
        get_resource = get_resource + player2->sheep;
        player2->hand -= player2->sheep;
        player2->sheep = 0;
        get_resource = get_resource + player3->sheep;
        player3->hand -= player3->sheep;
        player3->sheep = 0;
        get_resource = get_resource + player4->sheep;
        player4->hand -= player4->sheep;
        player4->sheep = 0;
        player1->sheep = player1->sheep + get_resource;
        player1->hand += get_resource;
    }     
    get_resource = 0;
}

//用卡階段偵錯 錯誤輸入 亂用卡防範  true表可用此卡 false表不可用此卡
bool error_detect_use_card_state(sPlayer * player,int8_t card_serial_number, uint8_t is_ai)
{
    if(player->U_develop == 1){
        if(!is_ai){ printf(RED"You have use one develop card in this turn!!\e[0m\n");}
        return false;
    }
    if(card_serial_number==0){
        if(player->knight==0){
            if(!is_ai){ printf(RED"You don't have Knight Card!!\e[0m\n");}
            return false;
        }
    }else if(card_serial_number==1){
        if(player->harvest_card==0){
            if(!is_ai){ printf(RED"You don't have Harvest Card!!\e[0m\n");}
            return false;
        }
    }else if(card_serial_number==2){
        if(player->build_card==0){
            if(!is_ai){ printf(RED"You don't have Build Card!!\e[0m\n");}
            return false;
        }
    }else if(card_serial_number==3){
        if(player->steal_card==0){
            if(!is_ai){ printf(RED"You don't have Steal Card!!\e[0m\n");}
            return false;
        }
    }
    return true;
}
//用卡階段 用卡與否以及是否能夠執行用卡的動作 --卡片記得 player1 is the people who is in the use card state
int32_t use_card_state(uint8_t player_number,int8_t card_serial_number,uint8_t is_ai)
{
    sPlayer * player;
    uint8_t player_steal = 0;
    if(player_number==1){player_steal = 1, player = p1;}
    else if(player_number==2){player_steal = 2, player = p2;}
    else if(player_number==3){player_steal = 3, player = p3;}
    else if(player_number==4){player_steal = 4, player = p4;}
    printf(RED"Player %d want to use develop card\e[0m\n",player_number);
    if(error_detect_use_card_state(player,card_serial_number,is_ai))
    {
        if((card_serial_number==0))
        {
            player->knight--;
            knight_card(player,player_number,is_ai);
            printf("Ending the use card state\n");
            player->U_develop = 1;
            return 0;
        }
        else if((card_serial_number==1))
        {
            player->harvest_card--;
            harvest_card(player,player_number,is_ai);
            printf("Ending the use card state\n");
            player->U_develop = 1;
            return 0;                       
        }
        else if((card_serial_number==2))
        {
            player->build_card--;
            build_card(player,player_number,is_ai); 
            printf("Ending the use card state\n");
            player->U_develop = 1;                
            return 0;                        
        }
        else if((card_serial_number==3))
        {
            player->steal_card--;
            if(player_steal==1){steal_card(player,p2,p3,p4,player_number,is_ai);}
            else if(player_steal==2){steal_card(player,p1,p3,p4,player_number,is_ai);}
            else if(player_steal==3){steal_card(player,p1,p2,p4,player_number,is_ai);}
            else if(player_steal==4){steal_card(player,p1,p2,p3,player_number,is_ai);}
            printf("Ending the use card state\n");
            player->U_develop = 1;
            return 0;
        }
    }
    else
    {
        printf("Error,using the wrong card\n");
        printf("Ending the use card state\n");
        return -1;
    }
}
