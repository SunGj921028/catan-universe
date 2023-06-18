#include"phase.h"
#include"data.h"
#include"init.h"
#include"color.h"
#include"map.h"

extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;
extern int resource[5];//sum is 95

bool judge_five(char input[30]){
    char temp[30] = {0};
    strncpy(temp,input,strlen(input));
    temp[strlen(input)-1] = '\0';
    int count = 0;
    char *tok = NULL;
    int number = 0;
    tok = strtok(temp," ");
    //printf("%c\n",*tok);
    number = (*tok) - '0';
    while(tok!=NULL){
        if(number>12 || number<0){
            return false;
        }
        tok = strtok(NULL," ");
        if(tok!=NULL){
            number = *tok - '0';
        }
        count++;
    }
    if(count>5){
        return false;
    }
    return true;
}

//dice == 7
//uint8_t count = 0;
void throw_card(sPlayer * player, int arr[], size_t n){
    //PASS;
    for(int i = 0;i < n; i++){
        if(arr[i]!=0){
            if(i==0){
                player->iron -= arr[i];
                resource[0] += arr[i];
            }else if(i==1){
                player->wood -= arr[i];
                resource[1] += arr[i];
            }else if(i==2){
                player->wheat -= arr[i];
                resource[2] += arr[i];
            }else if(i==3){
                player->brick -= arr[i];
                resource[3] += arr[i];
            }else{
                player->sheep -= arr[i];
                resource[4] += arr[i];
            }
            player->hand -= arr[i];
        }
    }
    // printf("%d. %d %d %d %d %d\n",count++,player->iron,player->wood,player->wheat,player->brick,player->sheep);
    return;
}
//可能可以做改強度
void input_key(sPlayer * player, uint8_t p_number, int num){
    //PASS;
    char input[30] = {0};
    int in_arr[5] = {0};
    char message[20] = {0};
    bool can_throw = true;
    int count_get_char = 0;
    if(p_number==1){
        while(1){
            // if(count_get_char!=0){
            //     getchar();
            // }
            // count_get_char++;
            fgets(input,30,stdin);
            if(strlen(input)>16) {printf(RED"invalid input!!\e[0m\n"); continue;}
            if(judge_five(input)){
                //printf("%s\n",input);
                sscanf(input,"%d %d %d %d %d",&in_arr[0],&in_arr[1],&in_arr[2],&in_arr[3],&in_arr[4]);
                /*for(int i=0;i<5;i++){
                    printf("%u ",in_arr[i]);
                }
                printf("\n");*/
                int sum = 0;
                for(int i=0;i<5;i++){
                    sum += in_arr[i];
                }
                if(sum!=num){
                    printf(RED"Invalid number of cards you throw!!\e[0m\n");
                    continue;
                }
                uint8_t *ptr[5] = {&(player->iron),&(player->wood),&(player->wheat),&(player->brick),&(player->sheep)};
                for(int i=0;i<5;i++){
                    //printf("%d\n",*ptr);
                    if(in_arr[i]<0 || in_arr[i]>*(ptr[i])){
                        printf(RED"invalid input!!\e[0m\n");
                        can_throw = false;
                        break;
                    }else{ can_throw = true;}
                }
                if(!can_throw) {
                    continue;
                }else{
                    throw_card(player,in_arr,5);
                    break;
                }
            }else{
                printf(RED"Wrong format of input!!\e[0m\n");
                continue;
            }
        }
        //print
        printf("%s throw\n",player_name);
        printf("%d irons, %d woods, %d wheats, %d bricks, %d wool\n",in_arr[0],in_arr[1],in_arr[2],in_arr[3],in_arr[4]);
    }else{
        //printf("ai throw turn\n");
        int choose[5] = {0};
        uint8_t player_resource[5] = {0};
        player_resource[0] = player->iron;
        player_resource[1] = player->wood;
        player_resource[2] = player->wheat;
        player_resource[3] = player->brick;
        player_resource[4] = player->sheep;
        //ai keep
        //build road
        if(((player->hand-2)>num) && (player_resource[1]!=0) && (player_resource[3]!=0)){
            player_resource[1]--, player_resource[3]--;
        }
        //progress card
        if(((player->hand-5)>num) && (player_resource[0]!=0) && (player_resource[2]!=0) && (player_resource[4]!=0)){
            player_resource[0]--, player_resource[2]--, player_resource[4]--;
        }
        //village
        if(((player->hand-9)>num) && (player_resource[1]!=0) && (player_resource[2]!=0) && (player_resource[3]!=0) && (player_resource[4]!=0)){
            player_resource[1]--, player_resource[2]--, player_resource[3]--, player_resource[4]--;
        }
        uint8_t count_throw = 0;
        while(count_throw<num){
            int type = rand() % 5;
            if(player_resource[type] <= 0){
                continue;
            }else{
                choose[type] += 1;
                player_resource[type]--;
                count_throw++;
            }
        }
        throw_card(player,choose,5);
        //print
        sprintf(message,"Player %d throw",p_number);
        printf("%s\n",message);
        printf("%d irons, %d woods, %d wheats, %d bricks, %d wool\n",choose[0],choose[1],choose[2],choose[3],choose[4]);
    }
    return;
}

