#include <iostream>
#include "TeslaCAN0210.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x210;
   msg.header.length = 7;
   msg.data[0] = 0x00;
   msg.data[1] = 0x00;
   msg.data[2] = 0xd6;
   msg.data[3] = 0x1b;
   msg.data[4] = 0x1e;
   msg.data[5] = 0x8a;
   msg.data[6] = 0x00;

   canhacks::TeslaCAN0210 eng;
   eng.decode(msg);
   TEST_ASSERT_EQ(eng.inputPower, 432);
   TEST_ASSERT_EQ(eng.outputCurrent, 30);
   TEST_ASSERT_FEQ(eng.outputVoltage, 13.8);
   TEST_ASSERT_FEQ(eng.inletTemp, 19);
   return failCount;
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
