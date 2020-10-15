#include "userdata.h"


UserData::UserData()
{
    points = 0;
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

