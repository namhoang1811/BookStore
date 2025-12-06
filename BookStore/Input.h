#include <windows.h> // Thư viện quan trọng để can thiệp bàn phím
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Input {
    static string read() {
        string temp;
        getline(cin, temp);
        return temp;
    }

    static void autoType(string source) {
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
        // Ép kiểu (DWORD) để sửa cảnh báo warning C4267 luôn
        WriteConsoleInput(hInput, &events[0], (DWORD)events.size(), &written);
    }
};
