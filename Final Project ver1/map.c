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
#define CCLEAR printf("\e[0m")

int8_t map[23][13][5];
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
//harvest
//move rubbor
//build road
//build village
//upgrade city
//calc lonest road

int8_t map_pk[19]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int8_t ocean_f[34]={62,27,26,25,17,16,15,7,6,5,4,5,6,7,6,5,4,5,6,7,6,5,4,5,6,7,15,16,17,25,26,27,62};
int8_t map_pk_i=0;
bool is_slash;

void map_point_init(int8_t i,int8_t j,int8_t map_p_type){
  map[i][j][0] = map_p_type;
  if(map_p_type == 0){//ocean
    for(int8_t k=0;k<c_map_deep;k++){
      map[i][j][k]=0;
    }
  }else if(map_p_type == 1){//point
    for(int8_t k=1;k<c_map_deep;k++){
      map[i][j][k]=0;
    }
  }else if(map_p_type == 2){//line
    map[i][j][1]=0;//owner
    if(i%2==1){
      map[i][j][2]=0;//----
    }else{
      map[i][j][2] = is_slash ? 1 : 2;/* / or \ */
      is_slash = !is_slash;
    }
    map[i][j][3]=0;
    map[i][j][4]=0;
  }else if(map_p_type == 3){//block
    for(int8_t ni=i-1;ni<=i+1;ni++){
      map[ni][j][0]=3;
      map[ni][j][1]=map_pk_i;
      for(int8_t k=2;k<c_map_deep;k++){
        map[ni][j][k]=0;
      }
    }
    map_pk_i++;
  }else if(map_p_type == 4){//port

  }
  return;
}

void map_color_slt(int8_t a){
  switch(a){
    case 1:BK_RED;break;
    case 2:BK_GRN;break;
    case 3:BK_YEL;break;
    case 0:BK_BUL;break;
  }
}

void map_print_slt(int8_t i,int8_t j,int8_t ptime){
  int8_t a=map[i][j][0];
  int8_t ptype;
  map_color_slt(a);
  if(a==1){
    printf("*");
  }else if(a==2){
    ptype=map[i][j][2];
    if(ptype==0){
      printf("------");
    }else if(ptype==1){
      printf("/");
    }else if(ptype==2){
      printf("\\");
    }
  }else if(a==3){
    ptype=map_pk[map[i][j][1]];
    if(ptype==0){
      printf("        ");
    }else if(ptype==1){
      printf("          ");
    }else if(ptype==2){
      printf("            ");
    }else if(ptype==3){
      printf("          ");
    }else if(ptype==4){
      printf("        ");
    }
    map_pk[map[i][j][1]] = map_pk[map[i][j][1]]+1;
  }else if(a==0){
    if(j==0||j==12){
      for(int8_t k=0;k<ocean_f[ptime];k++){
        printf(" ");
      }
    }
  }
}

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

int32_t map_set_road(int32_t pID, int32_t x,int32_t y){

}

//harvest


//52 one line
int32_t map_print(){
  int8_t ptime=0;
  for(int8_t i=0;i<23;i++){
    if(i==0||i==22){
      map_print_slt(i,0,ptime);
    }
    if(i%2==0 && 0<i && i<22){
      for(int8_t j=0;j<26;j++){
        if(j==13){
          ptime++;CCLEAR;printf("\n");
        }
        map_print_slt(i,j%13,ptime);
      }
    }else if(i%2==1 && 0<i && i<22){
      for(int8_t j=0;j<13;j++){
        map_print_slt(i,j,ptime);
      }
    }
    ptime++;CCLEAR;printf("\n");
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
}