#include <iostream>
#include "TeslaCAN0116.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x116;
   msg.header.length = 6;
   msg.data[0] = 0x5a;
   msg.data[1] = 0x44;
   msg.data[2] = 0x75;
   msg.data[3] = 0x44;
   msg.data[4] = 0x8e;
   msg.data[5] = 0xfc;

   canhacks::TeslaCAN0116 eng;
   eng.decode(msg);
   TEST_ASSERT_FEQ(eng.torqueEst, 557);
   TEST_ASSERT_FEQ(eng.speed, 32.05);
   TEST_ASSERT_EQ(eng.gearRequest, canhacks::TeslaCAN0116::gDrive);
   TEST_ASSERT_EQ(eng.gear, canhacks::TeslaCAN0116::gDrive);
   return failCount;
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
