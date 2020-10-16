#include "database.h"

#include <sqlite_orm/sqlite_orm.h>
#include <cstdlib>

using namespace sqlite_orm;
using namespace std;


Database::Database()
{
    bestTime = 0;
    noWinner = false;

    sqlite3 *db;
    sqlite3_open("../source/minesweeperUserData.sqlite", &db);

    string query = "CREATE TABLE IF NOT EXISTS users (userId INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "name TEXT, "
                   "success INTEGER, "
                   "time INTEGER)";


    char* messageError;


    int rc = sqlite3_exec(db,
                          query.c_str(),
                          NULL,
                          0,
                          &messageError);

}

void Database::addUser(UserData user)
{
    sqlite3 *db;
    char* messageError;
    int rc = sqlite3_open("../source/minesweeperUserData.sqlite", &db);

    string query = "INSERT INTO users (name, "
                   "success, "
                   "time) "
                   "VALUES ("
                   "'" + user.getName() + "', "
                                          "'" + to_string(user.getSuccess()) + "', "
                                                                               "'" + to_string(user.getTime())+ "')";

    rc = sqlite3_exec(db, query.c_str(), nullptr, 0, &messageError);
    if(rc != SQLITE_OK)
    {
        cout << "SQL error: %s\n"<< messageError;
        sqlite3_free(messageError);
    }
}

void Database::getBestUser()
{
    sqlite3 *db;
    char* messageError;
    int rc = sqlite3_open("../source/minesweeperUserData.sqlite", &db);

    string query = "SELECT min(time) FROM users "
                   " WHERE users.success=1";

    rc = sqlite3_exec(db, query.c_str(), bestUserCallback, 0, &messageError);

//    cout << "rc" <<  rc <<endl;
    if (rc != SQLITE_OK)
        throw string(sqlite3_errmsg(db));

}

void Database::getBestLoser()
{
    sqlite3 *db;
    char* messageError;
    int rc = sqlite3_open("../source/minesweeperUserData.sqlite", &db);

    string query = "SELECT min(time) FROM users ";

    rc = sqlite3_exec(db, query.c_str(), bestLoserCallback, 0, &messageError);

    if (rc != SQLITE_OK)
        throw string(sqlite3_errmsg(db));
}

bool Database::getNoWinner()
{
    return noWinner;
}

int Database::bestUserCallback(void *data, int argc, char **argv, char **columns)
{
    if(argc == 0)
    {
        noWinner = true;
    }
    else
    {
        for(int i = 0; i < argc; i++)
        {
            cout<<columns[i] << " " <<argv[i];
        }
        cout << "nieeee";
        noWinner = false;
    }

    return 0;
}

int Database::bestLoserCallback(void *data, int argc, char **argv, char **columns)
{
    if(argc == 0)
    {
    }
    else
    {
        for(int i = 0; i < argc; i++)
        {
            cout<<columns[i] << " " <<argv[i];
        }
        ss << argv[0];
    }

    return 0;
}




