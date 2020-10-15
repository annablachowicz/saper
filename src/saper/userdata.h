#ifndef USERDATA_H
#define USERDATA_H

#include <iostream>
#include <string>

class UserData
{
public:
    UserData();

    std::string getName() const;
    void setName(const std::string &_name);

private:
    int points;
    std::string name;
};

#endif // USERDATA_H
