#include"phase.h"
#include"data.h"
#include"init.h"
#include"color.h"

extern sPlayer * p1;
extern sPlayer * p2;
extern sPlayer * p3;
extern sPlayer * p4;
extern int resource[5];//sum is 95

//dice == 7
uint8_t count = 0;
void throw_card(sPlayer * player, uint8_t arr[], size_t n){
    PASS;
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
    PASS;
    char input[10] = {0};
    uint8_t in_arr[5] = {0};
    char message[20] = {0};
    bool can_throw = true;
    if(p_number==1){
        while(1){
            fgets(input,10,stdin);
            if(strlen(input)>10) {printf("invalid input!!\n"); continue;}
            sscanf(input,"%hhd %hhd %hhd %hhd %hhd",&in_arr[0],&in_arr[1],&in_arr[2],&in_arr[3],&in_arr[4]);
            int sum = 0;
            for(int i=0;i<5;i++){
                sum += in_arr[i];
            }
            if(sum!=num){
                printf("Invalid number of cards you throw!!\n");
                continue;
            }
            uint8_t *ptr = &player->iron;
            for(int i=0;i<5;i++){
                //printf("%d\n",*ptr);
                if(in_arr[i]<0 || in_arr[i]>(*ptr)){
                    printf("invalid input!!\n");
                    can_throw = false;
                    break;
                }else{ can_throw = true;}
                ptr++;
            }
            if(!can_throw) {
                continue;
            }else{
                throw_card(player,in_arr,5);
                break;
            }
            ptr = NULL;
        }
        //print
        printf("Player 1 throw\n");
        printf("%d irons, %d woods, %d wheats, %d bricks, %d wool",in_arr[0],in_arr[1],in_arr[2],in_arr[3],in_arr[4]);
    }else{
        //printf("ai throw turn\n");
        uint8_t choose[5] = {0};
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
        printf("%d irons, %d woods, %d wheats, %d bricks, %d wool",choose[0],choose[1],choose[2],choose[3],choose[4]);
    }
    return;
}

void print_player_hands(sPlayer * player, uint8_t n){
    PASS;
    int num = lrint(( double )( (player->hand)/2.0) );
    if(n==1){
        char state_with_player_number[60] = {0};
        sprintf(state_with_player_number,"player %u's resource card in hand:",n);
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
            printf("player throw card\n");
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

void move_thief(sPlayer * player, uint8_t is_ai){
    if(!is_ai){
    }else{}
}

void thief_action(sPlayer * player, uint8_t is_ai){
    PASS;
    //throw resource card
    check_hand();
    //move thief
    move_thief(player, is_ai);
    return;
}