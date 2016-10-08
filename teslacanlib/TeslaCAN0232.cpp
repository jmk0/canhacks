#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN0232.hpp"

namespace canhacks
{
   TeslaCAN0232 ::
   TeslaCAN0232()
   : maxDischargePower(0),
      maxRegenPower(0)
   {
   }


   void TeslaCAN0232 ::
   decode(tCAN& msg)
   {
      maxDischargePower = canhacks::fixedDecode<uint16_t>(&msg.data[2], .01, 0,
                                                          0);
      maxRegenPower = canhacks::fixedDecode<uint16_t>(&msg.data[0], .01, 0, 0);
   }


   std::string TeslaCAN0232 ::
   dump()
   {
      std::ostringstream s;
      s << std::fixed << std::setprecision(2)
        << "Max discharge power: " << maxDischargePower << " kW" << std::endl
        << "Max regen power: " << maxRegenPower << " kW" << std::endl;
      return s.str();
   }
}
