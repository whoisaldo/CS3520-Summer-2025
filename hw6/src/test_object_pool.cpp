/* 
 * Author:  Ali Younes & Ali Tleis 
 * Course:  CS3520
 * Date:    6/17/2025
 * Assignment 6: Automatic Parking Lot + Object Pool
 */
#include "ObjectPool.hpp"
#include "Vehicle.hpp"
#include "Customer.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// Custom test classes
class Book {
public:
    string title;
    string author;
    int pages;
    
    Book() : title(""), author(""), pages(0) {}
    Book(const string& t, const string& a, int p) 
        : title(t), author(a), pages(p) {}
    
    void reset() {
        title.clear();
        author.clear();
        pages = 0;
    }
    
    void display() const {
        cout << "Book: " << title << " by " << author 
                  << " (" << pages << " pages)\n";
    }
};

class GameItem {
public:
    string name;
    int damage;
    double weight;
    
    GameItem() : name(""), damage(0), weight(0.0) {}
    GameItem(const string& n, int d, double w) 
        : name(n), damage(d), weight(w) {}
    
    void reset() {
        name.clear();
        damage = 0;
        weight = 0.0;
    }
    
    void display() const {
        cout << "Item: " << name << " (Damage: " << damage 
                  << ", Weight: " << weight << ")\n";
    }
};

void testObjectPoolWithBooks() {
    cout << "\n=== Testing Object Pool with Books ===\n";
    
    ObjectPool<Book> bookPool(5);
    cout << "Initial pool size: " << bookPool.size() << "\n";
    
    // Get books from pool
    Book* book1 = bookPool.get_object();
    book1->title = "The C++ Programming Language";
    book1->author = "Bjarne Stroustrup";
    book1->pages = 1376;
    
    Book* book2 = bookPool.get_object();
    book2->title = "Design Patterns";
    book2->author = "Gang of Four";
    book2->pages = 395;
    
    cout << "Pool size after getting 2 objects: " << bookPool.size() << "\n";
    
    book1->display();
    book2->display();
    
    // Return books to pool
    bookPool.return_object(book1);
    bookPool.return_object(book2);
    
    cout << "Pool size after returning objects: " << bookPool.size() << "\n";
    
    // Test pool reuse
    Book* book3 = bookPool.get_object();
    book3->title = "Effective C++";
    book3->author = "Scott Meyers";
    book3->pages = 320;
    book3->display();
    
    bookPool.return_object(book3);
}

void testObjectPoolWithGameItems() {
    cout << "\n=== Testing Object Pool with Game Items ===\n";
    
    ObjectPool<GameItem> itemPool(3);
    cout << "Initial pool size: " << itemPool.size() << "\n";
    
    // Get items from pool
    GameItem* sword = itemPool.get_object();
    sword->name = "Excalibur";
    sword->damage = 100;
    sword->weight = 5.5;
    
    GameItem* bow = itemPool.get_object();
    bow->name = "Elven Bow";
    bow->damage = 75;
    bow->weight = 2.3;
    
    GameItem* axe = itemPool.get_object();
    axe->name = "Battle Axe";
    axe->damage = 90;
    axe->weight = 8.1;
    
    cout << "Pool size after getting 3 objects: " << itemPool.size() << "\n";
    
    sword->display();
    bow->display();
    axe->display();
    
    // Test pool expansion
    GameItem* hammer = itemPool.get_object(); // Should expand pool
    hammer->name = "War Hammer";
    hammer->damage = 85;
    hammer->weight = 7.2;
    hammer->display();
    
    // Return all items
    itemPool.return_object(sword);
    itemPool.return_object(bow);
    itemPool.return_object(axe);
    itemPool.return_object(hammer);
    
    cout << "Pool size after returning all objects: " << itemPool.size() << "\n";
}

void testObjectPoolWithPrimitives() {
    cout << "\n=== Testing Object Pool with Primitives ===\n";
    
    ObjectPool<int> intPool(4);
    ObjectPool<double> doublePool(4);
    
    // Test with integers
    int* num1 = intPool.get_object();
    int* num2 = intPool.get_object();
    *num1 = 42;
    *num2 = 100;
    
    cout << "Integer values: " << *num1 << ", " << *num2 << "\n";
    
    intPool.return_object(num1);
    intPool.return_object(num2);
    
    // Test with doubles
    double* d1 = doublePool.get_object();
    double* d2 = doublePool.get_object();
    *d1 = 3.14159;
    *d2 = 2.71828;
    
    cout << "Double values: " << *d1 << ", " << *d2 << "\n";
    
    doublePool.return_object(d1);
    doublePool.return_object(d2);
}

void testObjectPoolWithStrings() {
    cout << "\n=== Testing Object Pool with Strings ===\n";
    
    ObjectPool<string> stringPool(3);
    
    string* str1 = stringPool.get_object();
    string* str2 = stringPool.get_object();
    
    *str1 = "Hello, World!";
    *str2 = "Object Pool Testing";
    
    cout << "String 1: " << *str1 << "\n";
    cout << "String 2: " << *str2 << "\n";
    
    stringPool.return_object(str1);
    stringPool.return_object(str2);
    
    // Test reuse
    string* str3 = stringPool.get_object();
    *str3 = "Reused string object";
    cout << "String 3 (reused): " << *str3 << "\n";
    
    stringPool.return_object(str3);
}

void performanceTest() {
    cout << "\n=== Performance Test ===\n";
    
    const int iterations = 10000;
    
    // Test with object pool
    auto start = chrono::high_resolution_clock::now();
    {
        ObjectPool<Book> bookPool(100);
        for (int i = 0; i < iterations; ++i) {
            Book* book = bookPool.get_object();
            book->title = "Test Book " + to_string(i);
            book->author = "Test Author";
            book->pages = 200 + (i % 300);
            bookPool.return_object(book);
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto poolTime = chrono::duration_cast<chrono::microseconds>(end - start);
    
    // Test with regular allocation
    start = chrono::high_resolution_clock::now();
    {
        for (int i = 0; i < iterations; ++i) {
            Book* book = new Book();
            book->title = "Test Book " + to_string(i);
            book->author = "Test Author";
            book->pages = 200 + (i % 300);
            delete book;
        }
    }
    end = chrono::high_resolution_clock::now();
    auto normalTime = chrono::duration_cast<chrono::microseconds>(end - start);
    
    cout << "Object Pool Time: " << poolTime.count() << " microseconds\n";
    cout << "Normal Allocation Time: " << normalTime.count() << " microseconds\n";
    cout << "Performance improvement: " 
              << static_cast<double>(normalTime.count()) / poolTime.count() 
              << "x faster\n";
}

int main() {
    cout << "Object Pool Testing Program\n";
    cout << "============================\n";
    
    testObjectPoolWithBooks();
    testObjectPoolWithGameItems();
    testObjectPoolWithPrimitives();
    testObjectPoolWithStrings();
    performanceTest();
    
    cout << "\n=== All tests completed successfully! ===\n";
    return 0;
}
