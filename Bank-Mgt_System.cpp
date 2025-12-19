#include <iostream> // Allows the program to use cout for displaying messages and cin for reading user input.
#include <string> // Enables the use of string variables for customer names, passwords, and other textual data.
#include <ctime> // Provides functions to manipulate date and time, useful for tracking transactions.
#include <cstdlib> // Includes functions for random number generation and memory allocation.
#include <limits> // Provides numeric_limits to validate user input.
#include <vector> // Enables the use of dynamic arrays (vectors) for storing loan reasons.
#include <iomanip> // Provides input/output manipulation.

using namespace std; 

// Custom Stack Class using Array
class CustomStack {
private:
    static const int MAX_SIZE = 100; // Defines the maximum size of the stack.
    string elements[MAX_SIZE]; // Array to hold stack elements (transactions).
    int topIndex; // Index of the top element in the stack.

public:
    CustomStack() : topIndex(-1) {} // Initializes topIndex to -1, indicating an empty stack.

    void push(const string& element) { // Adds an element to the top of the stack.
        if (topIndex >= MAX_SIZE - 1) { // Checks for stack overflow.
            cout << "Stack overflow, unable to push element." << endl; // Notifies user if stack is full.
        } else {
            elements[++topIndex] = element; // Increments topIndex and adds the element to the stack.
        }
    }

    void pop() { // Removes the top element from the stack.
        if (topIndex >= 0) { // Checks if the stack is not empty.
            topIndex--; // Decrements topIndex to remove the top element.
        }
    }

    string top() const { // Returns the top element of the stack without removing it.
        if (topIndex >= 0) {
            return elements[topIndex]; // Returns the top element if the stack is not empty.
        }
        return ""; // Returns an empty string if the stack is empty.
    }

    bool empty() const { // Checks if the stack is empty.
        return topIndex == -1; // Returns true if topIndex is -1, indicating an empty stack.
    }
};

// Custom Queue Class
template<typename T> // Template to allow any data type for the queue.
class CustomQueue {
private:
    struct Node { // Node structure for the queue.
        T data; // Data stored in the node.
        Node* next; // Pointer to the next node.
        Node(const T& value) : data(value), next(nullptr) {} // Constructor to initialize node with value.
    };

    Node* frontNode; // Pointer to the front of the queue.
    Node* rearNode; // Pointer to the rear of the queue.

public:
    CustomQueue() : frontNode(nullptr), rearNode(nullptr) {} // Initializes an empty queue.

    ~CustomQueue() { // Destructor to free memory when the queue is no longer needed.
        while (!empty()) { // Loops until the queue is empty.
            dequeue(); // Removes each node from the queue.
        }
    }

    void enqueue(const T& value) { // Adds an element to the rear of the queue.
        Node* newNode = new Node(value); // Creates a new node with the given value.
        if (rearNode) { // If the queue is not empty.
            rearNode->next = newNode; // Links the new node to the rear.
        }
        rearNode = newNode; // Updates the rear to the new node.
        if (!frontNode) { // If the queue was empty.
            frontNode = rearNode; // Sets the front to the new node.
        }
    }

    void dequeue() { // Removes the front element from the queue.
        if (frontNode) { // If the queue is not empty.
            Node* temp = frontNode; // Temporarily stores the front node.
            frontNode = frontNode->next; // Moves front to the next node.
            if (!frontNode) { // If the queue is now empty.
                rearNode = nullptr; // Sets rear to nullptr.
            }
            delete temp; // Frees the memory of the removed node.
        }
    }

    T front() const { // Returns the front element of the queue without removing it.
        if (frontNode) {
            return frontNode->data; // Returns the data of the front node if the queue is not empty.
        }
        throw runtime_error("Queue is empty"); // Throws an error if the queue is empty.
    }

    bool empty() const { // Checks if the queue is empty.
        return frontNode == nullptr ; // Returns true if frontNode is nullptr, indicating an empty queue.
    }
};

// Loan history node class
class LoanNode {
public:
    double amount; // Amount of the loan.
    string reason; // Reason for the loan.
    string customerName; // Name of the customer requesting the loan.
    int accountNumber; // Account number associated with the loan.
    LoanNode* next; // Pointer to the next loan node in the history.
    LoanNode* prev; // Pointer to the previous loan node in the history.

    LoanNode(double amt, const string& r, const string& name, int accNum) // Constructor to initialize a loan node.
        : amount(amt), reason(r), customerName(name), accountNumber(accNum), next(nullptr), prev(nullptr) {} // Initializes loan details and sets next and prev to nullptr.
};

