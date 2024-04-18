// libaries used in the program
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_USERNAME_LENGTH 10
#define MAX_PASSWORD_LENGTH 10
#define MIN_PASSWORD_LENGTH 5


char username[MAX_USERNAME_LENGTH + 1];
char password[MAX_PASSWORD_LENGTH + 1];

struct User {
  char user[20];
  char pass[9];
};

char purchase[90];
char itemname[20];

int price;
int quantity;
int cost;

FILE *itemssold;
FILE *co;
FILE *orders;

bool successful_signin = false;



void makeod() {
  int amount;

  printf("What item would you like to purchase? ");
  scanf("%s", purchase);

  printf("How much would you like? ");
  char amt[10];
  scanf("%s", amt);

  int i;
  for (i = 0; i < strlen(amt); i++) {
    if (!isdigit(amt[i])) {
      printf("Invalid amount entered. Please enter a valid number\n");
      return;
    }
  }
  amount = atoi(amt);

  itemssold = fopen("item.txt", "r+");
  orders = fopen("Dsold.txt", "a");

  int present = 0;

  long int position;
  int original_quantity_width;

  while (fscanf(itemssold, "%s %d %d", itemname, &price, &quantity) == 3) {
      if (strcmp(itemname, purchase) == 0 && quantity >= amount) {
          present = 1;

          int cost = price * amount;
          printf("%-15s%-8s\n", "Item Name", "Cost");
          printf("%-15s%-8d\n", purchase, cost);
          fprintf(orders, "%s %d %d\n", purchase, amount, cost);

         
          position = ftell(itemssold);

     
          original_quantity_width = snprintf(NULL, 0, "%d", quantity);

       
          int new_quantity = quantity - amount;
          fseek(itemssold, position - original_quantity_width, SEEK_SET);
          fprintf(itemssold, "%*d", original_quantity_width, new_quantity);

          break;
      }
  }

  if (!present) {
      printf("Item not Available\n");
  }

  fclose(itemssold);
  fclose(orders);
}


void checstock() // function used to check amount of items in stock
{
  itemssold = fopen("item.txt", "r");
  printf("%-15s%-8s%-8s\n", "Item Name", "Price", "Quantity");
  while (fscanf(itemssold, "%s %d %d", itemname, &price, &quantity) != EOF)
  {
    printf("%-15s%-8d%-8d\n", itemname, price, quantity);
  }
  int choice;

  while(choice != -1)
  {
      printf("\n");
     
      printf ("Would you like to purchase an item?\n");
      printf("1. Yes\n2. No\n");
     
      scanf("%d", &choice);
      getchar();
   
      switch(choice)
      {
        case 1:
          makeod();
          break;
        case 2:  
          printf("Thanks for making it Byfield's butcher shop");
          fclose(itemssold);
          break;
          default:
          printf("Invalid Entry \n");
      }
    }
}
void cusmenu() //Menu for customers to make purchases.
{
  int choice;
  while(choice != -1){
    printf("1. Make an order\n");
    printf("2. Check items available\n");
    printf("3. Exit\n");
    printf("Please choose an option? ");
   
    scanf("%d", &choice);
    getchar();
    switch (choice) {
    case 1:
      makeod();
      break;
    case 2:
      checstock();
    case 3:
      printf("Thanks for making it Byfield’s butcher shop");
      exit(0);
      break;
      default:
      printf("Invalid Entry \n");
    }
  }
}

void additem() //Allows admins to add new items to the inventory.
{
  do {
    printf("Enter item name, enter xxx to stop: ");
    scanf("%s", itemname);

    if (strlen(itemname) > 10) {
        printf("Item name must be 10 characters or less.\n");
        return;
    }
    if (strcmp(itemname, "xxx") == 0) {
      break;
    }
    printf("Enter item price: ");
    char price_input[20];
    scanf("%s", price_input);

   
    int i;
    for (i = 0; i < strlen(price_input); i++) {
      if (!isdigit(price_input[i])) {
        printf("Invalid input for price. Please enter a valid number.\n");
        return;
      }
    }

    price = atoi(price_input);

    if (price > 99999) {
        printf("Price is too large\n");
        return;
    }
    if (price < 100) {
        printf("Price is too small\n");
        return;
    }

    printf("Enter item quantity: ");
    scanf("%d", &quantity);
    if (quantity > 99999) {
        printf("Quantity is too large\n");
        return;
    }

    itemssold = fopen("item.txt", "a");
    fprintf(itemssold, "%s %d %d\n", itemname, price, quantity);
    fclose(itemssold);
  } while (1);
}



void check_total_stock() //Displays the total stock of items.
{
  printf("The total stock is\n");
  itemssold = fopen("item.txt", "r");
  char band[100];
  printf("%-15s%-8s%-8s\n", "Item Name", "Price", "Quantity");
  while (fscanf(itemssold, "%s %d %d", itemname, &price, &quantity) != EOF) {
    printf("%-15s%-8d%-8d\n", itemname, price, quantity);

  }
  fclose(itemssold);
}

