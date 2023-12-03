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

char* getMenu()
{
    char buffer[1024];
    menudb = fopen("D:/projects/compsci/db/menu.txt", "r");
    fclose(menudb);
    return fgets(buffer, 1000, menudb);

}

int main()
{
    printf("Menu Reader");
    // makeUser("username", "password");
    printf("%s", getMenu());
    return 0;
}