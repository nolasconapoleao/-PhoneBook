//
// Created by nolasco on 06/09/20.
//

#define CATCH_CONFIG_MAIN
#include <Controller.h>

#include "catch.hpp"

namespace constants {
const std::string cUsername{"nolasco"};
const std::string cPassword{"password"};
const std::string cPassword2{"password2"};
const std::string cKey{"unused_key"};
const std::string cToken{"253235-32-632-23535"};
const AuthBundle cBundle{cUsername, cPassword, cKey};
const AuthBundle cBundleWrong{cUsername, cPassword2, cKey};

const Contact first{"nolasco", "123"};
const Contact first_updated = {"nolasco", "342"};
const Contact second{"pedro", "124"};
const Contact third{"jackie", "125"};

const std::string updateName = "Vinnie";
}; // namespace constants

SCENARIO("Sign up, sign in and authentication", "[Phonebook]") {
    phonebook::fullWipe();
  REQUIRE_NOTHROW(phonebook::signUp(constants::cBundle));
  REQUIRE_THROWS(phonebook::signUp(constants::cBundle));
  REQUIRE_NOTHROW(phonebook::signIn(constants::cBundle));
  REQUIRE_THROWS(phonebook::signIn(constants::cBundleWrong));

  const auto& uuid = phonebook::signIn(constants::cBundle);
  REQUIRE_NOTHROW(phonebook::readAll(AuthToken{constants::cBundle.username, uuid}));
}

SCENARIO("Create contact in include", "[Phonebook]") {
    phonebook::fullWipe();
  phonebook::signUp(constants::cBundle);
  phonebook::signIn(constants::cBundle);
  const auto& uuid = phonebook::signIn(constants::cBundle);
  const AuthToken& cAuthToken{constants::cBundle.username, uuid};

  GIVEN("A phonebook") {
    REQUIRE_THROWS(phonebook::read(cAuthToken, constants::updateName));

    WHEN("a contact is added") {
      REQUIRE_NOTHROW(phonebook::create(cAuthToken, constants::first));

      THEN("the entry exists") {
        const auto it = phonebook::read(cAuthToken, constants::first.name);
        REQUIRE(it.name == constants::first.name);
        REQUIRE(it.number == constants::first.number);
      }
    }

    AND_WHEN("another contact with the same id is added") {
      phonebook::create(cAuthToken, constants::first);
      REQUIRE_THROWS(phonebook::create(cAuthToken, constants::first_updated));

      THEN("the entry is not changed") {
        const auto it = phonebook::read(cAuthToken, constants::first.name);
        REQUIRE(it.name == constants::first.name);
        REQUIRE(it.number == constants::first.number);
      }
    }
  }
}

SCENARIO("Read contact by Id", "[Phonebook]") {
    phonebook::fullWipe();
  phonebook::signUp(constants::cBundle);
  phonebook::signIn(constants::cBundle);
  const auto& uuid = phonebook::signIn(constants::cBundle);
  const AuthToken& cAuthToken{constants::cBundle.username, uuid};

  GIVEN("A phonebook") {
    REQUIRE_THROWS(phonebook::read(cAuthToken, constants::updateName));

    WHEN("a contact is added") {
      REQUIRE_NOTHROW(phonebook::create(cAuthToken, constants::first));

      THEN("the entry exists") {
        const auto it = phonebook::read(cAuthToken, constants::first.name);
        REQUIRE(it.name == constants::first.name);
        REQUIRE(it.number == constants::first.number);
      }
    }
  }
}

SCENARIO("Delete contact", "[Phonebook]") {
    phonebook::fullWipe();
  phonebook::signUp(constants::cBundle);
  phonebook::signIn(constants::cBundle);
  const auto& uuid = phonebook::signIn(constants::cBundle);
  const AuthToken& cAuthToken{constants::cBundle.username, uuid};

  GIVEN("A phonebook with an entry") {
    phonebook::create(cAuthToken, constants::first);

    WHEN("the contact is removed") {
      REQUIRE_NOTHROW(phonebook::remove(cAuthToken, constants::first.name));

      THEN("the entry no longer exists") {
        REQUIRE_THROWS(phonebook::read(cAuthToken, constants::first.name));
      }
    }
  }
}

SCENARIO("Update contact", "[Phonebook]") {
    phonebook::fullWipe();
  phonebook::signUp(constants::cBundle);
  phonebook::signIn(constants::cBundle);
  const auto& uuid = phonebook::signIn(constants::cBundle);
  const AuthToken& cAuthToken{constants::cBundle.username, uuid};

  GIVEN("A phonebook with an entry") {
    phonebook::create(cAuthToken, constants::first);

    WHEN("the contact is updated") {
      REQUIRE_NOTHROW(phonebook::update(cAuthToken, constants::first.name, constants::second));

      THEN("the entry value changed") {
        REQUIRE_THROWS(phonebook::read(cAuthToken, constants::first.name));

        const auto it = phonebook::read(cAuthToken, constants::second.name);
        REQUIRE(it.name == constants::second.name);
        REQUIRE(it.number == constants::second.number);
      }
    }
  }
}
