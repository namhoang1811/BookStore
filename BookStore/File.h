#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>

using namespace std;

struct File {

    // --- PHẦN GHI (SAVE) ---
    // 1. Hàm ghi cơ bản cho các kiểu số (int, double, bool, char...)
    template <typename T>
    static void writeOne(ofstream& out, const T& value) {
        out.write((char*)&value, sizeof(T));
    }

    // 2. Hàm ghi đặc biệt dành riêng cho std::string
    static void writeOne(ofstream& out, const string& s) {
        int len = (int)s.length();
        out.write((char*)&len, sizeof(int));      // Ghi độ dài
        if (len > 0) {
            out.write(s.c_str(), len);            // Ghi nội dung
        }
    }

    // 3. Hàm tổng quát (Variadic Template) - Ghi N tham số
    // Cú pháp ...Args là của C++ hiện đại
    template <typename... Args>
    static void save(ofstream& out, const Args&... args) {
        // (Fold Expression - C++17): Gọi writeOne cho từng biến trong danh sách
        (writeOne(out, args), ...);
    }

    // --- PHẦN ĐỌC (LOAD) ---
    // 1. Hàm đọc cơ bản cho số
    template <typename T>
    static void readOne(ifstream& in, T& value) {
        in.read((char*)&value, sizeof(T));
    }

    // 2. Hàm đọc đặc biệt cho std::string
    static void readOne(ifstream& in, string& s) {
        int len = 0;
        in.read((char*)&len, sizeof(int));        // Đọc độ dài
        if (len > 0) {
            char* buf = new char[len + 1];        // Tạo bộ đệm
            in.read(buf, len);                    // Đọc nội dung
            buf[len] = '\0';                      // Kết thúc chuỗi
            s = buf;                              // Gán vào string
            delete[] buf;                         // Xóa bộ đệm
        }
        else {
            s = "";
        }
    }

    // 3. Hàm tổng quát - Đọc N tham số
    template <typename... Args>
    static void load(ifstream& in, Args&... args) {
        (readOne(in, args), ...);
    }

};