#include "../include/Ledger.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>

Ledger::Ledger() {
}

void Ledger::addTransaction(const Transaction& txn) {
    records.push_back(txn); 
    sortByDate();
}

const std::vector<Transaction>& Ledger::getAllTransactions() const {
    return records; 
}

double Ledger::calculateTotal() const {
    double total = 0.0;
    for (const Transaction& t : records) {
        total += t.getAmount(); 
    }
    return total;
}

void Ledger::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cout << "Error: Unable to open file " << filename << " for saving!\n";
        return;
    }

    for (const Transaction& t : records) {
        outFile << t.toCSV() << "\n"; 
    }

    outFile.close(); 
}

void Ledger::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);

    if (!inFile.is_open()) {
        std::cout << "[System] No historical records found. Starting a new ledger.\n";
        return; 
    }

    records.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue; 

        std::stringstream ss(line);
        std::string d, c, amountStr, n;
        
        std::getline(ss, d, ',');        
        std::getline(ss, c, ',');        
        std::getline(ss, amountStr, ','); 
        std::getline(ss, n, ',');        

        double a = 0.0;
        try {
            a = std::stod(amountStr);
        } catch (const std::exception& e) {
            std::cerr << "[Warning] Skipping corrupted record. Invalid amount: " << amountStr << "\n";
            continue; 
        }

        records.emplace_back(d, c, a, n); 
    }

    inFile.close(); 
    std::cout << "[System] Historical records loaded successfully!\n";

    sortByDate();
}

void Ledger::removeTransaction(int index) {
    if (records.empty() || index < 1 || index > records.size()) {
        std::cout << "Delete failed: Invalid ID! Please use [2] to check IDs first.\n";
        return;
    }

    int actualIndex = index - 1;
    records.erase(records.begin() + actualIndex);

    std::cout << "Success! Deleted record #" << index << ".\n";
}

void Ledger::printCategorySummary() const {
    if (records.empty()) {
        std::cout << "No records available for summary.\n";
        return;
    }

    std::map<std::string, double> summary;
    double totalIncome = 0.0;  
    double totalExpense = 0.0; 

    for (const Transaction& t : records) {
        double amt = t.getAmount();
        
        summary[t.getCategory()] += amt;
        
        if (amt > 0) {
            totalIncome += amt;
        } else {
            totalExpense += amt;
        }
    }

    std::cout << "\n=========== Financial Summary ===========\n";
    std::cout << "[Category Breakdown]\n";
    for (const auto& map_pair : summary) {
        std::cout << "  [" << map_pair.first << "] : $" << map_pair.second << "\n";
    }
    std::cout << "-----------------------------------------\n";
    std::cout << "  Total Income  : $" << totalIncome << "\n";
    std::cout << "  Total Expense : $" << totalExpense << "\n";
    std::cout << "  Net Balance   : $" << (totalIncome + totalExpense) << "\n";
    std::cout << "=========================================\n";
}

void Ledger::editTransaction(int index, const Transaction& newTxn) {
    if (records.empty() || index < 1 || index > records.size()) {
        std::cout << "Edit failed: Invalid ID! Please use [2] to check IDs first.\n";
        return;
    }

    int actualIndex = index - 1; 
    records[actualIndex] = newTxn; 

    std::cout << "Success! Record #" << index << " has been updated.\n";

    sortByDate();
}

int Ledger::getRecordCount() const {
    return records.size();
}

Transaction Ledger::getTransaction(int index) const {
    int actualIndex = index - 1;
    return records[actualIndex]; 
}

void Ledger::sortByDate() {
    if (records.size() < 2) {
        return; 
    }

    std::sort(records.begin(), records.end(), 
        [](const Transaction& a, const Transaction& b) {
            return a.getDate() < b.getDate();
        }
    );
}

std::vector<Transaction> Ledger::searchTransactions(const std::string& keyword) const {
    std::vector<Transaction> results; 

    std::copy_if(records.begin(), records.end(), std::back_inserter(results),
        [&keyword](const Transaction& t) {
            bool matchCategory = t.getCategory().find(keyword) != std::string::npos;
            bool matchNote = t.getNote().find(keyword) != std::string::npos;
            return matchCategory || matchNote; 
        }
    );

    return results; 
}