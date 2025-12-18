#include "DateTime.h"
#include <ctime>   // Thư viện thời gian

namespace {
    tm getNow() {
        time_t t = time(0);   // Lấy thời gian hiện tại
        struct tm now;
#if defined(_WIN32) || defined(_WIN64)
        // Sử dụng localtime_s (phiên bản an toàn của localtime trên Visual Studio)
        // Tham số 1: địa chỉ struct tm, Tham số 2: địa chỉ biến thời gian
        localtime_s(&now, &t);
#else
        // POSIX (Linux, MacOS, Unix)
        localtime_r(&t, &now);
#endif 
        return now;
    }
}

int DateTime::nowYear() {
    tm now = getNow();
    // tm_year tính từ năm 1900, nên phải cộng thêm 1900
    return now.tm_year + 1900;
}

string DateTime::nowString() {
    tm now = getNow();
    char buffer[80];
    // Các ký hiệu format:
    // %d: Ngày (01-31)
    // %m: Tháng (01-12)
    // %Y: Năm (2025)
    // %H: Giờ (00-23)
    // %M: Phút
    // %S: Giây
    strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", &now);
    // 4. Chuyển char[] sang string và return
    return string(buffer);
}