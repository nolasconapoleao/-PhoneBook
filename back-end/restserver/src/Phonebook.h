//
// Created by nolasco on 12/09/20.
//

#pragma once

#include <map>
#include <list>

#include "Contact.h"

namespace phonebook {
    std::list<Contact> readAll();
    Contact read(const std::string& id);
    std::string create(const Contact &contact);
    std::string remove(const std::string& id);
    std::string update(const std::string& id, const Contact &contact);

    bool idExists(const std::string& id);
    static std::map<std::string, std::string> contacts = std::map<std::string, std::string> {};
};
