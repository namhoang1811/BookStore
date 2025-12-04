#include "Base.h"
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

// --- TRIỂN KHAI CHO BOOK ---

void Book::serialize(ofstream& out) {
    // 1. Ghi các chuỗi (Dùng hàm hỗ trợ)
    writeString(out, id);     // id thừa hưởng từ Base hoặc khai báo trong Book
    writeString(out, name);
    writeString(out, author);

    // 2. Ghi các số (Ghi trực tiếp được)
    out.write((char*)&year, sizeof(int));
    out.write((char*)&price, sizeof(double));
    out.write((char*)&count, sizeof(int));
}

void Book::deserialize(ifstream& in) {
    // 1. Đọc chuỗi (Phải đúng thứ tự như lúc ghi)
    readString(in, id);
    readString(in, name);
    readString(in, author);

    // 2. Đọc số
    in.read((char*)&year, sizeof(int));
    in.read((char*)&price, sizeof(double));
    in.read((char*)&count, sizeof(int));
}