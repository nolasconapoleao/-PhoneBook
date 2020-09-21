//
// Created by nolasco on 12/09/20.
//

#include "Phonebook.h"

#include <ngrest/common/HttpException.h>

namespace phonebook {
    bool idExists(const std::string& id) {
        return list.contactDb.count(id) > 0;
    }

    std::list<Contact> readAll() {
        std::list<Contact> result;
        for(const auto &[key, value] : list.contactDb) {
            result.emplace_back(Contact{key, value});
        }

        return result;
    }

    Contact read(const std::string& id) {
        NGREST_ASSERT_HTTP(idExists(id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

        const auto &it = list.contactDb.find(id);
        Contact result {it->first, it->second};
        return result;
    }

    void create(const Contact &contact) {
        NGREST_ASSERT_HTTP(!idExists(contact.name), ngrest::HTTP_STATUS_409_CONFLICT, "Contact name already used");

        list.contactDb.emplace(contact.name, contact.number);
    }

    void remove(const std::string& id) {
        NGREST_ASSERT_HTTP(idExists(id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

        list.contactDb.erase(id);
    }

    void update(const std::string& id, const Contact &contact) {
        NGREST_ASSERT_HTTP(idExists(id), ngrest::HTTP_STATUS_404_NOT_FOUND, "Contact id does not exist");

        remove(id);
        create(contact);
    }

    std::string signIn(const AuthBundle& bundle) {
      if(authManager.authenticate(bundle)) {
        return authManager.generateToken();
      } else {
        return "Invalid credentials!";
      }
    }

    void signUp(const AuthBundle& bundle) {
      NGREST_ASSERT_HTTP(authManager.signUp(bundle), ngrest::HTTP_STATUS_404_NOT_FOUND, "Could not sign up!");
    }

    void clearAll() {
      list.clear();
    }

    void populateDb() {
      list.contactDb.emplace("nolasco", "123" );
      list.contactDb.emplace("jackie", "342");
      list.contactDb.emplace("pedro", "124" );
      list.contactDb.emplace("jackie", "125" );
    }
};
