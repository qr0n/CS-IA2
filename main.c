#include <stdio.h>
#include <string.h>

FILE* userdb;
FILE* menudb;

char current_username[20];

int credentialsExist(char *username, char *password) {
  
  char user[50];
  char pass[8];
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

void makeUser(const char username[20], const char password[20])
{
    char fp[60]; // file path
    char fc[40]; // file content 
    sprintf(fp, "%s/%s.txt", "D:/projects/compsci/db/users", username); // appends concatenated string to character array 

    userdb = fopen(fp, "a");
    sprintf(fc, "%s\n%s", username, password);
    fprintf(userdb, fc);
    fclose(userdb); // Close the file after writing
}

int login(const char  username[20], const char password[20])
{
    if(credentialsExist(username, password)){
        printf("Welcome back, %s", username);
    }
}

void getMenu()
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

void searchMenu(const char* searchPrefix)
{
    char buffer[1024];
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");

    while(fgets(buffer, sizeof(buffer), menudb) != NULL){
        if(strncmp(buffer, searchPrefix, strlen(searchPrefix)) == 0){
            printf(buffer);
        }
    }
}

int main()
{
    char searchPrefix[256];  // Adjust the size based on your requirements
    printf("Enter search prefix: ");
    scanf("%255s", searchPrefix);  // Limit input to prevent buffer overflow

    printf("Search results:\n");
    searchMenu(searchPrefix);

    return 0;
}