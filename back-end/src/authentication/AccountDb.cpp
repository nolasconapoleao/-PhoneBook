//
// Created by nolasco on 24/09/20.
//

#include "AccountDb.h"

#include <fstream>
#include <sstream>

constexpr const char* const filename{".ngrest/local/contacts/passwordDb.txt"};

AccountDb::AccountDb() {
  restore();
}

AccountDb::~AccountDb() {
  persist();
}

void AccountDb::clear() {
  accounts.clear();
  tokens.clear();
}

void AccountDb::restore() {
  std::string line;
  std::string temp[2];

  std::ifstream myfile(filename);
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      std::istringstream lineStream{line};
      int i = 0;
      while (std::getline(lineStream, temp[i], ',')) {
        ++i;
      };
      accounts.emplace(temp[0], temp[1]);
    }
    myfile.close();
  }
}

void AccountDb::persist() {
  std::ofstream myfile;
  myfile.open(filename);
  for (const auto& [username, password] : accounts) {
    myfile << username << "," << password << "\n";
  }
  myfile.close();
}
