#include "phase.h"
#include "data.h"
#include "color.h"

void first_sec_turn(){
	srand(time(NULL));
	first=rand()%4;//first設全域 在phase.h
	int count=0;
	while(count!=4){
		switch(first){
			case 0:
			  //build(p1);
			  first+=1;
			  count++;
			  break;
			
			case 1:
			  //build(p2);
			  first+=1;
			  count++;
			  break;
			
			case 2:
			  //build(p3);
			  first+=1;
			  count++;
			  break;
			
			case 3:
			  //build(p4);
			  first=0;
			  count++;
			  break;
		}
	}
	count=0;
	if(first==0){
		first=3;
	}
	else{
			first--;
	}//找第一輪最後一個放的
	
	while(count!=4){
		switch(first){
			case 0:
			  //build_and_take_surround(p1);
			  first=3;
			  count++;
			  break;
			
			case 1:
			  //build_and_take_surround(p2);
			  first--;
			  count++;
			  break;
			
			case 2:
			  //build_and_take_surround(p3);
			  first--;
			  count++;
			  break;
			
			case 3:
			  //build_and_take_surround(p4);
			  first--;
			  count++;
			  break;
		}
	}
	if(first==3){
		first=0;
	}
	else{
		first--;
	}//設回第二輪最後一個放的人開始
}

void turn_process(sPlayer *p){
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
			  //trade();
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
}
