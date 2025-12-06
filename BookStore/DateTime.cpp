#include "DateTime.h"
#include <ctime>   // Thư viện thời gian


int DateTime::nowYear() {
    time_t t = time(0);   // Lấy thời gian hiện tại
    struct tm now;
    // Sử dụng localtime_s
    // Tham số 1: địa chỉ struct tm, Tham số 2: địa chỉ biến thời gian
    localtime_s(&now, &t);
    // tm_year tính từ năm 1900, nên phải cộng thêm 1900
    return now.tm_year + 1900;
}