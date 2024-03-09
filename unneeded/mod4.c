#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_ITEM_NAME_LENGTH 20
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

struct MenuItem {
    char name[MAX_ITEM_NAME_LENGTH];
    int price;
    int quantity;
};

struct SalesRecord {
    char item[MAX_ITEM_NAME_LENGTH];
    int price;
    int quantity;
};

FILE* userdb;
FILE* menudb;
FILE* counterdb;

char current_username[MAX_USERNAME_LENGTH];

// Function to check if input is a valid integer
int isValidInt(char input[]) {
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return 0; // Not a valid integer
        }
    }
    return 1; // Valid integer
}

// Function to validate username and password length
int isValidCredentials(char username[], char password[]) {
    return (strlen(username) > 4 && strlen(username) <= MAX_USERNAME_LENGTH &&
            strlen(password) > 4 && strlen(password) <= MAX_PASSWORD_LENGTH);
}

// Takes 2 arguments `username` and `password` opens user file
// And checks if credentials input are correct returns 1 upon success
int credentialsExist(char username[MAX_USERNAME_LENGTH], char password[MAX_PASSWORD_LENGTH]) {
    if (!isValidCredentials(username, password)) {
        printf("Invalid credentials. Username and password must not be empty and should be less than or equal to %d characters.\n", MAX_USERNAME_LENGTH);
        return 0;
    }

    char user[50];
    char pass[20];
    char fp[40];
    sprintf(fp, "%s/%s.txt", "F:/projects/compsci/db/users", username);

    userdb = fopen(fp, "r");
    if (userdb == NULL) {
        perror("Error opening user file");
        return 0;
    }

    while (fscanf(userdb, "%s %s", user, pass) == 2) {
        if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
            fclose(userdb);
            return 1;
        }
    }
    fclose(userdb);
    return 0;
}

// Takes 2 arguments `username` and `password` calls credentialsExist and passes arguments
int login(char username[MAX_USERNAME_LENGTH], char password[MAX_PASSWORD_LENGTH]) {
    if (credentialsExist(username, password)) {
        return 1;
    } else {
        printf("You input the wrong credentials, please check again or ensure that your userfile is created.\n");
        return 0;
    }
}

// Returns current menu to user through stdout
void getMenu() {
    struct MenuItem {
        char name[MAX_ITEM_NAME_LENGTH];
        int price;
        int quantity;
    } menu_item;
    menudb = fopen("F:/projects/compsci/db/menu.txt", "r");

    if (menudb == NULL) {
        perror("Error opening menu file");
        return;
    }

    while (fscanf(menudb, "%s %d %d", menu_item.name, &menu_item.price, &menu_item.quantity) == 3) {
        printf("Item: %s, Price: $%d, Quantity: %d\n", menu_item.name, menu_item.price, menu_item.quantity);
    }

    fclose(menudb);
}

// Adds an item to the menu along with price and quantity
void addToMenu() {
    struct MenuItem {
        char name[MAX_ITEM_NAME_LENGTH];
        int price;
        int quantity;
    } new_item;

    printf("What would you like to add to the menu?\n> ");
    scanf("%19s", new_item.name);

    printf("What is the price of this item?\n> ");
    char priceInput[20];
    scanf("%19s", priceInput);
    if (!isValidInt(priceInput)) {
        printf("Invalid price input. Please enter a valid integer.\n");
        return;
    }
    new_item.price = atoi(priceInput);

    printf("How much of this item are you adding?\n> ");
    char quantityInput[20];
    scanf("%19s", quantityInput);
    if (!isValidInt(quantityInput)) {
        printf("Invalid quantity input. Please enter a valid integer.\n");
        return;
    }
    new_item.quantity = atoi(quantityInput);

    menudb = fopen("F:/projects/compsci/db/menu.txt", "a");
    fprintf(menudb, "%s %d %d", new_item.name, new_item.price, new_item.quantity);
    fclose(menudb);
}

