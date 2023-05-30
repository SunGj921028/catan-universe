#ifndef _COLOR_H
#define _COLOR_H

 //上色
#define RED "\e[0;32;31m" 
#define L_RED "\e[1;31m" 
#define GREEN "\e[0;32;32m" 
#define L_GREEN "\e[1;32m" 
#define BLUE "\e[0;32;34m" 
#define L_BLUE "\e[1;34m" 
#define DARY_GRAY "\e[1;30m" 
#define CYAN "\e[0;36m" 
#define L_CYAN "\e[1;36m" 
#define PURPLE "\e[0;35m" 
#define L_PURPLE "\e[1;35m" 
#define BROWN "\e[0;33m"
#define YELLOW "\e[1;33m"
#define L_GRAY "\e[0;37m"
#define WHITE"\e[1;37m"

//rgb
#define ASCII_ESC "\033"

#define CLR_BOLD ASCII_ESC"[1m"
#define CLR_FLASH ASCII_ESC"[5m"

#define CLR_RST ASCII_ESC"[0m"
#define CLR_RED ASCII_ESC"[31m"
#define CLR_GRN ASCII_ESC"[32m"
#define CLR_YLW ASCII_ESC"[33m"
#define CLR_BL ASCII_ESC"[34m"
#define CLR_MGT ASCII_ESC"[35m"
#define CLR_CYN ASCII_ESC"[36m"
#define CLR_WHT ASCII_ESC"[37m"
#define CLR_GRY ASCII_ESC"[90m"
#define CLR_LRED ASCII_ESC"[91m"
#define CLR_LGRN ASCII_ESC"[92m"
#define CLR_LYLW ASCII_ESC"[93m"
#define CLR_LBL ASCII_ESC"[94m"
#define CLR_LMGT ASCII_ESC"[95m"
#define CLR_LCYN ASCII_ESC"[96m"
#define CLR_LWHT ASCII_ESC"[97m"

#define CLR_24_FG(R,G,B) ASCII_ESC"[38;2;"#R ";"#G ";"#B "m"
#define CLR_24_BG(R,G,B) ASCII_ESC"[48;2;"#R ";"#G ";"#B "m"

#endif