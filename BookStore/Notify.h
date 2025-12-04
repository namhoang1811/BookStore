#pragma once 
#include <iostream>

using namespace std;

struct Notify {
    static void primary(string message, int sleep = 2000);
    static void danger(string message, int sleep = 2000);
    static void warning(string message, int sleep = 2000);
    static void success(string message, int sleep = 2000);
};