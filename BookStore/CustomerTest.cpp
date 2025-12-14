#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <cstdio>
#include "Customer.h"

using namespace std;

// Test counter
int testsPassed = 0;
int testsFailed = 0;

// Helper macro for test assertions
#define TEST_ASSERT(condition, testName) \
    if (condition) { \
        cout << "[PASS] " << testName << endl; \
        testsPassed++; \
    } else { \
        cout << "[FAIL] " << testName << endl; \
        testsFailed++; \
    }

// Test 1: Kiểm tra khởi tạo Customer mặc định
void testDefaultConstructor() {
    cout << "\n=== Test Default Constructor ===" << endl;
    
    Customer customer;
    
    TEST_ASSERT(customer.id.empty(), "Default id should be empty");
    TEST_ASSERT(customer.name.empty(), "Default name should be empty");
    TEST_ASSERT(customer.phone.empty(), "Default phone should be empty");
    TEST_ASSERT(customer.address.empty(), "Default address should be empty");
}

// Test 2: Kiểm tra gán giá trị cho các thuộc tính
void testPropertyAssignment() {
    cout << "\n=== Test Property Assignment ===" << endl;
    
    Customer customer;
    customer.id = "KH001";
    customer.name = "Nguyen Van A";
    customer.phone = "0901234567";
    customer.address = "123 Le Loi, Q1, HCM";
    
    TEST_ASSERT(customer.id == "KH001", "ID assignment works correctly");
    TEST_ASSERT(customer.name == "Nguyen Van A", "Name assignment works correctly");
    TEST_ASSERT(customer.phone == "0901234567", "Phone assignment works correctly");
    TEST_ASSERT(customer.address == "123 Le Loi, Q1, HCM", "Address assignment works correctly");
}

// Test 3: Kiểm tra serialize và deserialize
void testSerializeDeserialize() {
    cout << "\n=== Test Serialize/Deserialize ===" << endl;
    
    const string testFile = "test_customer.bin";
    
    // Tạo customer và serialize
    Customer original;
    original.id = "KH002";
    original.name = "Tran Thi B";
    original.phone = "0912345678";
    original.address = "456 Nguyen Hue, Q1, HCM";
    
    // Serialize to file
    {
        ofstream out(testFile, ios::binary);
        TEST_ASSERT(out.is_open(), "File opened for writing");
        original.serialize(out);
        out.close();
    }
    
    // Deserialize from file
    Customer loaded;
    {
        ifstream in(testFile, ios::binary);
        TEST_ASSERT(in.is_open(), "File opened for reading");
        loaded.deserialize(in);
        in.close();
    }
    
    // Verify data
    TEST_ASSERT(loaded.id == original.id, "Deserialized ID matches original");
    TEST_ASSERT(loaded.name == original.name, "Deserialized name matches original");
    TEST_ASSERT(loaded.phone == original.phone, "Deserialized phone matches original");
    TEST_ASSERT(loaded.address == original.address, "Deserialized address matches original");
    
    // Cleanup test file
    remove(testFile.c_str());
}

// Test 4: Kiểm tra serialize/deserialize với chuỗi rỗng
void testSerializeDeserializeEmptyStrings() {
    cout << "\n=== Test Serialize/Deserialize Empty Strings ===" << endl;
    
    const string testFile = "test_customer_empty.bin";
    
    // Tạo customer với một số field rỗng
    Customer original;
    original.id = "KH003";
    original.name = "Le Van C";
    original.phone = "";  // Empty phone
    original.address = "";  // Empty address
    
    // Serialize
    {
        ofstream out(testFile, ios::binary);
        original.serialize(out);
        out.close();
    }
    
    // Deserialize
    Customer loaded;
    {
        ifstream in(testFile, ios::binary);
        loaded.deserialize(in);
        in.close();
    }
    
    TEST_ASSERT(loaded.id == original.id, "ID with empty fields matches");
    TEST_ASSERT(loaded.name == original.name, "Name with empty fields matches");
    TEST_ASSERT(loaded.phone == "", "Empty phone deserialized correctly");
    TEST_ASSERT(loaded.address == "", "Empty address deserialized correctly");
    
    // Cleanup
    remove(testFile.c_str());
}

// Test 5: Kiểm tra serialize/deserialize với ký tự đặc biệt
void testSerializeDeserializeSpecialChars() {
    cout << "\n=== Test Serialize/Deserialize Special Characters ===" << endl;
    
    const string testFile = "test_customer_special.bin";
    
    Customer original;
    original.id = "KH-004";
    original.name = "Pham Thi D (VIP)";
    original.phone = "+84-901-234-567";
    original.address = "789 Dong Khoi, Q.1, TP.HCM";
    
    // Serialize
    {
        ofstream out(testFile, ios::binary);
        original.serialize(out);
        out.close();
    }
    
    // Deserialize
    Customer loaded;
    {
        ifstream in(testFile, ios::binary);
        loaded.deserialize(in);
        in.close();
    }
    
    TEST_ASSERT(loaded.id == original.id, "ID with special chars matches");
    TEST_ASSERT(loaded.name == original.name, "Name with special chars matches");
    TEST_ASSERT(loaded.phone == original.phone, "Phone with special chars matches");
    TEST_ASSERT(loaded.address == original.address, "Address with special chars matches");
    
    // Cleanup
    remove(testFile.c_str());
}

