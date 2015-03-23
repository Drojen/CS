// Q19 Monthly Payments - CS 318

#include <iomanip>
#include <iostream>
#include <math.h>

int main() {

	double rate, numPayments, loanAmt, payment;

	// get info
	std::cout << "Enter total loan amount        : ";
	std::cin >> loanAmt;
	std::cout << "Enter total number of payments : ";
	std::cin >> numPayments;	
	std::cout << "Enter annual interest rate     : ";
	std::cin >> rate;
	std::cout << "\n\n";

	if (rate >= 1) {
		rate /= 100;
	}

	rate /= 12;

	// formula from book
	payment = (rate * std::pow((1 + rate), numPayments)) / (std::pow((1 + rate), numPayments) - 1) * loanAmt;

	// report
	std::cout << std::setprecision(2) << std::fixed;
	std::cout << "Loan Amount:              $" << std::setw(12) << std::right << loanAmt << std::endl;
	std::cout << "Monthly Interest Rate:     " << std::setw(11) << std::right << std::setprecision(4) << rate * 100 << "%" << std::endl;
	std::cout << std::setprecision(2);
	std::cout << "Number of Payments:        " << std::setw(12) << std::right << static_cast<int>(numPayments) << std::endl;
	std::cout << "Monthly Payment:          $" << std::setw(12) << std::right << payment << std::endl;
	std::cout << "Amount Paid Back:         $" << std::setw(12) << std::right << payment * numPayments << std::endl;
	std::cout << "Interest Paid:            $" << std::setw(12) << std::right << (payment * numPayments) - loanAmt << std::endl;

	return 0;
}