void print_player_hands(sPlayer * player, uint8_t n){
    PASS;
    int num = floor(( double )( (player->hand)/2.0) );
    if(n==1){
        char state_with_player_number[60] = {0};
        sprintf(state_with_player_number,"%s resource card in hand:",player_name);
        printf("%s\n",state_with_player_number);
        printf(PURPLE"iron "CYAN"wood "YELLOW"wheat "RED"brick " L_GREEN"sheep");
        printf("\n");
        printf(PURPLE"%4d "CYAN"%4d "YELLOW"%5d "RED"%5d "L_GREEN"%5d",player->iron,player->wood,player->wheat,player->brick,player->sheep);
        printf(WHITE"\n");
        char number_requested_sentence[60] = {0};
        sprintf(number_requested_sentence,"You need to throw %d resource cards!!\n",num);
        printf("%s",number_requested_sentence);
        printf("please input the resource you want to throw (input's pattern is like x x x x x)\n");
    }
    input_key(player,n,num);
    return;
}

void check_hand(){
    uint8_t count = 1;
    while(count<5){
        uint8_t player_number = count%5;
        if(player_number == 1){
            if(p1->hand >= 7){
                print_player_hands(p1,1);
            }
        }else{
            if(player_number == 2){
                if(p2->hand >= 7){
                    print_player_hands(p2,2);
                }
            }else if(player_number == 3){
                if(p3->hand >= 7){
                    print_player_hands(p3,3);
                }
            }else{
                if(p4->hand >= 7){
                    print_player_hands(p4,4);
                }
            }
        }
        count++;
    }
    return;
}

int32_t move_robbor(int32_t block_id,int32_t *nearby_player_5x1, uint8_t is_ai, uint8_t player_num){
    for(int8_t i=3;i<20;i=i+2){
        for(int8_t j=2;j<12;j=j+2){
            if(map[i][j][0]==3 && map[i][j][4]==1){
                if(map[i][j][1]!=block_id){
                    map[i][j][4]=0;
                }else{
                    if(!is_ai){
                        printf(RED"Can't move to same place!\e[0m\n");
                    }
                    return -1;
                }
            }
        }
    }
    for(int8_t i=3;i<20;i=i+2){
        for(int8_t j=2;j<12;j=j+2){
            if(map[i][j][0]==3 && map[i][j][1]==block_id){
                map[i][j][4]=1;
                if(map[i-2][j-1][1] != 0){//0
                    *(nearby_player_5x1 + map[i-2][j-1][1]) = 1;
                }
                if(map[i-2][j+1][1] != 0){//1
                    *(nearby_player_5x1 + map[i-2][j+1][1]) = 1;
                }
                if(map[i][j-1][1] != 0){//2
                    *(nearby_player_5x1 + map[i][j-1][1]) = 1;
                }
                if(map[i][j+1][1] != 0){//3
                    *(nearby_player_5x1 + map[i][j+1][1]) = 1;
                }
                if(map[i+2][j-1][1] != 0){//4
                    *(nearby_player_5x1 + map[i+2][j-1][1]) = 1;
                }
                if(map[i+2][j+1][1] != 0){//5
                    *(nearby_player_5x1 + map[i+2][j+1][1]) = 1;
                }
            }
        }
    }
    map_log_update(player_num,"move robbor to point",block_id);
    return 1;
}

