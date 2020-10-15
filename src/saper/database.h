#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>

struct User
{
    int id;
    std::string name;
    int score;
    int time;
};

class Database
{
public:
    Database();
    void addUser(User user);
    User getBestScore();

private:
    std::string path;

    void createTablesIfNeeded();
};

#endif // DATABASE_H
