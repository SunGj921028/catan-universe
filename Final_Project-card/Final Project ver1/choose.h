#pragma once
#define _GNU_SOURCE
#include <dirent.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#define CLEAR printf("\033[H\033[2J"); //clear terminal

int getch() {
    int ch;
    // struct to hold the terminal settings
    struct termios old_settings, new_settings;
    // take default setting in old_settings
    tcgetattr(STDIN_FILENO, &old_settings);
    // make of copy of it (Read my previous blog to know 
    // more about how to copy struct)
    new_settings = old_settings;
    // change the settings for by disabling ECHO mode
    // read man page of termios.h for more settings info
    new_settings.c_lflag &= ~(ICANON | ECHO);
    // apply these new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    // now take the input in this mode
    ch = getchar();
    // reset back to default settings
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    return ch;
}//just some copy and paste