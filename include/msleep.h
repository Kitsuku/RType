//
// Created by 53983 on 12/19/2018.
//

#ifndef H_ED_PSLEEP
#define H_ED_PSLEEP

#if defined (WIN32) || defined (_WIN32)
#include <windows.h>

#define msleep(ms) Sleep(ms)

#elif defined (__linux) || defined (linux)

#include <unistd.h>

#define msleep(ms) usleep((ms) * 1000)

#endif

#endif