// Loan history management class
class LoanHistory {
private:
    LoanNode* head; // Pointer to the head of the loan history linked list.

public:
    LoanHistory() : head(nullptr) {} // Initializes an empty loan history.

    void addLoan(double amount, const string& reason, const string& customerName, int accountNumber) { // Adds a new loan to the history.
        LoanNode* newNode = new LoanNode(amount, reason, customerName, accountNumber); // Creates a new loan node.
        if (!head) { // If the loan history is empty.
            head = newNode; // Sets the head to the new node.
        } else {
            LoanNode* temp = head; // Temporary pointer to traverse the list.
            while (temp->next) { // Loops to find the end of the list.
                temp = temp->next; // Moves to the next node.
            }
            temp->next = newNode; // Links the new node at the end of the list.
            newNode->prev = temp; // Sets the previous pointer of the new node.
        }
    }

    void viewLoanHistory() const { // Displays the loan history.
        LoanNode* temp = head; // Temporary pointer to traverse the loan history.
        cout << "\nLoan History:\n"; // Header for loan history display.
        if (!temp) { // If there are no loans in history.
            cout << "No loan history available.\n"; // Notifies the user.
            return; // Exits the function.
        }
        while (temp) { // Loops through the loan history.
            cout << "Account Number: " << temp->accountNumber // Displays account number.
                 << ", Customer Name: " << temp->customerName // Displays customer name.
                 << ", Loan Amount: " << temp->amount // Displays loan amount.
                 << ", Reason: " << temp->reason << endl; // Displays reason for the loan.
            temp = temp->next; // Moves to the next loan node.
        }
    }

    ~LoanHistory() { // Destructor to free memory when the loan history is no longer needed.
        while (head) { // Loops until the loan history is empty.
            LoanNode* temp = head; // Temporarily stores the head node.
            head = head->next; // Moves head to the next node.
            delete temp; // Frees the memory of the removed node.
        }
    }
};

// Bank account class
class Account {
public:
    int accountNumber; // Unique account number for the bank account.
    string customerName; // Name of the account holder.
    double balance; // Current balance of the account.
    CustomStack transactionHistory; // Stack to hold transaction history.
    double loanAmount; // Amount of the loan requested.
    string loanReason; // Reason for the loan request.
    string password; // Password for account access.
    bool loanPending; // Flag to indicate if a loan request is pending.
    LoanHistory loanHistory; // Object to manage loan history.
    time_t lastTransactionTime; // Timestamp of the last transaction.

    Account() : accountNumber(0), balance(0.0), loanAmount(0.0), loanPending(false), lastTransactionTime(time(0)) {} // Default constructor initializes account with default values.

    Account(int accountNumber, const string& customerName, double initialBalance, const string& password) // Parameterized constructor to initialize account with specific values.
        : accountNumber(accountNumber), customerName(customerName), balance(initialBalance),
          transactionHistory(), loanAmount(0.0), loanReason(""), password(password),
          loanPending(false), lastTransactionTime(time(0)) {} // Initializes account details and sets last transaction time.

    bool validatePassword(const string& enteredPassword) { // Validates the entered password against the stored password.
        return enteredPassword == password; // Returns true if passwords match.
    }

