#include "Base.h"
#include "Book.h"
#include <fstream>

// --- HÀM HỖ TRỢ GHI CHUỖI ---
// (Bạn có thể để hàm này là static hoặc helper function bên ngoài)
void writeString(ofstream& out, string& s) {
    int len = s.length();
    out.write((char*)&len, sizeof(int));      // Ghi độ dài chuỗi
    out.write(s.c_str(), len);                // Ghi nội dung chuỗi
}

// --- HÀM HỖ TRỢ ĐỌC CHUỖI ---
void readString(ifstream& in, string& s) {
    int len;
    in.read((char*)&len, sizeof(int));        // Đọc độ dài
    if (len > 0) {
        char* buf = new char[len + 1];        // Tạo bộ đệm
        in.read(buf, len);                    // Đọc nội dung
        buf[len] = '\0';                      // Ký tự kết thúc
        s = buf;                              // Gán vào string
        delete[] buf;                         // Xóa bộ đệm
    }
    else {
        s = "";
    }
}
