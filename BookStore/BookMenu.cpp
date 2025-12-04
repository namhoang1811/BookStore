#include "BookMenu.h"

void BookMenu::show(List<Book> books) {
    while (true) {
        Print::title("QUAN LY SACH");
        cout << "1. Xem danh sach" << endl;
        cout << "2. Them mot Sach moi" << endl;
        cout << "3. Chinh sua Sach theo thu tu" << endl;
        cout << "4. Chinh sua Sach theo Ma" << endl;
        cout << "5. Xoa Sach theo thu tu" << endl;
        cout << "6. Xoa Sach theo Ma" << endl;
        cout << "0. Tro ve" << endl;
        cout << endl << "Bam phim lua chon: ";
        char k = _getch();
        switch ((int)k - 48) {
        case 1:
            Print::title("DANH SACH SACH");
            books.display(2);
            break;
        case 2: {
            Print::title("TAO MOT SACH MOI");
            auto model = Book::create();
            if (!books.any([model](Book d) {
                return d.id.find(model.id) != string::npos;
                })) {
                books.addLast(model);
                Notify::success("Them sach moi thanh cong!");
            }
            else {
                Notify::danger("Them sach moi that bai! Trung Ma");
            }
            break;
        }
        case 3: {
            int position;
            Print::title("CHINH SUA SACH THEO THU TU");
            cout << "Nhap thu tu sach can chinh sua: ";
            cin >> position;
            auto node = books.findAt(position);
            if (node) {
                Print::title("CHINH SUA SACH: " + node->data.name);
                Book::edit(node->data);
            }
            else {
                Print::invalid();
            }
            break;
        }
        case 0:
            return;
        }
    }
}