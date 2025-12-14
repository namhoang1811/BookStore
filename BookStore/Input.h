#include <iostream>
#include <string>

using namespace std;

struct Input {
	// Nhập với tham chiếu
    static void in(string& value, string label, bool isRequired = false) {
		value = read(label, value, isRequired);
    }
	// Nhập với trả về
    static string read(string label, bool isRequired = false) {
		return read(label, "", isRequired);
    }
	// Nhập với giá trị gợi ý và trả về
    static string read(string label, string value, bool isRequired = false) {
        string temp;
        bool firstLoop = true;
        do {
            if (!firstLoop)
                cout << "\033[2K\r\033[1A\033[2K\r"; // Xóa 2 dòng
            cout << label;
            autoTyping(value);
            firstLoop = false;
            getline(cin, temp);
        } while (isRequired && temp.empty());
        return temp;
    }
	// Gõ tự động
    static void autoTyping(string source) {
        if (source.empty()) return;
        // In sẵn giá trị gợi ý để người dùng chỉnh sửa nếu cần
        cout << source;
    }
};
