#include <windows.h> // Thư viện quan trọng để can thiệp bàn phím
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Input {
	// Nhập với tham chiếu
    static void in(string& value, string label, bool isRequired = false) {
		value = read(label, value, isRequired);
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
    }
};
