#include <chrono>
#include <thread>
#include "Print.h"

namespace {
    void equal(int count, bool isEnd = false) {
        for (int i = 0; i < count; i++) {
            cout << "=";
        }
        if (isEnd)
            cout << endl;
    }
}

void Print::title(string name) {
    Print::clearScreen();
    int length = static_cast<int>(name.length());
	int half = (120 - length - 2) / 2;
	equal(120, true);
    equal(half);
    cout << " " << name << " ";
    equal(half + length % 2, true);
    equal(120, true);
}

void Print::removeLine(int count) {
    for (int i = 0; i < count; i++) {
        cout << "\033[2K\r"; // Xóa toàn bộ dòng đó
		if (i < count - 1)
            cout << "\033[1A"; // Di chuyển con trỏ LÊN 1 dòng
    }
}

void Print::clearScreen() {
    // \033: Ký tự ESC (Escape).
    // [2J: Lệnh xóa toàn bộ màn hình.
    // [H: Lệnh đưa con trỏ về vị trí Home (0,0).
    cout << "\033[2J\033[H";
    cout.flush();
}

void Print::pressAnyKey() {
    cout << endl << PRESS_ANY_KEY;
    if (cin.peek() == '\n') {
        cin.get();
    }
    cin.get();
}

void Print::primary(string message, int sleep) {
    cout << BLUE << message << RESET << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
}

void Print::danger(string message, int sleep) {
    cout << RED << message << RESET << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
}

void Print::warning(string message, int sleep) {
    cout << YELLOW << message << RESET << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
}

void Print::success(string message, int sleep) {
    cout << GREEN << message << RESET << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
}

void Print::invalid() {
    warning(FIELD_INVALID, 1000);
    Print::removeLine(3);
}