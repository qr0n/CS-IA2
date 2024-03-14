#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100
#define REORDER_LEVEL 350
#define MAX_LEVEL 1000

 FILE *displaycustomers ;

typedef struct {
    int id;
    int stock;
    char name[100];
    char address[50];
    char dob[11]; // Date of birth as string
} Customer;

void addCustomer(int *numCustomers, Customer customers[]);
void displayCustomers(int numCustomers, Customer customers[]);
void modifyCustomer(int numCustomers, Customer customers[]);
void removeCustomer(int *numCustomers, Customer customers[]);
void stockCheck();

int main() {
    
    char password[20];
    char pass[20]="1";
    int i=4;
    
    printf("Please enter the password\n");
    scanf("%s",password);
    
    if(strcmp(password,pass)==0){
        printf("you have successfully logged in");
    }
    else{
       printf(" wrong password\n");
     
   }
   if (strcmp(password,pass)!=0){
       for(i=4 ; i >=1; i--){
       printf("The password entered was incorrect, please try again (%d attempts left)\n",i);
       scanf("%s",password);
       if(strcmp(password,pass)==0){
           printf("you have successfully logged in");
           break;
       }
       if(i == 1){
           i=0;
       }
       if (i==0){
           printf("You are out of attempts, hence you are unable to have access to the admin account");
           exit(1);
       }
   }
   }
   
    int numCustomers = 0;
    Customer customers[MAX_CUSTOMERS];
    int option;

    while (1) {
        printf("\nWelcome to Tech Jockies!\n");
        printf("1. Add Customer\n");
        printf("2. Display Customers\n");
        printf("3. Modify Customer\n");
        printf("4. Remove Customer\n");
        printf("5. Stock Analyzer\n");
        printf("6. Exit\n");
        printf("Enter Option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addCustomer(&numCustomers, customers);
                break;
            case 2:
                displayCustomers(numCustomers, customers);
                break;
            case 3:
                modifyCustomer(numCustomers, customers);
                break;
            case 4:
                removeCustomer(&numCustomers, customers);
                break;
            case 5:
                stockCheck();
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

void addCustomer(int *numCustomers, Customer customers[]) {
    if (*numCustomers >= MAX_CUSTOMERS) {
        printf("Customer database is full.\n");
        return;
    }

    printf("Enter Customer Information:\n");
    printf("ID: ");
    scanf("%d", &customers[*numCustomers].id);
    printf("username: ");
    scanf("%s", customers[*numCustomers].name);
    printf("Address: ");
    scanf("%s", customers[*numCustomers].address);
    printf("Date of Birth (DD/MM/YYYY): ");
    scanf("%s", customers[*numCustomers].dob);
    printf(customers[*numCustomers]., &customers[*numCustomers].address, &customers[*numCustomers].dob);

    FILE *displaycustomers = fopen("customer_information.txt", "a"); // Open file in append mode
    if (displaycustomers == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(displaycustomers, "%d %s %s %s\n", customers[*numCustomers].id, customers[*numCustomers].name, customers[*numCustomers].address, customers[*numCustomers].dob);

    fclose(displaycustomers);

    customers[*numCustomers].stock = 0;
    (*numCustomers)++;
    printf("Customer added successfully.\n");
}

void displayCustomers(int numCustomers, Customer customers[]) {
    if (numCustomers == 0) {
        printf("No customers in the database.\n");
        return;
    }

    printf("Customer Details:\n");
    printf("ID\tName\tAddress\tDOB\tStock\n");
    for (int i = 0; i < numCustomers; i++) {
        printf("%d\t%s\t%s\t%s\t%d\n", customers[i].id, customers[i].name,
               customers[i].address, customers[i].dob, customers[i].stock);
    }
}

void modifyCustomer(int numCustomers, Customer customers[]) {
    if (numCustomers == 0) {
        printf("No customers in the database.\n");
        return;
    }

    int id;
    printf("Enter Customer ID to Modify: ");
    scanf("%d", &id);

    for (int i = 0; i < numCustomers; i++) {
        if (customers[i].id == id) {
            printf("Enter new username: ");
            scanf("%s", customers[i].name);
            printf("Enter new address: ");
            scanf("%s", customers[i].address);
            printf("Enter new DOB: ");
            scanf("%s", customers[i].dob);
            printf("Customer details modified successfully.\n");
            return;
        }
    }

    printf("Customer not found.\n");
}

void removeCustomer(int *numCustomers, Customer customers[]) {
    if (*numCustomers == 0) {
        printf("No customers in the database.\n");
        return;
    }

    int id;
    printf("Enter Customer ID to Remove: ");
    scanf("%d", &id);

    for (int i = 0; i < *numCustomers; i++) {
        if (customers[i].id == id) {
            for (int j = i; j < *numCustomers - 1; j++) {
                customers[j] = customers[j + 1];
            }
            (*numCustomers)--;
            printf("Customer removed successfully.\n");
            return;
        }
    }

    printf("Customer not found.\n");
}

void stockCheck() {
    int currentStock, reorderQuantity;
    printf("Enter current stock: ");
    scanf("%d", &currentStock);

    if (currentStock < REORDER_LEVEL) {
        reorderQuantity = MAX_LEVEL - currentStock;
        printf("Current stock is below reorder level. Reorder quantity: %d\n", reorderQuantity);
        printf("Ordering more stock...\n");
        printf("Stock has been ordered.\n");
    } else {
        printf("Current stock level is sufficient.\n");
    }
   
}