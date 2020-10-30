//
// Created by nolasco on 18/09/20.
//

#pragma once

#include <map>

#include "AccountDb.h"
#include "include/AuthBundle.h"
#include "include/AuthToken.h"
#include "Cypher.h"

class AccountManager {
public:
  bool authenticate(const AuthToken& token);
  bool signIn(const AuthBundle& bundle, std::string& uuid);
  bool signUp(const AuthBundle& bundle);
  void clear();

private:
  std::string generateToken();
  AccountDb accountDb;
};
