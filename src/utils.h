#ifndef NES_EMULATOR_UTILS_H_
#define NES_EMULATOR_UTILS_H_

#include <iostream>

#define NES_ASSERT(condition, message) \
  do { \
    if (!(condition)) { \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                << " line " << __LINE__ << ": " << (message) << std::endl; \
      std::terminate(); \
    } \
  } while (false)

#endif  // NES_EMULATOR_UTILS_H_
