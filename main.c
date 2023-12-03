#include <stdio.h>
#include <time.h>

FILE* logfile;
FILE* menufile;
FILE* userfile;

char cwd[] = "C:/Users/bhave/OneDrive/Desktop/computer science"; // current working directory
char dbd[] = "C:/Users/bhave/OneDrive/Desktop/computer science/database"; // database directory
char lgd[] = "C:/Users/bhave/OneDrive/Desktop/computer science/logs.txt"; // logs directory


char current_user[50];
char current_user_privilege[5];
char username[50];
char password[50];

int readPrivliege = 1;
int writePrivilege = 2;
int userManage = 3;


int checkUserPrivilege(int level)
{
  switch(level)
  {
    case 1:
    // allow read
    break;
    case 2:
    // allow write
    break;
    case 3:
    // allow user to create/delete/delevel users
    break;
  }
}

void updateUser(char password[50], int privilege)
{
  
}


void makeUser(char username[50], char password[50])
{
  char ufp[256];
  sprintf(ufp, "%s/%s.txt", cwd, username);
  
  userfile = fopen(ufp, "w");
  fprintf(userfile, "%s\n%s", username, password);

  // Assuming menufile is declared somewhere in your program
  // fprintf(menufile, "%s\n%s", username, password);
}

void login()
{
  printf("Enter your username\n> ");
  scanf("%s", username);
  printf("Enter a password\n> ");
  scanf("%s", password);
  //login and set `current_user` to current logged in user
}

void loggerplslog(char* severity, char* user, char* message)
{
  logfile = fopen(lgd, "a");

  fprintf(logfile, "[][ %s %s ] : [%s]\n", severity, user, message);
  fclose(logfile);
}

const char* getMenu()
{
  
} 

void main()
{
  makeUser("admin", "1234");
}
