#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "map.h"
#include "init.h"
#include "data.h"

#define BK_RED printf("\e[0;101m")
#define BK_GRN printf("\e[0;102m")
#define BK_YEL printf("\e[0;103m")
#define BK_BUL printf("\e[0;104m")
#define BK_WIT printf("\e[0;107m")
#define CCLEAR printf("\e[0m")
#define CLR_F_256(N) printf("\e[38;5;"#N"m")
#define CLR_B_256(N) printf("\e[48;5;"#N"m")
#define MAX_VERTICES 100
#define LOG_LEN 30
//int8_t map[23][13][5];
int8_t c_map_deep = 5;

//update color
//block random
//puts point

//move rubbor
//port
//player log

//calc lonest road

char player_log[40][LOG_LEN+1];
int8_t map_pk[19]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int32_t map_ok=0;
int8_t ocean_f[38][2]={{31,31},{31,31},{29,29},{27,27},{26,26},{25,25},{17,17},{12,12},{15,15},{7,7},{6,6},{5,5},{4,4},{5,5},{6,6},{7,7},{2,2},{5,5},{4,4},{5,5},{6,6},{7,7},{6,6},{5,5},{4,4},{1,1},{6,6},{7,7},{15,15},{16,16},{17,17},{21,21},{26,26},{27,27},{31,31},{31,31},{31,31}};
int8_t map_block_i=0;
int8_t map_line_i=0;
int8_t map_point_i=0;
int max_length;
int32_t vertices_array[72];
int graph[MAX_VERTICES][MAX_VERTICES];
int visited[MAX_VERTICES];

bool is_slash;

bool judge_build(sPlayer * player, uint8_t build_type, uint8_t p){
    //0->village
    //1->road
    //2->city
    if(build_type==1){
        if(player->wood>0 && player->brick>0){ return true;}
        else{ return false;}
    }else if(build_type==0){
        if(player->wood>0 && player->sheep>0 && player->wheat>0 && player->brick>0 ){
          bool something_can = false;
          for(int m=0;m<54;m++){
            for(int8_t i=0;i<23;i++){
              for(int8_t j=0;j<13;j++){
                if(map[i][j][0] == 1 && map[i][j][2]==m){
                  if(map[i][j][1]==0){
                    bool near_no_player=true;
                    bool road_connected=false;
                    if(map[i-1][j][0]==2){//up
                      if(map[i-2][j][1]!=0){near_no_player=false;}
                      if(map[i-1][j][1]==p){road_connected=true;}
                    }
                    if(map[i+1][j][0]==2){//down
                      if(map[i+2][j][1]!=0){near_no_player=false;}
                      if(map[i+1][j][1]==p){road_connected=true;}
                    }
                    if(map[i][j-1][0]==2){//left
                      if(map[i][j-2][1]!=0){near_no_player=false;}
                      if(map[i][j-1][1]==p){road_connected=true;}
                    }
                    if(map[i][j+1][0]==2){//right
                      if(map[i][j+2][1]!=0){near_no_player=false;}
                      if(map[i][j+1][1]==p){road_connected=true;}
                    }
                    if(near_no_player && road_connected){
                      something_can = true;
                    }
                  }
                }
              }
            }
          }
          if(!something_can){
            return false;
          }
          return true;
        }
        else {return false;}
    }else if(build_type==2){
        if(player->wheat>=2 && player->iron>=3){ return true;}
        else{ return false;}
    }
}

/*resource switch*/
int32_t resource_switch(int32_t region_type){
  switch(region_type){
    case 0:return 5;break;
    case 1:return 3;break;
    case 2:return 0;break;
    case 3:return 4;break;
    case 4:return 1;break;
    case 5:return 2;break;
  }
}

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
    map[i][j][4]=-1;
    if((i==1 && j==5) || (i==1 && j==7) || (i==15 && j==1) || (i==17 && j==1) || (i==15 && j==11) || (i==17 && j==11) || (i==19 && j==3) || (i==19 && j==5) || (i==19 && j==7) || (i==19 && j==9)){
      map[i][j][4]=5;
    }else if((i==9 && j==11) || (i==11 && j==11)){
      map[i][j][4]=0;
    }else if((i==3 && j==3) || (i==5 && j==3)){
      map[i][j][4]=1;
    }else if((i==3 && j==9) || (i==5 && j==9)){
      map[i][j][4]=2;
    }else if((i==9 && j==1) || (i==11 && j==1)){
      map[i][j][4]=3;
    }else if((i==19 && j==7) || (i==19 && j==9)){
      map[i][j][4]=4;
    }
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
        map[ni][j][k]=0;
      }
    }
    map[i-1][j][1]=map_block_i;
    map[i-1][j][2]=resource_switch(re_t[map_block_i]);//region
    map[i][j][1]=map_block_i;
    map[i][j][2]=resource_switch(re_t[map_block_i]);//region
    map[i+1][j][1]=map_block_i;
    map[i+1][j][2]=resource_switch(re_t[map_block_i]);//region
    map[i][j][3]=pt_t[map_block_i];//point
    if(resource_switch(re_t[map_block_i])==5){
      map[i][j][4]=1;
    }
    map_block_i++;
  }
  return;
}

