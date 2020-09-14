//
// Created by nolasco on 06/09/20.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <Contact.h>
#include <Phonebook.h>

namespace constants {
    const Contact first {"nolasco", "123" };
    const Contact first_updated = {"nolasco", "342"} ;
    const Contact second {"pedro", "124" };
    const Contact third {"jackie", "125" };

    const std::string updateName = "Vinnie";
}; // namespace constants

SCENARIO("Create contact in include", "[Phonebook]") {
    phonebook::clearAll();

    GIVEN("A phonebook") {
        REQUIRE_THROWS(phonebook::read(constants::updateName));

        WHEN("a contact is added") {
            REQUIRE_NOTHROW(phonebook::create(constants::first));

            THEN("the entry exists") {
                const auto it = phonebook::read(constants::first.name);
                REQUIRE(it.name == constants::first.name);
                REQUIRE(it.number == constants::first.number);
            }
        }

        AND_WHEN("another contact with the same id is added") {
            phonebook::create(constants::first);
            REQUIRE_THROWS(phonebook::create(constants::first_updated));

            THEN("the entry is not changed") {
                const auto it = phonebook::read(constants::first.name);
                REQUIRE(it.name == constants::first.name);
                REQUIRE(it.number == constants::first.number);
            }
        }
    }
}

SCENARIO("Read contact by Id", "[Phonebook]") {
  phonebook::clearAll();

    GIVEN("A phonebook") {
        REQUIRE_THROWS(phonebook::read(constants::updateName));

        WHEN("a contact is added") {
            REQUIRE_NOTHROW(phonebook::create(constants::first));

            THEN("the entry exists") {
                const auto it = phonebook::read(constants::first.name);
                REQUIRE(it.name == constants::first.name);
                REQUIRE(it.number == constants::first.number);
            }
        }
    }
}

SCENARIO("Delete contact", "[Phonebook]") {
  phonebook::clearAll();

    GIVEN("A phonebook with an entry") {
        phonebook::create(constants::first);

        WHEN("the contact is removed") {
            REQUIRE_NOTHROW(phonebook::remove(constants::first.name));

            THEN("the entry no longer exists") {
                REQUIRE_THROWS(phonebook::read(constants::first.name));
            }
        }
    }
}

SCENARIO("Update contact", "[Phonebook]") {
  phonebook::clearAll();

    GIVEN("A phonebook with an entry") {
        phonebook::create(constants::first);

        WHEN("the contact is updated") {
            REQUIRE_NOTHROW(phonebook::update(constants::first.name, constants::second));

            THEN("the entry value changed") {
                REQUIRE_THROWS(phonebook::read(constants::first.name));

                const auto it = phonebook::read(constants::second.name);
                REQUIRE(it.name == constants::second.name);
                REQUIRE(it.number == constants::second.number);
            }
        }
    }
}
