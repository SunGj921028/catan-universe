#include "phase.h"
#include "data.h"
#include "color.h"
#include"init.h"
#include"map.h"

int player_order = 0;
extern int8_t init_build_take[5];

void take_init_resource(int player_order){
	sPlayer * player;
	if(player_order==0){ player = p1;}
	else if(player_order==1){ player = p2;}
	else if(player_order==2){ player = p3;}
	else { player = p4;}
	uint8_t *temp[5]={&(player->iron),&(player->wood),&(player->wheat),&(player->brick),&(player->sheep)};
	for(int i=0;i<5;i++){
		*(temp[i]) += init_build_take[i];
		resource[i] -= init_build_take[i];
	}
	for(int i=0;i<5;i++){
		player->hand += init_build_take[i];
	}
	return;
}

void first_sec_turn(){
	player_order = rand() % 4;//first設全域 在phase.h
	int count=0;
	int vi_cho = 0;
	int r_cho = 0;
	player_order = 0;
	while(count!=4){
		vi_cho = 0;
		r_cho = 0;
		switch(player_order)
		{
			case 0:
				//Temp message
				//printf("First round player 1\n");
				while(1){
					map_print(1);
					printf("Which point you want to build Village ? (0-53): ");
					if((scanf("%d",&vi_cho)) == 0){
						printf("Wrong Input!!\n");
						while (getchar() != '\n');
						continue;
					}
					if(build_village(1,vi_cho,1,0) == -1){
						continue;
					}
					break;
				}
				while(1){
					map_print(2);
					printf("Which point you want to build Road ? (0-71): ");
					if((scanf("%d",&r_cho)) == 0){
						printf("Wrong Input!!\n");
						while (getchar() != '\n');
						continue;
					}
					if(build_road(1,r_cho,0) == -1){
						continue;
					}
					break;
				}
				CLEAR;
				map_print(0);
				print_init(1);
				player_order+=1;
				count++;
				sleep(2);
				break;
			case 1:
				printf("First round player 2\n");
				while(1){
					vi_cho = rand() % 54;
					if(build_village(2,vi_cho,1,1) == -1){
						continue;
					}
					break;
				}
				while(1){
					r_cho = rand() % 72;
					if(build_road(2,r_cho,1) == -1){
						continue;
					}
					break;
				}
				CLEAR;
				map_print(0);
				//print_init(2);
				player_order+=1;
				count++;
				sleep(2);
				break;
			case 2:
				printf("First round player 3\n");
				while(1){
					vi_cho = rand() % 54;
					if(build_village(3,vi_cho,1,1) == -1){
						continue;
					}
					break;
				}
				while(1){
					r_cho = rand() % 72;
					if(build_road(3,r_cho,1) == -1){
						continue;
					}
					break;
				}
				CLEAR;
				map_print(0);
				//print_init(3);
				player_order+=1;
				count++;
				sleep(2);
				break;
			case 3:
				printf("First round player 4\n");
				while(1){
					vi_cho = rand() % 54;
					if(build_village(4,vi_cho,1,1) == -1){
						continue;
					}
					break;
				}
				while(1){
					r_cho = rand() % 72;
					if(build_road(4,r_cho,1) == -1){
						continue;
					}
					break;
				}
				CLEAR;
				map_print(0);
				//print_init(4);
				player_order=0;
				count++;
				sleep(2);
				break;
		}
	}
	count=0;
	if(player_order==0){
		player_order=3;
	}else{
		player_order--;
	}//找第一輪最後一個放的

	while(count!=4){
		vi_cho = 0;
		r_cho = 0;
		bool check_road = false;
		switch(player_order){
			case 0:
				while(1){
					map_print(1);
					printf("Which point you want to build Village ? (0-53): ");
					if((scanf("%d",&vi_cho)) == 0){
						printf("Wrong Input!!\n");
						while (getchar() != '\n');
						continue;
					}
					if(build_village(1,vi_cho,2,0) == -1){
						continue;
					}
					break;
				}
				while(1){
					map_print(2);
					printf("Which point you want to build Road ? (0-71): ");
					if((scanf("%d",&r_cho)) == 0){
						printf("Wrong Input!!\n");
						while (getchar() != '\n');
						continue;
					}
					for(int i=1;i<=init_near_road[0];i++){
						if(init_near_road[i]==r_cho){
							if(build_road(1,r_cho,0)){
								check_road = true;
								break;
							}
						}
					}
					if(check_road){
						break;
					}else{
						continue;
					}
				}
				take_init_resource(player_order);
				CLEAR;
				map_print(0);
				print_init(1);
				player_order=3;
				count++;
				sleep(2);
				break;
			case 1:
				printf("Second round player 2\n");
				while(1){
					vi_cho = rand() % 54;
					if(build_village(2,vi_cho,2,1) == -1){
						continue;
					}
					break;
				}
				while(1){
					r_cho = rand() % 72;
					for(int i=1;i<=init_near_road[0];i++){
						if(init_near_road[i]==r_cho){
							if(build_road(2,r_cho,1)){
								check_road = true;
								break;
							}
						}
					}
					if(check_road){
						break;
					}else{continue;}
				}
				take_init_resource(player_order);
				CLEAR;
				map_print(0);
				//print_init(2);
				player_order--;
				count++;
				sleep(2);
				break;
			case 2:
				printf("Second round player 3\n");
				while(1){
					vi_cho = rand() % 54;
					if(build_village(3,vi_cho,2,1) == -1){
						continue;
					}
					break;
				}
				while(1){
					r_cho = rand() % 72;
					for(int i=1;i<=init_near_road[0];i++){
						if(init_near_road[i]==r_cho){
							if(build_road(3,r_cho,1)){
								check_road = true;
								break;
							}
						}
					}
					if(check_road){
						break;
					}else{continue;}
				}
				take_init_resource(player_order);
				CLEAR;
				map_print(0);
				//print_init(3);
				player_order--;
				count++;
				sleep(2);
				break;
			case 3:
				printf("Second round player 4\n");
				while(1){
					vi_cho = rand() % 54;
					if(build_village(4,vi_cho,2,1) == -1){
						continue;
					}
					break;
				}
				while(1){
					r_cho = rand() % 72;
					for(int i=1;i<=init_near_road[0];i++){
						if(init_near_road[i]==r_cho){
							if(build_road(4,r_cho,1)){
								check_road = true;
								break;
							}
						}
					}
					if(check_road){
						break;
					}else{continue;}
				}
				take_init_resource(player_order);
				CLEAR;
				map_print(0);
				//print_init(4);
				player_order--;
				count++;
				sleep(2);
				break;
		}
	}
	if(player_order==3){
		player_order=0;
	}else{
		player_order++;
	}//設回第二輪最後一個放的人開始
	first_player = player_order;
	sPlayer * player[4] = {p1,p2,p3,p4};
	for(int i=0;i<4;i++){
		(player[i])->road.road_build += 2;
		(player[i])->road.road_hand -= 2;
		(player[i])->village.village_build += 2;
		(player[i])->village.village_hand -= 2;
	}
	return;
}