# C++ Expense Tracker 

C++ CLI expense tracker built with MVC architecture, ensuring a clean separation of business logic and user interface.

##  Features
* **Transaction Management:** Add, edit, and delete daily income and expense records with ease.
* **Smart Search:** Quickly locate specific transactions by searching keywords within categories or notes.
* **Auto-Sorting:** Automatically organizes all historical records chronologically by date.
* **Financial Summary:** Generates a clear report calculating the total amount spent or earned per category.
* **Persistent Data:** Automatically saves and loads your ledger data from a local `data.csv` file.

##  Project Structure
```text
MyAccountingApp/
├── include/
│   ├── Transaction.hpp   # Data model representing a single record
│   ├── Ledger.hpp        # Model layer managing business logic & File I/O
│   └── View.hpp          # View layer handling CLI input/output and menus
├── src/
│   ├── Transaction.cpp
│   ├── Ledger.cpp
│   ├── View.cpp
│   └── main.cpp          # Controller layer tying Model and View together
├── data.csv              # Auto-generated database file
└── .gitignore
```

## 🚀 How to Run

**1. Clone the repository:**
```bash
git clone [https://github.com/HsuehYu1027/MyAccountingApp.git](https://github.com/HsuehYu1027/MyAccountingApp.git)
cd MyAccountingApp