// Test 6: Kiểm tra printData output
void testPrintData() {
    cout << "\n=== Test PrintData ===" << endl;
    
    Customer customer;
    customer.id = "KH005";
    customer.name = "Hoang Van E";
    customer.phone = "0923456789";
    customer.address = "321 CMT8, Q3, HCM";
    
    // Redirect cout to stringstream
    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());
    
    customer.printData(false);  // Without header
    
    // Restore cout
    cout.rdbuf(oldCout);
    
    string output = buffer.str();
    
    TEST_ASSERT(output.find("KH005") != string::npos, "PrintData contains ID");
    TEST_ASSERT(output.find("Hoang Van E") != string::npos, "PrintData contains name");
    TEST_ASSERT(output.find("0923456789") != string::npos, "PrintData contains phone");
    TEST_ASSERT(output.find("321 CMT8, Q3, HCM") != string::npos, "PrintData contains address");
}

// Test 7: Kiểm tra printHeader output
void testPrintHeader() {
    cout << "\n=== Test PrintHeader ===" << endl;
    
    Customer customer;
    
    // Redirect cout to stringstream
    stringstream buffer;
    streambuf* oldCout = cout.rdbuf(buffer.rdbuf());
    
    customer.printHeader();
    
    // Restore cout
    cout.rdbuf(oldCout);
    
    string output = buffer.str();
    
    TEST_ASSERT(output.find("MA") != string::npos, "PrintHeader contains MA column");
    TEST_ASSERT(output.find("TEN KH") != string::npos, "PrintHeader contains TEN KH column");
    TEST_ASSERT(output.find("DIEN THOAI") != string::npos, "PrintHeader contains DIEN THOAI column");
    TEST_ASSERT(output.find("DIA CHI") != string::npos, "PrintHeader contains DIA CHI column");
}

// Test 8: Kiểm tra serialize/deserialize nhiều customers
void testMultipleCustomersSerialize() {
    cout << "\n=== Test Multiple Customers Serialize/Deserialize ===" << endl;
    
    const string testFile = "test_customers_multi.bin";
    
    // Tạo nhiều customers
    Customer customers[3];
    
    customers[0].id = "KH010";
    customers[0].name = "Customer A";
    customers[0].phone = "0901111111";
    customers[0].address = "Address A";
    
    customers[1].id = "KH011";
    customers[1].name = "Customer B";
    customers[1].phone = "0902222222";
    customers[1].address = "Address B";
    
    customers[2].id = "KH012";
    customers[2].name = "Customer C";
    customers[2].phone = "0903333333";
    customers[2].address = "Address C";
    
    // Serialize all
    {
        ofstream out(testFile, ios::binary);
        for (int i = 0; i < 3; i++) {
            customers[i].serialize(out);
        }
        out.close();
    }
    
    // Deserialize all
    Customer loaded[3];
    {
        ifstream in(testFile, ios::binary);
        for (int i = 0; i < 3; i++) {
            loaded[i].deserialize(in);
        }
        in.close();
    }
    
    // Verify
    bool allMatch = true;
    for (int i = 0; i < 3; i++) {
        if (loaded[i].id != customers[i].id ||
            loaded[i].name != customers[i].name ||
            loaded[i].phone != customers[i].phone ||
            loaded[i].address != customers[i].address) {
            allMatch = false;
            break;
        }
    }
    
    TEST_ASSERT(allMatch, "All 3 customers serialized/deserialized correctly");
    
    // Cleanup
    remove(testFile.c_str());
}

// Test 9: Kiểm tra chuỗi dài
void testLongStrings() {
    cout << "\n=== Test Long Strings ===" << endl;
    
    const string testFile = "test_customer_long.bin";
    
    Customer original;
    original.id = "KH-LONG-ID-12345";
    original.name = "Nguyen Thi Minh Chau - Khach hang VIP Gold Diamond Platinum";
    original.phone = "0901234567890123456789";
    original.address = "So 123, Duong Nguyen Van Linh, Phuong Tan Phong, Quan 7, Thanh pho Ho Chi Minh, Viet Nam";
    
    // Serialize
    {
        ofstream out(testFile, ios::binary);
        original.serialize(out);
        out.close();
    }
    
    // Deserialize
    Customer loaded;
    {
        ifstream in(testFile, ios::binary);
        loaded.deserialize(in);
        in.close();
    }
    
    TEST_ASSERT(loaded.id == original.id, "Long ID matches");
    TEST_ASSERT(loaded.name == original.name, "Long name matches");
    TEST_ASSERT(loaded.phone == original.phone, "Long phone matches");
    TEST_ASSERT(loaded.address == original.address, "Long address matches");
    
    // Cleanup
    remove(testFile.c_str());
}

// Main function - chạy tất cả tests
int main() {
    cout << "========================================" << endl;
    cout << "   CUSTOMER STRUCT AUTOMATION TESTS    " << endl;
    cout << "========================================" << endl;
    
    // Run all tests
    testDefaultConstructor();
    testPropertyAssignment();
    testSerializeDeserialize();
    testSerializeDeserializeEmptyStrings();
    testSerializeDeserializeSpecialChars();
    testPrintData();
    testPrintHeader();
    testMultipleCustomersSerialize();
    testLongStrings();
    
    // Summary
    cout << "\n========================================" << endl;
    cout << "           TEST SUMMARY                " << endl;
    cout << "========================================" << endl;
    cout << "Tests Passed: " << testsPassed << endl;
    cout << "Tests Failed: " << testsFailed << endl;
    cout << "Total Tests:  " << (testsPassed + testsFailed) << endl;
    
    if (testsFailed == 0) {
        cout << "\n*** ALL TESTS PASSED! ***" << endl;
        return 0;
    } else {
        cout << "\n*** SOME TESTS FAILED! ***" << endl;
        return 1;
    }
}