    void addTransaction(const 
    string& transaction) { // Adds a transaction to the transaction history.
        lastTransactionTime += rand() % 60 + 1; // Updates the last transaction time with a random increment.
        char buffer[80]; // Buffer to hold the formatted time string.
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&lastTransactionTime)); // Formats the time into a readable string.
        transactionHistory.push(string(buffer) + " - " + transaction); // Pushes the transaction with the timestamp onto the stack.
    }

    void requestLoan(double amount, const string& reason) { // Requests a loan with a specified amount and reason.
        loanAmount = amount; // Sets the loan amount.
        loanReason = reason; // Sets the reason for the loan.
        loanPending = true; // Marks the loan as pending.
        addTransaction("Loan requested: " + to_string(amount) + " for reason: " + reason); // Adds a transaction for the loan request.
        loanHistory.addLoan(amount, reason, customerName, accountNumber); // Adds the loan details to the loan history.
    }

    void clearLoan() { // Clears the loan details.
        loanAmount = 0; // Resets the loan amount.
        loanReason = ""; // Clears the loan reason.
        loanPending = false; // Marks the loan as not pending.
        addTransaction("Loan cleared."); // Adds a transaction for clearing the loan.
    }

    string getLoanDetails() const { // Retrieves the loan details.
        return loanAmount > 0 ? "Loan Amount: " + to_string(loanAmount) + ", Reason: " + loanReason : "No loan requested."; // Returns loan details or a message indicating no loan.
    }

    string getAccountInfo() const { // Retrieves account information.
        string info = "Account Number: " + to_string(accountNumber) + "\nCustomer Name: " + customerName + "\nBalance: " + to_string(balance); // Formats account info.
        if (loanAmount > 0) { // Checks if there is a loan amount.
            info += "\nLoan Amount: " + to_string(loanAmount) + ", Reason: " + loanReason; // Adds loan details to account info.
        }
        return info; // Returns the formatted account information.
    }

    void viewTransactionHistory() const { // Displays the transaction history for the account.
        cout << "\nTransaction History for Account: " << accountNumber << endl; // Header for transaction history.
        if (transactionHistory.empty()) { // Checks if there are no transactions.
            cout << "No transactions yet.\n"; // Notifies the user.
        } else {
            CustomStack temp = transactionHistory; // Creates a temporary stack to display transactions.
            while (!temp.empty()) { // Loops until all transactions are displayed.
                cout << temp.top() << endl; // Displays the top transaction.
                temp.pop(); // Removes the top transaction from the temporary stack.
            }
        }
    }
};

// Binary tree node for storing accounts
class AccountNode {
public:
    Account* account; // Pointer to the account object.
    AccountNode* left; // Pointer to the left child node.
    AccountNode* right; // Pointer to the right child node.

    AccountNode(Account* acc) : account(acc), left(nullptr), right(nullptr) {} // Constructor initializes the account node with a pointer to an account.
};

// Binary search tree for managing accounts
class AccountBinaryTree {
private:
    AccountNode* root; // Pointer to the root of the binary tree.

    void insert(AccountNode*& node, Account* acc) { // Inserts a new account into the binary tree.
        if (node == nullptr) { // If the current node is null.
            node = new AccountNode(acc); // Creates a new account node.
        } else if (acc->accountNumber < node->account->accountNumber) { // If the account number is less than the current node's account number.
            insert(node->left, acc); // Recursively inserts into the left subtree.
        } else {
            insert(node->right, acc); // Recursively inserts into the right subtree.
        }
    }

    Account* search(AccountNode* node, int accountNumber) { // Searches for an account by account number.
        if (node == nullptr) { // If the current node is null.
            return nullptr; // Returns null if the account is not found.
        } else if (node->account->accountNumber == accountNumber) { // If the account number matches.
            return node->account; // Returns the found account.
        } else if (accountNumber < node->account->accountNumber) { // If the account number is less than the current node's account number.
            return search(node->left, accountNumber); // Recursively searches in the left subtree.
        } else {
            return search(node->right, accountNumber); // Recursively searches in the right subtree.
        }
    }

    void inOrderDisplay(AccountNode* node) { // Displays accounts in in-order traversal.
        if (node == nullptr) return; // Base case: if the node is null, return.
        inOrderDisplay(node->left); // Recursively display the left subtree.
        cout << "| Account Number: " << node->account->accountNumber // Displays account number.
             << " | Customer Name: " << node->account->customerName // Displays customer name.
             << " | Balance: " << node->account->balance << " |\n"; // Displays account balance.
        inOrderDisplay(node->right); // Recursively display the right subtree.
    }

public:
    AccountBinaryTree() : root(nullptr) {} // Initializes an empty binary tree.

    void addAccount(Account* acc) { // Adds a new account to the binary tree.
        insert(root, acc); // Calls the insert function starting from the root.
    }

    Account* findAccount(int accountNumber) { // Finds an account by account number.
        return search(root, accountNumber); // Calls the search function starting from the root.
    }

    AccountNode* getRoot() { // Returns the root of the binary tree.
        return root; // Returns the root node.
    }

    void displayAccounts() { // Displays all accounts in the binary tree.
        if (!root) { // Checks if the tree is empty.
            cout << "No accounts available.\n"; // Notifies the user if there are no accounts.
            return; // Exits the function.
        }
        cout << "\n--- Accounts Sorted by Account Number ---\n"; // Header for account display.
        cout << "| Account Number | Customer Name | Balance |\n"; // Column headers.
        cout << "-------------------------------------------\n"; // Separator line.
        inOrderDisplay(root); // Calls in-order display to show accounts.
        cout << "-------------------------------------------\n"; // Separator line.
    }
};

