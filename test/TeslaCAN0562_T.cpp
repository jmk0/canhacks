#include <iostream>
#include "TeslaCAN0562.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x562;
   msg.header.length = 8;
   msg.data[0] = 0x3c;
   msg.data[1] = 0x27;
   msg.data[2] = 0x2c;
   msg.data[3] = 0x01;

   canhacks::TeslaCAN0562 eng;
   eng.decode(msg);
   TEST_ASSERT_FEQ(eng.batteryOdo, 19670.844);
   return failCount;
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
