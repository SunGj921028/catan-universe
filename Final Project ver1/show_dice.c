#include "phase.h"
#define MOVE printf("\033[9A");
#define ONE "\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m        \033[41m \033[47m        \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"
			
#define TWO "\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m     \033[40m \033[47m           \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m           \033[40m \033[47m     \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"
			
#define THREE "\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m     \033[40m \033[47m           \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m        \033[40m \033[47m        \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m           \033[40m \033[47m     \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"
			  
#define FOUR "\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m     \033[41m \033[47m     \033[41m \033[47m     \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m     \033[41m \033[47m     \033[41m \033[47m     \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"
			 
#define FIVE "\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m        \033[40m \033[47m        \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"
			
#define SIX "\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"\033[47m                 \033[m\n"\
"\033[47m                 \033[m\n"

#define SIX2 "                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"

#define FIVE2 "                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m        \033[40m \033[47m        \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m     \033[40m \033[47m     \033[40m \033[47m     \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"

#define FOUR2 "                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m     \033[41m \033[47m     \033[41m \033[47m     \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m     \033[41m \033[47m     \033[41m \033[47m     \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"

#define THREE2 "                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m     \033[40m \033[47m           \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m        \033[40m \033[47m        \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m           \033[40m \033[47m     \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"

#define TWO2 "                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m     \033[40m \033[47m           \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m           \033[40m \033[47m     \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"

#define ONE2 "                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m        \033[41m \033[47m        \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"\
"                  \033[47m                 \033[m\n"

void show_dice_v1(int dice){//垂直顯示
	CLEAR;
	int ran;
	switch(dice){
		case 2:
			printf(ONE"\n"ONE);
			sleep(2);
			CLEAR;
			break;
		case 3:
			srand(time(NULL));
			ran=rand()%2;
			if(ran==0){printf(ONE"\n"TWO);}
			else{printf(TWO"\n"ONE);}
			sleep(2);
			CLEAR;
			break;
		case 4:
			srand(time(NULL));
			ran=rand()%3;
			if(ran==0){printf(ONE"\n"THREE);}
			else if(ran==1){printf(TWO"\n"TWO);}
			else{printf(THREE"\n"ONE);}
			sleep(2);
			CLEAR;
			break;
		case 5:
			srand(time(NULL));
			ran=rand()%4;
			if(ran==0){printf(ONE"\n"FOUR);}
			else if(ran==1){printf(TWO"\n"THREE);}
			else if(ran==2){printf(THREE"\n"TWO);}
			else{printf(FOUR"\n"ONE);}
			sleep(2);
			CLEAR;
			break;
		case 6:
			srand(time(NULL));
			ran=rand()%5;
			if(ran==0){printf(ONE"\n"FIVE);}
			else if(ran==1){printf(TWO"\n"FOUR);}
			else if(ran==2){printf(THREE"\n"THREE);}
			else if(ran==3){printf(FOUR"\n"TWO);}
			else{printf(FIVE"\n"ONE);}
			sleep(2);
			CLEAR;
			break;
		case 7:
			srand(time(NULL));
			ran=rand()%6;
			if(ran==0){printf(ONE"\n"SIX);}
			else if(ran==1){printf(TWO"\n"FIVE);}
			else if(ran==2){printf(THREE"\n"FOUR);}
			else if(ran==3){printf(FOUR"\n"THREE);}
			else if(ran==4){printf(FIVE"\n"TWO);}
			else{printf(SIX"\n"ONE);}
			sleep(2);
			CLEAR;
			break;
		case 8:
			srand(time(NULL));
			ran=rand()%5;
			if(ran==0){printf(TWO"\n"SIX);}
			else if(ran==1){printf(THREE"\n"FIVE);}
			else if(ran==2){printf(FOUR"\n"FOUR);}
			else if(ran==3){printf(FIVE"\n"THREE);}
			else{printf(SIX"\n"TWO);}
			sleep(2);
			CLEAR;
			break;
		case 9:
			srand(time(NULL));
			ran=rand()%4;
			if(ran==0){printf(THREE"\n"SIX);}
			else if(ran==1){printf(FOUR"\n"FIVE);}
			else if(ran==2){printf(FIVE"\n"FOUR);}
			else{printf(SIX"\n"THREE);}
			sleep(2);
			CLEAR;
			break;
		case 10:
			srand(time(NULL));
			ran=rand()%3;
			if(ran==0){printf(FOUR"\n"SIX);}
			else if(ran==1){printf(FIVE"\n"FIVE);}
			else{printf(SIX"\n"FOUR);}
			sleep(2);
			CLEAR;
			break;
		case 11:
			srand(time(NULL));
			ran=rand()%2;
			if(ran==0){printf(SIX"\n"FIVE);}
			else{printf(FIVE"\n"SIX);}
			sleep(2);
			CLEAR;
			break;
		case 12:
			printf(SIX"\n"SIX);
			sleep(2);
			CLEAR;
			break;
	}
}

