#include "BookMenu.h"

namespace {
    Book* findAt(List<Book>& books) {
        while (true) {
            try {
                int position = stoi(Input::read("Nhap thu tu Sach: ", true));
                Book* result = books.findAt(position);
                if (!result)
                    Print::warning(NOT_FOUND);
                return result;
            } catch (...) {
				Print::removeLine(2);
            }
        }
    }
    Book* findById(List<Book>& books) {        
        string id = Input::read("Nhap ma Sach: ", true);
        Book* result = books.find([id](Book d) {
            return d.id == id;
            });
        if (!result)
            Print::warning(NOT_FOUND);
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
            books.display();
            break;
        case 2: {
            Print::title("TAO MOT SACH MOI");
            auto model = Book::create();
            bool isAny = books.any([model](Book d) {
                return d.id == model.id;
                });
            if (!isAny) {
                books.add(model);
				books.saveFile();
                Print::success(ACTIVE_SUCCESS);
            } else {
                Print::danger("Them sach moi that bai do trung Ma");
            }
            break;
        }
        case 3: {
            Print::title("TIM SACH THEO THU TU");
            Book* data = findAt(books);
            if (data) {
                data->printData();
                Print::pressAnyKey();
            }            
            break;
        }
        case 4: {
            Print::title("TIM KIEM SACH THEO TEN");
			string keyword;		
			keyword = Input::read("Nhap ten sach can tim: ", true);
            books.display([keyword](Book d) {
                return d.id.find(keyword) != string::npos;
                });
            break;
        }
        case 5: {
            Print::title("TIM SACH CO GIA TRI LON NHAT");
            Book* data = books.find([](Book a, Book b) {
                return a.price > b.price;
                });
            if (data) {
                data->printData();
                Print::pressAnyKey();
            }
            break;
		}
        case 6 : {
            Print::title("TIM SACH CO GIA TRI NHO NHAT");
            Book* data = books.find([](Book a, Book b) {
                return a.price < b.price;
                });
            if (data) {
                data->printData();
                Print::pressAnyKey();
            }
            break;
		}
        case 7: {
            Print::title("SAP XEP SACH THEO GIA TANG DAN");
            books.sort([](Book a, Book b) {
                return a.price > b.price;
                });
            Print::success(ACTIVE_SUCCESS, 1000);
            Print::removeLine(2);
            books.display();
            break;
        }
        case 8: {
            Print::title("SAP XEP SACH THEO GIA GIAM DAN");
            books.sort([](Book a, Book b) {
                return a.price < b.price;
                });
            Print::success(ACTIVE_SUCCESS, 1000);
            Print::removeLine(2);
            books.display();
            break;
        }
        case 9: {
            Print::title("THONG KE SACH CO SO LUONG > 10");
            books.display([](Book d) {
                return d.quantity > 10;
                });
            break;
		}
        case 17: case 49: { // A
            Print::title("THONG KE SACH DA HET HANG");
            books.display([](Book d) {
                return d.quantity == 0;
                });
            break;
		}
        case 18: case 50: { // B
            Print::title("TINH TONG SO LUONG SACH CON TON KHO");
            int total = books.sum<int>([](Book d) {
                return d.quantity;
                });
            cout << "Tong so luong sach con ton kho: " << total << endl;
            Print::pressAnyKey();
            break;
        }
        case 19: case 51: { // C
            Print::title("TINH TB GIA BAN CAC CUON SACH KHAC NHAU");
            double average = books.sum<double>([](Book d) {
                return d.price;
                }) / books.size;
            cout << "Trung binh gia ban cac cuon sach khac nhau: " << average << endl;
            Print::pressAnyKey();
            break;
		}
        case 20: case 52: {  // D
            Print::title("CHINH SUA SACH THEO THU TU");
            Book* data = findAt(books);
            if (data) {
                Print::title("CHINH SUA SACH: " + data->name);
                Book::edit(*data);
                books.saveFile();
                Print::success(ACTIVE_SUCCESS);
            }
            break;
        }
        case 21: case 53: {  // E
            Print::title("CHINH SUA SACH THEO MA");
            Book* data = findById(books);
            if (data) {
                Print::title("CHINH SUA SACH: " + data->name);
                Book::edit(*data);
                books.saveFile();
                Print::success(ACTIVE_SUCCESS);
            }
            break;
        }
        case 22: case 54: {  // F
            Print::title("XOA SACH THEO THU TU");
            Book* data = findAt(books);
            if (data) {
                bool isDeleted = books.remove([data](Book d) {
                    return d.id == data->id;
                    });
                if (isDeleted) {
                    books.saveFile();
                    Print::success(ACTIVE_SUCCESS);
                }
            }
            break;
		}
        case 23: case 55: {  // G
            Print::title("XOA SACH THEO MA");
            Book* data = findById(books);
            if (data) {
                bool isDeleted = books.remove([data](Book d) {
                    return d.id == data->id;
                    });
                if (isDeleted) {                    
                    books.saveFile();
                    Print::success(ACTIVE_SUCCESS);
                }
            }
            break;
        }
        case 0: case -21: // 0 or ESC
            return;
        }
    }
}