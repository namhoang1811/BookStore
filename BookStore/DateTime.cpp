#include "DateTime.h"
#include <ctime>   // Thư viện thời gian


int DateTime::nowYear() {
    time_t t = time(0);   // Lấy thời gian hiện tại
    struct tm now;
#if defined(_WIN32) || defined(_WIN64)
    // Sử dụng localtime_s (phiên bản an toàn của localtime trên Visual Studio)
    // Tham số 1: địa chỉ struct tm, Tham số 2: địa chỉ biến thời gian
    localtime_s(&now, &t);
    return now.tm_year + 1900;
#else
    // POSIX (Linux, MacOS, Unix)
    localtime_r(&t, &now);    
#endif     
    // tm_year tính từ năm 1900, nên phải cộng thêm 1900
    return now.tm_year + 1900;
}