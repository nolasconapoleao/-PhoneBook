//
// Created by nolasco on 12/09/20.
//

#pragma once

#include <map>
#include <list>

#include "Contact.h"
#include "ContactList.h"

namespace phonebook {
    std::list<Contact> readAll();
    Contact read(const std::string& id);
    void create(const Contact &contact);
    void remove(const std::string& id);
    void update(const std::string& id, const Contact &contact);

    bool idExists(const std::string& id);
    static ContactList list = ContactList{};
};
