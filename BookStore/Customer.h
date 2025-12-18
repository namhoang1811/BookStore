#pragma once
#include "Base.h"

struct Customer : Base {
    int points = 0;
    string phone;
    string address;	

    Customer() {}
    Customer(string id, string name, int points, string phone, string address) {
        this->id = id;
        this->name = name;
        this->points = points;
        this->phone = phone;
        this->address = address;
    }

    static void create(List<Customer>& sources);
    static void edit(Customer& customer, List<Customer>& sources);
    static void remove(Customer& customer, List<Customer>& sources);

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
