#include <stdio.h>
#include <string.h>

#define MAX_ITEM_NAME_LENGTH 20

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

char current_username[20];

// Takes 2 arguments `username` and `password` opens user file 
// And checks if credentials input are correct returns 1 upon success

int credentialsExist(char username[20], char password[20])
{
  
  char user[50];
  char pass[20];
  char fp[40];
  sprintf(fp, "%s/%s.txt", "D:/projects/compsci/db/users", username);
  
  userdb = fopen(fp, "r");
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

int login(char username[20], char password[20])
{
    if(credentialsExist(username, password)){
        
        return 1;
    }
    else {
        printf("You input the wrong credentials, please check again or ensure that your userfile is created.");
        return 0;
    }
}

// Returns current menu to user through stdout

void getMenu()
{
    struct MenuItem {
        char name[20];
        int price;
        int quantity;
    } menu_item;
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");

    while (fscanf(menudb, "%s %d %d", menu_item.name, &menu_item.price, &menu_item.quantity) == 3) {
        printf("Item: %s, Price: $%d, Quantity: %d\n", menu_item.name, menu_item.price, menu_item.quantity);
    }

    fclose(menudb);
}

// Adds an item to the menu along with price and quantity

void addToMenu()
{
    struct MenuItem {
        char name[20];
        int price;
        int quantity;
    } new_item;

    printf("What would you like to add to the menu?\n> ");
    scanf("%s", new_item.name);

    printf("What is the price of this item?\n> ");
    scanf("%d", &new_item.price);

    printf("How much of this item are you adding?\n> ");
    scanf("%d", &new_item.quantity);

    menudb = fopen("D:/projects/compsci/db/menu.txt", "a");
    fprintf(menudb, "%s %d %d", new_item.name, new_item.price, new_item.quantity);
    fclose(menudb);
}

// Accepts search prefix and indexes menu file based off of item
// And returns item name & item price formatted

int searchMenu()
{
    char i_searchPrefix[20];
    printf("Enter search prefix\n> ");
    scanf("%19s", i_searchPrefix);

    FILE *menudb = fopen("D:/projects/compsci/db/menu.txt", "r");
    if (menudb == NULL) {
        perror("Error opening file");
        return -1;  // Indicate failure
    }

    struct MenuItem {
        char name[20];
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

void sellItem()
{
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

    FILE *menudb = fopen("D:/projects/compsci/db/menu.txt", "r");
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
    scanf("%d", &sold_item.quantity);

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
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");
    FILE *tempdb = fopen("D:/projects/compsci/db/temp_menu.txt", "w");

    while (fscanf(menudb, "%19s %d %d", menu_item.name, &menu_item.price, &menu_item.quantity) == 3) {
        if (strcmp(menu_item.name, sold_item.item) == 0) {
            fprintf(tempdb, "%s %d %d\n", menu_item.name, menu_item.price, new_item_quantity);
        }
        else {
            fprintf(tempdb, "%s %d %d\n", menu_item.name, menu_item.price, menu_item.quantity);
        }
    }

    fclose(menudb);
    fclose(tempdb);

    remove("D:/projects/compsci/db/menu.txt");
    rename("D:/projects/compsci/db/temp_menu.txt", "D:/projects/compsci/db/menu.txt");

    // Add the sale to the sales records
    FILE *counterdb = fopen("D:/projects/compsci/db/sales.txt", "a");
    fprintf(counterdb, "%s %d %d\n", sold_item.item, menu_item.price, sold_item.quantity);
    fclose(counterdb);

    printf("Sale recorded successfully.\n");
    sellItem();
}

// Calculates every item sold along with money made and price it was sold for

void calculateSoldItem() // Implement pattern matching algorithim 
{
    struct SalesRecord sold_item;

    counterdb = fopen("D:/projects/compsci/db/sales.txt", "r");
    while (fscanf(counterdb, "%s %d %d", sold_item.item, &sold_item.price, &sold_item.quantity) == 3) {
        int money_made = sold_item.price * sold_item.quantity;
        printf("Item: %s, Price: $%d, Quantity: %d, Money made from item: $%d\n", 
            sold_item.item, sold_item.price, sold_item.quantity, money_made);
    }

    fclose(counterdb);
}

// Prompt for user to select action 1-6

void CLI(char *username, int reinit)
{
    
    int i_operation;

    if(reinit){
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
        }
        else {
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
            break;
    }
}

// Accepts username and password for new user to be made in system

void makeUser() 
{
    char fp[60]; // file path
    char fc[40]; // file content 

    char i_username[20];
    char i_password[20];
    printf("Enter the username of the user you'd like to create\n> ");
    scanf("%s", i_username);
    printf("Enter the password of the user you'd like to create\n> ");
    scanf("%s", i_password);

    sprintf(fp, "%s/%s.txt", "D:/projects/compsci/db/users", i_username); // appends concatenated string to character array 

    userdb = fopen(fp, "w");
    sprintf(fc, "%s\n%s", i_username, i_password);
    // fc = <username>\n<password>
    fprintf(userdb, fc);
    fclose(userdb); // Close the file after writing
    printf("`%s`, User created\n", i_username);
    strcpy(current_username, i_username);
    CLI(i_username, 0);
    
}

// Entrypoint

int main()
{
    char i_username[20];
    char i_password[20];
    int option;

    printf("Welcome to the York Castle canteen POS\n");
    printf("Enter 1 to make an account or 2 to login\n> ");
    scanf("%d", &option);
    switch (option) {
        case 1:
        makeUser();
        break;

        case 2:
        printf("Please enter username\n> ");
        scanf("%s", i_username);
        printf("Please enter password\n> ");
        scanf("%s", i_password);
        if(login(i_username, i_password)) {
            //printf("Welcome, %s", i_username);
            CLI(i_username, 1);
        }
        else {
            printf("Please check credentials and ensure your userfile exists");
        }
        break;

        case 3:
        calculateSoldItem();
        break;

        default:
        break;
    }
}