#include "CustomerMenu.h"

namespace {
    Customer* findAt(List<Customer>& customers) {
        while (true) {
            try {
                int position = stoi(Input::read("Nhap thu tu Khach Hang: ", true));
                Customer* result = customers.findAt(position);
                if (!result)
                    Print::warning(NOT_FOUND);
                return result;
            } catch (...) {
                Print::removeLine(2);
            }
        }
    }

    Customer* findById(List<Customer>& customers) {
        string id = Input::read("Nhap ma Khach Hang: ", true);
        Customer* result = customers.find([id](Customer d) {
            return d.id == id;
            });
        if (!result)
            Print::warning(NOT_FOUND);
        return result;
    }
}

void CustomerMenu::show(List<Customer>& sources) {
    while (true) {
        Print::title("QUAN LY KHACH HANG");
        cout << "1. Xem danh sach" << endl;
        cout << "2. Them Khach Hang moi" << endl;
        cout << "3. Tim Khach Hang theo thu tu" << endl;
        cout << "4. Tim kiem Khach Hang theo Ten" << endl;
        cout << "5. Tim Khach Hang co diem tich luy lon nhat" << endl;
        cout << "6. Tim Khach Hang co diem tich luy nho nhat" << endl;
        cout << "7. Sap xep Khach Hang theo diem tich luy tang dan" << endl;
        cout << "8. Sap xep Khach Hang theo diem tich luy giam dan" << endl;
        cout << "9. Thong ke Khach Hang co diem tich luy > 100" << endl;
        cout << "A. Thong ke Khach Hang chua diem tich luy" << endl;
        cout << "B. Tinh tong so diem tich luy cua tat ca khach hang" << endl;
        cout << "C. Tinh TB diem tich luy cua tat ca khach hang" << endl;
        cout << "D. Chinh sua Khach Hang theo thu tu" << endl;
        cout << "E. Chinh sua Khach Hang theo Ma" << endl;
        cout << "F. Xoa Khach Hang theo thu tu" << endl;
        cout << "G. Xoa Khach Hang theo Ma" << endl;
        cout << "0. Tro ve" << endl;
        cout << endl << PRESS_OPTION;
        char k = Input::getch();
        switch ((int)k - 48) {
        case 1:
            Print::title("DANH SACH KHACH HANG");
            sources.display();
            break;
        case 2: {
            Print::title("TAO KHACH HANG MOI");
            Customer::create(sources);            
            break;
        }
        case 3: {
            Print::title("TIM KHACH HANG THEO THU TU");
            Customer* data = findAt(sources);
            if (data) {
                data->printData();
                Print::pressAnyKey();
            }
            break;
        }
        case 4: {
            Print::title("TIM KIEM KHACH HANG THEO TEN");
            string keyword;
            keyword = Input::read("Nhap ten khach hang can tim: ", true);
            sources.display([keyword](Customer d) {
                return d.name.find(keyword) != string::npos;
                });
            break;
        }
        case 5: {
            Print::title("TIM KHACH HANG CO DIEN TICH LUY LON NHAT");
            Customer* data = sources.find([](Customer a, Customer b) {
                return a.points > b.points;
                });
            if (data) {
                sources.display([data](Customer d) {
                    return d.points == data->points;
                    });
            } else {
                Print::warning(NOT_FOUND);
			}
            break;
        }
        case 6: {
            Print::title("TIM KHACH HANG CO DIEN TICH LUY NHO NHAT");
            Customer* data = sources.find([](Customer a, Customer b) {
                return a.points < b.points;
                });
            if (data) {
                sources.display([data](Customer d) {
                    return d.points == data->points;
                    });
            } else {
                Print::warning(NOT_FOUND);
            }
            break;
        }
        case 7: {
            Print::title("SAP XEP KHACH HANG THEO DIEN TICH LUY TANG DAN");
            sources.sort([](Customer a, Customer b) {
                return a.points > b.points;
                });
            Print::success(ACTIVE_SUCCESS, 1000);
            Print::removeLine(2);
            sources.display();
            break;
        }
        case 8: {
            Print::title("SAP XEP KHACH HANG THEO DIEM TICH LUY GIAM DAN");
            sources.sort([](Customer a, Customer b) {
                return a.points < b.points;
                });
            Print::success(ACTIVE_SUCCESS, 1000);
            Print::removeLine(2);
            sources.display();
            break;
        }
        case 9: {
            Print::title("THONG KE KHACH HANG CO DIEN LICH LUY > 100");
            sources.display([](Customer d) {
                return d.points > 100;
                });
            break;
        }
        case 17: case 49: { // A
            Print::title("THONG KE KHACH HANG CHUA CO DIEM TICH LUY");
            sources.display([](Customer d) {
                return d.points == 0;
                });
            break;
        }
        case 18: case 50: { // B
            Print::title("TINH TONG SO DIEM TICH LUY CUA TAT CA KHACH HANG");
            int total = sources.sum<int>([](Customer d) {
                return d.points;
                });
            cout << "Tong so diem tich luy: " << total << endl;
            Print::pressAnyKey();
            break;
        }
        case 19: case 51: { // C
            Print::title("TINH TB DIEM TICH LUY CUA TAT CA KHACH HANG");
            int average = sources.sum<int>([](Customer d) {
                return d.points;
                }) / sources.size;
            cout << "Trung binh diem tich luy: " << average << endl;
            Print::pressAnyKey();
            break;
        }
        case 20: case 52: {  // D
            Print::title("CHINH SUA KHACH HANG THEO THU TU");
            Customer* data = findAt(sources);
            if (data) {
                Customer::edit(*data, sources);
            }
            break;
        }
        case 21: case 53: {  // E
            Print::title("CHINH SUA KHACH HANG THEO MA");
            Customer* data = findById(sources);
            if (data) {
                Customer::edit(*data, sources);
            }
            break;
        }
        case 22: case 54: {  // F
            Print::title("XOA KHACH HANG THEO THU TU");
            Customer* data = findAt(sources);
            if (data) {
                Customer::remove(*data, sources);
            }
            break;
        }
        case 23: case 55: {  // G
            Print::title("XOA KHACH HANG THEO MA");
            Customer* data = findById(sources);
            if (data) {
                Customer::remove(*data, sources);
            }
            break;
        }
        case 0: case -21: // 0 or ESC
            return;
        default:
            Print::invalid();
            break;
        }
    }
}
