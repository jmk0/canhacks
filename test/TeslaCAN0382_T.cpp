#include <iostream>
#include "TeslaCAN0382.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x382;
   msg.header.length = 8;
   msg.data[0] = 0xfc;
   msg.data[1] = 0x9a;
   msg.data[2] = 0xea;
   msg.data[3] = 0x69;
   msg.data[4] = 0xa9;
   msg.data[5] = 0x00;
   msg.data[6] = 0xa0;
   msg.data[7] = 0x00;

   canhacks::TeslaCAN0382 eng;
   eng.decode(msg);
   TEST_ASSERT_FEQ(eng.nomFullPackPower, 76.4);
   TEST_ASSERT_FEQ(eng.nomPowerRem, 67.8);
   TEST_ASSERT_FEQ(eng.expPowerRem, 67);
   TEST_ASSERT_FEQ(eng.idealPowerRem, 67.7);
   TEST_ASSERT_FEQ(eng.powerBuffer, 4);
   TEST_ASSERT_FEQ(eng.powerToFullCharge, 0);
   return failCount;
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
