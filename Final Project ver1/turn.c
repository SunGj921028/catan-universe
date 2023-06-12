#include "phase.h"
#include "data.h"
#include "color.h"
#include"init.h"

int player_order = 0;
void first_sec_turn(){
	player_order = rand() % 4;//first設全域 在phase.h
	int count=0;
	while(count!=4){
		switch(player_order)
		{
			case 0:
				//Temp message
				printf("First round player 1\n");
				//build(p1);
				player_order+=1;
				count++;
				break;
			case 1:
				printf("First round player 2\n");
				//build(p2);
				player_order+=1;
				count++;
				break;
			case 2:
				printf("First round player 3\n");
				//build(p3);
				player_order+=1;
				count++;
				break;
			case 3:
				printf("First round player 4\n");
				//build(p4);
				player_order=0;
				count++;
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
		switch(player_order){
			case 0:
				printf("Second round player 1\n");
				//build_and_take_surround(p1);
				player_order=3;
				count++;
				break;
			case 1:
				printf("Second round player 2\n");
				//build_and_take_surround(p2);
				player_order--;
				count++;
				break;
			case 2:
				printf("Second round player 3\n");
				//build_and_take_surround(p3);
				player_order--;
				count++;
				break;
			case 3:
				printf("Second round player 4\n");
				//build_and_take_surround(p4);
				player_order--;
				count++;
				break;
		}
	}
	if(player_order==3){
		player_order=0;
	}else{
		player_order++;
	}//設回第二輪最後一個放的人開始
	first_player = player_order;
	return;
}

/*void turn_process(sPlayer *p){//參數代Player[first] first是全域會自己變
	int end=0;
	throw_dice(p);
	char action[2];
	while(end!=1){
		printf("What do you want to do?\n(0:end turn 1:trade 2:build 3:use develop card):");	
		fgets(action,2,stdin);
		switch(action[0]){
			case '0':
			  first--;
			  end=1;
			  break;
			
			case '1':
			  trade(p);
			  break;
			
			case '2':
			  //build();
			  break;
			
			case '3':
			  printf("0:back 1:use card 2:buy card:");
			  fgets(action,2,stdin);
			  if(action[0]=='0'){
			  	break;
			  }
			  else if(action[0]=='1'){
			  	if(p->U_develop==1){
				  	printf("You have used 1 before\n");
			  	}
			  	else{
			  		//use_develop_card();
			  	}
		  	}
			  else if(action[0]=='2'){
			  	if(p->sheep==0 || p->wheat==0 || p->rock==0){
			  		printf("You don't have enough resource\n");
			  	}
			  	else{
			  		get_develop_card(p);
			  		p->sheep--;
			  		p->wheat--;
			  		p->rock--;
					p->hand-=3;
			  	}
			  }
			  else{
		  		printf("Invalid command\n");
		  	}
		  	break;
			
			default:
			  printf("Invalid command\n");
			  break;
		}
	}
}*/
