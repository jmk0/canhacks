#include <iostream>
#include "TeslaCAN03d2.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x3d2;
   msg.header.length = 8;
   msg.data[0] = 0x25;
   msg.data[1] = 0xae;
   msg.data[2] = 0x86;
   msg.data[3] = 0x00;
   msg.data[4] = 0x07;
   msg.data[5] = 0xdc;
   msg.data[6] = 0x8f;
   msg.data[7] = 0x00;

   canhacks::TeslaCAN03d2 eng;
   eng.decode(msg);
   TEST_ASSERT_FEQ(eng.chargeTotal, 9427.975);
   TEST_ASSERT_FEQ(eng.dischargeTotal, 8826.405);
   return failCount;
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
