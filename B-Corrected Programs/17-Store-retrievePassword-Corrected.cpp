#include <iostream>
#include <sqlite3.h>
#include <bcrypt/BCrypt.hpp>

using namespace std;

const int SALT_SIZE = 16;
const int HASH_ROUNDS = 12;

int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}

void create_database(sqlite3* db) {
    char* errMsg = nullptr;
    const char* sql = "CREATE TABLE IF NOT EXISTS users "
        "(id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL, "
        "salt BLOB NOT NULL, "
        "hash BLOB NOT NULL);";
    int rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Error creating table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
}

void add_user(sqlite3* db, const string& username, const string& password) {
    bcrypt::generate_salt([&](const uint8_t* salt, size_t salt_len) {
        bcrypt::generate_hash(password.c_str(), password.size(), salt, salt_len, HASH_ROUNDS, [&](const uint8_t* hash, size_t hash_len) {
            sqlite3_stmt* stmt;
            const char* sql = "INSERT INTO users (username, salt, hash) VALUES (?, ?, ?);";
            int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
            if (rc != SQLITE_OK) {
                cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                return;
            }
            rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
            if (rc != SQLITE_OK) {
                cerr << "Error binding parameter 1: " << sqlite3_errmsg(db) << endl;
                return;
            }
            rc = sqlite3_bind_blob(stmt, 2, salt, salt_len, SQLITE_STATIC);
            if (rc != SQLITE_OK) {
                cerr << "Error binding parameter 2: " << sqlite3_errmsg(db) << endl;
                return;
            }
            rc = sqlite3_bind_blob(stmt, 3, hash, hash_len, SQLITE_STATIC);
            if (rc != SQLITE_OK) {
                cerr << "Error binding parameter 3: " << sqlite3_errmsg(db) << endl;
                return;
            }
            rc = sqlite3_step(stmt);
            if (rc != SQLITE_DONE) {
                cerr << "Error inserting row: " << sqlite3_errmsg(db) << endl;
            }
            sqlite3_finalize(stmt);
            });
        }, SALT_SIZE);
}

bool check_user(sqlite3* db, const string& username, const string& password) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT salt, hash FROM users WHERE username=?;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    rc = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC
}