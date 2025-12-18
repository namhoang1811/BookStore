#pragma once // Chỉ thị tiền xử lý để tránh include nhiều lần
#include "Base.h"

struct Book : Base {
    string author;
    int year = 0;
    double price = 0;
    int quantity = 0;

    Book() {}
    Book(string id, string name, string author, int year, int quantity, double price) {
        this->id = id;
        this->name = name;
        this->author = author;
        this->year = year;
        this->quantity = quantity;
        this->price = price;
    }

    static void create(List<Book>& sources);
    static void edit(Book& book, List<Book>& sources);
    static void remove(Book& book, List<Book>& sources);

    void printHeader() override {
        cout << left << setw(10) << "MA" << setw(30) << "TEN SACH" << setw(30) << "TAC GIA" << setw(10) << "NAM" << setw(15) << "GIA" << setw(15) << "SO LUONG" << endl;
    }
    void printData(bool isHeader = true) override {
        if(isHeader)
			printHeader();
        cout << left << setw(10) << id << setw(30) << name << setw(30) << author << setw(10) << year << setw(15) << price << setw(15) << quantity << endl;
    }

    // --- GHI FILE ---
    void serialize(ofstream& out) override {
        // Liệt kê các biến muốn lưu theo đúng thứ tự
        File::save(out, id, name, author, year, price, quantity);
    }

    // --- ĐỌC FILE ---
    void deserialize(ifstream& in) override {
        // Liệt kê y hệt như lúc ghi
        File::load(in, id, name, author, year, price, quantity);
    }
};