/*print color selection*/
void map_color_slt(int8_t a,int8_t b){//a: type; b: playerID or block type
  CCLEAR;
  if(a==0){
    BK_BUL;
  }else if(a==1){
    CLR_B_256(8);
    switch(b){
      case 0:CLR_F_256(235);break;
      case 1:CLR_F_256(9);break;
      case 2:CLR_F_256(15);break;
      case 3:CLR_F_256(51);break;
      case 4:CLR_F_256(165);break;//208
    }
  }else if(a==2){
    switch(b){
      case 0:CLR_F_256(244);break;
      case 1:CLR_F_256(9);break;
      case 2:CLR_F_256(15);break;
      case 3:CLR_F_256(51);break;
      case 4:CLR_F_256(165);break;//208
    }
  }else if(a==3){
    switch(b){
      case 0:{CLR_B_256(249);CLR_F_256(0);}break;//iron
      case 1:CLR_B_256(22);break;//wood
      case 2:{CLR_B_256(226);CLR_F_256(0);}break;//wheat
      case 3:CLR_B_256(124);break;//blick
      case 4:{CLR_B_256(82);CLR_F_256(0);}break;//sheep
      case 5:{CLR_B_256(142);CLR_F_256(0);}break;//Desert
      case 7:{CLR_B_256(57);}break;
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
    if(pmood==2 && ptime%3==1){
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
    int8_t color_slt_tempi=0;
    ptype=map_pk[map[i][j][1]];
    if(ptype==0 || ptype==1){
      color_slt_tempi=i+1;
    }else if(ptype==2){
      color_slt_tempi=i;
    }else if(ptype==3 || ptype==4){
      color_slt_tempi=i-1;
    }
    if(map[color_slt_tempi][j][4]==1){
      map_color_slt(a,7);
    }else{
      map_color_slt(a,map[i][j][2]);
    }
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
        case 0:printf("    IRON    ");break;
        case 1:printf("    WOOD    ");break;
        case 2:printf("   WHEAT    ");break;
        case 3:printf("   BRICK    ");break;
        case 4:printf("   SHEEP    ");break;
        case 5:printf("   DESERT   ");break;
      }
    }else if(ptype==3){
      if(map[i-1][j][4]==1){
        printf(" occupied ");
      }else{
        printf("          ");
      }
    }else if(ptype==4){
      if(pmood==3){
        printf("   %02d   ",map[i][j][1]);
      }else{
        printf("        ");
      }
    }
    map_pk[map[i][j][1]] = map_pk[map[i][j][1]]+1;
  }else if(a==0){
    if(map_ok%2 == 1 && j==12){
      if(ptime==7){
        map_color_slt(3,2);printf("2:1 ");
      }else if(ptime==16){
        map_color_slt(3,0);printf("2:1 ");
      }else if(ptime==25){
        map_color_slt(3,5);printf("3:1 ");
      }else if(ptime==31){
        map_color_slt(3,4);printf("2:1 ");
      }
    }
    map_color_slt(a,0); 
    int8_t temp = ocean_f[ptime][map_ok%2]+3;
    if(pmood==2){
      if(ptime==13||ptime==19||ptime==25||ptime==28||ptime==31){
        temp -= 1;
      }
    }else if(pmood==1){
      if(ptime==12||ptime==18||ptime==24){
        temp -= 1;
      }
    }
    if(j==0||j==12){
      for(int8_t k=0;k<temp;k++){
        printf(" ");
      }
    }
    if(map_ok%2 == 0 && j==0){
      if(ptime==2){
        map_color_slt(3,5);printf(" 3:1");
      }else if(ptime==7){
        map_color_slt(3,1);printf(" 2:1");
      }else if(ptime==16){
        map_color_slt(3,3);printf(" 2:1");
      }else if(ptime==25){
        map_color_slt(3,5);printf(" 3:1");
      }else if(ptime==31){
        map_color_slt(3,5);printf(" 3:1");
      }
    }

    map_ok++;
    if(i==0 || i==22){
      temp = ocean_f[ptime][map_ok%2]+3;
      map_color_slt(a,0);
      for(int8_t k=0;k<temp;k++){
        printf(" ");
      }
      map_ok++;
    }
  }
}

