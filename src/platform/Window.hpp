#pragma once

#ifdef _WIN32
    #include <windows.h>
    #include <stdio.h>
    #include <tchar.h>
#endif

#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <map>
#include <cmath>
#include <vector>

#define FRAME_RATE 30
#define FRAME_PERIOD 1000 / FRAME_RATE

const int SCREEN_WIDTH 	= 624;
const int SCREEN_HEIGHT = 624;
