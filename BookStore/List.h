#pragma once
#include <functional> // Để dùng lambda function
#include <iostream>
#include <cstdio>

using namespace std;

// 1. Cấu trúc Node cho liên kết đôi
template <typename T>
struct Node {
    T data;
    Node* next; // Trỏ tới phần tử sau
    Node* prev; // Trỏ tới phần tử trước
    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

// 2. Cấu trúc Quản lý danh sách
template <typename T>
struct List {
    Node<T>* head; // Phần tử đầu
    Node<T>* tail; // Phần tử cuối
    int size;
    List() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor: Giải phóng bộ nhớ
    ~List() {
        clear();
    }

	// Hiển thị và chờ phím
    char displayPress(Node<T>* node) {
        if (node) {
            cout << endl << "Nhan phim bat ky de xem tiep, ESC de thoat...";
        } else {
            cout << endl << "Nhan PHIM bat ky de thoat...";
        }
        int ch = Input::getch();
    }
    // Hiển thị danh sách
    void display(int count = 5) {
        if (!any()) {
            cout << "Danh sach trong!" << endl;
            displayPress(nullptr);
            return;
        }
        Node<T>* current = head;
        current->data.printHeader();
        while (true) {
            for (int i = 0; i < count && current; i++) {
                if (current) {
                    current->data.printData(false); // T là struct có hàm printData
                    current = current->next;
                } else
                    break;
            }			
            char k = displayPress(current);
            if (!current || (int)k == 27) // Rỗng hoặc ấn ESC
                break;
            cout << "\033[2K\r\033[1A\033[2K\r"; // Xóa 2 dòng
        }
    }

	// Hiển thị theo điều kiện
    void display(function<bool(T)> predicate, int count = 5) {
        if (!any()) {
            cout << "Danh sach trong!" << endl;
			displayPress(nullptr);
            return;
        }
        Node<T>* current = head;
        current->data.printHeader();
        while (true) {
            for (int i = 0; i < count && current; i++) {
                while (current) {
					bool isFound = predicate(current->data);
                    if (isFound) {
                        current->data.printData(false); // T là struct có hàm printData
                    }
                    current = current->next;
                    if (isFound)
                        break;
                }
            }            
            char k = displayPress(current);
            if (!current || (int)k == 27) // Rỗng
                break;
            cout << "\033[2K\r\033[1A\033[2K\r"; // Xóa 2 dòng
        }
    }

	// Tìm kiếm phần tử đầu tiên thỏa mãn điều kiện
    T* find(function<bool(T)> predicate) {
        Node<T>* current = head;
        while (current) {
            if (predicate(current->data)) 
				return &(current->data);
            current = current->next;
        }
        return nullptr;
    }

	// Tìm kiếm phần tử tại vị trí
    T* findAt(int position) {
        if(position < 1)
			return nullptr;
        position--;
        Node<T>* current = head;
        if (!current)
            return nullptr;
        for (int i = 0; i < position; i++) {
            current = current->next;
            if (!current)
                return nullptr;
        }
        return &(current->data);
    }

    // Tìm theo điều kiện (Max/Min)
    T* find(function<bool(T, T)> condition) {
        if (!head) return nullptr;
        Node<T>* best = head;
        Node<T>* current = head->next;
        while (current) {
            if (condition(current->data, best->data)) {
                best = current;
            }
            current = current->next;
        }
        return &(best->data);
    }

	// Kiểm tra tồn tại
    bool any() {
        return head != nullptr;
    }

	// Kiểm tra tồn tại theo điều kiện
    bool any(function<bool(T)> predicate) {
        bool found = false;
        Node<T>* current = head;
        while (current) {
            if (predicate(current->data)) 
                return true;
            current = current->next;
        }
        return false;
    }

    // Thêm vào cuối danh sách
    void add(T item) {
        Node<T>* newNode = new Node<T>(item);
        if (!head) {
            // Danh sách rỗng: đầu và đuôi đều là node mới
            head = tail = newNode;
        } else {
            // Gắn vào sau đuôi cũ
            tail->next = newNode;
            newNode->prev = tail; // Node mới trỏ ngược lại đuôi cũ
            tail = newNode;       // Cập nhật đuôi mới
        }
        size++;
    }