void pdp0(int32_t len){
  CCLEAR;
  for(int8_t i=len;i<LOG_LEN;i++){
    printf(" ");
  }
}

int32_t pd_slt(int32_t player_ID, int32_t log_order){
  player_ID--;
  printf("%s",player_log[player_ID*10+log_order]);
  return strlen(player_log[player_ID*10+log_order]);
}

void pd_builder(){
  for(int32_t i=0;i<4;i++){
    if(i==0){
      sprintf(player_log[i*10+0],"1:player Name\0");
    }else{
      sprintf(player_log[i*10+0],"1:My Name\0");
    }
    sprintf(player_log[i*10+1],"2:Lonest road\0");
    sprintf(player_log[i*10+2],"3:Knight card\0");
    if(i==0){
      sprintf(player_log[i*10+3]," %02d %02d %02d %02d %02d\0",1,2,3,4,5);
    }else{
      sprintf(player_log[i*10+3],"4:total card\0");
    }
    if(i==0){
      sprintf(player_log[i*10+4],"5:z8 503 card\0");
    }else{
      sprintf(player_log[i*10+4],"5:total z8 503 card\0");
    }
    sprintf(player_log[i*10+5],"6:road card\0");
    sprintf(player_log[i*10+6],"7:village card\0");
    sprintf(player_log[i*10+7],"8:city card\0");
    sprintf(player_log[i*10+8],"9:score card\0");
    sprintf(player_log[i*10+9],"10:resss card\0");
  }
}

//me card type,knight used, latest move;
//oth card total,knight used, latest move;
/*log printer detect&select*/
void pd_print(int8_t ptime){
  char temp[100];
  int8_t u_h=10;
  int8_t d_h=9;
  for(int8_t i=0;i<100;i++){
    temp[i] = 0;
  }
  if(ptime<u_h+d_h+3){
    BK_WIT;printf("  ");CCLEAR;
    if(ptime==0 || ptime==u_h+1 || ptime==u_h+d_h+2){
      for(int8_t i=0;i<LOG_LEN*2+2;i++){
        sprintf(&(temp[i])," ");
      }
      BK_WIT;printf("%s",temp);CCLEAR;
    }else if(ptime<u_h+1){
      map_color_slt(2,1);
      if(ptime<4){
        pdp0(pd_slt(1,ptime-1));
      }else if(ptime==4){
        for(int8_t i=0;i<15;i++){
          if(i%3==0){map_color_slt(3,i/3);}
          printf("%c",player_log[3][i]);
        }
        CCLEAR;pdp0(15);
      }else if(ptime==5){
        pdp0(printf("c1 c2 c3\0"));
      }else{
        pdp0(pd_slt(1,(ptime-2)));
      }
      BK_WIT;printf("  ");CCLEAR;
      map_color_slt(2,2);pdp0(ptime<u_h ? pd_slt(2,(ptime-1)):0);
    }else if(u_h+1<ptime && ptime<u_h+d_h+2){
      map_color_slt(2,3);pdp0(pd_slt(3,(ptime%(u_h+1))-1));
      BK_WIT;printf("  ");CCLEAR;
      map_color_slt(2,4);pdp0(pd_slt(4,(ptime%(u_h+1))-1));
    }
    BK_WIT;printf("  ");CCLEAR;
  }
  
}