// Accepts search prefix and indexes menu file based off of item
// And returns item name & item price formatted
int searchMenu() {
    char i_searchPrefix[20];
    printf("Enter search prefix\n> ");
    scanf("%19s", i_searchPrefix);

    FILE *menudb = fopen("F:/projects/compsci/db/menu.txt", "r");
    if (menudb == NULL) {
        perror("Error opening menu file");
        return -1; // Indicate failure
    }

    struct MenuItem {
        char name[MAX_ITEM_NAME_LENGTH];
        int price;
        int quantity;
    } menu_item;

    int matchCount = 0;

    while (fscanf(menudb, "%19s %d %d", menu_item.name, &menu_item.price, &menu_item.quantity) == 3) {
        if (strncmp(menu_item.name, i_searchPrefix, strlen(i_searchPrefix)) == 0) {
            printf("Item: %s, Price: $%d, Quantity: %d\n", menu_item.name, menu_item.price, menu_item.quantity);
            matchCount++;
        }
    }

    fclose(menudb);

    return matchCount;
}

// Accepts item name, price and quantity sold and appends it to a database
void sellItem() {
    struct MenuItem {
        char name[MAX_ITEM_NAME_LENGTH];
        int price;
        int quantity;
    } menu_item;

    struct SalesRecord {
        char item[MAX_ITEM_NAME_LENGTH];
        int price;
        int quantity;
    } sold_item;

    printf("What item does the student want to purchase?\n> ");
    scanf("%19s", sold_item.item);

    FILE *menudb = fopen("F:/projects/compsci/db/menu.txt", "r");
    if (menudb == NULL) {
        perror("Error opening menu file");
        return;
    }

    // Check if the item is in the menu
    int itemFound = 0;
    while (fscanf(menudb, "%19s %d %d", menu_item.name, &menu_item.price, &menu_item.quantity) == 3) {
        if (strcmp(menu_item.name, sold_item.item) == 0) {
            itemFound = 1;
            break;
        }
    }

    fclose(menudb);

    if (!itemFound) {
        printf("Item not found in the menu.\n");
        return;
    }

    printf("How many of these are you selling?\n> ");
    char quantityInput[20];
    scanf("%19s", quantityInput);
    if (!isValidInt(quantityInput)) {
        printf("Invalid quantity input. Please enter a valid integer.\n");
        return;
    }
    sold_item.quantity = atoi(quantityInput);

    if (sold_item.quantity <= 0) {
        printf("Invalid quantity.\n");
        return;
    }

    // Check if there is enough stock
    if (menu_item.quantity < sold_item.quantity) {
        printf("Not enough stock available for %s.\n", sold_item.item);
        return;
    }

    // Deduct from the stock
    int new_item_quantity = menu_item.quantity - sold_item.quantity;

    // Update the menu file with the new stock
    menudb = fopen("F:/projects/compsci/db/menu.txt", "r");
    FILE *tempdb = fopen("F:/projects/compsci/db/temp_menu.txt", "w");

    while (fscanf(menudb, "%19s %d %d", menu_item.name, &menu_item.price, &menu_item.quantity) == 3) {
        if (strcmp(menu_item.name, sold_item.item) == 0) {
            fprintf(tempdb, "%s %d %d\n", menu_item.name, menu_item.price, new_item_quantity);
        } else {
            fprintf(tempdb, "%s %d %d\n", menu_item.name, menu_item.price, menu_item.quantity);
        }
    }

    fclose(menudb);
    fclose(tempdb);

    remove("F:/projects/compsci/db/menu.txt");
    rename("F:/projects/compsci/db/temp_menu.txt", "F:/projects/compsci/db/menu.txt");

    // Add the sale to the sales records
    FILE *counterdb = fopen("F:/projects/compsci/db/sales.txt", "a");
    fprintf(counterdb, "%s %d %d\n", sold_item.item, menu_item.price, sold_item.quantity);
    fclose(counterdb);

    printf("Sale recorded successfully.\n");
}

