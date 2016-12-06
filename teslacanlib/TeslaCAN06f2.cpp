#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN06f2.hpp"

#include <iostream>

namespace canhacks
{
   TeslaCAN06f2 ::
   TeslaCAN06f2()
   : index(0),
      d1(0),
      d2(0),
      d3(0),
      d4(0)
   {
   }


   void TeslaCAN06f2 ::
   decode(tCAN& msg)
   {
      index = msg.data[0];
         // bits -> data
         // 1        2        3        4        5        6        7
         // 11111111 11111122 22222222 22223333 33333333 33444444 44444444
         // scale for voltage is .000305
         // scale for temp is .0122
         // How do i know when it's temp and when it's volts?
         // Looking at data from my S-60, data looks like volts with
         // index from 0-20, temps from 24-30.  Not sure what 21-23
         // might contain or if there's anything beyond 30 in other
         // configurations.

      double scale = .000305;
      if (index >= 24)
      {
         scale = .0122;
         volts = false;
      }
      else
      {
         volts = true;
      }

      d1 = scale * (msg.data[1] | ( (msg.data[2] & 0x3F) << 8));
      d2 = scale * ( (msg.data[2] >> 6) |
                     ( (msg.data[3] << 2) |
                       ((msg.data[4] & 0xF) << 10) ) );
      d3 = scale * ( (msg.data[4] >> 4) |
                     ( (msg.data[5] << 4) |
                       ( (msg.data[6] & 0x03) << 12)));
      d4 = scale * ((msg.data[6] >> 2) | (msg.data[7] << 6));
   }


   std::string TeslaCAN06f2 ::
   dump()
   {
      std::ostringstream s;
      s << std::fixed << std::setprecision(6)
        << "Index: " << (unsigned)index << std::endl
        << std::hex
        << "d1: " << d1 << (volts ? " V" : " C") << std::endl
        << "d2: " << d2 << (volts ? " V" : " C") << std::endl
        << "d3: " << d3 << (volts ? " V" : " C") << std::endl
        << "d4: " << d4 << (volts ? " V" : " C") << std::endl;
      return s.str();
   }
}