void show_dice_v2(int dice){//水平顯示
	CLEAR;
	int ran;
	switch(dice){
		case 2:
			printf(ONE2);
			MOVE
			printf(ONE);
			sleep(2);
			CLEAR;
			break;
		case 3:
			srand(time(NULL));
			ran=rand()%2;
			if(ran==0){printf(TWO2); MOVE printf(ONE);}
			else{printf(ONE2); MOVE printf(TWO);}
			sleep(2);
			CLEAR;
			break;
		case 4:
			srand(time(NULL));
			ran=rand()%3;
			if(ran==0){printf(THREE2); MOVE printf(ONE);}
			else if(ran==1){printf(TWO2); MOVE printf(TWO);}
			else{printf(ONE2); MOVE printf(THREE);}
			sleep(2);
			CLEAR;
			break;
		case 5:
			srand(time(NULL));
			ran=rand()%4;
			if(ran==0){printf(FOUR2); MOVE printf(ONE);}
			else if(ran==1){printf(THREE2); MOVE printf(TWO);}
			else if(ran==2){printf(TWO2); MOVE printf(THREE);}
			else{printf(ONE2); MOVE printf(FOUR);}
			sleep(2);
			CLEAR;
			break;
		case 6:
			srand(time(NULL));
			ran=rand()%5;
			if(ran==0){printf(FIVE2); MOVE printf(ONE);}
			else if(ran==1){printf(FOUR2); MOVE printf(TWO);}
			else if(ran==2){printf(THREE2); MOVE printf(THREE);}
			else if(ran==3){printf(TWO2); MOVE printf(FOUR);}
			else{printf(ONE2); MOVE printf(FIVE);}
			sleep(2);
			CLEAR;
			break;
		case 7:
			srand(time(NULL));
			ran=rand()%6;
			if(ran==0){printf(SIX2); MOVE printf(ONE);}
			else if(ran==1){printf(FIVE2); MOVE printf(TWO);}
			else if(ran==2){printf(FOUR2); MOVE printf(THREE);}
			else if(ran==3){printf(THREE2); MOVE printf(FOUR);}
			else if(ran==4){printf(TWO2); MOVE printf(FIVE);}
			else{printf(ONE2); MOVE printf(SIX);}
			sleep(2);
			CLEAR;
			break;
		case 8:
			srand(time(NULL));
			ran=rand()%5;
			if(ran==0){printf(SIX2); MOVE printf(TWO);}
			else if(ran==1){printf(FIVE2); MOVE printf(THREE);}
			else if(ran==2){printf(FOUR2); MOVE printf(FOUR);}
			else if(ran==3){printf(THREE2); MOVE printf(FIVE);}
			else{printf(TWO2); MOVE printf(SIX);}
			sleep(2);
			CLEAR;
			break;
		case 9:
			srand(time(NULL));
			ran=rand()%4;
			if(ran==0){printf(SIX2); MOVE printf(THREE);}
			else if(ran==1){printf(FIVE2); MOVE printf(FOUR);}
			else if(ran==2){printf(FOUR2); MOVE printf(FIVE);}
			else{printf(THREE2); MOVE printf(SIX);}
			sleep(2);
			CLEAR;
			break;
		case 10:
			srand(time(NULL));
			ran=rand()%3;
			if(ran==0){printf(SIX2); MOVE printf(FOUR);}
			else if(ran==1){printf(FIVE2); MOVE printf(FIVE);}
			else{printf(FOUR2); MOVE printf(SIX);}
			sleep(2);
			CLEAR;
			break;
		case 11:
			srand(time(NULL));
			ran=rand()%2;
			if(ran==0){printf(FIVE2); MOVE printf(SIX);}
			else{printf(SIX2); MOVE printf(FIVE);}
			sleep(2);
			CLEAR;
			break;
		case 12:
			printf(SIX2);
			MOVE
			printf(SIX);
			sleep(2);
			CLEAR;
			break;
	}
}
