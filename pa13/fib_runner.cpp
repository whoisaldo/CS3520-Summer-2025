/*
 * Author: Ali Younes
 * Course: CS3520 - Summer 2025
 * Assignment: PA13 - Multithreading with Fibonacci
 * Date: 6/18/2025
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <array>

// A recursive Fibonacci function (deliberately inefficient for benchmarking)
unsigned long long calcFib(int n) {
    if (n <= 1)
        return n;
    return calcFib(n - 1) + calcFib(n - 2);
}

// Threaded execution wrapper
void runFib(int input) {
    auto id = std::this_thread::get_id();
    std::cout << "[Running on Thread " << id << "] Computing fib(" << input << ")...\n";
    auto t0 = std::chrono::steady_clock::now();
    auto value = calcFib(input);
    auto t1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = t1 - t0;
    std::cout << "[Thread " << id << "] fib(" << input << ") = " << value
              << " | Time: " << elapsed.count() << "s\n";
}

int main() {
    std::array<int, 3> inputs = {34, 35, 36};

    std::cout << "--- Sequential Execution ---\n";
    auto t_seq_start = std::chrono::steady_clock::now();
    for (int val : inputs) {
        runFib(val);
    }
    auto t_seq_end = std::chrono::steady_clock::now();
    std::cout << "[Sequential] Total Duration: "
              << std::chrono::duration<double>(t_seq_end - t_seq_start).count()
              << "s\n\n";

    std::cout << "--- Parallel Execution ---\n";
    auto t_par_start = std::chrono::steady_clock::now();
    std::array<std::thread, 3> threads;
    for (int i = 0; i < 3; ++i) {
        threads[i] = std::thread(runFib, inputs[i]);
    }
    for (auto& th : threads) {
        th.join();
    }
    auto t_par_end = std::chrono::steady_clock::now();
    std::cout << "[Parallel] Total Duration: "
              << std::chrono::duration<double>(t_par_end - t_par_start).count()
              << "s\n";

    return 0;
}

