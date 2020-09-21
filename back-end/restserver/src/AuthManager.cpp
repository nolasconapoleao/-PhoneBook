//
// Created by nolasco on 18/09/20.
//

#include "AuthManager.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <sstream>
#include <fstream>

constexpr const char *const filename {".ngrest/local/build/passwordDb.txt"};

constexpr const char *const cKey {"5420caeeaa744525b4b3e031c107d0b7"};
constexpr const auto cKeyLen {32};

AuthManager::AuthManager() {
  restore();
}

AuthManager::~AuthManager() {
  persist();
}

bool AuthManager::authenticate(const AuthBundle &bundle) {
  const auto &user = decode(bundle.username, bundle.key);
  const auto &pass = decode(bundle.password, bundle.key);
  return authDb.find(user)->second == pass;
}

bool AuthManager::signUp(const AuthBundle &bundle) {
  const auto &user = decode(bundle.username, bundle.key);
  const auto &pass = decode(bundle.password, bundle.key);
  if(authDb.count(user) > 0) {
    return false;
  }
  authDb.emplace(user, pass);
  return true;
}

std::string AuthManager::getUsername(const AuthBundle &bundle) {
  return decode(bundle.username, bundle.key);
}

std::string AuthManager::generateToken() {
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

void AuthManager::restore() {
  std::string line;
  std::string temp[2];

  std::ifstream myfile (filename);
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::istringstream lineStream {line};
      int i=0;
      while(std::getline(lineStream, temp[i], ','))
      {
        ++i;
      };
      authDb.emplace(temp[0], temp[1]);
    }
    myfile.close();
  }
}

void AuthManager::persist() {
  std::ofstream myfile;
  myfile.open(filename);
  for(const auto & [username, password]: authDb) {
    myfile << username << "," << password << "\n";
  }
  myfile.close();
}
