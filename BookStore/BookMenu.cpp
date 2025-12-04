#include "BookMenu.h"

namespace {
    Book* findAt(List<Book>& books) {
		int position;
        cout << "Nhap thu tu Sach: ";
        cin >> position;
        Book* result = books.findAt(position);
        if (!result) {
            Notify::warning(NOT_FOUND);
        }
        return result;
    }
    Book* findById(List<Book>& books) {
        string id;
        cout << "Nhap ma Sach: ";
		cin >> id;
        Book* result = books.find([id](Book d) {
            return d.id == id;
            });
        if (!result) {
            Notify::warning(NOT_FOUND);
        }
        return result;
    }
}

void BookMenu::show(List<Book>& books) {
    while (true) {
        Print::title("QUAN LY SACH");
        cout << "1. Xem danh sach" << endl;
        cout << "2. Them mot Sach moi" << endl;
        cout << "3. Tim Sach theo thu tu" << endl;
        cout << "4. Tim kiem Sach theo Ten" << endl;
        cout << "5. Tim Sach co gia tri lon nhat" << endl;
        cout << "6. Tim Sach co gia tri nho nhat" << endl;
        cout << "7. Sap xep Sach theo gia tang dan" << endl;
        cout << "8. Sap xep Sach theo gia giam dan" << endl;
        cout << "9. Thong ke Sach co so luong > 10" << endl;
        cout << "A. Thong ke Sach da het hang" << endl;
        cout << "B. Tinh tong so luong Sach con ton kho" << endl;
        cout << "C. Tinh TB gia ban cac cuon sach khac nhau" << endl;
        cout << "D. Chinh sua Sach theo thu tu" << endl;
        cout << "E. Chinh sua Sach theo Ma" << endl;
        cout << "F. Xoa Sach theo thu tu" << endl;
        cout << "G. Xoa Sach theo Ma" << endl;
        cout << "0. Tro ve" << endl;
        cout << endl << PRESS_OPTION;
        char k = _getch();
        switch ((int)k - 48) {
        case 1:
            Print::title("DANH SACH SACH");
            books.display(2);
            break;
        case 2: {
            Print::title("TAO MOT SACH MOI");
            auto model = Book::create();
            bool isAny = books.any([model](Book d) {
                return d.id == model.id;
                });
            if (!isAny) {
                books.addLast(model);
                Notify::success("Them sach moi thanh cong!");
            }
            else {
                Notify::danger("Them sach moi that bai! Trung Ma");
            }
            break;
        }
        case 3: {
            Print::title("TIM SACH THEO THU TU");
            Book* data = findAt(books);
            if (data) {
                data->printData();
                cout << endl << PRESS_EXIT;
                char _ = _getch(); // Chờ bất một phím bất kỳ
            }            
            break;
        }
        case 4: {
            Print::title("TIM KIEM SACH THEO TEN");
			string keyword;
			cout << "Nhap ten sach can tim: ";
			cin.ignore();
			getline(cin, keyword);
            books.display([keyword](Book d) {
                return d.id.find(keyword) != string::npos;
                });
            break;
        }
        case 5: {
            Print::title("CHINH SUA SACH THEO THU TU");
            auto data = findAt(books);
            if (data) {
                Print::title("CHINH SUA SACH: " + data->name);
                Book::edit(*data);
            }
            break;
        }
        case 0:
            return;
        }
    }
}