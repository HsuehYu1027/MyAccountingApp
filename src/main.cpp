#include <iostream>
#include <cstdlib>
#include <vector>
#include <limits>
#include <string>

#include "../include/Transaction.hpp"
#include "../include/Ledger.hpp"
#include "../include/View.hpp" 

int main() {
    system("chcp 65001 > nul"); // Keep console in UTF-8
    
    Ledger model; 
    View view;    

    model.loadFromFile("data.csv");

    bool running = true;
    while (running) {
        view.displayMainMenu();
        
        int choice = view.getIntegerInput(1, 5);

        switch (choice) {
            case 1: {
                Transaction newTxn = view.promptForNewTransaction();
                model.addTransaction(newTxn);
                view.displayMessage("[Success] Transaction added to the ledger.");
                break;
            }
            case 2: {
                view.displayTransactions(model.getAllTransactions(), "All Historical Records");
                
                if (model.getRecordCount() == 0) {
                    break;
                }

                view.displayPrompt("\nSelect action: [0] Back  [1] Edit  [2] Delete : ");
                int subChoice = view.getIntegerInput(0, 2);

                if (subChoice == 0) {
                    break; 
                } 
                else if (subChoice == 1) {
                    // Edit Logic
                    view.displayPrompt("Enter record ID to edit (0 to cancel): ");
                    int editIdx;
                    std::cin >> editIdx;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (editIdx > 0 && editIdx <= model.getRecordCount()) {
                        Transaction oldTxn = model.getTransaction(editIdx);
                        std::string newD = oldTxn.getDate();
                        std::string newC = oldTxn.getCategory();
                        double newA = oldTxn.getAmount();
                        std::string newN = oldTxn.getNote();
                        std::string inputStr;

                        view.displayMessage("\nEditing Record (Press Enter to keep current value):");

                        view.displayPrompt("Current Date [" + newD + "], New Date (YYYY/MM/DD): ");
                        std::getline(std::cin, inputStr);
                        if (!inputStr.empty()) newD = inputStr;

                        view.displayPrompt("Current Category [" + newC + "], New Category: ");
                        std::getline(std::cin, inputStr);
                        if (!inputStr.empty()) newC = inputStr;

                        while (true) {
                            view.displayPrompt("Current Amount [$" + std::to_string(newA) + "], New Amount: ");
                            std::getline(std::cin, inputStr);
                            if (inputStr.empty()) break; 
                            try {
                                newA = std::stod(inputStr); 
                                break;
                            } catch (...) {
                                view.displayMessage("Invalid format. Please enter a valid number.");
                            }
                        }

                        view.displayPrompt("Current Note [" + newN + "], New Note: ");
                        std::getline(std::cin, inputStr);
                        if (!inputStr.empty()) newN = inputStr;

                        Transaction updatedTxn(newD, newC, newA, newN);
                        model.editTransaction(editIdx, updatedTxn);
                        
                    } else if (editIdx != 0) {
                        view.displayMessage("Invalid ID. Action canceled.");
                    }
                } 
                else if (subChoice == 2) {
                    // Delete Logic
                    view.displayPrompt("Enter record ID to delete (0 to cancel): ");
                    int deleteIdx;
                    std::cin >> deleteIdx;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (deleteIdx > 0 && deleteIdx <= model.getRecordCount()) {
                        model.removeTransaction(deleteIdx);
                    } else if (deleteIdx != 0) {
                        view.displayMessage("Invalid ID. Action canceled.");
                    }
                }
                break;
            }
            case 3: {
                model.printCategorySummary();
                break;
            }
            case 4: {
                std::string kw = view.promptForKeyword();
                std::vector<Transaction> results = model.searchTransactions(kw);
                view.displayTransactions(results, "Search Results: " + kw);
                break;
            }
            case 5: {
                view.displayMessage("Saving data and shutting down...");
                model.saveToFile("data.csv");
                view.displayMessage("[Success] Data saved. Goodbye!");
                running = false;
                break;
            }
        }
    }
    return 0;
}