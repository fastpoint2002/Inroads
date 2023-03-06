#pragma once

/*
  Inroads
*/

// This module contains a helper function to standardize error message
// generation in template classes.

#include <string>

namespace cs35 {
    template <typename T>
    std::string to_string(T t) {
        return std::to_string(t);
    }

    std::string to_string(std::string s);
}
