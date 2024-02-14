#include <stdio.h>
#include <string.h>

// Struct for menu items
struct MenuItem {
    char name[20];
    int price;
};

// Struct for sales records
struct SalesRecord {
    char item[20];
    int price;
    int quantity;
};

FILE* userdb;
FILE* menudb;
FILE* counterdb;

char current_username[20];
int is_logged_in;

int credentialsExist(char username[20], char password[20]) // tested, works
{
  
  char user[50];
  char pass[20];
  char fp[40];
  sprintf(fp, "%s/%s.txt", "D:/projects/compsci/db/users", username);
//   printf(fp); // debug
//   printf(username); // debug
//   printf(password); // debug
  
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



int login(char username[20], char password[20]) // tested, works
{
    if(credentialsExist(username, password)){
        printf("Welcome back, %s", username);
        
        return 1; // add injection base for userfacing functions DONOT FORGET IT WILL BRICK UR CODE
    }
    else {
        printf("You input the wrong credentials, please check again or ensure that your userfile is created.");
        return 0;
    }
}

void getMenu() {
    struct MenuItem menu_item;
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");

    while (fscanf(menudb, "%s %d", menu_item.name, &menu_item.price) == 2) {
        printf("Item: %s, Price: $%d\n", menu_item.name, menu_item.price);
    }

    fclose(menudb);
}

void addToMenu() {
    struct MenuItem new_item;

    printf("What would you like to add to the menu?");
    scanf("%s", new_item.name);

    printf("What is the price of this item?");
    scanf("%d", &new_item.price);

    menudb = fopen("D:/projects/compsci/db/menu.txt", "a");
    fprintf(menudb, "\n%s    | $%d", new_item.name, new_item.price);
    fclose(menudb);
}

void searchMenu() {
    char i_searchPrefix[20];
    printf("Enter search prefix");
    scanf("%s", i_searchPrefix);

    struct MenuItem menu_item;
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");

    while (fscanf(menudb, "%s %d", menu_item.name, &menu_item.price) == 2) {
        if (strncmp(menu_item.name, i_searchPrefix, strlen(i_searchPrefix)) == 0) {
            printf("Item: %s, Price: $%d\n", menu_item.name, menu_item.price);
        }
    }

    fclose(menudb);
}

void sellItem() {
    struct SalesRecord sold_item;

    printf("What has been sold? ");
    scanf("%19s", sold_item.item);

    printf("What is the price of the item sold? ");
    scanf("%d", &sold_item.price);

    printf("How many of those have been sold? ");
    scanf("%d", &sold_item.quantity);

    counterdb = fopen("D:/projects/compsci/db/sales.txt", "a");
    fprintf(counterdb, "%s %d %d\n", sold_item.item, sold_item.price, sold_item.quantity);
    fclose(counterdb);
}

void calculateSoldItem() {
    struct SalesRecord sold_item;

    counterdb = fopen("D:/projects/compsci/db/sales.txt", "r");
    while (fscanf(counterdb, "%s %d %d", sold_item.item, &sold_item.price, &sold_item.quantity) == 3) {
        int money_made = sold_item.price * sold_item.quantity;
        printf("Item: %s, Price: $%d, Quantity: %d, Money made from item: $%d\n", 
            sold_item.item, sold_item.price, sold_item.quantity, money_made);
    }

    fclose(counterdb);
}

void CLI(char username[20]) 
{
    int i_operation;

    printf("Welcome %s, what would you like to do today?\n", username);
    printf("[1] Get the current menu\n");
    printf("[2] Add an item to the menu\n");
    printf("[3] Search the menu for a spesific item\n");
    printf("[4] Sell an item\n");
    printf("[5] Calaculate amount of item sold\n");
    printf("Please enter the number correlated to your option of choice.\n> ");
    scanf("%d", &i_operation);
    switch (i_operation)
    {
    case 1:
    getMenu();
    break;

    case 2:
    addToMenu();
    break;

    case 3:
    searchMenu(); 
    break;

    case 4:
    sellItem();
    break;

    case 5:
    calculateSoldItem();
    break;

    default:
    break;
    }
}

void makeUser() // tested, works
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

    userdb = fopen(fp, "a");
    sprintf(fc, "%s\n%s", i_username, i_password);
    // fc = <username>\n<password>
    fprintf(userdb, fc);
    fclose(userdb); // Close the file after writing
    printf("`%s`, User created\n", i_username);
    strcpy(current_username, i_username);
    CLI(i_username);
    
}

int main() // ENTRYPOINT
{
    // char i_username[20];
    // char i_password[20];
    // int option;

    // printf("Welcome to the York Castle canteen POS\n");
    // printf("Enter 1 to make an account or 2 to login\n> ");
    // scanf("%d", &option);
    // switch (option) {
    //     case 1:
    //     makeUser();
    //     break;

    //     case 2:
    //     printf("Please enter username\n> ");
    //     scanf("%s", i_username);
    //     printf("Please enter password\n> ");
    //     scanf("%s", i_password);
    //     if(login(i_username, i_password)) {
    //         printf("Welcome, %s", i_username);
    //         CLI(i_username);
    //     }
    //     else {
    //         printf("Please check credentials and ensure your userfile exists");
    //     }

    //     break;
        
    //     default:
    //     break;
    // }

    getMenu();
}