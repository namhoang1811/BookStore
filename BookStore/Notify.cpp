#include <windows.h>
#include "Notify.h"

// Định nghĩa mã màu
#define RED     "\033[31m"  // Màu đỏ (Lỗi)
#define GREEN   "\033[32m"  // Màu xanh lá (Thành công)
#define YELLOW  "\033[33m"  // Màu vàng (Cảnh báo)
#define BLUE    "\033[34m"  // Màu xanh dương (Tiêu đề)
#define CYAN    "\033[36m"  // Màu xanh lơ
#define RESET   "\033[0m"   // Trả về màu trắng mặc định

void Notify::primary(string message, int sleep) {
	cout << BLUE << message << RESET << endl;
	Sleep(sleep);
}

void Notify::danger(string message, int sleep) {
	cout << RED << message << RESET << endl;
	Sleep(sleep);
}

void Notify::warning(string message, int sleep) {
	cout << YELLOW << message << RESET << endl;
	Sleep(sleep);
}

void Notify::success(string message, int sleep) {
	cout << GREEN << message << RESET << endl;
	Sleep(sleep);
}
