/*
 * Younes.Al@Northeastern.edu
 * Ali Younes
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

int main() {
    map<string, map<string, double>> priceData = {
        {"iPhone14", {{"Amazon", 978.99}, {"eBay", 999.99}, {"BestBuy", 1009.99}, {"Staples", 1025.00}, {"OfficeMax", 1010.00}}},
        {"iPad Pro", {{"Amazon", 1459.98}, {"eBay", 1499.00}, {"BestBuy", 1545.99}, {"Staples", 1500.00}, {"OfficeMax", 1480.00}}},
        {"Back Roller", {{"Amazon", 47.99}, {"eBay", 44.78}, {"BestBuy", 49.99}, {"Staples", 46.50}, {"OfficeMax", 50.00}}},
        {"Noise Cancelling Headphones", {{"Amazon", 299.99}, {"eBay", 305.00}, {"BestBuy", 310.00}, {"Staples", 295.00}, {"OfficeMax", 300.00}}},
        {"Bike", {{"Amazon", 999.00}, {"eBay", 949.00}, {"BestBuy", 970.00}, {"Staples", 975.00}, {"OfficeMax", 960.00}}}
    };

    // Display header
    cout << fixed << setprecision(2);
    cout << "\nAll Prices by Product:\n";
    for (const auto& [product, storePrices] : priceData) {
        cout << product << ": ";
        for (const auto& [store, price] : storePrices) {
            cout << store << " $" << price << ", ";
        }
        cout << "\n";
    }

    // Average price calculation and sort
    vector<pair<string, double>> averages;
    for (const auto& [product, storePrices] : priceData) {
        double sum = 0;
        for (const auto& [_, price] : storePrices) sum += price;
        double avg = sum / storePrices.size();
        averages.push_back({product, avg});
    }

    sort(averages.begin(), averages.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    cout << "\nAverage Prices (ascending):\n";
    for (const auto& [product, avg] : averages) {
        cout << product << ", Avg: $" << avg << "\n";
    }

    // Best price store for each product
    cout << "\nBest Price by Store:\n";
    for (const auto& [product, storePrices] : priceData) {
        auto best = min_element(storePrices.begin(), storePrices.end(), [](auto& a, auto& b) {
            return a.second < b.second;
        });
        cout << product << ", Best Price Offered by: " << best->first << " ($" << best->second << ")\n";
    }

    return 0;
}

