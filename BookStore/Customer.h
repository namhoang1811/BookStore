#pragma once
#include "Base.h"

struct Customer : Base {
    int points;
    string phone;
    string address;	

    static Customer create();
    static void edit(Customer& source);

    void printHeader() override {
        cout << left << setw(10) << "MA" << setw(30) << "TEN KH" << setw(20) << "DIEM TICH LUY" << setw(20) << "DIEN THOAI" << setw(40) << "DIA CHI" << endl;
    }
    void printData(bool isHeader = true) override {
        if (isHeader)
            printHeader();
        cout << left << setw(10) << id << setw(30) << name << setw(20) << points << setw(20) << phone << setw(40) << address << endl;
    }

    void serialize(ofstream& out) override {
        File::save(out, id, name, points, phone, address);
    }

    void deserialize(ifstream& in) override {
        File::load(in, id, name, points, phone, address);
    }
};
