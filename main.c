#include <stdio.h>
#include <time.h>

FILE *logfile;
FILE *menufile;
FILE *userfile;

char cwd[] =
    "C:/Users/XXX/OneDrive/Desktop/compsci";   // current working directory
char dbd[] = "C:/XXX/bhave/OneDrive/Desktop/"; // database directory
char mnd[] =
    "C:/Users/XXX/OneDrive/Desktop/compsci/database/menu.txt"; // menu
                                                                 // directory
char lgd[] =
    "C:/Users/XXX/OneDrive/Desktop/compsci/logs.txt"; // logs directory

char current_user[50];
int current_user_privilege;
char username[256];
char password[256];

int readPrivliege = 1;
int writePrivilege = 2;
int userManage = 3;

int credentialsExist(char *username, char *password) {
  FILE *fptr = fopen("users.txt", "r");
  char user[50];
  char pass[8];

  while (fscanf(fptr, "%s %s", user, pass) == 2) {
    if (strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
      fclose(fptr);
      return 1;
    }
  }
  fclose(fptr);
  return 0;
}

int checkUserPrivilege(int level) {
  switch (level) {
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

void updateUser(char password[50], int privilege) {}

void makeUser(char username[256], char password[256], int privilege) {
  char ufp[256];
  sprintf(ufp, "%s/%s.txt", dbd, username);

  userfile = fopen(ufp, "w");
  fprintf(userfile, "%s\n%s", username, password);

  // Assuming menufile is declared somewhere in your program
  // fprintf(menufile, "%s\n%s", username, password);
}

void modifyCurrentSession(char cusername[50], int cpl) {
  /* modifies variable
  current_user
  current_user_privilege
  */
  *cusername = cusername;
  printf(cusername);
}

void login() {
  printf("Enter your username\n> ");
  scanf("%s", username);
  printf("Enter a password\n> ");
  scanf("%s", password);
  if (credentialsExist(username, password)) {
    printf("Welcome back %s", username);
  }

  // login and set `current_user` to current logged in user
}

void loggerplslog(char *severity, char *user, char *message) {
  logfile = fopen(lgd, "a");

  fprintf(logfile, "[ %s %s ] : [%s]\n", severity, user, message);
  fclose(logfile);
}

const char *getMenu() {
  menufile = fopen(mnd, "w");
  char line[100];

  fprintf(menufile, "hello");

  // while (fgets(line, sizeof(line), menufile) != NULL) {
  //       // Process the line as needed
  //       printf("%s", line);
  //   }
}

void main() {
  // getMenu();
  makeUser("admin", "balls", 1);
}
