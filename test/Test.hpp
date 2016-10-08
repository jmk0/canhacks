#ifndef CANHACKS_TEST_HPP
#define CANHACKS_TEST_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

#define TEST_TOLERANCE .001

#define TEST_ASSERT(COND)                                               \
   if (COND)                                                            \
   {                                                                    \
      std::cerr << std::left << std::setw(75) << #COND << "PASS"        \
                << std::endl;                                           \
   }                                                                    \
   else                                                                 \
   {                                                                    \
      std::cerr << std::left << std::setw(75) << #COND << "FAIL"        \
                << std::endl;                                           \
      failCount++;                                                      \
   }

#define TEST_ASSERT_EQ(A,B)                                             \
   {                                                                    \
      std::ostringstream cond;                                          \
      cond << #A << " == " << A << " == " << B;                         \
      if (A == B)                                                       \
      {                                                                 \
         std::cerr << std::left << std::setw(75) << cond.str()          \
                   << "PASS" << std::endl;                              \
      }                                                                 \
      else                                                              \
      {                                                                 \
         std::cerr << std::left << std::setw(75) << cond.str()          \
                   << "FAIL" << std::endl;                              \
         failCount++;                                                   \
      }                                                                 \
   }

#define TEST_ASSERT_FEQ(A,B)                                            \
   {                                                                    \
      std::ostringstream cond;                                          \
      cond << #A << " == " << A << " == " << B;                         \
      if ((A == 0) && (fabs(A-B) < TEST_TOLERANCE))                     \
      {                                                                 \
         std::cerr << std::left << std::setw(75) << cond.str()          \
                   << "PASS" << std::endl;                              \
      }                                                                 \
      else if ((fabs(A-B)/fabs(A)) < TEST_TOLERANCE)                    \
      {                                                                 \
         std::cerr << std::left << std::setw(75) << cond.str()          \
                   << "PASS" << std::endl;                              \
      }                                                                 \
      else                                                              \
      {                                                                 \
         std::cerr << std::left << std::setw(75) << cond.str()          \
                   << "FAIL" << std::endl;                              \
         failCount++;                                                   \
      }                                                                 \
   }

#endif // CANHACKS_TEST_HPP
