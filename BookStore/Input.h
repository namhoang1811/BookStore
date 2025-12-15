#pragma once
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <conio.h>
#include <vector>
#endif
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

    // Hàm thay thế _getch() chạy mọi nơi
    static char getch() {
#if defined(_WIN32) || defined(_WIN64)
        // Trên Windows: Gọi hàm có sẵn
        return _getch();
#else
        // Trên Linux/MacOS: Phải cấu hình thủ công Terminal
        struct termios oldattr, newattr;
        int ch;
        // 1. Lấy thuộc tính hiện tại của terminal
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        // 2. Tắt chế độ ICANON (để đọc từng phím thay vì chờ Enter) và tắt ECHO (để không in ký tự ra màn hình)
        newattr.c_lflag &= ~(ICANON | ECHO);
        // 3. Áp dụng thuộc tính mới ngay lập tức
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        // 4. Đọc ký tự
        ch = getchar();
        // 5. Trả lại thuộc tính cũ cho terminal (Rất quan trọng!)
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        return ch;
#endif
    }

	// Gõ tự động
    static void autoTyping(string source) {
        if (source.empty()) return;
#if defined(_WIN32) || defined(_WIN64)
        // vector
        vector<INPUT_RECORD> events(source.length());
        for (size_t i = 0; i < source.length(); ++i) {
            events[i].EventType = KEY_EVENT;
            events[i].Event.KeyEvent.bKeyDown = TRUE;
            events[i].Event.KeyEvent.dwControlKeyState = 0;
            events[i].Event.KeyEvent.wVirtualKeyCode = 0;
            events[i].Event.KeyEvent.wRepeatCount = 1;
            events[i].Event.KeyEvent.uChar.AsciiChar = source[i];
        }
        DWORD written;
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        // Ép kiểu (DWORD) để sửa cảnh báo warning C4267
        WriteConsoleInput(hInput, &events[0], (DWORD)events.size(), &written);
#else
        // In sẵn giá trị gợi ý để người dùng chỉnh sửa nếu cần
        cout << "(" << source << ") ";
#endif        
    }
};