// Bank Management System
class BankManagementSystem {
private:
    AccountBinaryTree accountTree; // Binary tree to manage accounts.
    Account* currentUser  = nullptr; // Pointer to the currently logged-in user.
    string adminPassword = "admin123"; // Hardcoded admin password for access control.

    Account* findAccountByNumber(int accountNumber) { // Finds an account by account number.
        return accountTree.findAccount(accountNumber); // Calls the findAccount method of the binary tree.
    }

public:
    void signup() { // Handles user signup process.
        string name; // Variable to store customer name.
        string password; // Variable to store password.
        double initialBalance; // Variable to store initial balance.

        cout << "Sign Up\n"; // Prompts user for signup.
        cout << "Enter customer name: "; // Asks for customer name.
        cin.ignore(); // Clears the input buffer.
        getline(cin, name); // Reads the full name including spaces.
        if (findAccountByName(name)) { // Checks if an account with this name already exists.
            cout << "An account with this name already exists. Please try logging in.\n"; // Notifies user if account exists.
            return; // Exits the function.
        }
        cout << "Enter initial balance: "; // Asks for initial balance.
        while (!(cin >> initialBalance)) { // Validates input for initial balance.
            cout << "Invalid input. Please enter a valid number for initial balance: "; // Prompts for valid input.
            cin.clear(); // Clears the error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input.
        }
        cin.ignore(); // Clears the input buffer.

        do {
            cout << "Enter password (5 to 8 characters): "; // Prompts for password.
            cin >> password; // Reads password input.

            if (password.length() < 5 || password.length() > 8) { // Validates password length.
                cout << "Password must be between 5 and 8 characters long. Please try again.\n"; // Notifies user of invalid password length.
            }
        } while (password.length() < 5 || password.length() > 8); // Repeats until a valid password is entered.

        int accountNumber = rand() % 9000 + 1000; // Generates a random account number between 1000 and 9999.
        Account* newAccount = new Account(accountNumber, name, initialBalance, password); // Creates a new account object with the provided details.
        accountTree.addAccount(newAccount); // Adds the new account to the binary tree.
        cout << "\nAccount created successfully! Your account number is " << accountNumber << ".\n"; // Confirms account creation and displays account number.
    }

    void login() { // Handles user login process.
        string name; // Variable to store customer name.
        string enteredPassword; // Variable to store entered password.
        cout << "Login\n"; // Prompts user for login.
        cout << "Enter customer name: "; // Asks for customer name.
        cin.ignore(); // Clears the input buffer.
        getline(cin, name); // Reads the full name including spaces.
        Account* acc = findAccountByName(name); // Finds the account by name.
        if (!acc) { // Checks if the account exists.
            cout << "No account found with this name. Please sign up first.\n"; // Notifies user if account is not found.
            return; // Exits the function.
        }
        cout << "Enter password: "; // Prompts for password.
        cin >> enteredPassword; // Reads password input.
        if (acc->validatePassword(enteredPassword)) { // Validates the entered password.
            cout << "Login successful!\n"; // Confirms successful login.
            currentUser  = acc; // Sets the current user to the logged-in account.
            menu(); // Calls the menu function to display user options.
        } else {
            cout << "Incorrect password. Please try again.\n"; // Notifies user of incorrect password.
        }
    }

    void adminLogin() { // Handles admin login process.
        string enteredPassword; // Variable to store entered admin password.
        cout << "Enter admin password: "; // Prompts for admin password.
        cin >> enteredPassword; // Reads admin password input.

        if (enteredPassword == adminPassword) { // Checks if the entered password matches the admin password.
            cout << "Admin login successful!\n"; // Confirms successful admin login.
            adminMenu(); // Calls the admin menu function to display admin options.
        } else {
            cout << "Incorrect password. Admin login failed.\n"; // Notifies user of incorrect admin password.
        }
    }

