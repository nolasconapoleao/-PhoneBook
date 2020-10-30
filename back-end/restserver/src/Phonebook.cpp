//
// Created by nolasco on 12/09/20.
//

#include "Phonebook.h"

#include <ngrest/common/HttpException.h>

namespace phonebook {
std::list<Contact> readAll(const AuthToken& token) {
  std::list<Contact> result;
  NGREST_ASSERT_HTTP(authManager.authenticate(token), ngrest::HTTP_STATUS_404_NOT_FOUND, "Invalid credentials!");
  for (const auto& [key, value] : list.contactDb) {
    if (key.first == token.username) {
      result.emplace_back(Contact{key.second, value});
    }
  }

  return result;
}

Contact read(const AuthToken& token, const std::string& id) {
  NGREST_ASSERT_HTTP(authManager.authenticate(token), ngrest::HTTP_STATUS_404_NOT_FOUND, "Invalid credentials!");
  NGREST_ASSERT_HTTP(idExists(token.username, id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

  const auto& it = list.contactDb.find(ContactId{token.username, id});
  Contact result{it->first.second, it->second};
  return result;
}

void create(const AuthToken& token, const Contact& contact) {
  NGREST_ASSERT_HTTP(authManager.authenticate(token), ngrest::HTTP_STATUS_404_NOT_FOUND, "Invalid credentials!");
  NGREST_ASSERT_HTTP(!idExists(token.username, contact.name), ngrest::HTTP_STATUS_409_CONFLICT,
                     "Contact name already used");

  list.contactDb.emplace(ContactId{token.username, contact.name}, contact.number);
}

void remove(const AuthToken& token, const std::string& id) {
  NGREST_ASSERT_HTTP(authManager.authenticate(token), ngrest::HTTP_STATUS_404_NOT_FOUND, "Invalid credentials!");
  NGREST_ASSERT_HTTP(idExists(token.username, id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

  list.contactDb.erase(ContactId{token.username, id});
}

void update(const AuthToken& token, const std::string& id, const Contact& contact) {
  NGREST_ASSERT_HTTP(authManager.authenticate(token), ngrest::HTTP_STATUS_404_NOT_FOUND, "Invalid credentials!");
  NGREST_ASSERT_HTTP(idExists(token.username, id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

  remove(token, id);
  create(token, contact);
}

std::string signIn(const AuthBundle& bundle) {
  std::string uuid;
  NGREST_ASSERT_HTTP(authManager.signIn(bundle, uuid), ngrest::HTTP_STATUS_404_NOT_FOUND, "Invalid credentials!");
  return uuid;
}

void signUp(const AuthBundle& bundle) {
  NGREST_ASSERT_HTTP(authManager.signUp(bundle), ngrest::HTTP_STATUS_404_NOT_FOUND, "Could not sign up!");
}

void clearAll() {
  list.clear();
  authManager.clear();
}

void populateDb() {
  list.contactDb.emplace(ContactId{"nolasco", "nolasco"}, "123");
  list.contactDb.emplace(ContactId{"nolasco", "jackie"}, "342");
  list.contactDb.emplace(ContactId{"nolasco", "pedro"}, "124");
  list.contactDb.emplace(ContactId{"nolasco", "jackie"}, "125");
}

bool idExists(const std::string& username, const std::string& id) {
  return list.contactDb.count(ContactId{username, id}) != 0;
}
}; // namespace phonebook
