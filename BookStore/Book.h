#pragma once // Chỉ thị tiền xử lý để tránh include nhiều lần
#include "Base.h"

struct Book : Base {
    string author;
    int year;
    double price;
    int count;

    void printHeader() {
        cout << left << setw(10) << "MA" << setw(30) << "TEN SACH" << setw(30) << "TAC GIA" << setw(10) << "NAM" << setw(15) << "GIA" << setw(15) << "SO LUONG" << endl;
    }
    void printData(bool isHeader = true) {
        if(isHeader)
			printHeader();
        cout << left << setw(10) << id << setw(30) << name << setw(30) << author << setw(10) << year << setw(15) << price << setw(15) << count << endl;
    }
    static Book create();
    static void edit(Book& source);

    // --- GHI FILE TỔNG QUAN ---
    void serialize(ofstream& out) {
        // Chỉ cần liệt kê các biến muốn lưu theo đúng thứ tự
        File::save(out, id, name, author, year, price, count);
    }

    // --- ĐỌC FILE TỔNG QUAN ---
    void deserialize(ifstream& in) {
        // Liệt kê y hệt như lúc ghi
        File::load(in, id, name, author, year, price, count);
    }
};
