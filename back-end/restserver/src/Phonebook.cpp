//
// Created by nolasco on 12/09/20.
//

#include "Phonebook.h"

#include <ngrest/common/HttpException.h>

namespace phonebook {
    bool idExists(const std::string& id) {
        return contacts.count(id) > 0;
    }

    std::list<Contact> readAll() {
        std::list<Contact> result;
        for(const auto &[key, value] : contacts) {
            result.emplace_back(Contact{key, value});
        }

        return result;
    }

    Contact read(const std::string& id) {
        NGREST_ASSERT_HTTP(idExists(id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

        const auto &it = contacts.find(id);
        Contact result {it->first, it->second};
        return result;
    }

    std::string create(const Contact &contact) {
        NGREST_ASSERT_HTTP(!idExists(contact.name), ngrest::HTTP_STATUS_409_CONFLICT, "Contact name already used");

        contacts.emplace(contact.name, contact.number);
        return "Contact created successfully";
    }

    std::string remove(const std::string& id) {
        NGREST_ASSERT_HTTP(idExists(id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

        contacts.erase(id);
        return "Contact deleted successfully";
    }

    std::string update(const std::string& id, const Contact &contact) {
        NGREST_ASSERT_HTTP(idExists(id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

        remove(id);
        create(contact);
        return "Contact updated successfully";
    }
};
