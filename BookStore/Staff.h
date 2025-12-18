#pragma once
#include "Base.h"

struct Staff : Base {
    string phone;
    string position;
    int salary = 0;

    Staff() {}
    Staff(string id, string name, string phone, string position, int salary) {
        this->id = id;
        this->name = name;
        this->phone = phone;
        this->position = position;
        this->salary = salary;
    }

    static void create(List<Staff>& sources);
    static void edit(Staff& staff, List<Staff>& sources);
    static void remove(Staff& staff, List<Staff>& sources);


    // Sắp xếp theo lương
    static bool sortBySalaryAsc(Staff a, Staff b);
    static bool sortBySalaryDesc(Staff a, Staff b);

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
