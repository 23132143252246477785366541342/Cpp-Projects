#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}

int main(int argc, char** argv) {
    string u;
    cout << "Type a username: ";
    cin >> u; 
    cout << "Type a password: ";
    string p;
    cin >> p;

    sqlite3* DB;
    string create_table = "CREATE TABLE IF NOT EXISTS Accounts (Username TEXT PRIMARY KEY, Password TEXT)";
    int exit = 0;
    exit = sqlite3_open("accounts.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, create_table.c_str(), NULL, 0, &messaggeError);
  
    if (exit != SQLITE_OK) {
        std::cerr << "Error Create Table" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Table created Successfully" << std::endl;
    
    string insert1 = "INSERT INTO Accounts VALUES(";
    string insert2 = u + "," + p;
    string insert = insert1 + insert2 + ");";
    sqlite3_exec(DB, insert.c_str(), NULL, 0, &messaggeError);
    sqlite3_close(DB);
    return 0;
}