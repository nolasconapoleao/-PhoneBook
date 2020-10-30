//
// Created by nolasco on 24/09/20.
//

#pragma once

#include <string>
#include <map>

using username = std::string;
using password = std::string;
using token = std::string;

class AccountDb {
public:
    AccountDb();
    ~AccountDb();
    void clear();

    std::map<username, password> accounts;
    std::map<username, token> tokens;
private:
    void restore();
    void persist();
};
