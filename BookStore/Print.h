#pragma once 
#include "Const.h"
#include <iostream>

using namespace std;

struct Print {
    static void title(string name);
	static void removeLine(int count);
    static void clearScreen();
	static void pressAnyKey();

    static void primary(string message, int sleep = 2000);
    static void danger(string message, int sleep = 2000);
    static void warning(string message, int sleep = 2000);
    static void success(string message, int sleep = 2000);
    static void invalid();
};