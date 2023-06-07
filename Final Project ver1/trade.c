void trade(sPlayer *p){
	char action[2]={0};
	char want[2]={0};
	char spend[2]={0};
	uint8_t *temp[5]={&(p->rock),&(p->wood),&(p->wheat),&(p->brick),&(p->sheep)};
	int iwant=0,ispend=0;
	printf("0:back 1:trade with bank 2:trade with player 3:trade with harbor\n:");
	fgets(action,2,stdin);
	switch(action[0]){
		case '0':
			return;
			break;
		
		case '1':
			printf("Which resource you want to trade?\n0:rock 1:wood 2:wheat 3:brick 4:sheep\n:");
			fgets(want,2,stdin);
			printf("Spend 4 same resource to trade 1\nYou want to spend 0:rock 1:wood 2:wheat 3:brick 4:sheep\n:");
			fgets(spend,2,stdin);
			iwant=want[0]-'0';
			ispend=spend[0]-'0';
			if(*(temp[ispend])<4){
				printf("You don't have enough resource\n");
				return;
			}
			else{
				*(temp[iwant])+=1;
				*(temp[ispend])-=4;
				p->hand-=3;
			}
			break;
		case '2':
			//trade_player();
			break;
		case '3':
			int number=0,resource=0;
			//number=get_harbor_number(); 數字比例 2:1 or 3:1
			//resource=get_harbor_resource(); 資源種類
			printf("Which harbor you want to trade:");
			//judge_harbor() blah blah
			if(number==2){
				printf("Spend 2 same resource to trade 1\nYou want to spend 0:rock 1:wood 2:wheat 3:brick 4:sheep\n:");
				fgets(spend,2,stdin);
				ispend=spend[0]-'0';
				*(temp[ispend])-=2;
				*(temp[resource])+=1;
				p->hand-=1;
			}
			else if(number==3){
				printf("Spend 3 same resource to trade 1\nYou want to spend 0:rock 1:wood 2:wheat 3:brick 4:sheep\n:");
				fgets(spend,2,stdin);
				printf("You wnat to trade: 0:rock 1:wood 2:wheat 3:brick 4:sheep\n:");
				fgets(want,2,stdin);
				ispend=spend[0]-'0';
				iwant=want[0]-'0';
				*(temp[ispend])-=3;
				*(temp[iwant])+=1;
				p->hand-=2;
			}
			break;
	}
}