    void adminMenu() { // Displays the admin menu for managing accounts.
        int choice; // Variable to store admin menu choice.
        do {
            cout << "\n--- Admin Menu ---\n"; // Header for admin menu.
            cout << "1. View All Accounts \n"; // Option to view all accounts.
            cout << "2. Search Account \n"; // Option to search for a specific account.
            cout << "3. View Loan History\n"; // Option to view loan history of accounts.
            cout << "4. Logout\n"; // Option to log out of the admin menu.
            cout << "Enter your choice: "; // Prompts for admin choice.
            cin >> choice; // Reads the admin's choice.
            switch (choice) { // Switch statement to handle admin menu options.
                case 1:
                    cout << "\n--- All Accounts ---\n"; // Header for displaying all accounts.
                    accountTree.displayAccounts(); // Calls the displayAccounts method to show all accounts.
                    break;
                case 2: {
                    int accountNumber; // Variable to store account number for search.
                    cout << "Enter account number to search: "; // Prompts for account number.
                    cin >> accountNumber; // Reads the account number.
                    Account* acc = findAccountByNumber(accountNumber); // Finds the account by number.
                    if (acc) {
                        cout << acc->getAccountInfo() << endl; // Displays account information if found.
                    } else {
                        cout << "Account not found.\n"; // Notifies if account is not found.
                    }
                    break;
                }
                case 3: {
                    int subChoice; // Variable to store sub-choice for loan history.
                    cout << "\n--- View Loan History ---\n"; // Header for loan history options.
                    cout << "1. View by Account Number\n"; // Option to view loan history by account number.
                    cout << "2. View All Customers' Loan History\n"; // Option to view all loan histories.
                    cout << "Enter your choice: "; // Prompts for sub-choice.
                    cin >> subChoice; // Reads the sub-choice.

                    if (subChoice == 1) { // If user chooses to view by account number.
                        int accountNumber; // Variable to store account number.
                        cout << "Enter account number to view loan history: "; // Prompts for account number.
                        cin >> accountNumber; // Reads the account number.
                        Account* acc = findAccountByNumber(accountNumber); // Finds the account by number.
                        if (acc) {
                            acc->loanHistory.viewLoanHistory(); // Displays loan history for the found account.
                        } else {
                            cout << "Account not found.\n"; // Notifies if account is not found.
                        }
                    } else if (subChoice == 2) { // If user chooses to view all loan histories.
                        viewAllLoanDetails(); // Calls method to display all loan details.
                        char searchChoice; // Variable to store choice for searching specific loan history.
                        cout << "Do you want to search for a specific account's loan history? (y/n): "; // Prompts for search choice.
                        cin >> searchChoice; // Reads the search choice.
                        if (searchChoice == 'y' || searchChoice == 'Y') { // If user wants to search.
                            int accountNumber; // Variable to store account number.
                            cout << "Enter account number to view loan history: "; // Prompts for account number.
                            cin >> accountNumber; // Reads the account number.
                            Account* acc = findAccountByNumber(accountNumber); // Finds the account by number.
                            if (acc) {
                                acc->loanHistory.viewLoanHistory(); // Displays loan history for the found account.
                            } else {
                                cout << "Account not found.\n"; // Notifies if account is not found.
                            }
                        }
                    } else {
                        cout << "Invalid choice. Please try again.\n"; // Notifies if invalid choice is made.
                    }
                    break;
                }
                case 4:
                    cout << "Logging out...\n"; // Notifies admin of logout.
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n"; // Notifies if invalid choice is made.
            }
        } while (choice != 4); // Repeats until admin chooses to log out.
    }

    void deposit() { // Handles deposit process for the current user.
        if (!currentUser ) { // Checks if a user is logged in.
            cout << "Please log in to deposit funds.\n"; // Notifies user to log in.
            return; // Exits the function.
        }
        int accountNumber; // Variable to store account number.
        double amount; // Variable to store deposit amount.
        cout << "Enter account number: "; // Prompts for account number.
        while (!(cin >> accountNumber)) { // Validates input for account number.
            cout << "Invalid input. Please enter a number for account number: "; // Prompts for valid input.
            cin.clear(); // Clears the error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input.
        }
        if (currentUser ->accountNumber != accountNumber) { // Checks if the entered account number matches the current user's account.
            cout << "Error: You can only deposit into your own account.\n"; // Notifies user of the error.
            return; // Exits the function.
        }
        cout << "Enter amount to deposit: "; // Prompts for deposit amount.
        while (!(cin >> amount) || amount <= 100) { // Validates input for deposit amount.
            cout << "Invalid input or amount too low. Please enter an amount greater than 100: "; // Prompts for valid input.
            cin.clear(); // Clears the error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input.
        }
        currentUser ->balance += amount; // Updates the current user's balance with the deposit amount.
        currentUser ->addTransaction("Deposit: " + to_string(amount)); // Adds a transaction record for the deposit.
        cout << "Deposited " << amount << " to account " << accountNumber << ".\n"; // Confirms the deposit.
        cout << "Current balance: " << currentUser ->balance << ".\n"; // Displays the updated balance.
    }

