#include <stdio.h>
FILE* userdb;

void makeUser(char username[20], char password[20])
{
    char fp[60];
    char fc[40];
    sprintf(fp, "%s/%s.txt", "D:/projects/compsci/db/users", username);

    userdb = fopen(fp, "a");
    sprintf(fc, "%s\n%s", username, password);
    fprintf(userdb, fc);
    fclose(userdb); // Close the file after writing
}

int main()
{
    printf("Hello, this is the C compiler!\n");
    makeUser("username", "password");

    return 0;
}