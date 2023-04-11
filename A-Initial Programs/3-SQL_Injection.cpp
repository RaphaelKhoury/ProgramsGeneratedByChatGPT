#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

int main() {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open("test.db", &db);
  
  if( rc ) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return(0);
  } else {
    fprintf(stderr, "Opened database successfully\n");
  }

  string name;
  string password;

  cout << "Enter name: ";
  cin >> name;
  cout << "Enter password: ";
  cin >> password;

  string sql = "INSERT INTO Users (name, password) VALUES ('" + name + "', '" + password + "');";

  rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);

  if( rc != SQLITE_OK ){
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Records created successfully\n");
  }

  sqlite3_close(db);
  
  return 0;
}
