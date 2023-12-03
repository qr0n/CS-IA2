#include <stdio.h>
FILE* userdb;
FILE* menudb;


void makeUser(char username[20], char password[20])
{
    char fp[60]; // file path
    char fc[40]; // file content 
    sprintf(fp, "%s/%s.txt", "D:/projects/compsci/db/users", username);

    userdb = fopen(fp, "a");
    sprintf(fc, "%s\n%s", username, password);
    fprintf(userdb, fc);
    fclose(userdb); // Close the file after writing
}

void getMenu()
{
    char buffer[1024];
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");

    if (menudb == NULL) {
        perror("Error opening menu file");
    }

    while (fgets(buffer, sizeof(buffer), menudb) != NULL) {
        printf("%s", buffer);
    }

    fclose(menudb);
}

void addToMenu(char item[20], int price)
{
    char fc[40] =  "%s    | $%d", item, price; // file content
    menudb = fopen("D:/projects/compsci/db/menu.txt", "a");
    fprintf(menudb, fc); 
}

int main()
{
    printf("Menu Reader\n");
    // makeUser("username", "password");
    getMenu();
    return 0;
}