#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "map.h"

#define BK_RED printf("\e[0;101m")
#define BK_GRN printf("\e[0;102m")
#define BK_YEL printf("\e[0;103m")
#define BK_BUL printf("\e[0;104m")
#define BK_WIT printf("\e[0;107m")
#define CCLEAR printf("\e[0m")
#define CLR_F_256(N) printf("\e[38;5;"#N"m")
#define CLR_B_256(N) printf("\e[48;5;"#N"m")

//int8_t map[23][13][5];
int8_t c_map_deep = 5;
/*
0 ocean
1 point
2 line
3 block
4 port
*/

//update color
//block random
//puts point

//move rubbor
//port
//player log

//calc lonest road

char map_log[4][6][80];
int8_t log_len=50;
int8_t map_pk[19]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int8_t re_t[19] = {1,3,2,0,5,5,4,2,3,1,4,3,4,1,5,4,3,2,5};
int8_t pt_t[19] = {5,2,6,0,3,8,10,9,12,11,4,8,10,9,4,5,6,3,11};
int8_t ocean_f[34]={62,27,26,25,17,16,15,7,6,5,4,5,6,7,6,5,4,5,6,7,6,5,4,5,6,7,15,16,17,25,26,27,62};
int8_t map_block_i=0;
int8_t map_line_i=0;
int8_t map_point_i=0;
bool is_slash;

/*init use*/
void map_point_init(int8_t i,int8_t j,int8_t map_p_type){
  map[i][j][0] = map_p_type;
  if(map_p_type == 0){//ocean
    for(int8_t k=0;k<c_map_deep;k++){
      map[i][j][k]=0;
    }
  }else if(map_p_type == 1){//point
    map[i][j][1]=0;
    map[i][j][2]=map_point_i;
    map[i][j][3]=0;
    map[i][j][4]=0;
    map_point_i++;
  }else if(map_p_type == 2){//line
    map[i][j][1]=0;//owner
    if(i%2==1){
      map[i][j][3]=0;//----
    }else{
      map[i][j][3] = is_slash ? 1 : 2;/* / or \ */
      is_slash = !is_slash;
    }
    map[i][j][2]=map_line_i;
    map[i][j][4]=0;
    map_line_i++;
  }else if(map_p_type == 3){//block
    for(int8_t ni=i-1;ni<=i+1;ni++){
      map[ni][j][0]=3;
      for(int8_t k=1;k<c_map_deep;k++){
        map[ni][j][4]=0;
      }
    }
    map[i-1][j][1]=map_block_i;
    map[i-1][j][2]=re_t[map_block_i];//region
    map[i][j][1]=map_block_i;
    map[i][j][2]=re_t[map_block_i];//region
    map[i+1][j][1]=map_block_i;
    map[i+1][j][2]=re_t[map_block_i];//region
    map[i][j][3]=pt_t[map_block_i];//point
    map_block_i++;
  }else if(map_p_type == 4){//port

  }
  return;
}

/*print color selection*/
void map_color_slt(int8_t a,int8_t b){//a: type; b: pID or block type
  CCLEAR;
  if(a==0){
    BK_BUL;
  }else if(a==1){
    CLR_B_256(8);
    switch(b){
      case 0:CLR_F_256(235);break;
      case 1:CLR_F_256(9);break;
      case 2:CLR_F_256(15);break;
      case 3:CLR_F_256(12);break;
      case 4:CLR_F_256(208);break;
    }
  }else if(a==2){
    switch(b){
      case 0:CLR_F_256(244);break;
      case 1:CLR_F_256(9);break;
      case 2:CLR_F_256(15);break;
      case 3:CLR_F_256(12);break;
      case 4:CLR_F_256(208);break;
    }
  }else if(a==3){
    switch(b){
      case 0:{CLR_B_256(142);CLR_F_256(0);}break;//Desert
      case 1:CLR_B_256(124);break;//blick
      case 2:{CLR_B_256(249);CLR_F_256(0);}break;//iron
      case 3:{CLR_B_256(82);CLR_F_256(0);}break;//sheep
      case 4:CLR_B_256(22);break;//wood
      case 5:{CLR_B_256(226);CLR_F_256(0);}break;//wheat
    }
  }
  
}

