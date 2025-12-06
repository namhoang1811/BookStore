#pragma once 
#include "Const.h"
#include <iostream>

using namespace std;

struct Print {
    static void title(string name);
	static void removeLine(int count);
    static void clearScreen();
	static void pressAnyKey();
};