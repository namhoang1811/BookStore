#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Input {
	// Nhập với tham chiếu
    static void in(string& value, string label, bool isRequired = false) {
		value = read(label, value, isRequired);
    }
	// Nhập số nguyên với validate
    static void in(int& value, string label, bool isRequired = false) {
        string temp;
        bool valid = false;
        do {
            temp = read(label, value > 0 ? to_string(value) : "", isRequired);
            if (temp.empty() && !isRequired) {
                return;
            }
            try {
                int num = stoi(temp);
                if (num >= 0) {
                    value = num;
                    valid = true;
                } else {
                    cout << "Vui long nhap so nguyen khong am!" << endl;
                }
            } catch (...) {
                cout << "Vui long nhap so nguyen hop le!" << endl;
            }
        } while (!valid);
    }
	// Nhập với trả về
    static string read(string label, bool isRequired = false) {
		return read(label, "", isRequired);
    }
	// Nhập với giá trị gợi ý và trả về
    static string read(string label, string value, bool isRequired = false) {
        string temp;
        bool firstLoop = true;
        do {
            if (!firstLoop)
                cout << "\033[2K\r\033[1A\033[2K\r"; // Xóa 2 dòng
            cout << label;
            autoTyping(value);
            firstLoop = false;
            getline(cin, temp);
        } while (isRequired && temp.empty());
        return temp;
    }
	// Gõ tự động
    static void autoTyping(string source) {
        if (source.empty()) return;
        // In sẵn giá trị gợi ý để người dùng chỉnh sửa nếu cần
        cout << source;
    }
};
