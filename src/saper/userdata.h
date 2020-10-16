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

    int getSuccess() const;
    void setSuccess(int value);

    int getTime() const;
    void setTime(int value);

private:
    std::string name;
    int success;
    int time;
};

#endif // USERDATA_H
