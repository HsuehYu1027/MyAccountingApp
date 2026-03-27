#include "../include/View.hpp"

#include <iostream>
#include <vector>
#include <limits>
#include <regex>

bool View::isValidDate(const std::string& dateStr) const {
    std::regex pattern("^\\d{4}/\\d{2}/\\d{2}$");
    return std::regex_match(dateStr, pattern);
}

void View::displayMainMenu() const {
    std::cout << "\n==================================\n";
    std::cout << "      Expense Tracker System      \n";
    std::cout << "==================================\n";
    std::cout << "  [1] Add Transaction\n";
    std::cout << "  [2] View / Edit / Delete Records\n";
    std::cout << "  [3] Financial Summary\n";
    std::cout << "  [4] Search Records\n";
    std::cout << "  [5] Exit\n";
    std::cout << "Select an option (1-5): ";
}

int View::getIntegerInput(int min, int max) const {
    int choice;
    while (!(std::cin >> choice) || choice < min || choice > max) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    return choice;
}

std::string View::promptForKeyword() const {
    std::string keyword;
    std::cout << "\nEnter search keyword (Category or Note): ";
    std::getline(std::cin, keyword);
    return keyword;
}

void View::displayMessage(const std::string& message) const {
    std::cout << message << "\n";
}

void View::displayPrompt(const std::string& prompt) const {
    std::cout << prompt;
}

Transaction View::promptForNewTransaction() const {
    std::cout << "\n--- Add New Transaction ---\n";
    std::string d, c, n;
    double a;

    while (true) {
        std::cout << "Enter Date (YYYY/MM/DD): ";
        std::getline(std::cin, d);
        if (isValidDate(d)) break;
        std::cout << "Invalid date format.\n";
    }

    std::cout << "Enter Category (e.g., Food, Transport): ";
    std::getline(std::cin, c);

    std::string inputStr;
    while (true) {
        std::cout << "Enter Amount (Negative for expenses): ";
        std::getline(std::cin, inputStr);
        if (inputStr.empty()) continue;
        try {
            a = std::stod(inputStr);
            break;
        } catch (const std::exception& e) {
            std::cout << "Invalid format. Please enter a number.\n";
        }
    }

    std::cout << "Enter Note (Optional, press Enter to skip): ";
    std::getline(std::cin, n);

    return Transaction(d, c, a, n);
}

void View::displayTransactions(const std::vector<Transaction>& txns, const std::string& title) const {
    if (txns.empty()) {
        std::cout << "No records found.\n";
        return;
    }

    std::cout << "\n=========== " << title << " ===========\n";
    double total = 0.0;
    
    for (size_t i = 0; i < txns.size(); ++i) {
        const auto& t = txns[i];
        std::cout << "[" << (i + 1) << "] " << t.getDate() << " | " 
                  << t.getCategory() << " | $" 
                  << t.getAmount() << " | " 
                  << t.getNote() << "\n";
        total += t.getAmount();
    }
    
    std::cout << "--------------------------------------------\n";
    std::cout << "  Total for this list: $" << total << "\n";
    std::cout << "============================================\n";
}