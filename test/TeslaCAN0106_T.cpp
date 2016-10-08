#include <iostream>
#include "TeslaCAN0106.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x106;
   msg.header.length = 8;
   msg.data[0] = 0x31;
   msg.data[1] = 0xff;
   msg.data[2] = 0x2d;
   msg.data[3] = 0x7f;
   msg.data[4] = 0xa3;
   msg.data[5] = 0x14;
   msg.data[6] = 0x0e;
   msg.data[7] = 0xa8;

   canhacks::TeslaCAN0106 eng;
   eng.decode(msg);
   TEST_ASSERT_EQ(eng.motorRPM, 5283);
   TEST_ASSERT_FEQ(eng.pedalPos, 5.6);
   return failCount;
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
