#include "../include/Transaction.hpp"
#include <sstream>

Transaction::Transaction(std::string d, std::string c, double a, std::string n)
    : date(d), category(c), amount(a), note(n) {
}

std::string Transaction::getDate() const { return date; }
std::string Transaction::getCategory() const { return category; }
double Transaction::getAmount() const { return amount; }
std::string Transaction::getNote() const { return note; }

std::string Transaction::toCSV() const {
    std::stringstream ss;
    ss << date << "," << category << "," << amount << "," << note;
    return ss.str();
}