/*center of map and log*/
void map_p_main2log(int8_t *ptime,int8_t pmood){
  CCLEAR;
  printf("%02d",*ptime);
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

/*Map initial*/
void map_init(){
  for(int8_t i=0;i<23;i++){
    for(int8_t j=0;j<13;j++){
      for(int8_t k=0;k<c_map_deep;k++){
        map[i][j][k]=0;
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
  pd_builder();
  int8_t ptime=0;
  for(int8_t i=0;i<23;i++){
    if(i==0||i==22){
      map_print_slt(i,0,ptime,printer_mood);map_p_main2log(&ptime,printer_mood);
      map_print_slt(i,0,ptime,printer_mood);map_p_main2log(&ptime,printer_mood);
      map_print_slt(i,0,ptime,printer_mood);map_p_main2log(&ptime,printer_mood);
    }
    if(i%2==0 && 0<i && i<22){
      for(int8_t j=0;j<26;j++){
        if(j==13){
          map_p_main2log(&ptime,printer_mood);
        }
        map_print_slt(i,j%13,ptime,printer_mood);
      }
      map_p_main2log(&ptime,printer_mood);
    }else if(i%2==1 && 0<i && i<22){
      for(int8_t j=0;j<13;j++){
        map_print_slt(i,j,ptime,printer_mood);
      }
      map_p_main2log(&ptime,printer_mood);
    }
  }
  for(int8_t i=0;i<19;i++){
    map_pk[i]=0;
  }
  map_ok=0;
  // for(int8_t i=0;i<23;i++){
  //   for(int8_t j=0;j<13;j++){
  //     printf("%d",map[i][j][4]);
  //   }
  //   printf("\n");
  // }
  printf("\e[0m \n\e[0m");
}

int32_t build_village(int32_t player_ID, int32_t point_ID, int8_t init_time, uint8_t is_ai){
  if(!(0 <= point_ID && point_ID < 54) && (!is_ai)){
    printf("Point ID is invalid!\n");
    return -1;
  }
  if(!(1 <=player_ID && player_ID <=4) && (!is_ai)){
    printf("No player exist!\n");
    return -1;
  }
  for(int i=0;i<5;i++){
    init_build_take[i] = 0;
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
          if(init_time>=1){
            road_connected=true;
          }
          if(near_no_player && road_connected){
            if(is_ai){
              for(int8_t m=i-1;m<=i+1;m++){
                for(int8_t n=j-1;n<=j+1;n++){
                  if(map[m][n][0]==3 && map[m][n][2]==5){
                    return 700;
                  }
                }
              }
            }
            map[i][j][1] = player_ID;
            map[i][j][3] = 1;
            if(!is_ai){
              printf("Build village %d %d success!\n",i,j);
            }
            if(init_time>=1){
              int32_t road_total_temp=0;
              for(int8_t i=0;i<4;i++){init_near_road[i] = -1;}
              if(map[i-1][j][0]==2){
                init_near_road[road_total_temp+1] = map[i-1][j][2];
                road_total_temp++;
              }
              if(map[i+1][j][0]==2){
                init_near_road[road_total_temp+1] = map[i+1][j][2];
                road_total_temp++;
              }
              if(map[i][j-1][0]==2){
                init_near_road[road_total_temp+1] = map[i][j-1][2];
                road_total_temp++;
              }
              if(map[i][j+1][0]==2){
                init_near_road[road_total_temp+1] = map[i][j+1][2];
                road_total_temp++;
              }
              init_near_road[0] = road_total_temp;
            }
            if(init_time==2){
              for(int8_t k=0;k<5;k++){
                init_build_take[k]=0;
              }
              if(map[i][j-1][0]==2){
                if(map[i][j+1][0]==3 && map[i][j+1][2]!=5){
                  init_build_take[map[i][j+1][2]]++;
                }
                if(map[i-1][j-1][0]==3 && map[i-1][j-1][2]!=5){
                  init_build_take[map[i-1][j-1][2]]++;
                }
                if(map[i+1][j-1][0]==3 && map[i+1][j-1][2]!=5){
                  init_build_take[map[i+1][j-1][2]]++;
                }
              }else if(map[i][j+1][0]==2){
                if(map[i][j-1][0]==3 && map[i][j-1][2]!=5){
                  init_build_take[map[i][j-1][2]]++;
                }
                if(map[i-1][j+1][0]==3 && map[i-1][j+1][2]!=5){
                  init_build_take[map[i-1][j+1][2]]++;
                }
                if(map[i+1][j+1][0]==3 && map[i+1][j+1][2]!=5){
                  init_build_take[map[i+1][j+1][2]]++;
                }
              }
            }
            return 1;
          }else if(!near_no_player && (!is_ai)){
            printf("This village is too close to others!\n");
            return -1;
          }else if(!road_connected && (!is_ai)){
            printf("No road connected!\n");
            return -1;
          }
        }else{
          if(!is_ai){
            printf("This village is owned by other players!\n");
          }
          return -1;
        }
      }
    }
  }
  if(!is_ai){
    printf("This point can't be build!\n");
  }
  return -1;
}

/*village upgrade*/
int32_t village_upgrade(int32_t player_ID,int32_t point_ID, uint8_t is_ai){
  for(int8_t i=0;i<23;i++){
    for(int8_t j=0;j<13;j++){
      if(map[i][j][0]==1 && map[i][j][2]==point_ID){
        if(map[i][j][1]==player_ID && map[i][j][3] == 1){
          map[i][j][3] = 2;
          if(!is_ai){
            printf("Upgrade success!\n");
          }
          return 1;
        }else{
          if(!is_ai){
            printf("Can't be upgrade!\n");
          }
          return -1;
        }
      }
    }
  }
}

int32_t build_road(int32_t player_ID, int32_t road_ID, uint8_t is_ai){
  if(!(0 <= road_ID && road_ID < 72)  && (!is_ai)){
    printf("Road ID is invalid!\n");
    return -1;
  }
  for(int8_t i=0;i<23;i++){
    for(int8_t j=0;j<13;j++){
      if(map[i][j][0] == 2 && map[i][j][2]==road_ID){
        if(map[i][j][1]==0){
          bool road_connected = false;
          bool near_point = false;
          if(map[i-1][j-1][0]==2 && map[i-1][j-1][1]==player_ID){if(map[i][j-1][0]==1 && map[i][j-1][1]==0){road_connected = true;}}
          if(map[i-1][j+1][0]==2 && map[i-1][j+1][1]==player_ID){if(map[i][j-1][0]==1 && map[i][j-1][1]==0){road_connected = true;}}
          if(map[i+1][j-1][0]==2 && map[i+1][j-1][1]==player_ID){if(map[i][j+1][0]==1 && map[i][j+1][1]==0){road_connected = true;}}
          if(map[i+1][j+1][0]==2 && map[i+1][j+1][1]==player_ID){if(map[i][j+1][0]==1 && map[i][j+1][1]==0){road_connected = true;}}
          if(map[i-2][j][0]==2 && map[i-2][j][1]==player_ID){if(map[i-1][j][0]==1 && map[i-1][j][1]==0){road_connected = true;}}
          if(map[i+2][j][0]==2 && map[i+2][j][1]==player_ID){if(map[i+1][j][0]==1 && map[i+1][j][1]==0){road_connected = true;}}
          if(map[i-1][j][0]==1 && map[i-1][j][1]==player_ID){near_point = true;}
          if(map[i+1][j][0]==1 && map[i+1][j][1]==player_ID){near_point = true;}
          if(map[i][j-1][0]==1 && map[i][j-1][1]==player_ID){near_point = true;}
          if(map[i][j+1][0]==1 && map[i][j+1][1]==player_ID){near_point = true;}
          if(near_point || road_connected){
            map[i][j][1] = player_ID;
            if(!is_ai){
              printf("Build road %d %d success!\n",i,j);
            }
            return 1;
          }else{
            if(!is_ai){
              printf("No road or village connected!\n");
            }
            return -1;
          }
        }
      }
    }
  }
  if(!is_ai){
    printf("This road can't be build!\n");
  }
  return -1;
}

int32_t harvest(int32_t dice_number,int32_t *harvest_resource_2x5){
  int32_t temp=0;
  for(int8_t i=3;i<20;i=i+2){
    for(int8_t j=2;j<12;j=j+2){
      if(map[i][j][0]==3 && map[i][j][3]==dice_number){
        *(harvest_resource_2x5 + temp*5) = map[i][j][2];
        if(map[i-2][j-1][1] != 0  && map[i][j][4] != 1){//0
          *(harvest_resource_2x5 + temp*5 + map[i-2][j-1][1]) += map[i-2][j-1][3];
        }
        if(map[i-2][j+1][1] != 0  && map[i][j][4] != 1){//1
          *(harvest_resource_2x5 + temp*5 + map[i-2][j+1][1]) += map[i-2][j+1][3];
        }
        if(map[i][j-1][1] != 0  && map[i][j][4] != 1){//2
          *(harvest_resource_2x5 + temp*5 + map[i][j-1][1]) += map[i][j-1][3];
        }
        if(map[i][j+1][1] != 0  && map[i][j][4] != 1){//3
          *(harvest_resource_2x5 + temp*5 + map[i][j+1][1]) += map[i][j+1][3];
        }
        if(map[i+2][j-1][1] != 0  && map[i][j][4] != 1){//4
          *(harvest_resource_2x5 + temp*5 + map[i+2][j-1][1]) += map[i+2][j-1][3];
        }
        if(map[i+2][j+1][1] != 0  && map[i][j][4] != 1){//5
          *(harvest_resource_2x5 + temp*5 + map[i+2][j+1][1]) += map[i+2][j+1][3];
        }
        temp++;
        if(dice_number == 2 || dice_number == 12){
          *(harvest_resource_2x5 + temp*5) = -1;
          for(int32_t k=1;k<5;k++){
            *(harvest_resource_2x5 + temp*5+k) = -1;
          }
          return 0;
        }
      }
    }
  }
  return 0;
}

// 深度優先搜索函式
void DFS(int vertex, int length) {
    visited[vertex] = 1; // 設定頂點為已訪問

    // 檢查與該頂點相鄰的其他頂點
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (graph[vertex][i] == 1 && visited[i] == 0) {
            DFS(i, length + 1); // 遞迴訪問相鄰頂點
        }
    }

    // 更新最長道路的長度
    if (length > max_length) {
        max_length = length;
    }

    visited[vertex] = 0; // 重置頂點為未訪問
}

