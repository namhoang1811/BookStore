#pragma once // Chỉ thị tiền xử lý để tránh include nhiều lần
#include "Base.h"

struct Book : Base {
    string author;
    int year;
    double price;
    int count;

	void printData();
    static Book create();
};
