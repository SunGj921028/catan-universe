#include "phase.h"
//#include "choose.h"
#define AI "                            ___         ________\n"\
"                           / _ \\       |__    __|\n"\
"                          / / \\ \\         |  |\n"\
"                         / /   \\ \\        |  |\n"\
"                        / /_____\\ \\       |  |\n"\
"                       /  _______  \\    __|  |__\n"\
"                      /_/         \\_\\  |________|\n"
/*int difficulty(){
	CLEAR;
    printf(AI);
    printf("                    \033[92mEasy(Press 'E')\033[m    ");
    printf("\033[91mHard(Press 'H')\033[m\n");
	  printf("                             Back(Press 'B')\n");
	while(1){
        char a=getch();
		if(a=='b' || a=='B'){
			return 0;
		}
		else if(a=='e' || a=='E'){
			//set_ai(easy);
			return 1;
		}
		else if(a=='h' || a=='H'){
			//set_ai(hard);
			return 1;
		}
		else{
			continue;
		}
    }
}*/

void gameover(char *name){
  CLEAR;
    char print[2000]="Player: ";
    char king[]=" has become the king\n";
    char con[]="Congradulations\n";
    strcat(print,name);
    strcat(print,king);

    printf("\n\n\n\n\n\n\n\n\n\n\n                    ");
    for(int i=0;i<strlen(print);i++){
      printf("%c",print[i]);
      fflush(stdout);
      usleep(60000);
    }
    sleep(2);
     printf("                              ");
    for(int i=0;i<strlen(con);i++){
      printf("%c",con[i]);
      fflush(stdout);
      usleep(60000);
    }
}
