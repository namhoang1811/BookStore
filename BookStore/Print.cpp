#include <windows.h>
#include <conio.h> // Add this include for _getch
#include "Print.h"
#include "Const.h"


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
    int length = name.length();
	int half = (120 - length - 2) / 2;
	equal(120, true);
    equal(half);
    cout << " " << name << " ";
    equal(half + length % 2, true);
    equal(120, true);
}

void Print::invalid() {
	cout << "Nhap khong hop le. Vui long nhap lai!" << endl;
}

void Print::removeLine(int count) {
    for (int i = 0; i < count; i++) {
        cout << "\033[2K\r"; // Xóa toàn bộ dòng đó
		if (i < count - 1)
            cout << "\033[1A"; // Di chuyển con trỏ LÊN 1 dòng
    }
}

void Print::clearScreen() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    // Lấy thông tin về kích thước màn hình hiện tại
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
        // Ghi khoảng trắng (space) lên toàn bộ màn hình
        FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        // Đặt lại thuộc tính văn bản (màu sắc)
        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        // Đưa con trỏ về vị trí (0, 0)
        SetConsoleCursorPosition(hStdOut, coord);
    }
}

void Print::pressAnyKey() {
    cout << endl << PRESS_ANY_KEY;
    char _ = _getch(); // Chờ bất một phím bất kỳ
}