void update_pric_quan() //  Allows admins to update the price and quantity of existing items.
{
      char search_name[50];
      printf("Please input the name of the item you wish to update ");
      scanf("%s", search_name);

   
      int found = 0;

      FILE *temp_file = fopen("temp.txt", "w");
      itemssold= fopen("item.txt", "r");
     
      while (fscanf(itemssold, "%s %d %d", itemname, &price, &quantity) != EOF) {
          if (strcmp(itemname, search_name) == 0) {
              found = 1;
              printf("Enter new price: ");
              scanf("%d", &price);
              if (price > 99999) {
                  printf("Price is too large\n");
                  return;
              }
              if (price < 100) {
                  printf("Price is too small\n");
                  return;
              }
              printf("Enter new quantity: ");
              scanf("%d", &quantity);
              if (quantity > 9999) {
                  printf("Quantity is too large.\n");
                  return;
              }
          }
          fprintf(temp_file, "%s %d %d\n", itemname, price, quantity);
      }

      fclose(itemssold);
      fclose(temp_file);

      remove("item.txt");
      rename("temp.txt", "item.txt");

      if (!found) {
          printf("Item not found.\n");
      } else {
          printf("Item updated successfully.\n");
      }
}
   

void adminmenu() /* Menu for admins to perform various actions like adding products, changing prices/quantities, checking total stock, and viewing a summary. */
{
  int option;
  while(option != 1){
   
    printf("Welcome admin\n");
    printf("1. Add new products\n");
    printf("2. Change Price/add Quantity\n");
    printf("3. Check Total stock\n");
    printf("4. summary\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
   
    scanf("%d", &option);
    getchar();
   
    // Process admin choice
    switch (option) {
        case 1:
          additem();
          break;
        case 2:
          update_pric_quan();
          break;
        case 3:
          check_total_stock();
          break;
        case 4:
          orders= fopen("Dsold.txt", "r");
          printf("%-15s%-10s%-8s\n", "Item Name", "Quantity", "Cost");
          while (fscanf(orders, "%s %d %d", itemname, &quantity, &cost) != EOF)
          {
              printf("%-15s%-10d%-8d\n", itemname, quantity, cost);  
              adminmenu();
          }
      case 5:
          printf("  Exiting....  ");
          exit(0);
          break;
      default:
      printf("Invalid Entry \n");
    }
  }
}


   

void signin() // Allows users to sign in as either a user or an admin.
{
    printf("Enter your username ");
    scanf("%s", username);

    if (strlen(username) > 10) {
        printf("Username must be at most 10 characters\n");
        return;
    }
    printf("Enter your password ");
    scanf("%s", password);

    if (strlen(password) > 10) {
        printf("Username  must be at most 10 characters\n");
        return;
    }
    if (strlen(password) < MIN_PASSWORD_LENGTH)
      {
        printf("Password must be at least 5 characters.\n");
        return;
      }
    if (strcmp(username, "pas") == 0 && strcmp(password, "12345") == 0) {
        adminmenu();
        successful_signin = true;
     
    } else {
       FILE *co;
          co = fopen("customers.txt", "r");

          struct User currentUser;
          bool found = false;

          while (fscanf(co, "%s %s", currentUser.user, currentUser.pass) == 2) {
              if (strcmp(currentUser.user, username) == 0 &&
                  strcmp(currentUser.pass, password) == 0) {
                  printf("Welcome %s\n", username);
                  successful_signin = true;
                  cusmenu();
                  found = true;
                  break;
              }
          }

          fclose(co);

          if (!found) {
              printf("Login failed. Invalid credentials.\n");
              signin();

              successful_signin = false;
          }
      }
}


void signup() // Allows customers to create accounts.
{
 
    printf("Enter your username ");
    scanf("%s", username);
    if (strlen(username) > 10  )
    {
        printf ("Username must be at most 10 characters\n");
        return;
    }
    printf("Enter your password ");
    scanf("%s", password);


    if (strlen(password) > 10 )
    {
        printf ("Password must be at most 10 characters\n");
        return;
    }
      if (strlen(password) < MIN_PASSWORD_LENGTH)
      {
        printf("Password must be at least 5 characters.\n");
        return;
      }
    else
    {
        co = fopen("customers.txt", "a");
        fprintf(co, "%s %s\n", username, password);
        printf("\nWelcome %s\n", username);
        cusmenu();
        fclose(co);
    }
}


void displaymenu() // Main menu interface for the program.
{
  int choice;
  while(choice != 1)
  {
   
    printf("----- Welcome to Byfield’s butcher shop -----\n");
    printf("1. signin\n");
    printf("2. signup\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
 
   
    scanf("%d", &choice);
    getchar();
   
    // Process user choice
    switch (choice) {
      case 1:
        signin();
        break;
      case 2:
        signup();
        break;
      case 3:
        printf("Have a wonderful day.\n");
        exit(0);
        break;
        default:
        printf("Invalid Entry \n");
    }    
  }
}

int main() // main function
{
 displaymenu();
  return 0;
}