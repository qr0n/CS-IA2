#include <stdio.h>
#include <string.h>

FILE* userdb;
FILE* menudb;

char current_username[20];

int credentialsExist(char username[20], char password[20])
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

void makeUser(const char username[20], const char password[20])
{
    char fp[60]; // file path
    char fc[40]; // file content 
    sprintf(fp, "%s/%s.txt", "D:/projects/compsci/db/users", username); // appends concatenated string to character array 

    userdb = fopen(fp, "a");
    sprintf(fc, "%s\n%s", username, password);
    // fc = <username>\n<password>
    fprintf(userdb, fc);
    fclose(userdb); // Close the file after writing
}

int login(char username[20], char password[20])
{
    if(credentialsExist(username, password)){
        printf("Welcome back, %s", username);
        strcpy(current_username, username);
    }
    else {
        printf("You input the wrong credentials, please check again or ensure that your userfile is created.");
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

void searchMenu(const char *searchPrefix)
{
    char buffer[1024];
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");

    while(fgets(buffer, sizeof(buffer), menudb) != NULL){
        if(strncmp(buffer, searchPrefix, strlen(searchPrefix)) == 0){
            printf(buffer);
        }
    }
}


// tests
char helloworld[20] = "hello";

void test()
{
    // login("username", "password");
    /* 
    test 1:
    username: "username",
    password: "password"

    expected result : "Welcome back, username"
    Result : "Welcome back, username"

    test 2:
    # things modified 
    updated userfile username parameter to "iron"
    */
}

int main()
{
    test();
}

/*
melody is gay
*/