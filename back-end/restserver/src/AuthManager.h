//
// Created by nolasco on 18/09/20.
//

#pragma once

#include <map>

#include "AuthBundle.h"
#include "AuthToken.h"

using username = std::string;
using password = std::string;
using token = std::string;

class AuthManager {
public:
  AuthManager();
  ~AuthManager();
  bool authenticate(const AuthToken& token);
  bool signIn(const AuthBundle& bundle, std::string& uuid);
  bool signUp(const AuthBundle& bundle);
  std::string generateToken();
  void clear();

private:
  std::string decode(const std::string& rawData, const std::string& key);
  void restore();
  void persist();
  std::map<username, password> authDb;
  std::map<username, token> tokenDb;
};
