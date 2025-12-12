#pragma once
#include "Input.h"
#include "Print.h"
#include "File.h"
#include <string>
#include <iostream> // Để sử dụng lệnh cout
#include <iomanip>  // Để sử dụng lệnh setw

using namespace std;

struct Base {
    string id;
    string name;

    // Đây là cách tạo abstract method trong C++ chuẩn
    virtual void printHeader() = 0;
    virtual void printData(bool isHeader = true) = 0;
    virtual void serialize(ofstream& out) = 0;
    virtual void deserialize(ifstream& in) = 0;
};
