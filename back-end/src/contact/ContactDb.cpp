//
// Created by nolasco on 13/09/20.
//

#include "ContactDb.h"

#include <fstream>
#include <sstream>

constexpr const char* const filename{".ngrest/local/contacts/contacts.txt"};

ContactDb::ContactDb() {
    contacts = std::map<std::pair<std::string, std::string>, std::string>{};
  restore();
}

ContactDb::~ContactDb() {
  persist();
}

void ContactDb::clear() {
  contacts.clear();
}

void ContactDb::restore() {
  std::string line;
  std::string temp[3];

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      std::istringstream lineStream{line};
      int i = 0;
      while (std::getline(lineStream, temp[i], ',')) {
        ++i;
      };
      contacts.emplace(ContactId{temp[0], temp[1]}, temp[2]);
    }
    myfile.close();
  }
}

void ContactDb::persist() {
  std::ofstream myfile;
  myfile.open(filename);
  for (const auto& [id, name] : contacts) {
    myfile << id.first << "," << id.second << "," << name << "\n";
  }
  myfile.close();
}
