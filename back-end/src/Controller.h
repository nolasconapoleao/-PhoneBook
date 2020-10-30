//
// Created by nolasco on 12/09/20.
//

#pragma once

#include <list>
#include <map>

#include "Contact.h"
#include "authentication/AccountManager.h"
#include "contact/ContactDb.h"

namespace phonebook {
std::list<Contact> readAll(const AuthToken& token);
Contact read(const AuthToken& token, const std::string& id);
void create(const AuthToken& token, const Contact& contact);
void remove(const AuthToken& token, const std::string& id);
void update(const AuthToken& token, const std::string& id, const Contact& contact);
std::string signIn(const AuthBundle& bundle);
void signUp(const AuthBundle& bundle);

void fullWipe();
void populateDb();
bool idExists(const std::string& username, const std::string& id);

static ContactDb contactDb = ContactDb{};
static AccountManager authManager = AccountManager{};
}; // namespace phonebook
