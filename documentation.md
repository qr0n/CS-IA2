# Code Documentation

## Introduction
This code is a user authentication and menu management system implemented in C.

## Functions
- `modifyGlobalVariable(char *variablePointer, const char overwriteContent)`: Modifies a global variable with the specified content.
- `credentialsExist(char username[20], char password[20])`: Checks if the provided username and password exist in the user database.
- `makeUser(const char username[20], const char password[20])`: Creates a new user with the provided username and password.
- `login(const char username[20], const char password[20])`: Authenticates the user with the provided username and password.
- `getMenu()`: Displays the menu items and prices.
- `addToMenu(const char item[20], int price)`: Adds a new item with its price to the menu.
- `searchMenu(const char searchPrefix)`: Searches for menu items that start with the specified prefix.
- `sellItem(char, int, int)` : Adds an entry in sales.txt for the item, price and its quantity sold, user face.
- `CLI` : Provides the user with a list of operations.