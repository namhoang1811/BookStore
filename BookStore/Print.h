#pragma once 
#include "Input.h"
#include <iostream>

using namespace std;

struct Print {
	// Hiển thị tiêu đề chương trình có trang trí
    static void title(string name);
	// Xóa count dòng đã in
	static void removeLine(int count);
	// Xóa toàn bộ màn hình
    static void clearScreen();
	// Chờ nhấn phím bất kỳ
	static void pressAnyKey();

	// Các hàm in thông báo với màu sắc khác nhau
    static void primary(string message, int sleep = 2000);
    static void danger(string message, int sleep = 2000);
    static void warning(string message, int sleep = 2000);
    static void success(string message, int sleep = 2000);

	// In thông báo nhập liệu không hợp lệ
    static void invalid();
};