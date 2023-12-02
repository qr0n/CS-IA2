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

int checkUserPrivilege(int level)
{
  
}

void makeUser(char username[50], char password[50], char privilege[5])
{
  char ufp[256];
  sprintf(ufp, "%s/users/%s.txt", dbd, username);
  
  userfile = fopen(ufp, "w");
  fprintf(userfile, "%s\n%s\n%s", username, password, privilege);

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
// void signUp() {
//   // printf("Enter an username\n> ");
//   // scanf("%s", username);
//   // printf("Enter a password\n> ");
//   // scanf("%s", password);
  
//   //FILE* fptr = fopen("users.txt", "a");
//   fprintf(fptr, "%s\n", username);
//   fprintf(fptr, "%s\n\n", password);
//   fclose(fptr);
//   printf("Made user '%s'", username);
// }

void loggerplslog(char* severity, char* user, char* message)
{
  logfile = fopen(lgd, "a");

  fprintf(logfile, "[][ %s %s ] : [%s]\n", severity, user, message);
  fclose(logfile);
}

const char* getMenu()
{
  //loggerplslog()
  //menufile = fopen("")
} 

void main()
{
  makeUser("admin", "1234", "all");
}