/*print symbol selection*/
void map_print_slt(int8_t i,int8_t j,int8_t ptime,int8_t pmood){
  int8_t a=map[i][j][0];
  int8_t ptype;
  if(a==1){
    map_color_slt(a,map[i][j][1]);
    if(pmood==1){
      printf("%02d",map[i][j][2]);
    }else{
      if(map[i][j][3]==1){
        printf("V");
      }else if(map[i][j][3]==2){
        printf("C");
      }else{
        printf("*");
      }
    }
  }else if(a==2){
    map_color_slt(a,map[i][j][1]);
    ptype=map[i][j][3];
    if(pmood==2 && ptime%3==2){
      printf("%02d",map[i][j][2]);
    }else if(ptype==0){
      if(pmood==2){
        printf("--%02d--",map[i][j][2]);
      }else if(pmood == 1){
        printf("----");
      }else{
        printf("------");
      }
    }else if(ptype==1){
      printf("/");
    }else if(ptype==2){
      printf("\\");
    }
  }else if(a==3){
    map_color_slt(a,map[i][j][2]);
    ptype=map_pk[map[i][j][1]];
    if(ptype==0){
      if(pmood == 2){
        printf("      ");
      }else{
        printf("        ");
      }
    }else if(ptype==1){
      printf("    %02d    ",map[i+1][j][3]);
    }else if(ptype==2){
      switch(map[i][j][2]){
        case 0:printf("   DESERT   ");break;
        case 1:printf("   BRICK    ");break;
        case 2:printf("    IRON    ");break;
        case 3:printf("   SHEEP    ");break;
        case 4:printf("    WOOD    ");break;
        case 5:printf("   WHEAT    ");break;
      }
    }else if(ptype==3){
      if(map[i-1][j][4]==1){
        printf(" occupied ");
      }else{
        printf("          ");
      }
    }else if(ptype==4){
      printf("   %02d   ",map[i][j][1]);
    }
    map_pk[map[i][j][1]] = map_pk[map[i][j][1]]+1;
  }else if(a==0){
    map_color_slt(a,0);
    int32_t temp = ocean_f[ptime];
    if(pmood==2){
      if(ptime==11||ptime==17||ptime==23||ptime==26||ptime==29){
        temp -= 1;
      }
    }else if(pmood==1){
      if(ptime==10||ptime==16||ptime==22){
        temp -= 1;
      }
    }
    if(j==0||j==12){
      for(int8_t k=0;k<temp;k++){
        printf(" ");
      }
    }
  }
}

//me card type,knight used, latest move;
//oth card total,knight used, latest move;
/*log printer detect&select*/
void pd_print(int8_t ptime){
  if(ptime<29){
    printf("%02d",ptime);BK_WIT;printf("  ");CCLEAR;
  }
  int8_t playerID=(ptime/7);
  int8_t pd_line=ptime%7;
  map_color_slt(2,playerID+1);
  if(pd_line==0){
    BK_WIT;
    for(int8_t i=0;i<log_len;i++){
      printf(" ");
    }
    CCLEAR;
  }else{
    printf("%s",map_log[playerID][pd_line-1]);
    for(int8_t i=strlen(map_log[playerID][pd_line-1]);i<log_len;i++){
      printf(" ");
    }
  }
  if(ptime<29){
    BK_WIT;printf("  ");CCLEAR;
  }
  CCLEAR;
}

/*center of map and log*/
void map_p_main2log(int8_t *ptime,int8_t pmood){
  CCLEAR;
  if(pmood==0){
    pd_print(*ptime);
  }
  (*ptime)++;
  printf("\n");
}

/*debug tool: point details*/
void d3_pd(int32_t x,int32_t y){
  for(int8_t k=0;k<c_map_deep;k++){
    printf("%d:%d/",k,map[x][y][k]);
  }
  printf("\n");
}

/*resource switch*/
int32_t resource_switch(int32_t region_ID){
  switch(region_ID){
    case 1:return 3;break;
    case 2:return 0;break;
    case 3:return 4;break;
    case 4:return 1;break;
    case 5:return 2;break;
  }
}

/*village upgrade*/
int32_t village_upgrade(int32_t point_ID,int32_t player_ID){
  for(int8_t i=0;i<23;i++){
    for(int8_t j=0;j<13;j++){
      if(map[i][j][0]==1 && map[i][j][2]==point_ID){
        if(map[i][j][1]==player_ID && map[i][j][3] == 1){
          map[i][j][3] = 2;
          printf("Upgrade success!\n");
          return 0;
        }else{
          printf("Can't be upgrade!\n");
          return -1;
        }
      }
    }
  }
}

