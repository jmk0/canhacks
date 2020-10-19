#include <math.h>
#include <sstream>
#include <iomanip>
#include <limits>
#include "TeslaCAN0266.hpp"

namespace canhacks
{
   TeslaCAN0266 ::
   TeslaCAN0266()
   : inverter12V(0),
      dissipation(0),
      mechPower(0),
      statorCurrent(0),
      regenPowerMax(0),
      drivePowerMax(0)
   {
   }


   void TeslaCAN0266 ::
   decode(tCAN& msg)
   {
      inverter12V = msg.data[0] / 10.0;
      dissipation = msg.data[1] * 125;
      mechPower = canhacks::fixedDecode<int16_t>(&msg.data[2], 0.5, 5, 0);
      statorCurrent = canhacks::fixedDecode<uint16_t>(&msg.data[4], 1, 5, 0);
         // it's a bit different...
      drivePowerMax = (((msg.data[5] & 0xf0) >> 3) +
                       ((msg.data[6] & 0x3f) << 5) + 1);
      regenPowerMax = (msg.data[7]*4)-200;
   }


   std::string TeslaCAN0266 ::
   dump(bool verbose)
   {
      std::ostringstream s;
      s << std::setprecision(1) << std::fixed
        << "12V inverter voltage: " << inverter12V << " V" << std::endl
        << "Dissipation: " << dissipation << " W" << std::endl
        << "mechPower: " << mechPower << " W" << std::endl
        << "Stator current: " << statorCurrent << " A" << std::endl
        << "Drive power max: " << drivePowerMax << " kW" << std::endl
        << "Regen power max: " << regenPowerMax << " kW" << std::endl;
      return s.str();
   }
}
