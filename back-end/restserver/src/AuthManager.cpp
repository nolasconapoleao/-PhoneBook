//
// Created by nolasco on 18/09/20.
//

#include "AuthManager.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

constexpr const char *const filename {".ngrest/local/build/passwordDb.txt"};

constexpr const char *const cKey {"5420caeeaa744525b4b3e031c107d0b7"};
constexpr const auto cKeyLen {32};

bool AuthManager::authenticate(const AuthBundle &bundle) {
  const auto &user = decode(bundle.username, bundle.key);
  const auto &pass = decode(bundle.password, bundle.key);
  return authDb.find(user)->second == pass;
}

void AuthManager::signUp(const AuthBundle &bundle) {
  const auto &user = decode(bundle.username, bundle.key);
  const auto &pass = decode(bundle.password, bundle.key);
  authDb.emplace(user, pass);
}

std::string AuthManager::getUsername(const AuthBundle &bundle) {
  return decode(bundle.username, bundle.key);
}

std::string AuthManager::generateToken(const AuthBundle &bundle) {
  boost::uuids::random_generator gen;
  boost::uuids::uuid id = gen();
  return boost::uuids::to_string(id);
}

std::string AuthManager::decode(const std::string &rawData, const std::string &key) {
  // TODO: Add more sofisticated encryption system
  std::string result = "";
  auto k = 0;

  for(const auto ch : rawData) {
    result  += ch + cKey[k % cKeyLen-1];
    k++;
  }
  return result;
}
