# Library Management System

This project is a Library Management System built using the Qt framework and C++. It provides a GUI for managing books in a library, with functionalities for adding, searching, filtering, and removing books. The system also includes user authentication with admin and user roles.

## Features

### Admin and User Roles
- **Admins** can add, search, filter, and remove books.
- **Users** can only search and filter books.

### User Authentication
- Simple login system with admin and user roles.

### Persistent Storage
- Books are stored in a JSON file (`books.json`), ensuring data is saved between sessions.

### Memento Design Pattern
- Save and restore user login details for convenience.

## Technologies Used
- **Qt Framework**: For building the GUI.
- **C++**: For backend logic.
- **JSON**: For storing book data and user login details.

## Getting Started

### Prerequisites
- Qt 5 or higher
- C++ compiler (e.g., g++, clang)

