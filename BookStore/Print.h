#pragma once 
#include <iostream>

using namespace std;

struct Print {
    static void title(string name);
    static void invalid();
	static void removeLine();
    static void clearScreen();
};