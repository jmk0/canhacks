#include <iostream>
#include "TeslaCAN0102.hpp"
#include "Test.hpp"

using namespace std;

/* Yes, I know that doing a direct comparison of floating point values
 * is a bad idea.  I'll address that issue later. */

unsigned decodeTestDualMotor()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x102;
   msg.header.length = 8;
   msg.data[0] = 0x66;
   msg.data[1] = 0x97;
   msg.data[2] = 0xf8;
   msg.data[3] = 0xa6;
   msg.data[4] = 0xf2;
   msg.data[5] = 0x4d;
   msg.data[6] = 0x28;
   msg.data[7] = 0x01;

   canhacks::TeslaCAN0102 eng(canhacks::mcDualMotor);
   eng.decode(msg);
   TEST_ASSERT(eng.batteryPackVoltage == 387.58);
}

unsigned decodeTestSingleMotor()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x102;
   msg.header.length = 6;
   msg.data[0] = 0x5c;
   msg.data[1] = 0x99;
   msg.data[2] = 0x9f;
   msg.data[3] = 0x83;
   msg.data[4] = 0x3c;
   msg.data[5] = 0x07;

   canhacks::TeslaCAN0102 eng(canhacks::mcSingleMotor);
   eng.decode(msg);
   TEST_ASSERT(eng.batteryPackCurrent == 92.7);
}

int main()
{
   int failCount = 0;

   failCount += decodeTestDualMotor();
   failCount += decodeTestSingleMotor();

   return failCount;
}