/*Map initial*/
void map_init(){
  for(int8_t i=0;i<23;i++){
    for(int8_t j=0;j<13;j++){
      for(int8_t k=0;k<c_map_deep;k++){
        map[i][j][k]=0;
      }
    }
  }
  for(int8_t i=0;i<4;i++){//D3rr0r
    for(int8_t j=0;j<6;j++){
      for(int8_t k=0;k<80;k++){
        map_log[i][j][k]=0;
      }
    }
  }
  for(int8_t i=0;i<4;i++){//D3rr0r
    for(int8_t j=0;j<6;j++){
      for(int8_t k=0;k<26+j;k++){
        map_log[i][j][k]=65+k;
      }
    }
  }
  for(int8_t i=0;i<23;i++){
    if(i<=6){
      is_slash = true;
    }else if(6<i && i<16){
      is_slash = i%4==0 ? false : true;
    }else if(16<=i){
      is_slash = false;
    }
    for(int8_t j=0;j<13;j++){
      if(j==0||j==12||i==0||i==22){
        map_point_init(i,j,0);
      }else if(i%2==1 && j%2==1){//point
        if(5<=j && j<=7){
          map_point_init(i,j,1);
        }else if(3<=j && j<=9 && 3<=i && i<=19){
          map_point_init(i,j,1);
        }else if(1<=j && j<=11 && 5<=i && i<=17){
          map_point_init(i,j,1);
        }
      }else if(j%2==1 && i%2==0){//line-1
        if(5<=j && j<=7){
          map_point_init(i,j,2);
        }else if(3<=j && j<=9 && 3<=i && i<=19){
          map_point_init(i,j,2);
        }else if(1<=j && j<=11 && 5<=i && i<=17){
          map_point_init(i,j,2);
        }
      }else if(j%2==0 && i%2==1){//line-2 & block
        if(j==6 && i%4==1){
          map_point_init(i,j,2);
        }else if((j==4||j==8)&&(2<i&&i<20)&&i%4==3){
          map_point_init(i,j,2);
        }else if((j==2||j==10)&&(4<i&&i<18)&&i%4==1){
          map_point_init(i,j,2);
        }else if(j==6 && i%4==3){
          map_point_init(i,j,3);
        }else if((j==4||j==8)&&(2<i&&i<20)&&i%4==1){
          map_point_init(i,j,3);
        }else if((j==2||j==10)&&(4<i&&i<18)&&i%4==3){
          map_point_init(i,j,3);
        }
      }
    }
  }
}

/*Map printer*/
int32_t map_print(int8_t printer_mood){
  int8_t ptime=0;
  for(int8_t i=0;i<23;i++){
    if(i==0||i==22){
      map_print_slt(i,0,ptime,printer_mood);
    }
    if(i%2==0 && 0<i && i<22){
      for(int8_t j=0;j<26;j++){
        if(j==13){
          map_p_main2log(&ptime,printer_mood);
        }
        map_print_slt(i,j%13,ptime,printer_mood);
      }
    }else if(i%2==1 && 0<i && i<22){
      for(int8_t j=0;j<13;j++){
        map_print_slt(i,j,ptime,printer_mood);
      }
    }
    map_p_main2log(&ptime,printer_mood);
  }
  for(int8_t i=0;i<19;i++){
    map_pk[i]=0;
  }
  // for(int8_t i=0;i<23;i++){
  //   for(int8_t j=0;j<13;j++){
  //     printf("%d",map[i][j][0]);
  //   }
  //   printf("\n");
  // }
  printf("\e[0m \n\e[0m");
}

