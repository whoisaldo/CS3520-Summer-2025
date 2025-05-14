/*
 * Q2 – Magic of Compound Interest
 *
 * Starting with $11.00 in 1626, compute the future value over 398 years
 * for annual interest rates from 2.0% to 10.0% in 0.5% increments.
 * Then compute the growth at:
 *   • S&P 500 with 10.17% average return
 *   • NASDAQ with 10.40% average return
 * Finally, compare all results to a Mona Lisa valuation of $860 million.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const double principal       = 11.0;       // initial deposit
    const int    years           = 398;        // from 1626 to 2024
    const double monaLisaValue   = 860e6;      // $860 million

    // Set up fixed‑point output with two decimals
    cout << fixed << setprecision(2);

    // Header
    cout << "Compound interest on $" << principal 
         << " over " << years << " years:\n\n";
    cout << setw(6) << "Rate" << setw(20) << "Future Value\n";
    cout << string(26, '-') << "\n";

    // 1) Loop over rates 2.0% → 10.0% in 0.5% steps
    for (double rate = 2.0; rate <= 10.0; rate += 0.5) {
        double amount = principal * pow(1.0 + rate/100.0, years);
        cout << setw(5) << rate << "%" 
             << setw(15) << "$" << amount << "\n";
    }

    // 2) Special cases: S&P 500 & NASDAQ
    cout << "\n";
    double spAmount     = principal * pow(1.0 + 10.17/100.0, years);
    double nasdaqAmount = principal * pow(1.0 + 10.40/100.0, years);

    cout << "S&P 500 @ 10.17%: $" << setw(13) << spAmount << "\n";
    cout << "NASDAQ @ 10.40%: $" << setw(13) << nasdaqAmount << "\n\n";

    // 3) Mona Lisa comparison
    cout << "Mona Lisa valuation: $" << setw(13) << monaLisaValue << "\n";

    return 0;
}