// Calculates every item sold along with money made and price it was sold for
void calculateSoldItem() {
    struct SalesRecord sold_item;

    FILE* counterdb = fopen("F:/projects/compsci/db/sales.txt", "r");
    if (counterdb == NULL) {
        perror("Error opening sales file");
        return;
    }

    // Use arrays to store information for each unique item
    char items[100][50];
    int quantities[100] = {0}; // Initialize quantities to zero
    int prices[100];
    int count = 0;

    while (fscanf(counterdb, "%s %d %d", sold_item.item, &sold_item.price, &sold_item.quantity) == 3) {
        int index = -1;

        // Check if the item is already in the array
        for (int i = 0; i < count; i++) {
            if (strcmp(items[i], sold_item.item) == 0) {
                index = i;
                break;
            }
        }

        // If the item is not in the array, add it
        if (index == -1) {
            strcpy(items[count], sold_item.item);
            quantities[count] = sold_item.quantity;
            prices[count] = sold_item.price;
            count++;
        } else {
            // If the item is already in the array, update the quantity
            quantities[index] += sold_item.quantity;
        }
    }

    fclose(counterdb);

    // Print the consolidated information
    for (int i = 0; i < count; i++) {
        int money_made = prices[i] * quantities[i];
        printf("Item: %s, Price per unit: $%d, Total Quantity: %d, Total Money made from item: $%d\n",
               items[i], prices[i], quantities[i], money_made);
    }
}

// Prompt for user to select action 1-6
void CLI(char *username, int reinit) {
    int i_operation;

    if (reinit) {
        printf("Welcome %s, what would you like to do today?\n", username);
    }

    printf("[1] Get the current menu\n");
    printf("[2] Add an item to the menu\n");
    printf("[3] Search the menu for a specific item\n");
    printf("[4] Sell an item\n");
    printf("[5] Calculate amount of item sold\n");
    printf("[6] Exit the program\n");
    printf("Please enter the number correlated to your option of choice.\n> ");
    scanf("%d", &i_operation);

    switch (i_operation) {
        case 1:
            getMenu();
            CLI("", 0);
            break;

        case 2:
            addToMenu();
            CLI("", 0);
            break;

        case 3:
            int result = searchMenu();
            if (result == -1) {
                printf("Failed to open menu file.\n");
            } else {
                printf("Found %d matching items.\n", result);
            }
            CLI("", 0);
            break;

        case 4:
            sellItem();
            CLI("", 0);
            break;

        case 5:
            calculateSoldItem();
            CLI("", 0);
            break;

        case 6:
            break;
        default:
        printf("Error invalid input, please pick another (1-6)");
        CLI("", 0);
            break;
    }
}

// Accepts username and password for new user to be made in the system
void makeUser() {
    char fp[100]; // file path
    char fc[80]; // file content

    char i_username[MAX_USERNAME_LENGTH];
    char i_password[MAX_PASSWORD_LENGTH];

    // Get the username
    printf("Enter the username of the user you'd like to create\n> ");
    scanf("%19s", i_username);

    // Check the validity of the username
    if (strlen(i_username) < 4 || strlen(i_username) > MAX_USERNAME_LENGTH) {
        printf("Invalid username. Username must be between 4 and %d characters.\n", MAX_USERNAME_LENGTH);
        return;
    }

    // Get the password
    printf("Enter the password of the user you'd like to create\n> ");
    scanf("%19s", i_password);

    // Check the validity of the password
    if (strlen(i_password) < 4 || strlen(i_password) > MAX_PASSWORD_LENGTH) {
        printf("Invalid password. Password must be between 4 and %d characters.\n", MAX_PASSWORD_LENGTH);
        return;
    }

    sprintf(fp, "F:/projects/compsci/db/users/%s.txt", i_username);

    FILE *userdb = fopen(fp, "w");
    if (userdb == NULL) {
        perror("Error opening user file");
        return;
        }
}

// Entrypoint
int main() {
    char i_username[MAX_USERNAME_LENGTH];
    char i_password[MAX_PASSWORD_LENGTH];
    int option;

    do {
        printf("Welcome to the York Castle canteen POS || ");
        printf("Enter 1 to login or 2 to make one.|| > ");
        scanf("%d", &option);

        // Check if the input option is valid
        if (option != 1 && option != 2) {
            printf("Not a valid option. Please try again.\n");
            main();
        }

    } while (option != 1 && option != 2);

    switch (option) {
        case 1:
            printf("Please enter username\n> ");
            scanf("%19s", i_username);
            printf("Please enter password\n> ");
            scanf("%19s", i_password);

            if (login(i_username, i_password)) {
                //printf("Welcome, %s", i_username);
                CLI(i_username, 1);
            } else {
                //printf("Please check credentials and ensure your userfile exists\n");
            }
            break;

        case 2:
            makeUser();
            break;
        default:
        printf("1\n");
        break;
    }

    return 0;
}