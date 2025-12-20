#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

struct File {
    // --- PHẦN GHI (SAVE) ---
    // 1. Hàm ghi cho int, double, bool, char...
    template <typename T>
    static void writeOne(ofstream& out, const T& value) {
        out.write((char*)&value, sizeof(T));
    }

    // 2. Hàm ghi cho std::string
    static void writeOne(ofstream& out, const string& s) {
        int len = (int)s.length();
        out.write((char*)&len, sizeof(int));      // Ghi độ dài
        if (len > 0) {
            out.write(s.c_str(), len);            // Ghi nội dung
        }
    }

    // 3. Hàm ghi cho std::vector<T> 
    template <typename T>
    static void writeOne(ofstream& out, const vector<T>& vec) {
        int size = (int)vec.size();
        writeOne(out, size); // Ghi kích thước vector trước
        for (const auto& item : vec) {
            writeOne(out, item); // Ghi từng phần tử
        }
    }

    // 4. Hàm tổng quát - Ghi N tham số
    template <typename... Args>
    static void save(ofstream& out, const Args&... args) {
        (writeOne(out, args), ...);
    }

    // --- PHẦN ĐỌC (LOAD) ---
    // 1. Hàm đọc cho int, double, bool, char...
    template <typename T>
    static void readOne(ifstream& in, T& value) {
        in.read((char*)&value, sizeof(T));
    }

	// 2. Hàm đọc cho std::string
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

    // 3. Hàm đọc cho std::vector<T>
    template <typename T>
    static void readOne(ifstream& in, vector<T>& vec) {
        int size = 0;
        readOne(in, size); // Đọc kích thước
        vec.resize(size);  // Cấp phát bộ nhớ
        for (int i = 0; i < size; ++i) {
            readOne(in, vec[i]); // Đọc từng phần tử
        }
    }

    // 4. Hàm tổng quát - Đọc N tham số
    template <typename... Args>
    static void load(ifstream& in, Args&... args) {
        (readOne(in, args), ...);
    }

};