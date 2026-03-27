#ifndef VIEW_HPP
#define VIEW_HPP

#include <string>
#include <vector>
#include "Transaction.hpp"

class View {
private:
    bool isValidDate(const std::string& dateStr) const;

public:
    void displayMainMenu() const;
    int getIntegerInput(int min, int max) const;
    std::string promptForKeyword() const;
    
    void displayMessage(const std::string& message) const;
    void displayPrompt(const std::string& prompt) const;
    
    void displayTransactions(const std::vector<Transaction>& txns, const std::string& title) const;
    Transaction promptForNewTransaction() const;
};

#endif