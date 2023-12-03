`void makeUser(char username[20], char password[20])`
Accepts 20 bytes on `username` and 20 bytes on `password`.
Creates a user in D:/projects/compsci/db/users/<username.txt>

`void getMenu()`
Accepts no arguments.
Prints menu on console

`void addToMenu(char item[20], int price)`
Accepts 20 bytes on `item` and an integer `price`.
Apends to D:/projects/compsci/db/menu.txt
<item> | <price>

`void searchMenu(char searchPrefix)`
Accepts `searchPrefix`
Indexes D:/projects/compsci/db/menu.txt

`int main()`
Current use : test functions