int32_t build_village(int32_t player_ID, int32_t point_ID, int8_t is_init){
  if(!(0 <= point_ID && point_ID < 54)){
    printf("Point ID is invalid!\n");
    return -1;
  }
  for(int8_t i=0;i<23;i++){
    for(int8_t j=0;j<13;j++){
      if(map[i][j][0] == 1 && map[i][j][2]==point_ID){
        if(map[i][j][1]==0){
          bool near_no_player=true;
          bool road_connected=false;
          if(map[i-1][j][0]==2){//up
            if(map[i-2][j][1]!=0){near_no_player=false;}
            if(map[i-1][j][1]==player_ID){road_connected=true;}
          }
          if(map[i+1][j][0]==2){//down
            if(map[i+2][j][1]!=0){near_no_player=false;}
            if(map[i+1][j][1]==player_ID){road_connected=true;}
          }
          if(map[i][j-1][0]==2){//left
            if(map[i][j-2][1]!=0){near_no_player=false;}
            if(map[i][j-1][1]==player_ID){road_connected=true;}
          }
          if(map[i][j+1][0]==2){//right
            if(map[i][j+2][1]!=0){near_no_player=false;}
            if(map[i][j+1][1]==player_ID){road_connected=true;}
          }
          if(is_init==1){
            road_connected=true;
          }
          if(near_no_player && road_connected){
            map[i][j][1] = player_ID;
            map[i][j][3] = 1;
            printf("Build village %d %d success!\n",i,j);
            return 0;
          }else if(!near_no_player){
            printf("This village is too close to others!\n");
            return -1;
          }else if(!road_connected){
            printf("No road connected!\n");
            return -1;
          }
        }else{
          printf("This village is owned by other players!\n");
          return -1;
        }
      }
    }
  }
  printf("This point can't be build!\n");
  return -1;
}

int32_t build_road(int32_t player_ID, int32_t road_ID){
  if(!(0 <= road_ID && road_ID < 72)){
    printf("Road ID is invalid!\n");
    return -1;
  }
  for(int8_t i=0;i<23;i++){
    for(int8_t j=0;j<13;j++){
      if(map[i][j][0] == 2 && map[i][j][2]==road_ID){
        if(map[i][j][1]==0){
          bool road_connected = false;
          bool near_point = false;
          if(map[i-1][j-1][0]==2 && map[i-1][j-1][1]==player_ID){road_connected = true;}
          if(map[i-1][j+1][0]==2 && map[i-1][j+1][1]==player_ID){road_connected = true;}
          if(map[i+1][j-1][0]==2 && map[i+1][j-1][1]==player_ID){road_connected = true;}
          if(map[i+1][j+1][0]==2 && map[i+1][j+1][1]==player_ID){road_connected = true;}
          if(map[i-2][j][0]==2 && map[i-2][j][1]==player_ID){road_connected = true;}
          if(map[i+2][j][0]==2 && map[i+2][j][1]==player_ID){road_connected = true;}
          if(map[i-1][j][0]==1 && map[i-1][j][1]==player_ID){near_point = true;}
          if(map[i+1][j][0]==1 && map[i+1][j][1]==player_ID){near_point = true;}
          if(map[i][j-1][0]==1 && map[i][j-1][1]==player_ID){near_point = true;}
          if(map[i][j+1][0]==1 && map[i][j+1][1]==player_ID){near_point = true;}
          if(near_point || road_connected){
            map[i][j][1] = player_ID;
            printf("Build road %d %d success!\n",i,j);
            return 0;
          }else{
            printf("No road or village connected!\n");
            return -1;
          }
        }
      }
    }
  }
  printf("This road can't be build!\n");
  return -1;
}

int32_t harvest(int32_t dice_number,int32_t *harvest_resource){
  int32_t temp=0;
  for(int8_t i=3;i<20;i=i+2){
    for(int8_t j=2;j<12;j=j+2){
      if(map[i][j][0]==3 && map[i][j][3]==dice_number && map[i][j][4] != 1){
        *(harvest_resource + temp*5) = resource_switch(map[i][j][2]);
        if(map[i-2][j-1][1] != 0){//0
          *(harvest_resource + temp*5 + map[i-2][j-1][1]) += map[i-2][j-1][3];
        }
        if(map[i-2][j+1][1] != 0){//1
          *(harvest_resource + temp*5 + map[i-2][j+1][1]) += map[i-2][j+1][3];
        }
        if(map[i][j-1][1] != 0){//2
          *(harvest_resource + temp*5 + map[i][j-1][1]) += map[i][j-1][3];
        }
        if(map[i][j+1][1] != 0){//3
          *(harvest_resource + temp*5 + map[i][j+1][1]) += map[i][j+1][3];
        }
        if(map[i+2][j-1][1] != 0){//4
          *(harvest_resource + temp*5 + map[i+2][j-1][1]) += map[i+2][j-1][3];
        }
        if(map[i+2][j+1][1] != 0){//5
          *(harvest_resource + temp*5 + map[i+2][j+1][1]) += map[i+2][j+1][3];
        }
        temp++;
        if(dice_number == 2 || dice_number == 12){
          *(harvest_resource + temp*5) == -1;
          return 0;
        }
      }
    }
  }
  return 0;
}