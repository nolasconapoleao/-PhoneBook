//
// Created by nolasco on 13/09/20.
//

#pragma once

#include <map>
#include <string>

using ContactId = std::pair<std::string, std::string>;

class ContactDb {
public:
  ContactDb();
  ~ContactDb();
  void clear();
  std::map<ContactId, std::string> contacts;

private:
  void restore();
  void persist();
};
