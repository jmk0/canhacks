#include <iostream>
#include "TeslaCAN0256.hpp"
#include "Test.hpp"

using namespace std;

unsigned decodeTest()
{
   unsigned failCount = 0;
   canhacks::tCAN msg;
   msg.id = 0x256;
   msg.header.length = 8;
   msg.data[0] = 0x84;
   msg.data[1] = 0x19;
   msg.data[2] = 0x40;
   msg.data[3] = 0x31;
   msg.data[4] = 0x00;
   msg.data[5] = 0xf2;
   msg.data[6] = 0x20;
   msg.data[7] = 0x78;

   canhacks::TeslaCAN0256 eng;
   eng.decode(msg);
      // need some stuff here...
   return failCount;
}

int main()
{
   int failCount = 0;

   failCount += decodeTest();

   return failCount;
}
