#ifndef CANHACKS_TEST_HPP
#define CANHACKS_TEST_HPP

#include <iostream>

#define TEST_ASSERT(COND)                               \
   if (!COND)                                           \
   {                                                    \
      std::cerr << "FAIL: " << #COND << std::endl;      \
      failCount++;                                      \
   }

#endif // CANHACKS_TEST_HPP
