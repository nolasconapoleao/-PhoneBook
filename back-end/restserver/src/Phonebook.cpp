//
// Created by nolasco on 12/09/20.
//

#include "Phonebook.h"

#include <ngrest/common/HttpException.h>

namespace phonebook {
    bool idExists(const std::string& id) {

        return list.contacts.count(id) > 0;

    }

    std::list<Contact> readAll() {
        std::list<Contact> result;

        for(const auto &[key, value] : list.contacts) {

            result.emplace_back(Contact{key, value});
        }

        return result;
    }

    Contact read(const std::string& id) {
        NGREST_ASSERT_HTTP(idExists(id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");


        const auto &it = list.contacts.find(id);

        Contact result {it->first, it->second};
        return result;
    }


    void create(const Contact &contact) {
        NGREST_ASSERT_HTTP(!idExists(contact.name), ngrest::HTTP_STATUS_409_CONFLICT, "Contact name already used");

        list.contacts.emplace(contact.name, contact.number);
    }

    void remove(const std::string& id) {
        NGREST_ASSERT_HTTP(idExists(id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

        list.contacts.erase(id);
    }

    void update(const std::string& id, const Contact &contact) {

        NGREST_ASSERT_HTTP(idExists(id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

        remove(id);
        create(contact);

    }

    void clearAll() {
      list.clear();
    }

    void populateDb() {
      list.contacts.emplace("nolasco", "123" );
      list.contacts.emplace("jackie", "342");
      list.contacts.emplace("pedro", "124" );
      list.contacts.emplace("jackie", "125" );

    }
};