    void withdraw() { // Handles withdrawal process for the current user.
        if (!currentUser ) { // Checks if a user is logged in.
            cout << "Please log in to withdraw funds.\n"; // Notifies user to log in.
            return; // Exits the function.
        }
        int accountNumber; // Variable to store account number.
        double amount; // Variable to store withdrawal amount.
        string enteredPassword; // Variable to store entered password.
        cout << "Enter account number: "; // Prompts for account number.
        while (!(cin >> accountNumber)) { // Validates input for account number.
            cout << "Invalid input. Please enter a number for account number: "; // Prompts for valid input.
            cin.clear(); // Clears the error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input.
        }
        if (currentUser ->accountNumber != accountNumber) { // Checks if the entered account number matches the current user's account.
            cout << "Error: You can only withdraw from your own account.\n"; // Notifies user of the error.
            return; // Exits the function.
        }
        cout << "Enter password: "; // Prompts for password.
        cin >> enteredPassword; // Reads password input.
        if (!currentUser ->validatePassword(enteredPassword)) { // Validates the entered password.
            cout << "Incorrect password. Withdrawal denied.\n"; // Notifies user of incorrect password.
            return; // Exits the function.
        }
        cout << "Enter amount to withdraw: "; // Prompts for withdrawal amount.
        while (!(cin >> amount) || amount <= 100) { // Validates input for withdrawal amount.
            cout << "Invalid input or amount too low. Please enter an amount greater than 100: "; // Prompts for valid input.
            cin.clear(); // Clears the error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input.
        }
        if (currentUser ->balance >= amount) { // Checks if the current balance is sufficient for the withdrawal.
            currentUser ->balance -= amount; // Deducts the withdrawal amount from the current balance.
            currentUser ->addTransaction("Withdraw: " + to_string(amount)); // Adds a transaction record for the withdrawal.
            cout << "Withdrew " << amount << " from account " << accountNumber << ".\n"; // Confirms the withdrawal.
            cout << "Current balance: " << currentUser ->balance << ".\n"; // Displays the updated balance.
        } else {
            cout << "Insufficient funds.\n"; // Notifies user of insufficient funds for the withdrawal.
        }
    }

    void requestLoan() { // Handles loan request process for the current user.
        if (!currentUser ) { // Checks if a user is logged in.
            cout << "Please log in to request a loan.\n"; // Notifies user to log in.
            return; // Exits the function.
        }

        int accountNumber; // Variable to store account number.
        double loanAmount; // Variable to store requested loan amount.
        string reason; // Variable to store reason for the loan.
        vector<string> loanReasons = { // Vector to store predefined loan reasons.
            "Medical Emergency", // Reason option 1.
            "Education", // Reason option 2.
            "Home Renovation", // Reason option 3.
            "Business Investment", // Reason option 4.
            "Car Purchase" // Reason option 5.
        };

        cout << "Enter account number: "; // Prompts for account number.
        while (!(cin >> accountNumber)) { // Validates input for account number.
            cout << "Invalid input. Please enter a number for account number: "; // Prompts for valid input.
            cin.clear(); // Clears the error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input.
        }

        if (currentUser ->accountNumber != accountNumber) { // Checks if the entered account number matches the current user's account.
            cout << "Error: You can only request a loan for your own account.\n"; // Notifies user of the error.
            return; // Exits the function.
        }

        cout << "Enter password: "; // Prompts for password.
        string enteredPassword; // Variable to store entered password.
        cin >> enteredPassword; // Reads password input.

        if (!currentUser ->validatePassword(enteredPassword)) { // Validates the entered password.
            cout << "Incorrect password. Loan request denied.\n"; // Notifies user of incorrect password.
            return; // Exits the function.
        }

        cout << "Select a reason for the loan:\n"; // Prompts for loan reason selection.
        for (size_t i = 0; i < loanReasons.size(); ++i) { // Loops through loan reasons.
            cout << i + 1 << ". " << loanReasons[i] << endl; // Displays each loan reason with a corresponding number.
        }

        int reasonChoice; // Variable to store user's choice of loan reason.
        cout << "Enter the number corresponding to your reason: "; // Prompts for reason choice.
        while (!(cin >> reasonChoice) || reasonChoice < 1 || reasonChoice > static_cast<int>(loanReasons.size())) { // Validates reason choice.
            cout << "Invalid choice. Please select a valid option: "; // Prompts for valid input.
            cin.clear(); // Clears the error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input.
        }

        reason = loanReasons[reasonChoice - 1]; // Sets the reason based on user's choice.

        cout << "Enter loan amount: "; // Prompts for loan amount.
        while (!(cin >> loanAmount)) { // Validates input for loan amount.
            cout << "Invalid input. Please enter a valid number for loan amount: "; // Prompts for valid input.
            cin.clear(); // Clears the error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores invalid input.
        }

        // Loan approval logic
        if (currentUser ->balance < 50000 && loanAmount <= 100000) { // Checks if balance is less than 50,000 and loan amount is within limit.
            currentUser ->loanAmount = loanAmount; // Sets the loan amount for the current user.
            currentUser ->loanReason = reason; // Sets the loan reason for the current user.
            currentUser ->loanPending = true; // Marks the loan as pending.

            // Add loan to loan history
            currentUser ->loanHistory.addLoan(loanAmount, reason, currentUser ->customerName, currentUser ->accountNumber); // Adds the loan details to the user's loan history.
            cout << "Loan approved for " << loanAmount << " with reason: " << reason << ".\n"; // Confirms loan approval.
        } else if (currentUser ->balance >= 50000 && currentUser ->balance <= 100000 && loanAmount <= 8000) { // Checks if balance is between 50,000 and 100,000 and loan amount is within limit.
            currentUser ->loanAmount = loanAmount; // Sets the loan amount for the current user.
            currentUser ->loanReason = reason; // Sets the loan reason for the current user.
            currentUser ->loanPending = true; // Marks the loan as pending.

            // Add loan to loan history
            currentUser ->loanHistory.addLoan(loanAmount, reason, currentUser ->customerName, currentUser ->accountNumber); // Adds the loan details to the user's loan history.
            cout << "Loan request approved for " << loanAmount << " with reason: " << reason << ".\n"; // Confirms loan approval.
        } else {
            cout << "Loan request denied. Reason: Requested amount exceeds the allowed limit for your balance range.\n"; // Notifies user of loan denial.
        }
    }