// 偵測最長道路
int detectLongestPath(int vertices) {
    max_length = 0;

    // 對每個頂點進行深度優先搜索
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < vertices; j++) {
            visited[j] = 0; // 重置頂點的訪問狀態
        }
        DFS(i, 1);
    }

    return max_length;
}

int32_t Longest_Path(int32_t player_ID){
  int32_t edges=0;
  int32_t vertices=0;
  int32_t edgesArr[72][2];
  for(int8_t i=0;i<72;i++){
    edgesArr[i][0]=0;
    edgesArr[i][1]=0;
  }
  for(int8_t i=0;i<72;i++){
    vertices_array[i]=0;
  }
  for (int i = 0; i < vertices; i++) {
      for (int j = 0; j < vertices; j++) {
          graph[i][j] = 0;
      }
  }
  for(int8_t i=0;i<23;i++){
    for(int8_t j=0;j<13;j++){
      if(map[i][j][0]==2 && map[i][j][1]==player_ID){
        if(map[i][j][3]==0){
          edgesArr[edges][0] = map[i][j-1][2];
          edgesArr[edges][1] = map[i][j+1][2];
          if(vertices_array[map[i][j-1][2]]==0){
            vertices_array[map[i][j-1][2]]=1;
            vertices++;
          }
          if(vertices_array[map[i][j+1][2]]==0){
            vertices_array[map[i][j+1][2]]=1;
            vertices++;
          }
        }else{
          edgesArr[edges][0] = map[i-1][j][2];
          edgesArr[edges][1] = map[i+1][j][2];
          if(vertices_array[map[i-1][j][2]]==0){
            vertices_array[map[i-1][j][2]]=1;
            vertices++;
          }
          if(vertices_array[map[i+1][j][2]]==0){
            vertices_array[map[i+1][j][2]]=1;
            vertices++;
          }
        }
        edges++;
      }
    }
  }
  for (int i = 0; i < edges; i++) {
      int src = edgesArr[i][0];
      int dest = edgesArr[i][1];
      graph[src][dest] = 1;
      graph[dest][src] = 1; // 無向圖，需設定雙向
  }
  for(int8_t i=0;i<12;i++){//D3rr0r
    printf("%d %d\n",edgesArr[i][0],edgesArr[i][1]);
  }
  printf("%d %d\n",edges,vertices);
  int longestPath = detectLongestPath(vertices);
  printf("Lonest path: %d\n", longestPath);
}

int32_t find_port(int32_t player_ID,int32_t *port_array_1x6){
    for(int32_t i=0;i<6;i++){
      *(port_array_1x6 + i)=0;
    }
    for(int8_t i=1;i<23;i=i+2){
      for(int8_t j=1;j<13;j=j+2){
        if(map[i][j][0]==1 && map[i][j][1]==player_ID && map[i][j][4]!= -1){
          *(port_array_1x6 + map[i][j][4])=1;
        }
      }
    }
    return 0;
}