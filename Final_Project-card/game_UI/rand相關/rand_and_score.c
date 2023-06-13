void score_calculate(Player * ptr){
    ptr->final_score = ptr->city*2 + ptr->village*1 + ptr->special_road*2 +
    ptr->special_army*2 + ptr->develop_card_score*1;
}

int dice(){
    srand(time(NULL));
    return ((rand()%6+1)+(rand()%6+1));
}

/*0:沙漠 1:丘陵 2:山脈 3:草原 4:森林 5:麥田*/
int region[19]={0 ,1,1,1, 2,2,2, 3,3,3,3, 4,4,4,4, 5,5,5,5};
int temp_num[18]={5,2,6,3,8,10,9,12,11,4,8,10,9,4,5,6,3,11};
int real_num[19]={0};

//抄的
void region_random(int *arr){
    srand(time(NULL));
    for (int i=0; i<18; i++){
        int j=i+rand()/(RAND_MAX/(18-i)+1);
        int t=arr[j];
        arr[j]=arr[i];
        arr[i]=t;
    }
}

//標板塊數字
void rnum_initial(int *region,int *temp_num, int *real_num){
    for(int i=0;i<19;i++){
        real_num[i]=-1;
    }//初始化成-1

    for(int i=0;i<19;i++){
        if(region[i]==0){
            real_num[i]=0;
        }
    }//先標沙漠

    int j=0;
    for(int i=0;i<19;i++){
        if(real_num[i]==0){
            continue;
        }//遇到沙漠跳下一個
        else{
            real_num[i]=temp_num[j];
            j++;
        }//否則對應填入
    }

}