    void viewLoanDetails() { // Handles viewing loan details for the current user.
        if (!currentUser ) { // Checks if a user is logged in.
            cout << "Please log in to view loan details.\n"; // Notifies user to log in.
            return; // Exits the function.
        }
        cout << currentUser ->getLoanDetails() << endl; // Displays the loan details for the current user.
    }

    void viewAllLoanDetails() { // Handles viewing loan details for all customers.
        CustomQueue<AccountNode*> q; // Creates a queue to traverse the account binary tree.
        AccountNode* root = accountTree.getRoot(); // Gets the root of the account binary tree.
        if (!root) { // Checks if the tree is empty.
            cout << "No accounts available.\n"; // Notifies user if there are no accounts.
            return; // Exits the function.
        }
        q.enqueue(root); // Enqueues the root node for traversal.
        cout << "\n--- Loan Details of All Customers ---\n"; // Header for loan details display.
        while (!q.empty()) { // Loops until all nodes are processed.
            AccountNode* current = q.front(); // Gets the front node from the queue.
            q.dequeue(); // Dequeues the front node.
            if (current && current->account) { // Checks if the current node and account are valid.
                string loanDetails = current->account->getLoanDetails(); // Retrieves loan details for the current account.
                cout << "Account Number: " << current->account->accountNumber << "\n"; // Displays account number.
                cout << "Customer Name: " << current->account->customerName << "\n"; // Displays customer name.
                cout << "Loan Details: " << loanDetails << "\n"; // Displays loan details.
                cout << "---------------------------------------\n"; // Separator line for clarity.
            }
            if (current->left) q.enqueue(current->left); // Enqueues the left child if it exists.
            if (current->right) q.enqueue(current->right); // Enqueues the right child if it exists.
        }
    }

