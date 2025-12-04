#pragma once // Chỉ thị tiền xử lý để tránh include nhiều lần
#include "Base.h"
#include "FileHelper.h"

struct Book : Base {
    string author;
    int year;
    double price;
    int count;

	void printData();
    static Book create();
    static void edit(Book& source);

    // --- GHI FILE TỔNG QUAN ---
    void serialize(ofstream& out) {
        // Chỉ cần liệt kê các biến muốn lưu theo đúng thứ tự
        FileHelper::save(out, id, name, author, year, price, count);
    }

    // --- ĐỌC FILE TỔNG QUAN ---
    void deserialize(ifstream& in) {
        // Liệt kê y hệt như lúc ghi
        FileHelper::load(in, id, name, author, year, price, count);
    }
};
