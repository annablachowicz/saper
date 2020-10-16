#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <sstream>
#include "userdata.h"


static int bestTime;
static bool noWinner;
static std::stringstream ss;

class Database
{
public:
    Database();
    void addUser(UserData user);
    void getBestUser();
    void getBestLoser();

    static bool getNoWinner();

private:
    std::string path;

    void createTablesIfNeeded();
    static int bestUserCallback(void *data, int argc, char **argv, char **columns);
    static int bestLoserCallback(void *data, int argc, char **argv, char **columns);

};

#endif // DATABASE_H
