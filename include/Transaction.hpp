#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

class Transaction {
private:
    std::string date;
    std::string category;
    double amount;
    std::string note;

public:
    Transaction(std::string d, std::string c, double a, std::string n);

    std::string getDate() const;
    std::string getCategory() const;
    double getAmount() const;
    std::string getNote() const;

    std::string toCSV() const;
};

#endif