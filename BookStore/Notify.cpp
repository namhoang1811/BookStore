#include <windows.h>
#include "Notify.h"

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

void Notify::invalid() {
	warning(FIELD_INVALID, 1000);
	Print::removeLine(3);
}