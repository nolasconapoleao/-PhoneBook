//
// Created by nolasco on 13/09/20.
//

#pragma once

#include <map>
#include <string>

using ContactId = std::pair<std::string, std::string>;

class ContactList {
public:
  ContactList();
  ~ContactList();
  void clear();

  std::map<ContactId, std::string> contactDb;

private:
  void restore();
  void persist();
};
