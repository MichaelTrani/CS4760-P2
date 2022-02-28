/*  Author: Michael Trani
    February 2022       */
#ifndef P2_H
#define P2_H
#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<algorithm>
#include<ctime>
#include <time.h>
#include <errno.h>
#include <stdint.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>




char* timeFunction();
std::string whitespaceRemover(std::string);

#define SHMKEY	859047
#define STR_SZ	sizeof ( std::string )
#define INT_SZ	sizeof ( int )
#define PERM (S_IRUSR | S_IWUSR)

//rebuild
key_t shmkey;


char* timeFunction() { // Grabs current time and outputs hour/min/sec
    time_t current_sec = time(0);
    int length = 9;
    std::string formatted_time = "%H:%M:%S";

    struct tm* local = localtime(&current_sec);

    char* output = new char[length];
    strftime(output, length, formatted_time.c_str(), local);
    return output;
}


std::string whitespaceRemover(std::string modifyME){ // This removes an annoying whitespace fed into the program.
    remove(modifyME.begin(), modifyME.end(), ' ');  

    return modifyME;
}






#endif

/*
    std::time_t now = time(0); // get time
    char* stringnow = ctime(&now);
    std::cout << "time caught: " << stringnow << std::endl; // outputs full date
    std::cout << timeFunction() << std::endl;

*/