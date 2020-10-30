//
// Created by nolasco on 24/09/20.
//

#pragma once

#include <string>

namespace cypher {
  std::string decode(const std::string& rawData, const std::string& key);
  std::string encode(const std::string& rawData, const std::string& key);
};
