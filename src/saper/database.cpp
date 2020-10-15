#include "database.h"

#include <sqlite_orm/sqlite_orm.h>


using namespace sqlite_orm;
using namespace std;

int callback(void *unused, int count, char **data, char **columns)
{
    int idx;

//    printf("There are %d column(s)\n", count);

    for (idx = 0; idx < count; idx++) {
        cout << "The data in column " <<columns[idx] << " is " <<data[idx];
//        printf("The data in column \"%s\" is: %s\n", columns[idx], data[idx]);
    }
//    User u;
//    u.id = stoi(data[0]);
//    u.name = data[1];


    printf("\n");

    return 0;
}

Database::Database()
{
    sqlite3 *db;
    sqlite3_open("../source/minesweeperUserData.sqlite", &db);

    string query = "CREATE TABLE IF NOT EXISTS users (userId INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "name TEXT, "
                   "score INTEGER, "
                   "time INTEGER)";


    char* messageError;


    int rc = sqlite3_exec(db,
                          query.c_str(),
                          NULL,
                          0,
                          &messageError);

}

void Database::addUser(User user)
{
    sqlite3 *db;
    char* messageError;
    int rc = sqlite3_open("../source/minesweeperUserData.sqlite", &db);

    string query = "INSERT INTO users (name, "
                   "score, "
                   "time) "
                   "VALUES ("
                   "'" + user.name + "', "
                    "'" + to_string(user.score) + "', "
                    "'" + to_string(user.time)+ "')";

    rc = sqlite3_exec(db, query.c_str(), nullptr, 0, &messageError);
    if(rc != SQLITE_OK)
    {
        cout << "SQL error: %s\n"<< messageError;
        sqlite3_free(messageError);
    }
}

User Database::getBestScore()
{
    sqlite3 *db;
    char* messageError;
    int rc = sqlite3_open("../source/minesweeperUserData.sqlite", &db);

    string query ="SELECT *, MAX(score) FROM users";

    rc = sqlite3_exec(db, query.c_str(), callback, 0, &messageError);
    if(rc != SQLITE_OK)
    {
        cout << "SQL error: %s\n"<< messageError;
        sqlite3_free(messageError);
    }
}


