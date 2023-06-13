#include "catan_windows.h"
#include <stdio.h>
void startstory(){
    CLEAR
    char a[]="Welcome\nNew comer\nTo this mysterious island\nI know why you are here\nTo find yourself a better life, huh?\nUnfortunately, you are not the only one\nThere are also lots of people want to build their own kingdoms\nAnd there can be ONLY ONE ruler\nNow, you've probably guessed what you have to do\nShow them who's the superior\nGood luck...";
    for(int i=0;i<strlen(a);i++){
        if(a[i]=='\n'){
            printf("\n\n");
            usleep(1000000);
        }
        else if(a[i]==','){
            printf("%c",a[i]);
            usleep(600000);
        }
        else if(a[i]=='.'){
            printf("%c",a[i]);
            usleep(700000);
        }
        else{
            printf("%c",a[i]);
            usleep(60000);
        }
    }
}

int choosemode(){
    CLEAR
    printf("\n\n\n\n\n\033[30C###############      ###############\n"
           "\033[30C#  3 Players  #      #  4 Players  #\n"
           "\033[30C###############      ###############\n"
           "\033[30C   (PRESS 3)            (PRESS 4)\n\n"
           "\033[30C       BACK TO TITLE(PRESS B)");
           while(1){
                char a=getch();
                if(a=='3'){
                    //start game in 3 mode
                    //...
                    //...
                    return 3;
                }
                else if(a=='4'){
                    //start gamr in 4 mode
                    //...
                    //...
                    return 4;
                }
                else if(a=='b' || a=='B'){
                    return 0;
                }
                else{
                    continue;
                }
           }
}

void startup(){
    CLEAR
    printf("\033[30C ________        ___      ____________      ___         _       _\n"
       "\033[30C/ _______|      / _ \\    |____    ____|    / _ \\       | \\     | |\n"
      "\033[29C/ /	     / / \\ \\        |  |        / / \\ \\      |  \\    | |\n"
     "\033[28C/ /	            / /   \\ \\       |  |       / /   \\ \\     | | \\   | |\n"
     "\033[28C\\ \\            / /_____\\ \\      |  |      / /_____\\ \\    | |\\ \\  | |\n"
      "\033[29C\\ \\_______   /  _______  \\     |  |     /  _______  \\   | | \\ \\_| |\n"
       "\033[30C\\________| /_/         \\_\\    |__|    /_/         \\_\\  |_|  \\____|\n\n\n");//print title
    printf("\033[35CSTART(PRESS S)             HOW TO PLAY(PRESS H)             QUIT(PRESS Q)");

    while(1){
            char a=getch();
        if(a=='h' || a=='H'){
            system("start https://andyventure.com/boardgame-catan/");
        }
        else if(a=='s' || a=='S'){
            return;
        }
        else if(a=='q' || a=='Q'){
            exit(0);
        }
        else{
            continue;
        }
    }
}

int main(){
    int mode=0;
    while(1){
        startup();
        mode=choosemode();
        if(mode==3 || mode==4){
            break;
        }
    }
    startstory();
}
