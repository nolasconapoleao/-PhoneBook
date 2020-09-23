//
// Created by nolasco on 18/09/20.
//

#include "AccountManager.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

bool AccountManager::authenticate(const AuthToken& token) {
  return (accountDb.tokens.count(token.username) && accountDb.tokens.find(token.username)->second == token.token);
}

bool AccountManager::signIn(const AuthBundle& bundle, std::string& uuid) {
  const auto& user = cypher::decode(bundle.username, bundle.key);
  const auto& pass = cypher::decode(bundle.password, bundle.key);

  if (accountDb.accounts.count(user) && accountDb.accounts.find(user)->second == pass) {
    uuid = generateToken();
    accountDb.tokens.insert_or_assign(user, uuid);
    return true;
  } else {
    return false;
  }
}

bool AccountManager::signUp(const AuthBundle& bundle) {
  const auto& user = cypher::decode(bundle.username, bundle.key);
  const auto& pass = cypher::decode(bundle.password, bundle.key);
  return accountDb.accounts.emplace(user, pass).second;
}

void AccountManager::clear() {
  accountDb.accounts.clear();
  accountDb.tokens.clear();
}

std::string AccountManager::generateToken() {
  boost::uuids::random_generator gen;
  boost::uuids::uuid id = gen();
  return boost::uuids::to_string(id);
}
