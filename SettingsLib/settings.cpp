#include "settings.h"
#include <fstream>

//settings::param::param()
//{
//    owner = 0;
//    value = "";
//    //name = "";
//    isEmpty = true;
//}

settings::param::param(const std::string & name, std::string value, settings *owner, bool empty)
{
    this->value = value;
    this->name = name;
    this->owner = owner;
    isEmpty = empty;
}

settings::param::operator std::string() const
{
    if (isEmpty)
        throw EmptyProperty(name);
    return value;
}

settings::param::operator int() const
{
    if (isEmpty)
        throw EmptyProperty(name);
    return std::stoi(value);
}

settings::param::operator bool() const
{
    if (isEmpty)
        throw EmptyProperty(name);
    bool result;
    if (value == "true")
        result = true;
    else if (value == "false")
        result = false;
    else
        throw std::invalid_argument(value);
    return result;
}

settings::param::operator double() const
{
    if (isEmpty)
        throw EmptyProperty(name);
    return std::stod(value);
}

settings::param &settings::param::operator=(const std::string &newValue)
{
    value = newValue;
    isEmpty = false;
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator=(const char *newValue)
{
    value = std::string(newValue);
    isEmpty = false;
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator=(int newValue)
{
    value = std::to_string(newValue);
    isEmpty = false;
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator=(bool newValue)
{
    std::cout << newValue << " from settings.cpp" << std::endl;
    value = newValue?"true":"false";
    isEmpty = false;
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator=(double newValue)
{
    value = std::to_string(newValue);
    isEmpty = false;
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator+=(const std::string &newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    value += newValue;
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator+=(int newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    value = std::to_string(stoi(value) + newValue);
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator+=(double newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    value = std::to_string(stod(value) + newValue);
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator-=(int newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    value = std::to_string(stoi(value) - newValue);
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator-=(double newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    value = std::to_string(stod(value) - newValue);
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator*=(int newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    value = std::to_string(stoi(value) * newValue);
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator*=(double newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    value = std::to_string(stod(value) * newValue);
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator/=(int newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    value = std::to_string(stoi(value) / newValue);
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator/=(double newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    value = std::to_string(stoi(value) / newValue);
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator|=(bool newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    if (value != "false" && value != "true")
        throw std::invalid_argument(name +": "+ value);
    else if (newValue == true)
        value = "true";
    owner->sync(name, value);
    return *this;
}

settings::param &settings::param::operator&=(bool newValue)
{
    if (isEmpty)
        throw EmptyProperty(name);
    if (value == "true" && newValue == true)
        value = "true";
    else if (value == "false" || value == "true")
        value = "false";
    else
        throw std::invalid_argument(name +": "+ value);
    owner->sync(name, value);
    return *this;
}

bool settings::param::is_empty() const
{
    return isEmpty;
}


settings::settings(const std::string &filename)
{
    //Is file exist?
    if (!std::ifstream(filename).good()){
        std::ofstream(filename);
    }
    this->filename = filename;
    reload();
}

const std::string &settings::get(const std::string &name, const std::string &def) const
{
    try {
        return list.at(name);
    }
    catch (std::out_of_range) {
        return def;
    }
}

void settings::set(const std::string &name, const std::string &value)
{
    list[name] = value;
    sync();
}

void settings::reset()
{
    std::ofstream(filename, std::ofstream::trunc);
    list.clear();
}

void settings::reload()
{
    list.clear();
    std::ifstream in(filename);
    std::string current;
    while (std::getline(in, current)){
        std::size_t pos = current.find("=\"");
        std::string name = current.substr(0, pos);
        std::size_t lpos = current.find_last_of("\"");
        std::string value = current.substr(pos + 2, lpos - (pos + 2));
        list[name] = value;
    }
}

void settings::sync()
{
    std::ofstream out(filename);
    for (auto it = list.begin(); it != list.end(); it++){
        std::string val = it->second;
        out << it->first << "=\"" << val << "\"" << std::endl;
    }
    out.close();
}

const settings::param settings::operator[](const std::string &name) const
{
    bool empty = false;
    std::string result = "";
    try {
        result = list.at(name);
    }
    catch (std::out_of_range) {
        empty = true;
    }
    return param(name, result, this, empty);
}

settings::param settings::operator[](const std::string &name)
{
    bool empty = false;
    std::string result = "";
    try {
        result = list.at(name);
    }
    catch (std::out_of_range) {
        empty = true;
    }
    return param(name, result, this, empty);
}

void settings::sync(std::string & name, std::string & value)
{
    list[name] = value;
    sync();
}
