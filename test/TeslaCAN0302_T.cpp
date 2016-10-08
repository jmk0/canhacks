#include <iostream>
#include "TeslaCAN0302.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x302;
   msg.header.length = 3;
   msg.data[0] = 0x82;
   msg.data[1] = 0xdf;
   msg.data[2] = 0x0d;

   canhacks::TeslaCAN0302 eng;
   eng.decode(msg);
   TEST_ASSERT_FEQ(eng.socMin, 89.8);
   TEST_ASSERT_FEQ(eng.socUI, 88.7);
   return failCount;
}


int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
