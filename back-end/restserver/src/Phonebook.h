//
// Created by nolasco on 12/09/20.
//

#pragma once

#include <map>
#include <list>

#include "Contact.h"
#include "ContactList.h"
#include "AuthManager.h"

namespace phonebook {
    std::list<Contact> readAll();
    Contact read(const std::string& id);
    void create(const Contact &contact);
    void remove(const std::string& id);
    void update(const std::string& id, const Contact &contact);
    std::string signIn(const AuthBundle& bundle);
    void signUp(const AuthBundle& bundle);

    void clearAll();
    void populateDb();
    bool idExists(const std::string& id);

    static ContactList list = ContactList{};
    static AuthManager authManager = AuthManager{};
};
