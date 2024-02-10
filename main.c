#include <stdio.h>
#include <string.h>

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
}

int login(char username[20], char password[20]) // tested, works
{
    if(credentialsExist(username, password)){
        printf("Welcome back, %s", username);
        strcpy(current_username, username);
        return 1; // add injection base for userfacing functions DONOT FORGET IT WILL BRICK UR CODE
    }
    else {
        printf("You input the wrong credentials, please check again or ensure that your userfile is created.");
        return 0;
    }
}

void getMenu() // userfacing or proxy function 
{
    char buffer[1024];
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");

    while (fgets(buffer, sizeof(buffer), menudb) != NULL) {
        printf("%s", buffer);
    }

    fclose(menudb);
}

void addToMenu(const char item[20], int price)
{
    menudb = fopen("D:/projects/compsci/db/menu.txt", "a");
    fprintf(menudb, "\n%s    | $%d", item, price); 
}

void searchMenu(const char *searchPrefix) // userfacing function or proxy func
{
    char buffer[1024];
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");

    while(fgets(buffer, sizeof(buffer), menudb) != NULL){
        if(strncmp(buffer, searchPrefix, strlen(searchPrefix)) == 0){
            printf(buffer);
        }
    }
}

void sellItem() 
{
    char i_item[20];
    printf("What has been sold? ");
    scanf("%19s", i_item); // Limit input to 19 characters to avoid buffer overflow

    int i_price;
    printf("What is the price of the item sold? ");
    scanf("%d", &i_price);

    int i_quantity;
    printf("How many of those have been sold? ");
    scanf("%d", &i_quantity);

    FILE *counterdb = fopen("D:/projects/compsci/db/sales.txt", "a");
    if (counterdb == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    fprintf(counterdb, "%s %d %d\n", i_item, i_price, i_quantity);

    fclose(counterdb);
}

void CLI() {
    int i_operation;
    int mu_username;
    printf("Hello, what would you like to do today?\n");
    printf("[1] Make a user\n");
    printf("[2] Get the current menu\n");
    printf("[3] Add an item to the menu\n");
    printf("[4] Search the menu for a spesific item\n");
    printf("[5] Sell an item\n");
    printf("Please enter the number correlated to your option of choice.\n> ");
    scanf("%d", &i_operation);
    switch (i_operation)
    {
    case 1:
    makeUser();
    break;

    case 2:
    getMenu();
    break;

    case 3:
    addToMenu();
    break;

    case 4:
    searchMenu(); 
    default:
        break;
    }
}

void test() //boiler plate function only tests individual funcs
{
    sellItem();
}

int main() // ENTRYPOINT
{
    char i_username[20];
    char i_password[20];

    printf("Please enter username\n> ");
    scanf("%s", i_username);
    printf("Please enter password\n> ");
    scanf("%s", i_password);
    if(login(i_username, i_password))
    {
        CLI();
    }
}