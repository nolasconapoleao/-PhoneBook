//
// Created by nolasco on 18/09/20.
//

#pragma once

#include "AuthBundle.h"

#include <map>

using username = std::string;
using password = std::string;
using token = std::string;

class AuthManager {
public:
    AuthManager();
    ~AuthManager();
    bool authenticate(const AuthBundle& bundle);
    bool signUp(const AuthBundle& bundle);
    std::string getUsername(const AuthBundle& bundle);
    std::string generateToken();

private:
    std::string decode(const std::string& rawData, const std::string& key);
    void restore();
    void persist();
    std::map<username, password> authDb;
    std::map<username, token> tokenDb;
};
