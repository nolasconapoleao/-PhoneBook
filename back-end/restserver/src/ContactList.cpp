//
// Created by nolasco on 13/09/20.
//

#include <sstream>
#include <fstream>
#include "ContactList.h"

constexpr const char *const filename {".ngrest/local/build/example.txt"};

ContactList::ContactList() {
  contacts = std::map<std::string, std::string>{};
  restore();
}

ContactList::~ContactList() {
  persist();
}

void ContactList::restore() {
      std::string line;
      std::string temp[2];

      std::ifstream myfile (filename);
      if (myfile.is_open())
      {
        while ( getline (myfile,line) )
        {
          std::istringstream lineStream {line};
          int i=0;
          while(std::getline(lineStream, temp[i], ','))
          {
            ++i;
          };
          contacts.emplace(temp[0], temp[1]);
        }
        myfile.close();
      }
    }

void ContactList::persist() {
  std::ofstream myfile;
  myfile.open(filename);
  for(const auto & [id, name]: contacts) {
    myfile << id << "," << name << "\n";
  }
  myfile.close();
}
