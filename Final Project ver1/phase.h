#pragma once
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//play dice
//take resource and see the pirate's move
void throw_dice(sPlayer * player);
//dice random
int32_t dice();
//search and judge to take the resource
void take_resource(sPlayer * player, int32_t dice);
