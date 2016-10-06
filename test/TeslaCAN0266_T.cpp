#include <iostream>
#include "TeslaCAN0266.hpp"
#include "Test.hpp"

using namespace std;

/* Yes, I know that doing a direct comparison of floating point values
 * is a bad idea.  I'll address that issue later. */

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x266;
   msg.header.length = 8;
   msg.data[0] = 0x85;
   msg.data[1] = 0xb1;
   msg.data[2] = 0x9f;
   msg.data[3] = 0x01;
   msg.data[4] = 0x3e;
   msg.data[5] = 0xeb;
   msg.data[6] = 0x8a;
   msg.data[7] = 0x44;

   canhacks::TeslaCAN0266 eng;
   eng.decode(msg);
   TEST_ASSERT(eng.inverter12V == 13.3);
   TEST_ASSERT(eng.dissipation == 22125);
   TEST_ASSERT(eng.mechPower == 207.5);
   TEST_ASSERT(eng.statorCurrent == 830);
   TEST_ASSERT(eng.regenPowerMax == 72);
   TEST_ASSERT(eng.drivePowerMax == 349);
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
