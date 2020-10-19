#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN0116.hpp"

namespace canhacks
{
   TeslaCAN0116 ::
   TeslaCAN0116()
   : torqueEst(0),
      speed(0),
      gearRequest(gInvalid),
      gear(gInvalid)
   {
   }


   void TeslaCAN0116 ::
   decode(tCAN& msg)
   {
      torqueEst = canhacks::fixedDecode<int16_t>(&msg.data[0], .5, 4, 0);
      speed = canhacks::fixedDecode<uint16_t>(&msg.data[2], .05, 4, -500);
      gearRequest = (Gear)((msg.data[3] & 0x70) >> 4);
      gear = (Gear)((msg.data[1] & 0x70) >> 4);
   }


   std::string TeslaCAN0116 ::
   dump(bool verbose)
   {
      std::ostringstream s;
      if (verbose)
      {
         s << std::fixed << std::setprecision(2)
           << "Torque estimate: " << torqueEst << " N*m ("
           << (torqueEst * 0.737562149277) << " ft*lb)" << std::endl
           << "Vehicle speed: " << speed << " MPH" << std::endl
           << "Gear request: " << gearRequest << std::endl
           << "Gear: " << gear << std::endl;
      }
      else
      {
         s << std::fixed << std::setprecision(2)
           << torqueEst << " " << (torqueEst * 0.737562149277) << " "
           << speed << " " << gearRequest << " " << gear;
      }
      return s.str();
   }
}


std::ostream& operator<<(std::ostream& s, canhacks::TeslaCAN0116::Gear g)
{
   switch (g)
   {
      case canhacks::TeslaCAN0116::gPark:    s << "Park";    break;
      case canhacks::TeslaCAN0116::gReverse: s << "Reverse"; break;
      case canhacks::TeslaCAN0116::gNeutral: s << "Neutral"; break;
      case canhacks::TeslaCAN0116::gDrive:   s << "Drive";   break;
      default:                               s << "Invalid"; break;
   }
   return s;
}
