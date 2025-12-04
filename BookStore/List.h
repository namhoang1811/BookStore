//#pragma once
#include <functional> // Để dùng lambda function
#include <conio.h>   // Để dùng _getch()
#include <iostream>
#include "Print.h"

using namespace std;

// 1. Cấu trúc Node cho liên kết kép
template <typename T>
struct Node {
    T data;
    Node* next; // Trỏ tới phần tử sau
    Node* prev; // Trỏ tới phần tử trước (MỚI)
    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

// 2. Cấu trúc Quản lý danh sách
template <typename T>
struct List {
    Node<T>* head; // Phần tử đầu
    Node<T>* tail; // Phần tử cuối (MỚI - giúp thêm vào cuối nhanh hơn)
    int size;
    List() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor: Giải phóng bộ nhớ
    ~List() {
        clear();
    }

    Node<T>* findAt(int position) {
        Node<T>* current = head;
        if (!current)
            return current;
        for (int i = 0; i < position; i++) {
            current = current->next;
            if (!current)
                break;
        }
        return current;
    }

    // Thêm vào cuối danh sách (Logic của Doubly Linked List)
    void addLast(T item) {
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

    // Hiển thị danh sách
    void display(int count = 10) {
        if (isEmpty())
            return;
        Node<T>* current = head;
        while (true) {
            for (int i = 0; i < count && current; i++) {
                if (current) {
                    current->data.printData(); // Giả sử T là struct có hàm printData
                    current = current->next;
                } else 
                    break;
            }
            if (current) {
				cout << "--- Nhan phim bat ky de xem tiep, ESC de thoat ---";
            } else {
				cout << "--- Da het danh sach, nhan PHIM bat ky de thoat ---";
            }
            char k = _getch();
            cout << (int)k;
            if (!current || (int)k == 27) // Rỗng
                break;
            Print::removeLine();
        }
    }

    // Xóa theo điều kiện (Logic xóa của Doubly Linked List phức tạp hơn xíu)
    void remove(function<bool(T)> predicate) {
        Node<T>* current = head;
        while (current) {
            Node<T>* nextNode = current->next; // Lưu lại node tiếp theo trước khi xử lý
            if (predicate(current->data)) {
                // Logic xóa node current
                // 1. Xử lý liên kết với node trước (prev)
                if (current->prev) {
                    current->prev->next = current->next;
                } else {
                    // Nếu không có prev, tức là đang xóa head
                    head = current->next;
                }
                // 2. Xử lý liên kết với node sau (next)
                if (current->next) {
                    current->next->prev = current->prev;
                } else {
                    // Nếu không có next, tức là đang xóa tail
                    tail = current->prev;
                }
                delete current;
                size--;
            }
            current = nextNode; // Nhảy sang node tiếp theo
        }
    }

    // Tìm kiếm (Giữ nguyên logic duyệt xuôi)
    void find(function<bool(T)> predicate) {
        bool found = false;
        Node<T>* current = head;
        while (current) {
            if (predicate(current->data)) {
                current->data.printData();
                found = true;
            }
            current = current->next;
        }
        if (!found) cout << "(Khong tim thay ket qua)" << endl;
    }

    // Sắp xếp (Interchange Sort - Đổi chỗ data, không đổi pointer nên code như cũ)
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

    // Tính tổng
    double sum(function<double(T)> selector) {
        double total = 0;
        Node<T>* current = head;
        while (current) {
            total += selector(current->data);
            current = current->next;
        }
        return total;
    }

    // Đếm
    int countIf(function<bool(T)> predicate) {
        int count = 0;
        Node<T>* current = head;
        while (current) {
            if (predicate(current->data)) count++;
            current = current->next;
        }
        return count;
    }

    // Tìm tốt nhất (Max/Min)
    T* findBest(function<bool(T, T)> isBetter) {
        if (!head) return nullptr;
        Node<T>* best = head;
        Node<T>* current = head->next;
        while (current) {
            if (isBetter(current->data, best->data)) {
                best = current;
            }
            current = current->next;
        }
        return &(best->data);
    }

    bool remove(Node<T>* node) {
        if (node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            size--;
            return true;
        }
        return false;
    }

    bool isEmpty() {
        if (!head) {
            cout << "Danh sach trong!" << endl;
            return true;
        }
        return false;
    }

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