void steal_resource(uint8_t player_cho, sPlayer * player){
    sPlayer * ps;
    if(player_cho==1) {ps = p1;}
    else if(player_cho==2) {ps = p2;}
    else if(player_cho==3) {ps = p3;}
    else { ps = p4;}
    uint8_t *temp[5]={&(ps->iron),&(ps->wood),&(ps->wheat),&(ps->brick),&(ps->sheep)};
    uint8_t *temp2[5]={&(player->iron),&(player->wood),&(player->wheat),&(player->brick),&(player->sheep)};
    int res_cho = 0;
    while(1){
        res_cho = rand() % 5;
        if((*(temp[res_cho])) <= 0){
            continue;
        }else{break;}
    }
    *(temp2[res_cho]) += 1;
    //printf("*%u\n",*(temp2[res_cho]));
    *(temp[res_cho]) -= 1;
    ps->hand--;
    player->hand++;
    //printf("%u %u %u %u %u\n",player->iron,player->wood,player->wheat,player->brick,player->sheep);
    return;
}

void thief_action(sPlayer * player, uint8_t is_ai, uint8_t player_number){
    PASS;
    //throw resource card
    check_hand();
    //move thief
    //choose the position you want to place robbor first
    int32_t nearby_player[5] = {0};//0->nothing
    int region_cho = 0;
    if(is_ai){
        while(1){
            region_cho = rand() % 19;
            if(move_robbor(region_cho,&nearby_player[0],is_ai,player_number) != -1){
                break;
            }else{continue;}
        }
    }else{
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
                }else{
                    if(region_cho<0 || region_cho>18){
                        printf(RED"Wrong Input!!\e[0m\n");
                        continue;
                    }
                }
            }
            if(move_robbor(region_cho,&nearby_player[0],is_ai,player_number) != -1){
                break;
            }else{continue;}
        }
    }
    int player_cho = 0;
    uint8_t *temp_hand[4] = {&(p1->hand),&(p2->hand),&(p3->hand),&(p4->hand)};
    bool have_people = false;
    if(is_ai){
        uint8_t temp_player[5] = {0};
        for(int i=1;i<5;i++){
            if(nearby_player[i]!=0 && i!=player_number){
                temp_player[i] = *(temp_hand[i-1]);
                have_people = true;
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
    }else{
        uint8_t player_can_steal[5] = {0};
        for(int i=2;i<5;i++){
            if(nearby_player[i]!=0){
                player_can_steal[i] = 1;
                printf("--> You can take player %d's resource!!\n",i);
            }
        }
        while(1){
            player_cho = 0;
            for(int i=2;i<5;i++){
                if(player_can_steal[i] == 1){
                    have_people = true;
                    break;
                }
            }
            if(!have_people){printf(RED"There are not any people around this region!!\e[0m\n");break;}
            printf("Which player's resource you want to steal ? (2-4): ");
            if((scanf("%d",&player_cho)) == 0){
                printf(RED"Wrong Input!!\e[0m\n");
                while (getchar() != '\n');
                continue;
            }else{
                if(scanf("%c",&extra)==1 && extra != '\n'){
                    printf(RED"Wrong Input!!\e[0m\n");
                    while (getchar() != '\n');
                    continue;
                }else{
                    if(player_cho<2 || player_cho>4){
                        printf(RED"Wrong Input!!\e[0m\n");
                        continue;
                    }else{
                        break;
                    }
                }
            }
            if(player_can_steal[player_cho]==1){
                break;
            }else{
                printf(RED"You can't steal resource from this player!!\e[0m\n");
                continue;
            }
        }
    }
    PASS;
    if(have_people){
        //print_init(player_cho);
        steal_resource(player_cho,player);
    }
    return;
}