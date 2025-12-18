# Bank Management System

A comprehensive console-based banking application developed in C++ that implements advanced data structures and algorithms to manage banking operations efficiently.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Data Structures Implemented](#data-structures-implemented)
- [System Requirements](#system-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Functionality](#functionality)
- [Project Structure](#project-structure)
- [Security](#security)
- [Contributors](#contributors)

## Overview

This Bank Management System is a robust application designed to simulate real-world banking operations. Built with object-oriented programming principles and custom implementations of fundamental data structures, this project demonstrates proficiency in C++ programming, algorithm design, and system architecture.

## Features

### Customer Features
- **Account Management**: Create new accounts with secure password protection
- **Authentication**: Secure login system with password validation
- **Transactions**: Deposit and withdraw funds with transaction validation
- **Loan Services**: Request loans based on account balance criteria
- **Transaction History**: View complete history of all account activities
- **Account Information**: Access detailed account information and balance

### Administrative Features
- **Account Overview**: View all customer accounts sorted by account number
- **Account Search**: Search for specific accounts using account numbers
- **Loan Management**: Monitor and review loan history for individual or all customers
- **System Access**: Secure admin authentication for privileged operations

## Data Structures Implemented

This project showcases custom implementations of several fundamental data structures:

### 1. **Stack (Array-Based)**
- Manages transaction history using LIFO principle
- Stores chronological transaction records
- Maximum capacity of 100 transactions per account

### 2. **Queue (Linked List-Based)**
- Template-based implementation for type flexibility
- Used for level-order tree traversal
- Efficient enqueue and dequeue operations

### 3. **Binary Search Tree (BST)**
- Stores and organizes customer accounts
- Enables efficient account searching by account number
- Supports in-order traversal for sorted account display

### 4. **Doubly Linked List**
- Manages comprehensive loan history
- Allows bidirectional traversal of loan records
- Maintains detailed loan information for each customer

## System Requirements

- **Compiler**: C++11 compatible compiler (GCC, Clang, MSVC)
- **Operating System**: Windows, Linux, or macOS
- **Memory**: Minimum 2MB RAM
- **Dependencies**: Standard C++ libraries only

## Installation

1. Clone or download the project files
2. Navigate to the project directory
3. Compile the program using your preferred C++ compiler:

```bash
g++ final.cpp -o BankManagementSystem
```

4. Run the executable:

```bash
# Windows
BankManagementSystem.exe

# Linux/macOS
./BankManagementSystem
```

## Usage

### Initial Setup

Upon launching the application, you'll be presented with the main menu:

```
--- Bank Management System ---
1. Sign Up
2. Login
3. Admin Login
4. Exit
```

### Creating an Account

1. Select option `1` for Sign Up
2. Enter your name
3. Provide an initial deposit amount
4. Create a password (5-8 characters)
5. Your account number will be automatically generated

### User Login

1. Select option `2` for Login
2. Enter your registered name
3. Enter your password
4. Access your personal banking menu

### Admin Access

- Select option `3` for Admin Login
- Default admin password: `admin123`
- Access administrative functions

## Functionality

### Customer Operations

#### 1. View Account Information
- Display account number, customer name, and current balance
- Show active loan details if applicable

#### 2. Deposit Funds
- Minimum deposit: $100
- Real-time balance updates
- Transaction logging with timestamps

#### 3. Withdraw Funds
- Minimum withdrawal: $100
- Password verification required
- Balance validation before processing

#### 4. Request Loan
Select from predefined loan purposes:
- Medical Emergency
- Education
- Home Renovation
- Business Investment
- Car Purchase

**Loan Approval Criteria:**
- Balance < $50,000: Eligible for loans up to $100,000
- Balance $50,000 - $100,000: Eligible for loans up to $8,000

#### 5. View Transaction History
- Complete chronological record of all transactions
- Timestamped entries for each operation
- Deposits, withdrawals, and loan activities

### Administrative Operations

#### 1. View All Accounts
- Sorted display of all registered accounts
- Shows account number, customer name, and balance
- In-order BST traversal for sorted output

#### 2. Search Account
- Search by account number
- Display complete account information
- Quick O(log n) search complexity

#### 3. View Loan History
- Individual account loan history
- System-wide loan overview
- Detailed loan records with reasons and amounts

## Project Structure

```
Bank Management System
│
├── Custom Data Structures
│   ├── CustomStack (Array-based)
│   ├── CustomQueue (Template-based linked list)
│   ├── AccountBinaryTree (BST)
│   └── LoanHistory (Doubly linked list)
│
├── Core Classes
│   ├── Account (Customer account management)
│   ├── AccountNode (BST node structure)
│   ├── LoanNode (Loan record structure)
│   └── BankManagementSystem (Main system controller)
│
└── Main Functions
    ├── Authentication (Login/Signup)
    ├── Transaction Processing
    ├── Loan Management
    └── Administrative Controls
```

## Security

- **Password Protection**: All accounts require 5-8 character passwords
- **Transaction Verification**: Password required for withdrawals
- **Admin Authentication**: Separate admin credentials for privileged access
- **Account Isolation**: Users can only access their own accounts
- **Input Validation**: Comprehensive input checking to prevent errors

## Technical Highlights

- **Object-Oriented Design**: Encapsulation, inheritance, and polymorphism
- **Template Programming**: Generic queue implementation
- **Memory Management**: Proper allocation and deallocation
- **Error Handling**: Input validation and exception handling
- **Time Complexity**: Optimized operations using appropriate data structures
- **Code Documentation**: Comprehensive inline comments

## Future Enhancements

Potential improvements for future versions:
- Database integration for persistent storage
- Multi-threading for concurrent transactions
- Enhanced security with encryption
- Transfer between accounts functionality
- Interest calculation for savings accounts
- GUI implementation
- File-based data persistence

## Contributors

Developed as part of 3rd Semester C++ coursework.

---

**Note**: This is an educational project designed to demonstrate data structure implementation and banking system logic. It is not intended for production use.
