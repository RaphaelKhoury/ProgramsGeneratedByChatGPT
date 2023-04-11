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

  sqlite3_stmt *stmt;
  const char *sql = "INSERT INTO Users (name, password) VALUES (?, ?)";

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return 1;
  }

  rc = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to bind name: %s\n", sqlite3_errmsg(db));
    return 1;
  }

  rc = sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to bind password: %s\n", sqlite3_errmsg(db));
    return 1;
  }

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    return 1;
  }

  fprintf(stdout, "Records created successfully\n");

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  
  return 0;
}