#include "userdata.h"


UserData::UserData()
{
    success = 0;
    time = 0;
    name = "";
}

std::string UserData::getName() const
{
    return name;
}

void UserData::setName(const std::string &_name)
{
    name = _name;
}

int UserData::getSuccess() const
{
    return success;
}

void UserData::setSuccess(int value)
{
    success = value;
}

int UserData::getTime() const
{
    return time;
}

void UserData::setTime(int value)
{
    time = value;
}
