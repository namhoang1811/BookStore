#pragma once
#include "Base.h"

struct Staff : Base {
    string phone;
    string position;
    string salary;

    static Staff create();
    static void edit(Staff& source);

    void printHeader() override {
        cout << left << setw(10) << "MA" << setw(30) << "TEN NV" << setw(20) << "DIEN THOAI" << setw(20) << "CHUC VU" << setw(15) << "LUONG" << endl;
    }
    void printData(bool isHeader = true) override {
        if (isHeader)
            printHeader();
        cout << left << setw(10) << id << setw(30) << name << setw(20) << phone << setw(20) << position << setw(15) << salary << endl;
    }

    void serialize(ofstream& out) override {
        File::save(out, id, name, phone, position, salary);
    }

    void deserialize(ifstream& in) override {
        File::load(in, id, name, phone, position, salary);
    }
};
