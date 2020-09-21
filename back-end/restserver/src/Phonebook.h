//
// Created by nolasco on 12/09/20.
//

#pragma once

#include <list>
#include <map>

#include "AuthManager.h"
#include "Contact.h"
#include "ContactList.h"

namespace phonebook {
std::list<Contact> readAll(const AuthToken& token);
Contact read(const AuthToken& token, const std::string& id);
void create(const AuthToken& token, const Contact& contact);
void remove(const AuthToken& token, const std::string& id);
void update(const AuthToken& token, const std::string& id, const Contact& contact);
std::string signIn(const AuthBundle& bundle);
void signUp(const AuthBundle& bundle);

void clearAll();
void populateDb();
bool idExists(const std::string& username, const std::string& id);

static ContactList list = ContactList{};
static AuthManager authManager = AuthManager{};
}; // namespace phonebook