    void menu() { // Displays the main menu for the current user.
        if (!currentUser ) { // Checks if a user is logged in.
            cout << "Please log in first to access the menu.\n"; // Notifies user to log in.
            return; // Exits the function.
        }
        int choice; // Variable to store user's menu choice.
        do {
            cout << "\n--- Menu ---\n"; // Header for user menu.
            cout << "1. View Account Info\n"; // Option to view account information.
            cout << "2. Deposit\n"; // Option to deposit funds.
            cout << "3. Withdraw\n"; // Option to withdraw funds.
            cout << "4. Request Loan\n"; // Option to request a loan.
            cout << "5. View Loan Details\n"; // Option to view loan details.
            cout << "6. View Transaction History\n"; // Option to view transaction history.
            cout << "7. Logout\n"; // Option to log out.
            cout << "Enter your choice: "; // Prompts for user choice.

            cin >> choice; // Reads the user's choice.
            switch (choice) { // Switch statement to handle user menu options.
                case 1:
                    cout << "\n*****VIEW ACCOUNT INFO*****\n";
                    cout << currentUser ->getAccountInfo() << endl; // Displays the account information of the current user.
                    break; // Ends case 1.
                case 2:
                    cout << "\n*****DEPOSIT*****\n"; // Header for deposit section.
                    deposit(); // Calls the deposit function to handle deposit process.
                    break; // Ends case 2.
                case 3:
                    cout << "\n*****WITHDRAW*****\n"; // Header for withdrawal section.
                    withdraw(); // Calls the withdraw function to handle withdrawal process.
                    break; // Ends case 3.
                case 4:
                    cout << "\n*****REQUEST LOAN*****\n"; // Header for loan request section.
                    requestLoan(); // Calls the requestLoan function to handle loan requests.
                    break; // Ends case 4.
                case 5:
                    cout << "\n*****VIEW LOAN DETAILS*****\n"; // Header for viewing loan details.
                    viewLoanDetails(); // Calls the viewLoanDetails function to display loan information.
                    break; // Ends case 5.
                case 6:
                    cout << "\n*****VIEW TRANSACTION HISTORY*****\n"; // Header for transaction history section.
                    currentUser ->viewTransactionHistory(); // Calls the viewTransactionHistory function to display transaction history.
                    break; // Ends case 6.
                case 7:
                    currentUser  = nullptr; // Logs out the current user by setting currentUser  to nullptr.
                    cout << "\n*****LOGOUT SUCCESSFUL*****\n"; // Confirms successful logout.
                    break; // Ends case 7.
                default:
                    cout << "\nInvalid choice. Please try again.\n"; // Notifies user of invalid choice.
            }
        } while (choice != 7); // Repeats until the user chooses to log out.
    }

private:
    Account* findAccountByName(const string& name) { // Finds an account by customer name.
        CustomQueue<AccountNode*> q; // Creates a queue to traverse the account binary tree.
        AccountNode* root = accountTree.getRoot(); // Gets the root of the account binary tree.
        if (root) q.enqueue(root); // Enqueues the root node for traversal.
        while (!q.empty()) { // Loops until all nodes are processed.
            AccountNode* current = q.front(); // Gets the front node from the queue.
            q.dequeue(); // Dequeues the front node.
            if (current && current->account && current->account->customerName == name) { // Checks if the current node and account are valid and if the name matches.
                return current->account; // Returns the found account.
            }
            if (current && current->left) q.enqueue(current->left); // Enqueues the left child if it exists.
            if (current && current->right) q.enqueue(current->right); // Enqueues the right child if it exists.
        }
        return nullptr; // Returns nullptr if no account is found with the given name.
    }
};

int main() { // Main function where the program execution starts.
    cout << "Starting Bank Management System..." << endl;
    srand(static_cast<unsigned>(time(0))); // Seeds the random number generator with the current time.
    cout << "Creating BankManagementSystem object..." << endl;
    BankManagementSystem bms; // Creates an instance of the BankManagementSystem class.
    cout << "Ready!" << endl;
    int choice; // Variable to store user's choice for the main menu.
    do {
        cout << "\n--- Bank Management System ---\n"; // Header for the bank management system.
        cout << "1. Sign Up\n"; // Option for user signup.
        cout << "2. Login\n"; // Option for user login.
        cout << "3. Admin Login\n"; // Option for admin login.
        cout << "4. Exit\n"; // Option to exit the program.
        cout << "Enter your choice: "; // Prompts for user choice.
        cin >> choice; // Reads the user's choice.
        switch (choice) { // Switch statement to handle main menu options.
            case 1:
                bms.signup(); // Calls the signup function to handle user registration.
                break; // Ends case 1.
            case 2:
                bms.login(); // Calls the login function to handle user login.
                break; // Ends case 2.
            case 3:
                bms.adminLogin(); // Calls the adminLogin function to handle admin login.
                break; // Ends case 3.
            case 4:
                cout << "Exiting...\n"; // Notifies user of program exit.
                break; // Ends case 4.
            default:
                cout << "Invalid choice. Please try again.\n"; // Notifies user of invalid choice.
        }
    } while (choice != 4); // Repeats until the user chooses to exit.

    return 0; // Returns 0 to indicate successful program termination.

}