    // Sắp xếp (Interchange Sort - Đổi chỗ data)
    void sort(function<bool(T, T)> compare) {
        if (!head || !head->next) return;
        for (Node<T>* i = head; i != nullptr; i = i->next) {
            for (Node<T>* j = i->next; j != nullptr; j = j->next) {
                if (compare(i->data, j->data)) {
                    swap(i->data, j->data);
                }
            }
        }
    }

	// Tính tổng theo điều kiện
    template <typename R>
    R sum(function<R(T)> selector) {
        R total = 0;
        Node<T>* current = head;
        while (current) {
            total += selector(current->data);
            current = current->next;
        }
        return total;
    }

	// Đếm theo điều kiện
    int count(function<bool(T)> predicate) {
        int count = 0;
        Node<T>* current = head;
        while (current) {
            if (predicate(current->data)) count++;
            current = current->next;
        }
        return count;
    }

    // Xóa theo điều kiện 
    bool remove(function<bool(T)> predicate) {
		bool isRemoved = false;
        Node<T>* current = head;
        while (current) {
            Node<T>* nextNode = current->next; // Lưu lại node tiếp theo trước khi xử lý
            if (predicate(current->data)) {
                // Logic xóa node current
                isRemoved = remove(current);
            }
            current = nextNode; // Nhảy sang node tiếp theo
        }
        return isRemoved;
    }

	// Xóa node cụ thể
    bool remove(Node<T>* node) {
        if (node) {
            // 1. Xử lý liên kết với node trước (prev)
            if (node->prev) {
                node->prev->next = node->next;
            } else {
                // Nếu không có prev, tức là đang xóa head
                head = node->next;
            }
            // 2. Xử lý liên kết với node sau (next)
            if (node->next) {
                node->next->prev = node->prev;
            } else {
                // Nếu không có next, tức là đang xóa tail
                tail = node->prev;
            }
            delete node;
            size--;
            return true;
        }
        return false;
    }

    // --- LƯU FILE NHỊ PHÂN ---
    void saveFile() {
        string fileName = getName() + ".bin";
        ofstream out(fileName, ios::binary);
        if (!out) 
            return;
        // 1. Ghi số lượng phần tử đầu tiên
        out.write((char*)&size, sizeof(int));
        // 2. Duyệt và ghi từng phần tử
        Node<T>* current = head;
        while (current) {
            // Gọi hàm serialize của đối tượng T để nó tự ghi
            current->data.serialize(out);
            current = current->next;
        }
        out.close();
    }

    // --- ĐỌC FILE NHỊ PHÂN ---
    void loadFile() {
        ifstream in(getName() + ".bin", ios::binary);
        if (!in) 
            return;
        // Xóa sạch danh sách cũ trước khi load
        clear();
        // 1. Đọc số lượng phần tử
        int count = 0;
        in.read((char*)&count, sizeof(int));
        // 2. Vòng lặp đọc từng phần tử
        for (int i = 0; i < count; ++i) {
            T item; // Tạo đối tượng tạm
            item.deserialize(in); // Bảo nó tự đọc dữ liệu từ file
            add(item); // Thêm vào list
        }
        in.close();
    }

	// Lấy tên kiểu T dưới dạng chuỗi
    string getName() {
        string name = typeid(T).name();
        // Tìm vị trí khoảng trắng cuối cùng (để bỏ qua chữ struct)
        // Trong Visual Studio, nó thường là "struct TenClass"
        size_t lastSpace = name.find_last_of(' ');
        if (lastSpace != string::npos) {
            // Cắt từ sau khoảng trắng đến hết
            return name.substr(lastSpace + 1);
        }
        return name; // Nếu không có khoảng trắng thì trả về nguyên gốc
    }

	// Xóa toàn bộ danh sách
    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
        size = 0;
    }
};