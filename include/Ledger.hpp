#ifndef LEDGER_HPP
#define LEDGER_HPP

#include "Transaction.hpp"
#include <vector>
#include <string>
#include <map>

class Ledger {
private:
    std::vector<Transaction> records;
    void sortByDate();

public:
    Ledger();

    // Data Operations
    void addTransaction(const Transaction& txn);
    void removeTransaction(int index);
    void editTransaction(int index, const Transaction& newTxn);
    
    // Queries
    const std::vector<Transaction>& getAllTransactions() const;
    std::vector<Transaction> searchTransactions(const std::string& keyword) const;
    Transaction getTransaction(int index) const;
    int getRecordCount() const;

    // Reports
    double calculateTotal() const;
    void printCategorySummary() const;

    // File I/O
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif