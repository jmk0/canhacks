#include <iostream>
#include "TeslaCAN0154.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x154;
   msg.header.length = 8;
   msg.data[0] = 0x30;
   msg.data[1] = 0x63;
   msg.data[2] = 0xfa;
   msg.data[3] = 0xfa;
   msg.data[4] = 0x48;
   msg.data[5] = 0xcc;
   msg.data[6] = 0x09;
   msg.data[7] = 0xf9;

   canhacks::TeslaCAN0154 eng;
   eng.decode(msg);
   TEST_ASSERT_FEQ(eng.torque, 627);
   TEST_ASSERT_FEQ(eng.pedalA, 100);
   TEST_ASSERT_FEQ(eng.pedalB, 100);
   return failCount;
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
