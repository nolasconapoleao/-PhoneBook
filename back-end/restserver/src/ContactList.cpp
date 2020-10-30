//
// Created by nolasco on 13/09/20.
//

#include "ContactList.h"

#include <fstream>
#include <sstream>

constexpr const char* const filename{".ngrest/local/build/contactDb.txt"};

ContactList::ContactList() {
  contactDb = std::map<std::pair<std::string, std::string>, std::string>{};
  restore();
}

ContactList::~ContactList() {
  persist();
}

void ContactList::clear() {
  contactDb.clear();
}

void ContactList::restore() {
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
      contactDb.emplace(ContactId{temp[0], temp[1]}, temp[2]);
    }
    myfile.close();
  }
}

void ContactList::persist() {
  std::ofstream myfile;
  myfile.open(filename);
  for (const auto& [id, name] : contactDb) {
    myfile << id.first << "," << id.second << "," << name << "\n";
  }
  myfile.close();
}
