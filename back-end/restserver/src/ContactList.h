//
// Created by nolasco on 13/09/20.
//

#pragma once

#include <string>
#include <map>

class ContactList {
public:
    ContactList();
    ~ContactList();
    void clear();

    std::map<std::string, std::string> contactDb;

private:
    void restore();
    void persist();
};
