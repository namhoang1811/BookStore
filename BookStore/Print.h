#pragma once 
#include <iostream>

using namespace std;

struct Print {
    static void title(string name);
    static void invalid();
	static void removeLine(int count);
    static void clearScreen();
	static void pressAnyKey();
};