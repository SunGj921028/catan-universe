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

bool judge_buy_card(sPlayer * player){
    //printf("%u %u %u %u %u\n",player->iron,player->wood,player->wheat,player->brick,player->sheep);
    if((player->wheat <= 0) || (player->iron <= 0) || (player->sheep <= 0)){
        return false;
    }else{
        return true;
    }
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
    (player->wheat) -= 1;
    (player->sheep) -= 1;
    (player->iron) -= 1;
    (player->hand) -= 3;
    //not sure
    resource[0] += 1;
    resource[2] += 1;
    resource[4] += 1;
    //printf("%u %u %u %u\n",player->knight,player->harvest_card,player->build_card,player->steal_card);
    map_log_update(player_number,"buy a develop card!!",-1);
    //PASS;
    keep_index++;
    develop_index++;
    REFRESH
    return;
}
//顯示當下的手牌種類及數量
void develop_card_state(sPlayer * player, uint8_t player_number, uint8_t is_ai)
{
    REFRESH
    if(is_ai==0)
    {
        printf("*%s :\n",player_name);
        printf(GREEN"knight(0) "YELLOW"harvest_card(1) "L_BLUE"build_card(2) "RED"steal_card(3) ");
        printf("\n");
        printf(GREEN"%9d "YELLOW"%15d "L_BLUE"%13d "RED"%13d",player->knight,player->harvest_card,player->build_card,player->steal_card);
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

int32_t judge_the_U_knight(){
    uint8_t *temp[4]={&(p1->U_knight),&(p2->U_knight),&(p3->U_knight),&(p4->U_knight)};
    bool over_three = false;
    for(int i=0;i<4;i++){
        if((*(temp[i]))>=3){
            over_three = true;
        }
    }
    if(over_three){
        int32_t count = *(temp[0]);
        int8_t max = 0;
        for(int32_t i =0;i<4;i++)
        {
            if(*(temp[i])>count)
            {
                count = *(temp[i]);
                max = i;
            }
        }
        uint8_t *temp2[4]={&(p1->M_knight),&(p2->M_knight),&(p3->M_knight),&(p4->M_knight)};
        for(int32_t i =0;i<4;i++)
        {
            *temp2[i] = 0;
            if( i==max )
            {
                *(temp2[i]) = 1;
            }
        }
    }
    return 0;
}

int32_t knight_card(sPlayer * player,uint8_t player_number,uint8_t is_ai){
    //move thief
    int nearby[5] = {0};
    int region_cho = 0;
    int player_cho = 0;
    uint8_t *temp_hand[4] = {&(p1->hand),&(p2->hand),&(p3->hand),&(p4->hand)};
    if(!is_ai){
        //原本的點不能放
        while(1){
            map_print(3);
            printf("Which region you want to place the robbor ? (0-18): ");
            if((scanf("%d",&region_cho)) == 0){
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
            if(move_robbor(region_cho, &nearby[0],is_ai,player_number)!=-1){
                break;
            }else{continue;}
        }
        uint8_t player_can_steal[5] = {0};
        for(int i=2;i<5;i++){
            if(nearby[i]!=0){
                player_can_steal[i] = 1;
                printf("--> You can take player %d's resource!!\n",i);
            }
        }
        while(1){
            player_cho = 0;
            printf("Which player's resource you want to steal? :");
            if((scanf("%d",&player_cho)) == 0){
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
            if(player_can_steal[player_cho]==1){
                break;
            }else{
                printf(RED"You can't steal resource from this player!!\e[0m\n");
                continue;
            }
        }
    }else{
        while(1){
            usleep(500000);
            region_cho = rand() % 18;
            if(move_robbor(region_cho, &nearby[0],is_ai,player_number)!=-1){
                break;
            }else{continue;}
            uint8_t temp_player[5] = {0};
            for(int i=1;i<5;i++){
                if(nearby[i]==1 && i!=player_number){
                    temp_player[i] = *(temp_hand[i-1]);
                }
            }
            uint8_t max_player = 0;
            uint8_t max_hand = 0;
            for(int i=1;i<5;i++){
                if(temp_player[i] >= max_hand){
                    max_hand = temp_player[i];
                    max_player = i;
                }
            }
            player_cho = max_player;
        }
    }
    steal_resource(player_cho,player);
    return 0;
}

void harvest_card(sPlayer * player, uint8_t p, uint8_t is_ai)
{
    int32_t take_resource1 = 0;  
    int8_t count = 1;
    while(count<3)
    {
        while(1)
        {
            REFRESH
            if(is_ai==0){
                printf("Please input the resource serial number you want to get(%dth resource)\n",count);
                printf(CYAN"iron(0) "BROWN"wood(1) "YELLOW"wheat(2) "L_RED"brick(3) " L_GREEN"wool(4)\e[0m\n");
                if((scanf("%d",&take_resource1)) == 0){
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
                if((take_resource1>4)||(take_resource1<0))
                {
                    printf(RED"Error,you should check your input again\e[0m\n");
                    continue;
                }
            }else{
                take_resource1 = rand() % 5;
            }

            if(resource[take_resource1]==0)
            {
                printf("-> the resuorce you choose is none left\n");
                printf("   you should change your input\n");
                continue;
            }
            else
            {
                if(take_resource1==0)
                {
                    player->iron += 1;
                    player->hand += 1;
                    resource[take_resource1] -= 1;
                }
                else if(take_resource1==1)
                {
                    player->wood += 1;
                    player->hand += 1;
                    resource[take_resource1] -= 1;
                }            
                else if(take_resource1==2)
                {
                    player->wheat += 1;
                    player->hand += 1;
                    resource[take_resource1] -= 1;
                }            
                else if(take_resource1==3)
                {
                    player->brick += 1;
                    player->hand +=1;
                    resource[take_resource1] -= 1;
                }            
                else if(take_resource1==4)
                {
                    player->sheep += 1;
                    player->hand += 1;
                    resource[take_resource1] -= 1;
                }
                take_resource1 = 0;
                count++;
                break;
            }
        }
    }
    return;
}

void build_card(sPlayer * player,uint8_t player_number,uint8_t is_ai)
{
    int8_t count = 1;
    int32_t road = 0;
    int32_t limit = 0;
    if((player->road.road_hand) < 2){
        limit = (player->road.road_hand) + 1;
    }else{
        limit = 3;
    }
    if(is_ai==0)
    {
        while(count<limit)
        {
            while(1)
            {
                map_print(2);
                printf("Please input the road serial number you want to build\n");
                if((scanf("%d",&road)) == 0){
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
                if(build_road(player_number,road,is_ai)== -1)
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
        while(count<limit)
        {
            while(1)
            {
                road= rand() % 72;//確切的路數量
                if(build_road(player_number,road,is_ai)==0)
                {
                    break;
                }
            }
            road = 0;
            count++;
        }            
    }
    player->road.road_build += (limit-1);
    player->road.road_hand -= (limit-1);
    return;
}

//player1 is the people who uses the steal_card
void steal_card(sPlayer * player1,sPlayer * player2, sPlayer * player3, sPlayer * player4, uint8_t player_number, uint8_t is_ai)
{
    int32_t take_resource2 = 0;
    int32_t get_resource = 0;
    while(1)
    {
        REFRESH
        if(is_ai==0){
            printf("Please input the resource serial number you want to get\n");
            printf(CYAN"iron(0) "BROWN"wood(1) "YELLOW"wheat(2) "L_RED"brick(3) " L_GREEN"wool(4)\e[0m\n");
            if((scanf("%d",&take_resource2)) == 0){
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
            if((take_resource2>4)||(take_resource2<0))
            {
                printf(RED"Error,you should check your input again\e[0m\n");
                continue;
            }
            else
            {
                break;
            }
        }else{
            take_resource2 = rand() % 5;
            break;
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
        if(!is_ai){ printf(RED"!! But You have use one develop card in this turn !!\e[0m\n");}
        return false;
    }
    if(card_serial_number==0){
        if(player->knight==0){
            if(!is_ai){ printf(RED"!! But You don't have Knight Card !!\e[0m\n");}
            return false;
        }
    }else if(card_serial_number==1){
        if(player->harvest_card==0){
            if(!is_ai){ printf(RED"!! But You don't have Harvest Card !!\e[0m\n");}
            return false;
        }
    }else if(card_serial_number==2){
        if(player->build_card==0){
            if(!is_ai){ printf(RED"!! But You don't have Build Card !!\e[0m\n");}
            return false;
        }
    }else if(card_serial_number==3){
        if(player->steal_card==0){
            if(!is_ai){ printf(RED"!! But You don't have Steal Card !!\e[0m\n");}
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
    if(error_detect_use_card_state(player,card_serial_number,is_ai))
    {
        if((card_serial_number==0))
        {
            (player->knight) -= 1;
            knight_card(player,player_number,is_ai);
            player->U_knight++;
            player->U_develop = 1;
            REFRESH
            map_log_update(player_number,"uses knight card.",-1);
            return 0;
        }
        else if((card_serial_number==1))
        {
            player->harvest_card--;
            harvest_card(player,player_number,is_ai);
            player->U_develop = 1;
            REFRESH
            map_log_update(player_number,"uses harvest card.",-1);
            return 0;
        }
        else if((card_serial_number==2))
        {
            player->build_card--;
            build_card(player,player_number,is_ai);
            player->U_develop = 1;
            REFRESH
            map_log_update(player_number,"uses build card.",-1);
            return 0;
        }
        else if((card_serial_number==3))
        {
            player->steal_card--;
            if(player_steal==1){steal_card(player,p2,p3,p4,player_number,is_ai);}
            else if(player_steal==2){steal_card(player,p1,p3,p4,player_number,is_ai);}
            else if(player_steal==3){steal_card(player,p1,p2,p4,player_number,is_ai);}
            else if(player_steal==4){steal_card(player,p1,p2,p3,player_number,is_ai);}
            player->U_develop = 1;
            REFRESH
            map_log_update(player_number,"uses the steal card.",-1);
            return 0;
        }
    }
    return -1;
}
