#include "pch.h"
#include "CppUnitTest.h"
#include "../BookStore/Book.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BookStoreTest {
    TEST_CLASS(FileTest) {
    public:
		// Test 1: Kiểm tra ghi và đọc Book
		TEST_METHOD(TestSaveAndLoadBooks) {
			List<Book> inputData;
			Book b1("B01", "Test Book 1", "Author A", 2020, 100, 50000);
			inputData.add(b1);
			Book b2("B02", "Test Book 2", "Author B", 2021, 200, 20000);
			inputData.add(b2);
			inputData.saveFile();
			List<Book> outputData;
			outputData.loadFile();
			// Kiểm tra số lượng phần tử
			Assert::AreEqual(inputData.size, outputData.size, L"So luong khong khop");
			// Kiểm tra id phần tử đầu tiên
			Assert::AreEqual(inputData.head->data.id, outputData.head->data.id, L"Id khong khop");
		}

		// Test 2: Kiểm tra file
		TEST_METHOD(TestFileCreation) {
			List<Book> dummyData;
			dummyData.add(Book("D1", "A", "", 2000, 50, 10000));
			dummyData.saveFile();
			// Kiểm tra file
			ifstream f("Book.bin");
			bool exists = f.good();
			f.close();
			Assert::IsTrue(exists, L"File khong duoc tao");
		}

		// Test 3: Kiểm tra đọc file rỗng
		TEST_METHOD(TestLoadEmptyOrNonExist) {
			// Xóa file nếu tồn tại
			remove("Book.bin");
			List<Book> result;
			result.loadFile();
			Assert::AreEqual(0, result.size);
		}
    };
}
