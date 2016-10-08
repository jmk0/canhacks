#include <iostream>
#include "TeslaCAN0232.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x232;
   msg.header.length = 4;
   msg.data[0] = 0x80;
   msg.data[1] = 0x19;
   msg.data[2] = 0x10;
   msg.data[3] = 0x89;

   canhacks::TeslaCAN0232 eng;
   eng.decode(msg);
   TEST_ASSERT_FEQ(eng.maxDischargePower, 350.88);
   TEST_ASSERT_FEQ(eng.maxRegenPower, 65.28);
   return failCount;
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
