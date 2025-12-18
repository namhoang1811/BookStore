#include "InvoiceMenu.h"

namespace {
    Invoice* findAt(List<Invoice>& sources) {
        while (true) {
            try {
                int position = stoi(Input::read("Nhap thu tu Hoa don: ", true));
                Invoice* result = sources.findAt(position);
                if (!result)
                    Print::warning(NOT_FOUND);
                return result;
            }
            catch (...) {
                Print::removeLine(2);
            }
        }
    }
    Invoice* findById(List<Invoice>& sources) {
        string id = Input::read("Nhap ma Hoa don: ", true);
        Invoice* result = sources.find([id](Invoice d) {
            return d.id == id;
            });
        if (!result)
            Print::warning(NOT_FOUND);
        return result;
    }    
}

void InvoiceMenu::show(List<Invoice>& sources, List<Book>& books, List<Customer>& customers) {
    while (true) {
        Print::title("QUAN LY HOA DON");
        cout << "1. Xem danh Hoa don" << endl;
        cout << "2. Them mot Hoa don moi" << endl;
        cout << "3. Tim Hoa don theo thu tu" << endl;
        cout << "4. Tim kiem Hoa don theo Ten" << endl;
        cout << "5. Tim Hoa don co gia tri lon nhat" << endl;
        cout << "6. Tim Hoa don co gia tri nho nhat" << endl;
        cout << "7. Sap xep Hoa don theo gia tang dan" << endl;
        cout << "8. Sap xep Hoa don theo gia giam dan" << endl;
        cout << "9. Thong ke Hoa don co gia tri > 500.000" << endl;
        cout << "A. Thong ke Hoa don co gia tri < 500.000" << endl;
        cout << "B. Tinh tong gia tri cua tat ca Hoa don" << endl;
        cout << "C. Tinh TB gia tri cua tat ca Hoa don" << endl;
        cout << "D. Chinh sua Hoa don theo thu tu" << endl;
        cout << "E. Chinh sua Hoa don theo Ma" << endl;
        cout << "F. Xoa Hoa don theo thu tu" << endl;
        cout << "G. Xoa Hoa don theo Ma" << endl;
        cout << "0. Tro ve" << endl;
        cout << endl << PRESS_OPTION;
        char k = Input::getch();
        switch ((int)k - 48) {
        case 1:
            Print::title("DANH SACH HOA DON");
            sources.display();
            break;
        case 2: {
            Print::title("TAO MOT HOA DON MOI");
            Invoice::create(sources, books, customers);
            Print::success(ACTIVE_SUCCESS);
            break;
        }
        case 3: {
            Print::title("TIM SACH THEO THU TU");
            Invoice* data = findAt(sources);
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
            sources.display([keyword](Invoice d) {
                return d.id.find(keyword) != string::npos;
                });
            break;
        }
        case 5: {
            Print::title("TIM HOA DON CO GIA TRI LON NHAT");
            Invoice* data = sources.find([](Invoice a, Invoice b) {
                return a.total > b.total;
                });
            if (data) {
                sources.display([data](Invoice d) {
                    return d.total == data->total;
                    });
            } else {                
                Print::warning(NOT_FOUND);
            }
            break;
        }
        case 6: {
            Print::title("TIM HOA DON CO GIA TRI NHO NHAT");
            Invoice* data = sources.find([](Invoice a, Invoice b) {
                return a.total < b.total;
                });
            if (data) {
                sources.display([data](Invoice d) {
                    return d.total == data->total;
                    });
            } else {
				Print::warning(NOT_FOUND);
			}
            break;
        }
        case 7: {
            Print::title("SAP XEP HOA DON THEO GIA TANG DAN");
            sources.sort([](Invoice a, Invoice b) {
                return a.total > b.total;
                });
            Print::success(ACTIVE_SUCCESS, 1000);
            Print::removeLine(2);
            sources.display();
            break;
        }
        case 8: {
            Print::title("SAP XEP HOA DON THEO GIA GIAM DAN");
            sources.sort([](Invoice a, Invoice b) {
                return a.total < b.total;
                });
            Print::success(ACTIVE_SUCCESS, 1000);
            Print::removeLine(2);
            sources.display();
            break;
        }
        case 9: {
            Print::title("THONG KE HOA DON CO GIA TRI > 500000");
            sources.display([](Invoice d) {
                return d.total > 500000;
                });
            break;
        }
        case 17: case 49: { // A
            Print::title("THONG KE HOA DON CO GIA TRI < 500000");
            sources.display([](Invoice d) {
                return d.total < 500000;
                });
            break;
        }
        case 18: case 50: { // B
            Print::title("TINH TONG GIA TRI CUA TAT CA HOA DON");
            double total = sources.sum<double>([](Invoice d) {
                return d.total;
                });
            cout << "Tong gia tri cac hoa don: " << total << endl;
            Print::pressAnyKey();
            break;
        }
        case 19: case 51: { // C
            Print::title("TINH TB GIA TRI CUA TAT CA HOA DON");
            double average = sources.sum<double>([](Invoice d) {
                return d.total;
                }) / sources.size;
            cout << "Trung binh gia tri cua hoa don: " << average << endl;
            Print::pressAnyKey();
            break;
        }
        case 20: case 52: {  // D
            Print::title("CHINH SUA HOA DON THEO THU TU");
            Invoice* data = findAt(sources);
            if (data) {
                Invoice::edit(*data, sources, books, customers);
            }
            break;
        }
        case 21: case 53: {  // E
            Print::title("CHINH SUA HOA DON THEO MA");
            Invoice* data = findById(sources);
            if (data) {
                Invoice::edit(*data, sources, books, customers);
            }
            break;
        }
        case 22: case 54: {  // F
            Print::title("XOA SACH THEO THU TU");
            Invoice* data = findAt(sources);
            if (data) {
                Invoice::remove(*data, sources, books);
            }
            break;
        }
        case 23: case 55: {  // G
            Print::title("XOA SACH THEO MA");
            Invoice* data = findById(sources);
            if (data) {
                Invoice::remove(*data, sources, books);
            }
            break;
        }
        case 0: case -21: // 0 or ESC
            return;
        }
    }
}